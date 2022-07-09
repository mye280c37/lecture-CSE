#define _USE_MATH_DEFINES
#include <math.h>

double _f1(double x) {
	return pow(x, 2) - 4.0*x + 4.0 - log(x);
}

double _fp1(double x) {
	return 2.0*x -4.0 - (1.0/x);
}

double _f2(double x) {
	return x + 1.0 - 2.0*sin(M_PI * x);
}

double _fp2(double x) {
	return 1.0 -2.0*M_PI*cos(M_PI*x);
}

double _f3(double x) {
	// f3 = x^4 -11.0x^3 +42.35x^2 -66.55x +35.1384 = 0
	return pow(x, 4) - 11.0 * pow(x, 3) + 42.35 * pow(x, 2) - 66.55 * x + 35.1384;
}

double _fp3(double x) {
	// f3 = x^4 -11.0x^3 +42.35x^2 -66.55x +35.1384 = 0
	return 4.0 * pow(x, 3) - 33.0 * pow(x, 2) + 84.7 * x - 66.55;
}

double _f_sqrt(double x) {
	return x * x - 2.0;
}

double _fp_sqrt(double x) {
	return 2.0 * x;
}

double _f_vehicle(double x) {
	return 0.0;
}

double _fp_vehicle(double x) {
	return 0.0;
}

double _f_comp(double x) {
	return log(x)-1;
}

double _fp_comp(double x) {
	return 1.0 / x;
}
