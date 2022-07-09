#include "my_solver.h"

void program2_1()
{
	FILE* fp_r, *fp_w;
	__int64 start, freq, end;
	float resultTime = 0;

	fp_r = fopen("sampling_table.txt", "r");
	if (fp_r == NULL) {
		printf("input file not found....\n");
		exit(0);
	}

	fp_w = fopen("pdf_table.txt", "w");

	/***************************************************/

	int n;
	double h, x;
	fscanf(fp_r, "%d %lf", &n, &h);
	n--;

	double normed_h = 1.0 / n;

	double* y = (double*)malloc(sizeof(double) * (n+1));
	int i = 0;
	while (fscanf(fp_r, "%lf %lf", &x, &y[i]) != -1) {
		i++;
	}

	// normalization
	double cur_x = 0;
	double* normed_y = (double*)malloc(sizeof(double) * (n + 1));

	fprintf(fp_w, "%d %lf\n", n + 1, normed_h);

	double total_integral = y[0] + y[n];
	for (i = 1; i < n; i++) {
		total_integral += (2 * y[i]);
	}
	total_integral *= (normed_h / 2);

	for (i = 0; i <= n; i++) {
		normed_y[i] = y[i] / total_integral;
		fprintf(fp_w, "%lf %lf\n", cur_x, normed_y[i]);
		cur_x += normed_h;
	}

	// check px(x)
	// [0.0, 1.0]
	printf("*** Integrating the pdf from 0.0 to 1.0 = %lf\n", F(1.0, normed_y, normed_h, n));
	// [0.0 0.25]
	printf("*** Integrating the pdf from 0.0 to 0.25 = %lf\n", F(0.25, normed_y, normed_h, n));
	// [0.25, 0.5]
	printf("*** Integrating the pdf from 0.25 to 0.5 = %lf\n", F(0.5, normed_y, normed_h, n)- F(0.25, normed_y, normed_h, n));
	// [0.5, 0.75]
	printf("*** Integrating the pdf from 0.5 to 0.75 = %lf\n", F(0.75, normed_y, normed_h, n) - F(0.5, normed_y, normed_h, n));
	// [0.75, 1.0]
	printf("*** Integrating the pdf from 0.75 to 1.0 = %lf\n", F(1.0, normed_y, normed_h, n) - F(0.75, normed_y, normed_h, n));

	free(y);
	free(normed_y);

	/***************************************************/

	if (fp_r != NULL) fclose(fp_r);
	if (fp_w != NULL) fclose(fp_w);
}
