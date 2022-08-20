#pragma once
#include <limits>
#include "computorv1.h"

class CV1Solution
{
public:
	virtual ~CV1Solution() {}
	virtual std::string toString() = 0;
};

class Polynomial
{
public:
	Polynomial();
	Polynomial(const Polynomial& p);
	~Polynomial();

	float getCoef(int pow) const;
	float sumCoef() const;
	int getSize() const;
    std::vector<CV1Solution*> getSolution();
	int getDegree();
	bool descriminantPositive();
    Polynomial& addCoef(int pow, float coef);
	Polynomial& addPolynomial(const Polynomial& additionalPolynomial);
	Polynomial& invert();
	Polynomial& clear();
    void solve();
private:
	void solveSquared();
	
	std::vector<float> vector;
	std::vector<CV1Solution*> solution;
	float discriminantSquared;
};

class CV1Real : public CV1Solution
{
public:
	CV1Real(float real) : real(real) {}
	~CV1Real() {}
	float real;

	std::string toString();
};

class CV1Complex : public CV1Solution
{
public:
	CV1Complex(float real, float im) : real(real), im(im) {}
	~CV1Complex() {}
	float real;
	float im;

	std::string toString();
};
