#include "my_solver.h"

extern double (*_f)(double);
extern double (*_fp)(double);

/*********************************************
  Secant Method
**********************************************/
void program1_2(FILE* fp) {
	double x0, x1, temp;
	int n;

	if (fp == NULL)
		return;

	printf("Enter x0, x1: ");
	scanf("%lf %lf", &x0, &x1);

	fprintf(fp, "  i                 xn1                              | f(xn1) |\n");

	n = 0;

	fprintf(fp, "%3d    %.15e    %.15e\n", n++, x0, fabs(_f(x0)));
	fprintf(fp, "%3d    %.15e    %.15e\n", n++, x1, fabs(_f(x1)));

	for (n; n <= Nmax; n++) {
		temp = x1 - _f(x1)*((x1-x0)/(_f(x1)-_f(x0)));
		fprintf(fp, "%3d    %.15e    %.15e\n", n, temp, fabs(_f(temp)));
		if (fabs(_f(temp)) < DELTA  || fabs(temp - x1) < EPSILON) {
			break;
		}
		x0 = x1;
		x1 = temp;
	}

}
