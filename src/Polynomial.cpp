#include "../lib/computorv1.h"

Polynomial::Polynomial()
{}

Polynomial::Polynomial(const Polynomial& p)
{
	vector.resize(p.vector.size());
	for (size_t i = 0; i < p.vector.size(); i++) 
        vector[i] = p.vector[i]; 
}

Polynomial::~Polynomial()
{
	for (auto s : solution)
		delete s;
}

float Polynomial::getCoef(int pow) const
{
	return vector[pow];
}

float Polynomial::sumCoef() const
{
	return std::accumulate(vector.begin(), vector.end(), 0.0);
}

int Polynomial::getSize() const
{
	return vector.size();
}

std::vector<CV1Solution*> Polynomial::getSolution()
{
	return solution;
}

int Polynomial::getDegree()
{
	int deg = 0;
    for (size_t i = 0; i < vector.size(); i++)
		if (vector[i] != 0)
			deg = i;
	if (deg == 0 && sumCoef() == 0)
		return -1;	
    return deg;
}

bool Polynomial::descriminantPositive()
{
	return discriminantSquared > 0;
}

Polynomial& Polynomial::addCoef(int pow, float coef)
{
	if (vector.size() <= static_cast<size_t>(pow))
		vector.resize(pow + 1, 0);
	vector[pow] += coef;
	return *this;
}

Polynomial& Polynomial::addPolynomial(const Polynomial& additionalPolynomial)
{
	int thisPolySize = getSize();
	int additPolySize = additionalPolynomial.getSize();
	int i = 0;

	for (; i < thisPolySize; i++)
		if (i < additPolySize)
			vector[i] += additionalPolynomial.getCoef(i);

	for (; i < additPolySize; i++)
		vector.push_back(additionalPolynomial.getCoef(i));

	return *this;
}

Polynomial& Polynomial::invert()
{
	for (size_t i = 0; i < vector.size(); i++)
	{
		vector[i] *= -1;		
	}
	return *this;
}


Polynomial& Polynomial::clear()
{
	vector.clear();
	return *this;
}

void Polynomial::solveSquared()
{
	float descriminant = vector[1] * vector[1] - 4 * vector[0] * vector[2];
	float eps = std::numeric_limits<float>::epsilon();
	if (descriminant > eps)
	{
		float sqrtDes = CV1Math::sqrt(descriminant);
		solution.push_back(new CV1Real((-vector[1] + sqrtDes) / (2 * vector[2])));
		solution.push_back(new CV1Real((-vector[1] - sqrtDes) / (2 * vector[2])));
	}
	else if (descriminant < -std::numeric_limits<float>::epsilon())
	{
		float sqrtDes = CV1Math::sqrt(-descriminant);
		solution.push_back(new CV1Complex((-vector[1]) / (2 * vector[2]), sqrtDes / (2 * vector[2])));
		solution.push_back(new CV1Complex((-vector[1]) / (2 * vector[2]), -sqrtDes / (2 * vector[2])));
	}
	else
		solution.push_back(new CV1Real((-vector[1]) / (2 * vector[2])));
	discriminantSquared = descriminant;
}

void Polynomial::solve()
{
	int deg = getDegree();
	if (deg == 1)
	{
		int sign = (vector[0] == 0) ? 1 : -1;
		solution.push_back(new CV1Real(vector[0] * sign / vector[1]));
	}
	if (deg == 2)
		solveSquared();
}