#include "./include/math.h"

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

double sin(double x)
{
	x = reduce_angle(x);

	// Taylor series expansion for sine function
	return x - (x * x * x) / 6.0 + (x * x * x * x * x) / 120.0 -
	       (x * x * x * x * x * x * x) / 5040.0;
}

double cos(double x)
{
	x = reduce_angle(x);

	// Taylor series expansion for cosine function
	return 1.0 - (x * x) / 2.0 + (x * x * x * x) / 24.0 -
	       (x * x * x * x * x * x) / 720.0;
}

double tan(double x)
{
	return sin(x)/cos(x);
}
