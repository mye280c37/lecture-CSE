#include "my_solver.h"
#include <time.h>
#include <math.h>
#include <stdlib.h>

double F(double x, double* y, double h, int n) {
	int m = 0;
	double xm = 0.0;
	double result = 0.0;
	if (x > 1) printf("error 1) x: %lf\n", x);
	while (1) {
		if (xm + h > x) break;
		xm += h;
		m++;
	}
	if (m > n) m = n;
	if (m > 0) {
		result = y[0] + y[m];
		for (int i = 1; i < m; i++) {
			result += (2 * y[i]);
		}
		result *= (h / 2);
	}
	if (m < n) {
		result += ((y[m] + (y[m + 1] - y[m]) / h * (x - xm) / 2) * (x - xm));
	}
	return result;
}

double _f(double x, double* y, double h, double u, int n) {
	return F(x, y, h, n) - u;
}

double _fp(double x, double* y, double h, double u, int n) {
	int i = 0;
	double xi = 0.0, s;
	while (1) {
		xi += h;
		i++;
		if (xi + h > x) break;
	}
	if (i > n) i = n;
	if (i < n) {
		s = (x - xi) / h;
		return (1 - s) * y[i] + s * y[i + 1];
	}
	else return y[n];
}

double bisection(double* y, double h, double u, int n)
{
	double a0 = 0, b0 = 1, x0, x1, temp;
	int N;

	if (-DELTA < _f(a0, y, h, u, n) && _f(a0, y, h, u, n) < DELTA) {
		return a0;
	}
	if (-DELTA < _f(b0, y, h, u, n) && _f(b0, y, h, u, n) < DELTA) {
		return b0;
	}

	N = 0;
	x0 = a0;

	for (N; N <= Nmax; N++) {
		x1 = (a0 + b0) / 2;
		if ((-DELTA < _f(x1, y, h, u, n) && _f(x1, y, h, u, n) < DELTA) && (-EPSILON < x1 - x0 && x1 - x0 < EPSILON)) {
			break;
		}
		if (_f(a0, y, h, u, n) * _f(x1, y, h, u, n) < 0)  b0 = x1; // [ a0, x1 ]
		else if(_f(x1, y, h, u, n) * _f(b0, y, h, u, n) < 0) {
			a0 = x1; // [x1, b0]
		}
		else {
			break;
		}
		x0 = x1;
	}

	return x1;
}

double secant(double* y, double h, double u, int n) {
	double x0 = 0.0, x1 = 1.0, temp;
	int N;

	if (-DELTA < _f(x0, y, h, u, n) && _f(x0, y, h, u, n) < DELTA) {
		return x0;
	}
	if (-DELTA < _f(x1, y, h, u, n) && _f(x1, y, h, u, n) < DELTA) {
		return x1;
	}

	for (int i = 0; i < 3; i++) {
		temp = (x0 + x1) / 2;
		if ((-DELTA < _f(temp, y, h, u, n) && _f(temp, y, h, u, n) < DELTA) && (-EPSILON < temp - x1 && temp - x1 < EPSILON)) {
			return temp;
		}
		if (_f(x0, y, h, u, n) * _f(temp, y, h, u, n) < 0)  x1 = temp; // [ x0, temp ]
		else if (_f(temp, y, h, u, n) * _f(x1, y, h, u, n) < 0) {
			x1 = temp; // [temp, x1]
		}
		else {
			return temp;
		}
	}

	N = 0;

	for (N; N <= Nmax; N++) {
		temp = x1 - _f(x1, y, h, u, n) * ((x1 - x0) / (_f(x1, y, h, u, n) - _f(x0, y, h, u, n)));
		if ((-DELTA < _f(temp, y, h, u, n) && _f(temp, y, h, u, n) < DELTA) && (-EPSILON < temp - x1 && temp - x1 < EPSILON)) {
			break;
		}
		x0 = x1;
		x1 = temp;
	}

	return temp;
}

double newton(double* y, double h, double u, int n) {
	double x0 , x1;
	double a0 = 0.0, b0 = 1.0;
	int N;

	if (-DELTA < _f(a0, y, h, u, n) && _f(a0, y, h, u, n) < DELTA) {
		return a0;
	}
	if (-DELTA < _f(b0, y, h, u, n) && _f(b0, y, h, u, n) < DELTA) {
		return b0;
	}

	x0 = a0;
	for (int i = 0; i < 3; i++) {
		x1 = (a0 + b0) / 2;
		if ((-DELTA < _f(x1, y, h, u, n) && _f(x1, y, h, u, n) < DELTA) && (-EPSILON < x1 - x0 && x1 - x0 < EPSILON)) {
			return x1;
		}
		if (_f(a0, y, h, u, n) * _f(x1, y, h, u, n) < 0)  b0 = x1; // [ a0, x1 ]
		else if (_f(x1, y, h, u, n) * _f(b0, y, h, u, n) < 0) {
			a0 = x1; // [x1, b0]
		}
		else {
			return x1;
		}
		x0 = x1;
	}
	
	N = 0;
	x0 = (a0 + b0)/2;
	for (N; N <= Nmax; N++) {
		x1 = x0 - (_f(x0, y, h, u, n) / _fp(x0, y, h, u, n));
		if ((-DELTA < _f(x1, y, h, u, n) && _f(x1, y, h, u, n) < DELTA) && (-EPSILON < x1 - x0 && x1 - x0 < EPSILON)) {
			break;
		}
		x0 = x1;
	}
	return x1;
}