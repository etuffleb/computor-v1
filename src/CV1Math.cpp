#include "../lib/computorv1.h"

float CV1Math::sqrt(float number)
{	
	long i;
	float x2, y;
	const float threehalfs = 1.5F;

	x2 = number * 0.5F;
	y = number;
	i = *(long *)&y;                     // floating point bit level hacking [sic]
	i = 0x5f3759df - (i >> 1);           // Newton's approximation
	y = *(float *)&i;
	y = y * (threehalfs - (x2 * y * y)); // 1st iteration
	y = y * (threehalfs - (x2 * y * y)); // 2nd iteration
	y = y * (threehalfs - (x2 * y * y)); // 3rd iteration

	return 1 / y;
}

std::string CV1Real::toString()
{
	if (real == 0)
		return "0";
	return std::to_string(real);
}

std::string CV1Complex::toString()
{
	std::string realSign = (real > 0) ? "" : "- ";
	std::string imSign = (im > 0) ? " + " : " - ";
	real *= (real < 0) ? -1 : 1;
	im *= (im < 0) ? -1 : 1;
	return realSign + std::to_string(real) + imSign + std::to_string(im) + "i";
}
