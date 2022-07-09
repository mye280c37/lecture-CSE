#include "my_solver.h"

extern float (*_sp_f)(float);
extern float (*_sp_fp)(float);

/*********************************************
  Secant Method
**********************************************/
void sp_program1_2(FILE* fp) {
	float x0, x1, temp;
	int n;

	if (fp == NULL)
		return;

	printf("Enter x0, x1: ");
	scanf("%f %f", &x0, &x1);

	fprintf(fp, "  i                 xn1                              | f(xn1) |\n");

	n = 0;

	fprintf(fp, "%3d    %.15e    %.15e\n", n++, x0, (float)fabs(_sp_f(x0)));
	fprintf(fp, "%3d    %.15e    %.15e\n", n++, x1, (float)fabs(_sp_f(x1)));

	for (n; n <= Nmax; n++) {
		temp = x1 - _sp_f(x1) * ((x1 - x0) / (_sp_f(x1) - _sp_f(x0)));
		fprintf(fp, "%3d    %.15e    %.15e\n", n, temp, fabs(_sp_f(temp)));
		if ((float)fabs(_sp_f(temp)) < DELTA || (float)fabs((double)(temp - x1)) < EPSILON) {
			break;
		}
		x0 = x1;
		x1 = temp;
	}


}
