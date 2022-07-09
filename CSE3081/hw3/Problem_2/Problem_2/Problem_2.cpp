#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define DEBUG 1
#define TRUE 1
#define FALSE 0

int main(void)
{
	FILE* fp_r, * f_out, * f_comm;
	char input_f[100];
	int L, R, N, * arr_l, * arr_r, *arr_n;
	int i, j, t;
	int** O;

	f_comm = fopen("commands_3_2.txt", "r");
	if (f_comm == NULL) exit(1);

	f_out = fopen("outputs_3_2.txt", "w");
	if (f_out == NULL) exit(1);

	while (fscanf(f_comm, "%s", input_f) != -1) {
		fp_r = fopen(input_f, "r");

		fscanf(fp_r, "%d", &L);
		arr_l = (int*)malloc(sizeof(int) * (L+1));
		if (arr_l == NULL) exit(1);
		for (i = 1; i <= L; i++) fscanf(fp_r, "%d", &arr_l[i]);

		fscanf(fp_r, "%d", &R);
		arr_r = (int*)malloc(sizeof(int) * (R+1));
		if (arr_r == NULL) exit(1);
		for (i = 1; i <= R; i++) fscanf(fp_r, "%d", &arr_r[i]);

		for (t = 0; t <2; t++) {
			fscanf(fp_r, "%d", &N);
			arr_n = (int*)malloc(sizeof(int) * (N+1));
			for(i=1; i<=N; i++) fscanf(fp_r, "%d", &arr_n[i]);

			O = (int**)malloc(sizeof(int*) * (L+1));
			if (O == NULL) exit(1);
			for (i = 0; i <= L; i++) {
				O[i] = (int*)malloc(sizeof(int) * (R + 1));
				if (O[i] == NULL) exit(1);
			}

			O[0][0] = TRUE;
			for (j = 1; j <= R; j++) {
				O[0][j] = FALSE;
				if (O[0][j-1] && arr_r[j] == arr_n[0 + j]) O[0][j] = TRUE;
			}
			for (i = 1; i <= L; i++) {
				O[i][0] = FALSE;
				if (O[i - 1][0] && arr_l[i] == arr_n[i + 0]) O[i][0] = TRUE;
			}

			for (i = 1; i <= L; i++) {
				for (j = 1; j <= R; j++) {
					O[i][j] = FALSE;
					if (O[i - 1][j] && arr_l[i] == arr_n[i + j]) O[i][j] = TRUE;
					if (O[i][j - 1] && arr_r[j] == arr_n[i + j]) O[i][j] = TRUE;
				}
			}

			fprintf(f_out, "%d", O[L][R]);

			// decalloc O
			for (i = 0; i <= L; i++) free(O[i]);
			free(O);
		}

		fprintf(f_out, "\n");

		fclose(fp_r);
		//strcpy(input_f, NULL);

		free(arr_l);
		free(arr_r);
	}

	fclose(f_comm);
	fclose(f_out);

	return 0;
}