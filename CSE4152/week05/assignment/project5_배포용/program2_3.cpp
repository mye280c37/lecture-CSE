#include "my_solver.h"
#include <time.h>
#include <math.h>
#include <stdlib.h>

extern void (*_f2_3_2)(FILE*, double*, double, int, int);

// HOMEWORK
void program2_3_1()
{
	double lambda;
	int i, Nr; 
	double var, mean, squared_m;

	printf("Enter the lambda : ");
	scanf("%lf", &lambda);
	printf("Enter the number of random numbers: ");
	scanf("%d", &Nr);

	double irand;
	unsigned int iseed = (unsigned int)time(NULL);
	srand(iseed);

	squared_m = mean = 0.0;

	for (i = 0; i < Nr; i++) {
		irand = (double)rand() + DELTA; // DELTA ~ 32767+DELTA
		double u = irand / (MAX + DELTA * 2); // 32767에 2DELTA를 더해 0또는 1 나오는 것을 방지
		double xu = -(log(1-u)/lambda);
		//printf("u: % lf, xu : % lf\n", u, xu);
		mean += xu;
		squared_m += (xu * xu);
	}
	mean /= Nr;
	squared_m /= Nr;
	var = squared_m - (mean * mean);

	printf("mean: % lf, variance : % lf\n\n", mean, var);
}

// HOMEWORK
void program2_3_2()
{
	FILE* fp_r, *fp_w;

	fp_r = fopen("pdf_table.txt", "r");
	fp_w = fopen("random_event_table.txt", "w");

	int i, n, m;
	double h, x;
	fscanf(fp_r, "%d %lf", &n, &h);
	n--;
	double* y = (double*)malloc(sizeof(double) * (n + 1));
	i = 0;
	while (fscanf(fp_r, "%lf %lf", &x, &y[i]) != -1) {
		i++;
	}

	printf("Enter the number of random numbers: ");
	scanf("%d", &m);
	fprintf(fp_w, "%d\n", m);

	_f2_3_2(fp_w, y, h, n, m);

	if (fp_r != NULL) fclose(fp_r);
	if (fp_w != NULL) fclose(fp_w);

	fp_r = fopen("random_event_table.txt", "r");
	fp_w = fopen("histogram.txt", "w");

	double xr;
	int* his = (int*)malloc(sizeof(int) * n);
	for (i = 0; i < n; i++) 
		his[i] = 0;

	fscanf(fp_r, "%d", &m);
	i = 0;
	while (fscanf(fp_r, "%lf", &xr) != -1) {
		int s = (int)(xr / h);
		//printf("%d\n", s);
		his[s]++;
		i++;
	}

	fprintf(fp_w, "         [xi, xi+1)                  data/Nr                   F(xi+1)-F(xi)\n");
	for (i = 0; i < n; i++) {
		fprintf(fp_w, "[%lf, %lf)    %.15lf     %.15lf\n", h*i, h*(i+1), (double)his[i]/m, F(h*(i+1), y, h, n) - F(h * i, y, h, n));
	}

	if (fp_r != NULL) fclose(fp_r);
	if (fp_w != NULL) fclose(fp_w);

	free(y);
	free(his);
}

// HOMEWORK
void program2_2_a(FILE *fp_w, double *y, double h, int n, int m)
{
	__int64 start, freq, end;
	float resultTime = 0;

	CHECK_TIME_START;
	int i;
	double irand;
	unsigned int iseed = (unsigned int)time(NULL);
	srand(iseed);

	for (i = 0; i < m; i++) {
		irand = (double)rand() + DELTA; 
		double u = irand / (MAX + DELTA * 2); 
		double xu = bisection(y, h, u, n);
		fprintf(fp_w, "%.15lf\n", xu);
	}

	CHECK_TIME_END(resultTime);

	printf("The program2_2_a run time is %f(ms)..\n", resultTime * 1000.0);
}

void program2_2_b(FILE* fp_w,  double* y, double h, int n, int m)
{
	__int64 start, freq, end;
	float resultTime = 0;

	CHECK_TIME_START;

	/***************************************************/
	int i;
	double irand;
	unsigned int iseed = (unsigned int)time(NULL);
	srand(iseed);

	for (i = 0; i < m; i++) {
		irand = (double)rand() + DELTA; // DELTA ~ 32767+DELTA
		double u = irand / (MAX + DELTA * 2); // 32767에 2DELTA를 더해 0또는 1 나오는 것을 방지
		double xu = secant(y, h, u, n);
		fprintf(fp_w, "%.15lf\n", xu);
	}

	/***************************************************/

	CHECK_TIME_END(resultTime);

	printf("The program2_2_b run time is %f(ms)..\n", resultTime * 1000.0);
}

void program2_2_c(FILE* fp_w, double* y, double h, int n, int m)
{
	__int64 start, freq, end;
	float resultTime = 0;

	CHECK_TIME_START;

	/***************************************************/
	int i;
	double irand;
	unsigned int iseed = (unsigned int)time(NULL);
	srand(iseed);

	for (i = 0; i < m; i++) {
		irand = (double)rand(); // DELTA ~ 32767+DELTA
		double u = irand / MAX; // 32767에 2DELTA를 더해 0또는 1 나오는 것을 방지
		double xu = newton(y, h, u, n);
		fprintf(fp_w, "%.15lf\n", xu);
	}

	/***************************************************/

	CHECK_TIME_END(resultTime);

	printf("The program2_2_c run time is %f(ms)..\n", resultTime * 1000.0);
}