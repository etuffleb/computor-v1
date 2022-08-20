#include "../lib/computorv1.h"

ParsableString::ParsableString(char *str) : 
    originalStr(str),
    restStr(str)
{}

ParsableString::Snapshot::Snapshot(ParsableString& ps) :
    polynomial(ps.polynomial),
    restStr(ps.restStr)
{}

void ParsableString::loadSnapshot(Snapshot s)
{
    polynomial = s.polynomial;
    restStr = s.restStr;
}

void ParsableString::addPolynomialCoef(int pow, float coef)
{
    polynomial.addCoef(pow, coef);
}

void ParsableString::parsePolynomial()
{
    if (errors.size() != 0)
        return;

	parseDiv();
	parseElements();
	parseDiv();
	parseChar('=');
	parseDiv();
	parseInvElements();
    parseDiv();
}

void ParsableString::parseElements()
{
    if (errors.size() != 0)
        return;

	parseElementOptionalSign();
	parseDiv();
	parseElementsRest();
}

void ParsableString::parseElementsRest()
{
    if (errors.size() != 0)
        return;

    ParsableString::Snapshot snapshot1 = ParsableString::Snapshot(*this);
    parseElementWithSign();
    if (errors.size() > 0)
    {
        loadSnapshot(snapshot1);
        errors.clear();
        return;
    }
    ParsableString::Snapshot snapshot2 = ParsableString::Snapshot(*this);
    parseDiv();
    parseElementsRest();
    if (errors.size() > 0)
    {
        loadSnapshot(snapshot2);
        errors.clear();
        return;
    }
    return;
}

void ParsableString::parseInvElements()
{
    if (errors.size() != 0)
        return;

    ParsableString rest = ParsableString(*this);
    rest.polynomial.clear();
	rest.parseElements();
    if (rest.errors.size() > 0)
    {
        for (auto e : rest.errors)
            errors.push_back(e);
        return;
    }
    polynomial.addPolynomial(rest.polynomial.invert());
    restStr = rest.restStr;
}

void ParsableString::parseElement(int sign)
{
    if (errors.size() != 0)
        return;

    sign = sign >= 0 ? 1 : -1;
    float coef = 1.0;
    int pow = 0;

    ParsableString::Snapshot snapshot = ParsableString::Snapshot(*this);
	parseF10(&coef);
	parseDiv();
	parseChar('*');
	parseDiv();
    parseXPow(&pow);
    if (errors.size() == 0)
    {
        if (pow >= 0)
            return addPolynomialCoef(pow, coef * sign);
        loadSnapshot(snapshot);
        errors.push_back(ParserError(*this, "X power cannot be negative"));
        return;
    }
    loadSnapshot(snapshot);
    errors.clear();

	parseXPow(&pow);
	parseDiv();
	parseChar('*');
	parseDiv();
    parseF10(&coef);
    if (errors.size() == 0)
    {
        if (pow >= 0)
            return addPolynomialCoef(pow, coef * sign);
        loadSnapshot(snapshot);
        errors.push_back(ParserError(*this, "X power cannot be negative"));
        return;
    }
    loadSnapshot(snapshot);
    errors.clear();

    parseF10(&coef);
    if (errors.size() == 0)
        return addPolynomialCoef(0, coef * sign);
    loadSnapshot(snapshot);
    errors.clear();
    
    parseXPow(&pow);
    if (errors.size() == 0)
    {
        if (pow >= 0)
            return addPolynomialCoef(pow, 1.0 * sign);
        loadSnapshot(snapshot);
        errors.push_back(ParserError(*this, "X power cannot be negative"));
        return;
    }
    loadSnapshot(snapshot);

    errors.push_back(ParserError(*this, "Expected X^n or a number here"));
}

void ParsableString::parseElementWithSign()
{
    if (errors.size() != 0)
    {
        return;
    }

    int sign = 0;
	parseSign(&sign);
    if (errors.size() > 0)
    {
        return;
    }
	parseDiv();
    parseElement(sign);
}

void ParsableString::parseElementOptionalSign()
{
    if (errors.size() != 0)
        return;

    ParsableString::Snapshot snapshot = ParsableString::Snapshot(*this);
    parseElementWithSign();
    if (errors.size() == 0)
        return;
    loadSnapshot(snapshot);
    errors.clear();

    parseElement(1);
}

void ParsableString::parseXPow(int *pow)
{
    if (errors.size() != 0)
        return;

    ParsableString::Snapshot snapshot = ParsableString::Snapshot(*this);
	parseX();
	parseDiv();
	parseChar('^');
	parseDiv();
    parseN10(pow);
    if (errors.size() == 0)
        return;
    loadSnapshot(snapshot);
    errors.clear();

    parseX();
    if (errors.size() == 0)
    {
        *pow = 1;
        return;
    }
    loadSnapshot(snapshot);

    errors.push_back(ParserError(*this, "Expected X power here"));
}

void ParsableString::parseX()
{
    if (errors.size() != 0)
        return;

    ParsableString::Snapshot snapshot = ParsableString::Snapshot(*this);
    parseChar('X');
    if (errors.size() == 0)
        return;
    loadSnapshot(snapshot);
    errors.clear();
    
    parseChar('x');
    if (errors.size() == 0)
        return;
    loadSnapshot(snapshot);
    errors.clear();

    errors.push_back(ParserError(*this, "Expected X here"));
}

void ParsableString::parseSign(int *sign)
{
    if (errors.size() != 0)
        return;

    ParsableString::Snapshot snapshot = ParsableString::Snapshot(*this);
    parseChar('-');
    if (errors.size() == 0)
    {
        *sign = -1;
        return;
    }
    loadSnapshot(snapshot);
    errors.clear();

    parseChar('+');
    if (errors.size() == 0)
    {
        *sign = 1;
        return;
    }
    loadSnapshot(snapshot);
    errors.clear();

    errors.push_back(ParserError(*this, "Expected sign here"));
}

void ParsableString::parseF10(float *num)
{
    if (errors.size() != 0)
        return;
    char* rest = restStr;
    *num = std::strtof(restStr, &restStr);
    if (rest == restStr)
        errors.push_back(ParserError(*this, "Expected float number here"));
}

void ParsableString::parseN10(int *num)
{
    if (errors.size() != 0)
        return;
    char* initial = restStr;
    *num = std::strtod(restStr, nullptr);
    while (restStr[0] && std::isdigit(restStr[0]))
        restStr++;
    if (restStr == initial)
        errors.push_back(ParserError(*this, "Expected integer number here"));
}

void ParsableString::parseDiv()
{
    if (errors.size() != 0)
        return;
    while (restStr[0] && std::isspace(restStr[0]))
        restStr++;
}

void ParsableString::parseChar(char ch)
{
    if (errors.size() != 0)
        return;
    if (restStr[0] == ch)
        restStr++;
    else 
        errors.push_back(ParserError(*this, "Expected '" + std::string(1, ch) + "' here"));
}

Polynomial ParsableString::parse()
{
    parsePolynomial();
    if (strlen(restStr) > 0)
    {
        errors.push_back(ParserError(*this, "Parser didn't finish"));
    }
    return polynomial;
}
