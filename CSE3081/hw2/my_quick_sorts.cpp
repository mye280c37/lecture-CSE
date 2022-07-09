#define _CRT_SECURE_NO_WARNINGS

#include "my_quick_sorts.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <Windows.h>

#define MAX_BUF 256
#define MIN_NUM 10
#define P_CAND_N 3

__int64 start, freq, end;
#define CHECK_TIME_START QueryPerformanceFrequency((LARGE_INTEGER*)&freq); QueryPerformanceCounter((LARGE_INTEGER*)&start)
#define CHECK_TIME_END(a) QueryPerformanceCounter((LARGE_INTEGER*)&end); a = (float)((float)(end - start) / (freq / 1000.0f))
float compute_time;

int score_comparison(const void* a, const void* b) {
	ELEMENT* ele_a, * ele_b;

	ele_a = (ELEMENT*)a;
	ele_b = (ELEMENT*)b;

	if (ele_a->score == ele_b->score)
		return 0;
	else if (ele_a->score < ele_b->score)
		return -1;
	else return 1;

	// could be "return ele_a->score - ele_b->score;"
}

void swap_ele(const void* a, const void* b) {
	ELEMENT* ele_a = (ELEMENT*)a;
	ELEMENT* ele_b = (ELEMENT*)b;
	ELEMENT* tmp = (ELEMENT*)malloc(sizeof(ELEMENT));
	if (tmp != NULL) {
		memcpy(tmp, ele_a, sizeof(ELEMENT));
		memcpy(ele_a, ele_b, sizeof(ELEMENT));
		memcpy(ele_b, tmp, sizeof(ELEMENT));
	}
	else {
		fprintf(stderr, "allocate memeory error\n");
		exit(-1);
	}
	free(tmp);
}

void insert_sort(void* base, size_t num, size_t size, _Cmpfun* cmp_func) {
	int i, j, tmp;
	char* start = (char*)base;
	char* tmp_ele = (char*)malloc(sizeof(char) * size);
	if (tmp_ele == NULL) {
		fprintf(stderr, "allocate memeory error\n");
		exit(-1);
	}
	for (i = 1; i < num; i++) {
		memcpy(tmp_ele, start + i * size, size);
		j = i;
		for (j = i; j > 0; j--) {
			if (cmp_func(tmp_ele, start + (j - 1) * size) >= 0) break;
			swap_ele(start + j * size, start + (j - 1) * size);
		}
		memcpy(start + j * size, tmp_ele, size);
	}
	free(tmp_ele);
}

void qsort_orig(void* base, size_t num, size_t size, _Cmpfun* cmp_func) {
	int i;
	if (num <= 1) return;
	int num_l = 0, num_r = 0;
	char* pivot = (char*)base;
	char* l_ptr = (char*)base;
	char* r_ptr = (char*)base + (num - 1) * size;
	while (l_ptr != r_ptr) {
		while (l_ptr < pivot) {
			if (cmp_func(l_ptr, pivot) == 1) break;
			l_ptr += size;
		}
		while (pivot < r_ptr) {
			if (cmp_func(pivot, r_ptr) == 1) break;
			r_ptr -= size;
		}
		swap_ele(l_ptr, r_ptr);
		if (l_ptr == pivot) {
			pivot = r_ptr;
		}
		else if (r_ptr == pivot) {
			pivot = l_ptr;
		}
	}
	num_l = (pivot - (char*)base) / size;
	num_r = num - num_l - 1;
	qsort_orig(base, num_l, size, cmp_func);
	qsort_orig(pivot + size, num_r, size, cmp_func);
}

void qsort_median_insert(void* base, size_t num, size_t size, _Cmpfun* cmp_func) {
	if (num <= MIN_NUM) {
		if (num > 1) {
			// insertion sort
			insert_sort(base, num, size, cmp_func);
		}
		return;
	}
	char* pivot = (char*)base + (num/2)*size;
	char* l_ptr = (char*)base;
	char* r_ptr = (char*)base + (num - 1) * size;
	if (cmp_func(l_ptr, r_ptr) == 1) swap_ele(l_ptr, r_ptr);
	if (cmp_func(l_ptr, pivot) == 1) swap_ele(l_ptr, pivot);
	if (cmp_func(pivot, r_ptr) == 1) swap_ele(pivot, r_ptr);
	int num_l = 0, num_r = 0;
	while (l_ptr != r_ptr) {
		while (l_ptr < pivot) {
			if (cmp_func(l_ptr, pivot) == 1) break;
			l_ptr += size;
		}
		while (pivot < r_ptr) {
			if (cmp_func(pivot, r_ptr) == 1) break;
			r_ptr -= size;
		}
		swap_ele(l_ptr, r_ptr);
		if (l_ptr == pivot) {
			pivot = r_ptr;
		}
		else if (r_ptr == pivot) {
			pivot = l_ptr;
		}
	}
	num_l = (pivot - (char*)base) / size;
	num_r = num - num_l - 1;
	qsort_median_insert(base, num_l, size, cmp_func);
	qsort_median_insert(pivot+size, num_r, size, cmp_func);
}

