#include "my_solver.h"

extern float (*_sp_f)(float);
extern float (*_sp_fp)(float);

/*********************************************
  Newton-Rapson Method
**********************************************/
void sp_program1_1(FILE* fp) {
	float x0, x1;
	int n;

	if (fp == NULL)
		return;

	printf("Enter x0: ");
	scanf("%f", &x0);

	if (fp == NULL)
		return;

	fprintf(fp, "  i                 xn1                              | f(xn1) |\n");

	n = 0;

	fprintf(fp, "%3d    %.15e    %.15e\n", n++, x0, (float)fabs(_sp_f(x0)));

	for (n; n <= Nmax; n++) {
		x1 = x0 - (float)(_sp_f(x0) / _sp_fp(x0));
		fprintf(fp, "%3d    %.15e    %.15e\n", n, x1, (float)fabs(_sp_f(x1)));
		if ((float)fabs(_sp_f(x1)) < DELTA || (float)fabs((double)(x1 - x0)) < EPSILON) {
			break;
		}
		x0 = x1;
	}

}
