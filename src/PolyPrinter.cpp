#include "../lib/computorv1.h"

PolyPrinter::PolyPrinter(Polynomial& polynomial) : polynomial(polynomial)
{}

PolyPrinter::~PolyPrinter()
{}

void PolyPrinter::print()
{
	printReducedForm();
	if (printPolynomialDegree())
		printPolinomialSolution();	
}

bool PolyPrinter::printPolynomialDegree()
{
	int polynomialDegree = polynomial.getDegree();	
	if (polynomialDegree > 2)
	{
		std::cout << BOLDWHITE << "Polynomial Degree: " << polynomialDegree << std::endl;
		std::cout << YELLOW << "The polynomial degree is strictly greater then 2, I can't solve it :(" << std::endl << std::endl;
	}
	else if (polynomialDegree == 0)
	{
		//if (polynomial.getSize() == 1 && polynomial.getCoef(0) == 0)
		std::cout << BOLDWHITE << "Polynomial Degree: 0" << std::endl;
		std::cout << YELLOW << "There are no solutions" << std::endl << std::endl;	
	}
	else if (polynomialDegree == -1)
	{
		std::cout << BOLDWHITE << "Polynomial Degree is undefined (-1)" << std::endl;
		std::cout << GREEN << "This polynomial has an infinite number of solutions" << std::endl << std::endl;		
	}
	else
		return true;
	return false;
}

void PolyPrinter::printPolinomialSolution()
{
	polynomial.solve();
	std::vector<CV1Solution*> solution = polynomial.getSolution();

	if (solution.size() == 1)
		std::cout << GREEN << "The solution is:" << std::endl << RESET << solution[0]->toString() << std::endl << std::endl;
	else if (polynomial.descriminantPositive())
		std::cout << GREEN << "Discriminant is strictly positive, there are two solutions:" << RESET << std::endl <<
			solution[0]->toString() << "\n" << solution[1]->toString() << std::endl << std::endl;
	else
		std::cout << GREEN << "Discriminant is strictly negative, but there are two complex solutions:" << RESET << std::endl <<
			solution[0]->toString() << "\n" << solution[1]->toString() << std::endl << std::endl;
}

void PolyPrinter::printReducedForm()
{
	int flagFirst = 0;
	int polySize = polynomial.getSize();
	std::stringstream out;
	std::cout << BOLDWHITE << "\n";
	for (int i = 0; i < polySize; i++)
	{
		auto coef = polynomial.getCoef(i);
		if (coef == 0)
			continue;
		else if (flagFirst != 0 && coef < 0)
		{
			out << "- ";
			coef *= -1;
		}
		else if (flagFirst != 0)
			out << "+ ";
		out << coef << " * X^" << i << " ";
		flagFirst = 1;
	}
	if (out.rdbuf()->in_avail() == 0)
		std::cout << "0 ";
	std::cout << out.str() <<"= 0\n";
}