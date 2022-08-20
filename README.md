# computor-v1

The goal of this project is to make a simple equation solving program. It takes polynomial equations into account. These equations only require exponents. No complex function. The program has to display its solution(s).

## Example

$>./computor "5 * X^0 + 4 * X^1 - 9.3 * X^2 = 1 * X^0"
<br/>Reduced form: 4 * X^0 + 4 * X^1 - 9.3 * X^2 = 0
<br/>Polynomial degree: 2
<br/>Discriminant is strictly positive, the two solutions are:
<br/>0.905239
<br/>-0.475131
<br/>$>./computor "5 * X^0 + 4 * X^1 = 4 * X^0"
<br/>Reduced form: 1 * X^0 + 4 * X^1 = 0
<br/>Polynomial degree: 1
<br/>The solution is:
<br/>-0.25
