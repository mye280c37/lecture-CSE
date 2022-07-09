#ifndef __MY_SOLVER_H__
#define __MY_SOLVER_H__

#include <stdio.h>
#include <Windows.h>

#define CHECK_TIME_START QueryPerformanceFrequency((_LARGE_INTEGER*) &freq); QueryPerformanceCounter((_LARGE_INTEGER*)&start);
#define CHECK_TIME_END(a) QueryPerformanceCounter((_LARGE_INTEGER*)&end); a = (float)((float) (end - start)/freq);

#define DELTA 0.000000000001
#define Nmax 100
#define EPSILON 0.00000000001

#define MAX 32767

void program2_1();
void program2_2();

// HOMEWORK
void program2_3_1(void);
void program2_2_a(FILE* fp_w, double* y, double h, int n, int m);
void program2_2_b(FILE* fp_w, double* y, double h, int n, int m);
void program2_2_c(FILE* fp_w, double* y, double h, int n, int m);
void program2_3_2(void);

// MyFunctions
double F(double x, double* y, double h, int n);
double _f(double x, double* y, double h, double u, int n);
double _fp(double x, double* y, double h, double u, int n);
double bisection(double* y, double h, double u, int n);
double secant(double* y, double h, double u, int n);
double newton(double* y, double h, double u, int n);

#endif  // __MY_SOLVER_H__
