#include "my_solver.h"
#include <time.h>
#include <math.h>
#include <stdlib.h>

void program2_2()
{
	FILE* fp_r, *fp_w;

	fp_r = fopen("pdf_table.txt", "r");
	fp_w = fopen("random_event_table.txt", "w");

	/***************************************************/
	int i, m;
	double irand, x;
	unsigned int iseed = (unsigned int)time(NULL);
	srand(iseed);

	int n;
	double h;
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

	for (i = 0; i < m; i++) {
		irand = (double)rand()+DELTA; // DELTA ~ 32767+DELTA
		double u = irand / (MAX+DELTA*2); // 32767에 2DELTA를 더해 0또는 1 나오는 것을 방지
		double xu = bisection(y, h, u, n);
		fprintf(fp_w, "%.15lf\n", xu);
	}

	free(y);

	/***************************************************/

	if (fp_r != NULL) fclose(fp_r);
	if (fp_w != NULL) fclose(fp_w);
}
