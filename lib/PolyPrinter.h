#pragma once

#include "computorv1.h"

#define YELLOW  "\033[33m"
#define GREEN   "\033[32m"
#define RESET   "\033[0m"
#define BOLDWHITE   "\033[1m\033[37m"

class PolyPrinter
{
public:
	PolyPrinter(Polynomial& polynomial);
	~PolyPrinter();

	void print();

private:
	Polynomial& polynomial;

	bool printPolynomialDegree();
	void printPolinomialSolution();
	void printReducedForm();
};
