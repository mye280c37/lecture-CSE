#include "my_solver.h"

extern void program1_1(FILE* fp); // Newton-Raphson Method
extern void program1_2(FILE* fp); // Secant Method
extern void program1_3(FILE* fp); // Bisection Method

extern void sp_program1_1(FILE* fp); // Newton-Raphson Method
extern void sp_program1_2(FILE* fp); // Secant Method

double (*_f)(double);
double (*_fp)(double);

float (*_sp_f)(float);
float (*_sp_fp)(float);

int main() {
	FILE* fp;
	fp = fopen("result.txt", "w");

	/**********************
	  Problem 1-1
	 **********************/
	// f1 = x^2 -4x +4 -lnx = 0
	_f = _f1;
	_fp = _fp1;

	program1_1(fp);
	program1_2(fp);


	// f2 = x +1 -2sin(PI*x) = 0
	_f = _f2;
	_fp = _fp2;

	program1_1(fp);
	program1_2(fp);

	/**********************
	  Problem 1-2
	**********************/
	// f3 = x^4 -11.0x^3 +42.35x^2 -66.55x +35.1384 = 0
	_f = _f3;
	_fp = _fp3;

	for (int i = 3; i >= 0; i--)
		program1_1(fp);

	/**********************
	  Problem 1-4
	**********************/
	_f = _f_comp;
	_fp = _fp_comp;
	program1_1(fp);

	_sp_f = _sp_f_comp;
	_sp_fp = _sp_fp_comp;
	sp_program1_1(fp);


	/**********************
	  Homework 1
	 **********************/


	/**********************
	  Homework 2
	 **********************/


	fclose(fp);
	return 0;
}
