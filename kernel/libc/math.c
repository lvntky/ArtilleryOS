#include "./include/math.h"

// Trigonometry functions
// Helper function to reduce angles to the range [-PI, PI]
static double reduce_angle(double angle)
{
	while (angle > PI) {
		angle -= TWO_PI;
	}
	while (angle < -PI) {
		angle += TWO_PI;
	}
	return angle;
}

// Taylor series expansion for sine function
double sin(double x)
{
	x = reduce_angle(x);

	return x - exp(x, 3) / 6.0 + exp(x, 5) / 120.0 -
	       exp(x, 7) / 5040.0;
}

// Taylor series expansion for cosine
double cos(double x)
{
	x = reduce_angle(x);

	return 1.0 - exp(x, 2) / 2.0 + exp(x, 4) / 24.0 -
	       exp(x, 6) / 720.0;
}

// Tangent calculation
double tan(double x)
{
	return sin(x)/cos(x);
}

// Taylor series expansion for inverse sine function (arcsin)
double arcsin(double x)
{
    return x + ( (exp(x, 3))/6 ) + (( 1 * 3 * exp(x, 5)) / 40.0 ) + ( ( 1 * 3 * 5 * exp(x, 7) ) / 384.0 );
}

// Taylor series expansion for inverse cosine (arccos)
double arccos(double x)
{
    return ( PI / 2 ) - x - (exp(x, 3)/6.0) - ( 3 * exp(x, 5)) / 40.0 + ( 15 * exp(x, 7)) / 336.0;
}

// Taylor series expansion for inverse tangent (arctan)
// Use this with caution, needs to be re-implemented later for more accuracy.
double arctan(double x)
{
    return x - exp(x, 3) / 3.0 + exp(x, 5) / 5.0 - exp(x, 7) / 7.0 + exp(x, 9) / 9.0 - exp(x, 11) / 11.0
    + exp(x, 13) / 13.0 - exp(x, 15) / 15.0 + exp(x, 17) / 17.0;
}

// Returns the value of n factorial
int factorial(int n)
{
    int result = n;

    if (n == 0)
    {
	return 1;
    }

    while (n != 1)
    {
	result = result*(n-1);
	n--;
    }

    return result;
}

// Returns the value of b to the power of n
double exp(double b, double n)
{
    double result = 1.0;
    if (n < 0)
    {
	return -1;
    }

    while (n != 0)
    {
	result *= b;
	n--;
    }
    return result;
}

// Returns square root of x
double sqrt(double x)
{
    if (x < 0)
    {
	return -1;
    }
    return exp(x, 0.5); 
}

// Returns absolute value of x
double abs(double x)
{
    if (x < 0)
    {
	return -x ;
    }
    return x;
}

// Conversion from radian to degree - Conversion to degree
double toDeg(double rad)
{
    return rad * (180 / PI); 
}

// Conversion from degree to radian - Conversion to radian
double toRad(double deg)
{
    return deg * (PI / 180);
}
