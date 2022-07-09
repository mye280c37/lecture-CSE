#include "my_solver.h"

extern double (*_f)(double);
extern double (*_fp)(double);

/*********************************************
  Newton-Rapson Method
**********************************************/
void program1_1(FILE* fp) {
	double x0 , x1;
	int n;

	printf("Enter x0: ");
	scanf("%lf", &x0);

	if (fp == NULL)
		return;
	
	fprintf(fp, "  i                 xn1                              | f(xn1) |\n");

	n = 0;

	fprintf(fp, "%3d    %.15e    %.15e\n", n++, x0, fabs(_f(x0)));

	for(n; n<=Nmax; n++) {
		x1 = x0 - (_f(x0) / _fp(x0));
		fprintf(fp, "%3d    %.15e    %.15e\n", n, x1, fabs(_f(x1)));
		if (fabs(_f(x1)) < DELTA  || fabs(x1 - x0) < EPSILON) {
			break;
		}
		x0 = x1;
	}
	
}
