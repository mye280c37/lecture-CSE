#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdlib.h>

#define DEBUG 0

typedef struct _info {
	int freq;
	int code;
	unsigned int bits;
} INFO;

typedef struct _node {
	int key;
	INFO* t_ptr;
	struct _node* left;
	struct _node* right;
	struct _node* next;
} NODE;

NODE* pop_min(NODE** list)
{
	NODE* min_node = *list;
	*list = min_node->next;
	return min_node;
}

void insert_node(NODE** list, NODE* new_node)
{
	NODE* cur = *list, *prev = NULL;
	while (cur != NULL) {
		if (new_node->key < cur->key) break;
		prev = cur;
		cur = cur->next;
	}
	if (prev != NULL) prev->next = new_node;
	else *list = new_node;
	new_node->next = cur;
}

void fill_code(NODE* root, int b,  int code, int bits) {
	if (root == NULL) return;
	code <<= 1;
	code += b;
	if (root->t_ptr != NULL) {
		root->t_ptr->bits = bits;
		root->t_ptr->code = code;
	}
	fill_code(root->left, 0, code, ++bits);
	fill_code(root->right, 1, code, bits);
}

void fprint_code(FILE *fp, int bits, int code) {
	if (bits == 0) return;
	fprint_code(fp, bits - 1, code/2);
	fprintf(fp, "%d", code%2);
}

void dealloc_tree(NODE* root) {
	if (root == NULL) return;
	dealloc_tree(root->left);
	dealloc_tree(root->right);
	free(root);
}

int main()
{
	FILE* fp_r, * fp_w;
	INFO ascii_table[128];
	NODE* root, * tmp_node, *min1, *min2;
	int i, j, char_cnt = 0, tree_cnt = 0, bits_cnt;
	char tmp, * encoding;
	unsigned int total_bits = 0, total_bytes;
	int* bits_arr;

	fp_r = fopen("P3_input_ASCII.txt", "r");
	if (fp_r == NULL) exit(1);
	fp_w = fopen("P3_output_codewords.txt", "w");
	if (fp_w == NULL) exit(1);

	// initialize table
	for (i = 0; i < 128; i++) {
		ascii_table[i].code = 0;
		ascii_table[i].freq = 0;
		ascii_table[i].bits = 0;
	}

	// read input text and count char
	while (fscanf(fp_r, "%c", &tmp) != -1) {
		if (ascii_table[(int)tmp].freq == 0) tree_cnt++;
		(ascii_table[(int)tmp].freq)++;
		char_cnt++;
	}

	// initialize single node tree
	root = NULL;
	for (i = 0; i < 128; i++) {
		if (ascii_table[i].freq != 0) {
			tmp_node = (NODE*)malloc(sizeof(NODE));
			tmp_node->t_ptr = &ascii_table[i];
			tmp_node->key = ascii_table[i].freq;
			tmp_node->left = tmp_node->right = tmp_node-> next = NULL;
			insert_node(&root, tmp_node);
		}
	}
	// MaxHeap
	for (i = 0; i < tree_cnt-1; i++) {
		min1 = pop_min(&root);
		min2 = pop_min(&root);
		tmp_node = (NODE*)malloc(sizeof(NODE));
		tmp_node->key = min1->key + min2->key;
		tmp_node->t_ptr = NULL;
		tmp_node->left = min1;
		tmp_node->right = min2;
		tmp_node->next = NULL;
		insert_node(&root, tmp_node);
	}
	// get code using tree search
	fill_code(root, 0, 0, 0);

	// write P3_output_codewords.txt
	for (i = 0; i < 128; i++) {
		if (ascii_table[i].freq > 0) {
			fprintf(fp_w, "%c ", i);
			fprint_code(fp_w, ascii_table[i].bits, ascii_table[i].code);
			fprintf(fp_w, "  %.2f\n", (float)ascii_table[i].freq / char_cnt * 100.0);
		}
	}

	fclose(fp_r);
	fclose(fp_w);

	fp_r = fopen("P3_input_ASCII.txt", "r");
	if (fp_r == NULL) exit(1);
	fp_w = fopen("P3_output_encoded.bin", "wb");
	if (fp_w == NULL) exit(1);

	// get bits_arr of input txt
	bits_arr = (int*)malloc(sizeof(int));
	while (fscanf(fp_r, "%c", &tmp) != -1) {
		total_bits += ascii_table[(int)tmp].bits;
		bits_arr = (int*)realloc(bits_arr, total_bits*sizeof(int));
		if (bits_arr == NULL) {
			fprintf(stderr, "memory allocation error\n");
			exit(1);
		}
		int dec_code = ascii_table[(int)tmp].code;
		for (i = 0; i < ascii_table[(int)tmp].bits; i++) {
			bits_arr[total_bits -1 - i] = dec_code%2;
			dec_code /= 2;
		}
	}

#ifdef DEBUG
	printf("total bits: %d\n", total_bits);
	printf("total bytes: %d\n", total_bytes=(total_bits+7)/8);
#endif

	bits_arr = (int*)realloc(bits_arr, total_bytes * 8 * sizeof(int));

	encoding = (char*)calloc(total_bytes, sizeof(char));
	j = 0;
	bits_cnt = total_bytes * 8 - total_bits;
	for (i = 0; i < total_bits; i++) {
		encoding[j] <<= 1;
		encoding[j] += bits_arr[i];
		bits_cnt++;
		if (bits_cnt % 8 == 0) {
			j++;
		}
	}
#ifdef DEBUG
	for (i = 0; i < total_bytes; i++) printf("%d: %d \n", i, encoding[i]);
#endif

	fwrite(&total_bits, sizeof(unsigned), 1, fp_w);
	fwrite(&total_bytes, sizeof(unsigned), 1, fp_w);
	fwrite(encoding, sizeof(char), total_bytes, fp_w);

	fclose(fp_r);
	fclose(fp_w);

	dealloc_tree(root);
	free(bits_arr);
	free(encoding);

	return 0;
}