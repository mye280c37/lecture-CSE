#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define DEBUG 0

void LPS(const int m, const char* X, int* LPS_length, char** LPS_string);

int main(void)
{
	FILE* fp_r, * fp_w, *conf;
	char input_f[100], output_f[100];
	int test_num, t, i, j, m, LPS_length;
	char* X, * LPS_string;

	conf = fopen("config_LPS.txt", "r");
	if (conf == NULL) exit(1);
	fscanf(conf, "%d", &test_num);

	for (t = 1; t <= test_num; t++) {
		fscanf(conf, "%s", input_f);
		fscanf(conf, "%s", output_f);

		fp_r = fopen(input_f, "rb");
		fp_w = fopen(output_f, "wb");
		if (fp_r == NULL) exit(1);
		if (fp_w == NULL) exit(1);

		// read string X's length
		fread(&m, sizeof(int), 1, fp_r);

		// read string X
		X = (char*)malloc(sizeof(char) * (m + 1));
		if (X == NULL) exit(1);
		fread(X, sizeof(char), m, fp_r);
		X[m] = '\0';

		LPS(m, X, &LPS_length, &LPS_string);
#ifdef DEBUG
		printf("LPS_length: %d\n", LPS_length);
		printf("LPS_string: %s\n", LPS_string);
#endif
		fwrite(&LPS_length, sizeof(int), 1, fp_w);
		fwrite(LPS_string, sizeof(char), LPS_length, fp_w);

		fclose(fp_r);
		fclose(fp_w);
	}
	
	fclose(conf);

	return 0;
}

void LPS(const int m, const char* X, int* LPS_length, char** LPS_string) 
{
	// X가 가리키는 길이가 m인 문자열의 LPS를 구함
	// LPS를 LPS_string에 저장, 그 길이를 LPS_length에 저장해 return
	int** L, ** P, leng;
	int i, j, g;
	char* str;

	L = (int**)malloc(sizeof(int*) * m);
	P = (int**)malloc(sizeof(int*) * m);
	for (i = 0; i < m; i++) {
		L[i] = (int*)malloc(sizeof(int) * m);
		P[i] = (int*)malloc(sizeof(int) * m);
	}

	// base step
	for (i = 0; i < m; i++) {
		L[i][i] = 1;
		P[i][i] = 2;
	}
	
	for (g = 1; g < m; g++) {
		for (i = 0 ; i < m-g; i++) {
			j = i + g;
			if (X[i] == X[j]) {
				if (j == i + 1) L[i][j] = 2;
				else L[i][j] = L[i + 1][j - 1] + 2;
				P[i][j] = 2;
			}
			else {
				L[i][j] = L[i + 1][j];
				P[i][j] = 1;
				if (L[i][j] < L[i][j - 1]) {
					L[i][j] = L[i][j - 1];
					P[i][j] = -1;
				}
			}
		}
	}

	leng = L[0][m - 1];
	str = (char*)malloc(sizeof(char) * (leng + 1));
	str[leng] = '\0';

	i = 0; j = m - 1;
	int a = 0, b = leng - 1;
	while (i <= j) {
		if (P[i][j] == 2) {
			str[a] = X[i];
			str[b] = X[j];
			a++;
			b--;
			i++;
			j--;
		}
		else if (P[i][j] == 1) {
			i += 1;
		}
		else j -= 1;
	}

	*LPS_length = leng;
	*LPS_string = str;
	
	for (i - 0; i < m; i++) free(L[i]);
	free(L);
}