void qsort_median_insert_iter(void* base, size_t num, size_t size, _Cmpfun* cmp_func) {
	if (num <= MIN_NUM) {
		if (num > 1) {
			// insertion sort
			insert_sort(base, num, size, cmp_func);
		}
		return;
	}
	char* start = (char*)base;
	int n = num;
	char* pivot = (char*)base + (n / 2) * size;
	char* l_ptr = (char*)base;
	char* r_ptr = (char*)base + (n - 1) * size;
	if (cmp_func(l_ptr, r_ptr) == 1) swap_ele(l_ptr, r_ptr);
	if (cmp_func(l_ptr, pivot) == 1) swap_ele(l_ptr, pivot);
	if (cmp_func(pivot, r_ptr) == 1) swap_ele(pivot, r_ptr);
	int num_l = 0, num_r = 0;
	while (n > MIN_NUM) {
		while (l_ptr != r_ptr) {
			while (l_ptr < pivot) {
				if (cmp_func(l_ptr, pivot) == 1) break;
				l_ptr += size;
			}
			while (pivot < r_ptr) {
				if (cmp_func(pivot, r_ptr) == 1) break;
				r_ptr -= size;
			}
			swap_ele(l_ptr, r_ptr);
			if (l_ptr == pivot) {
				pivot = r_ptr;
			}
			else if (r_ptr == pivot) {
				pivot = l_ptr;
			}
		}
		num_l = (pivot - (char*)start) / size;
		num_r = n - num_l - 1;
		if (num_l < num_r) {
			qsort_median_insert_iter(start, num_l, size, cmp_func);
			n = num_r;
			if (n <= 1) break;
			start = l_ptr = pivot + size;
			r_ptr = l_ptr + (n - 1) * size;
		}
		else {
			qsort_median_insert_iter(pivot + size, num_r, size, cmp_func);
			n = num_l;
			if (n <= 1) break;
			r_ptr = pivot - size; 
			l_ptr = start;
		}
		pivot = l_ptr + (n / 2) * size;
		if (cmp_func(l_ptr, r_ptr) == 1) swap_ele(l_ptr, r_ptr);
		if (cmp_func(l_ptr, pivot) == 1) swap_ele(l_ptr, pivot);
		if (cmp_func(pivot, r_ptr) == 1) swap_ele(pivot, r_ptr);
	}
	if (start < (char*)base) start = (char*)base;
	if(n > 1) insert_sort(start, n, size, cmp_func);
}

int main(void) {
	FILE* fp_r, * fp_w;
	int funNum, n, i;
	char input_f[100], output_f[100];
	ELEMENT* in_arr;

	fp_r = fopen("HW_commands.txt", "r");
	if (fp_r == NULL) exit(1);
	fscanf(fp_r, "%d", &funNum);
	fscanf(fp_r, "%d", &n);
	fscanf(fp_r, "%s", input_f);
	fscanf(fp_r, "%s", output_f);
	fclose(fp_r);

	in_arr = (ELEMENT*)malloc(sizeof(ELEMENT) * n);
	
	fp_r = fopen(input_f, "rb");
	if (fp_r == NULL) exit(1);
	fread(in_arr, sizeof(ELEMENT), n, fp_r);
	fclose(fp_r);

	if (funNum >= 22) {
		if ((P_CAND_N - 1) * 2 > MIN_NUM-1) {
			fprintf(stderr, "reset 'P_CAND_N' and 'MIN_NUM' to meet below \n (P_CAND_N - 1) * 2 <= MIN_NUM-1 \n");
			exit(-1);
		}
	}

	if (funNum == 1) {
		CHECK_TIME_START;
		qsort(in_arr, n, sizeof(ELEMENT), score_comparison);
		CHECK_TIME_END(compute_time);
		printf("*** ELEMENT type of size %d: Time taken by qsort() = %.3fms\n", sizeof(ELEMENT), compute_time);
	}
	else if (funNum == 21) {
		CHECK_TIME_START;
		qsort_orig(in_arr, n, sizeof(ELEMENT), score_comparison);
		CHECK_TIME_END(compute_time);
		printf("*** ELEMENT type of size %d: Time taken by qsort_orig() = %.3fms\n", sizeof(ELEMENT), compute_time);
	}
	else if (funNum == 22) {
		CHECK_TIME_START;
		qsort_median_insert(in_arr, n, sizeof(ELEMENT), score_comparison);
		CHECK_TIME_END(compute_time);
		printf("*** ELEMENT type of size %d: Time taken by qsort_median_insert() = %.3fms\n", sizeof(ELEMENT), compute_time);
	}
	else if (funNum == 23) {
		CHECK_TIME_START;
		qsort_median_insert_iter(in_arr, n, sizeof(ELEMENT), score_comparison);
		CHECK_TIME_END(compute_time);
		printf("*** ELEMENT type of size %d: Time taken by qsort_median_inset_iter() = %.3fms\n", sizeof(ELEMENT), compute_time);
	}
	else exit(1);


	fp_w = fopen(output_f, "wb");
	if (fp_w == NULL) exit(1);
	fwrite(in_arr, sizeof(ELEMENT), n, fp_w);
	fclose(fp_w);

	free(in_arr);
	
	return 0;
}