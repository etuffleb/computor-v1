#pragma once

#include "computorv1.h"

class ParsableString
{
public:
    ParsableString(char* str);
    ~ParsableString() = default;
    ParsableString(const ParsableString& ps) = default;
    Polynomial parse();

    Polynomial polynomial;
    std::vector<ParserError> errors;
    char* const originalStr;
    char* restStr;
private:

    struct Snapshot 
    {
        Snapshot(ParsableString& ps);
        ~Snapshot() = default;
        Polynomial polynomial;
        char* restStr;
    };
    
    void loadSnapshot(Snapshot s);
    void addPolynomialCoef(int pow, float coef);
    void parsePolynomial();
    void parseElements();
    void parseElementsRest();
    void parseInvElements();
    void parseElement(int sign);
    void parseElementWithSign();
    void parseElementOptionalSign();
    void parseXPow(int* pow);
    void parseX();
    void parseSign(int* sign);
    void parseF10(float* num);
    void parseN10(int* num);
    void parseDiv();
    void parseChar(char ch);
};