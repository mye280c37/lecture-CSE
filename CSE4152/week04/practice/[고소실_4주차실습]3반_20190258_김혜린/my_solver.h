#ifndef __MY_SOLVER_H__
#define __MY_SOLVER_H__

#include <stdio.h>
#include <stdlib.h>
#include <float.h>
#include <math.h>

#define DELTA 0.00001
#define Nmax 50
#define EPSILON 0.0001

double _f1(double x);
double _fp1(double x);

double _f2(double x);
double _fp2(double x);

double _f3(double x);
double _fp3(double x);

double _f_sqrt(double x);
double _fp_sqrt(double x);

double _f_vehicle(double x);
double _fp_vehicle(double x);

double _f_comp(double x);
double _fp_comp(double x);

float _sp_f_comp(float x);
float _sp_fp_comp(float x);

#endif  // __MY_SOLVER_H__
