#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

double start, end;

typedef struct _edge {
	int u;
	int v;
	int key;
}Edge;

typedef struct _disjoint {
	int parent;
	int rank;
	int cnt;
	long long weight;
	int searched;
}Disjoint;

void adjust_minheap(Edge* heap, int root, int n);
Edge* pop(Edge* minheap, int* heapsize);
int find_set(Disjoint* dsj_set, int v);
void add_and_union_set(Disjoint* dsj_set, Edge* e);

int main(void)
{
	FILE* fp, *fp_r, *fp_w;
	char in_fn[128] = "Graphs_HW4/", out_fn[128] = "Graphs_HW4/", tmp[128];
	Edge* minheap;
	Disjoint* dsj_set;
	int heapsize;
	int scanned_edges = 0, k_scanned = 0;
	int mst_cnt = 0;
	int n_vertices;
	int n_edges;
	int MAX_WEIGHT;

	fp = fopen("Graphs_HW4/commands.txt", "r");
	if (fp == NULL) fprintf(stderr, "command file open error\n");
	fscanf(fp, "%s", tmp);
	strcat(in_fn, tmp);
	fscanf(fp, "%s", tmp);
	strcat(out_fn, tmp);
	printf("input file name: %s\n", in_fn);
	printf("output file name : % s\n", out_fn);

	fp_r = fopen(in_fn, "r");
	if (fp_r == NULL) fprintf(stderr, "input file open error\n");
	fp_w = fopen(out_fn, "w");
	if (fp_w == NULL) fprintf(stderr, "output file open error\n");

	fscanf(fp_r, "%d %d %d", &n_vertices, &n_edges, &MAX_WEIGHT);

	printf("vertices : %d  edges: %d  max_weight: %d\n", n_vertices, n_edges, MAX_WEIGHT);
	// initializing graph
	minheap = (Edge*)malloc(sizeof(Edge) * (n_edges + 1));
	heapsize = n_edges;
	dsj_set = (Disjoint*)malloc(sizeof(Disjoint) * (n_vertices));

	for (int i = 0; i <= n_vertices; i++) {
		dsj_set[i].parent = i;
		dsj_set[i].rank = 0;
		dsj_set[i].cnt = 1;
		dsj_set[i].weight = 0;
		dsj_set[i].searched = 0;
	}

	for (int i = 1; i <= n_edges; i++) {
		fscanf(fp_r, "%d %d %d", &minheap[i].u, &minheap[i].v, &minheap[i].key);
	}

	start = (double)clock() / CLOCKS_PER_SEC;
	for (int i = n_edges / 2; i >= 1; i--) {
		adjust_minheap(minheap, i, n_edges);
	}

	while (scanned_edges < n_vertices - 1 && heapsize > 0) {
		Edge* me = pop(minheap, &heapsize);
		k_scanned++;
		if (find_set(dsj_set, me->u) != find_set(dsj_set, me->v)) {
			scanned_edges++;
			add_and_union_set(dsj_set, me);
		}
	}
	end = (double)clock() / CLOCKS_PER_SEC;

	mst_cnt = n_vertices - scanned_edges;

	printf("CPU time = %.6lf\n", end-start);
	printf("k_scanned : %d\n\n", k_scanned);
	printf("the number of connected components: %d\n", mst_cnt);
	fprintf(fp_w, "%d\n", n_vertices - scanned_edges);
	for (int i = 0; i < n_vertices; i++) {
		int iroot = find_set(dsj_set, i);
		if (dsj_set[iroot].searched == 0) {
			printf("total vertices: %d, total weight: %lld\n",dsj_set[iroot].cnt, dsj_set[iroot].weight);
			fprintf(fp_w, "%d\t%lld\n", dsj_set[iroot].cnt, dsj_set[iroot].weight);
			dsj_set[iroot].searched = 1;
		}
	}
	
	fclose(fp);
	fclose(fp_r);
	fclose(fp_w);
	free(minheap);
	free(dsj_set);
	return 0;
}

void adjust_minheap(Edge* heap, int root, int n)
{
	int root_u = heap[root].u;
	int root_v = heap[root].v;
	int root_key = heap[root].key;
	int child = root * 2;
	while (child <= n) {
		if (child + 1 <= n) {
			if (heap[child + 1].key < heap[child].key) {
				child++;
			}
		}
		if (heap[child].key < root_key) {
			heap[child / 2] = heap[child];
			child *= 2;
		}
		else break;
	}
	heap[child / 2].u = root_u;
	heap[child / 2].v = root_v;
	heap[child / 2].key = root_key;
}

Edge* pop(Edge* minheap, int* heapsize)
{
	Edge tmp = minheap[1];
	int size = *heapsize;
	minheap[1] = minheap[size];
	minheap[size] = tmp;
	adjust_minheap(minheap, 1, size - 1);
	*heapsize = size - 1;
	return &minheap[size];
}


int find_set(Disjoint* dsj_set, int v)
{
	int x = v;
	while (x != dsj_set[x].parent) {
		x = dsj_set[x].parent;
	}
	dsj_set[v].parent = x;
	return x;
}

void add_and_union_set(Disjoint* dsj_set, Edge* e)
{
	int u = e->u;
	int v = e->v;
	int uroot = find_set(dsj_set, u);
	int vroot = find_set(dsj_set, v);
	if (dsj_set[uroot].rank > dsj_set[vroot].rank) {
		dsj_set[vroot].parent = uroot;
		dsj_set[uroot].cnt += dsj_set[vroot].cnt;
		dsj_set[uroot].weight += (dsj_set[vroot].weight + (long long)e->key);
	}
	else if (dsj_set[uroot].rank < dsj_set[vroot].rank) {
		dsj_set[uroot].parent = vroot;
		dsj_set[vroot].cnt += dsj_set[uroot].cnt;
		dsj_set[vroot].weight += (dsj_set[uroot].weight + (long long)e->key);
	}
	else {
		dsj_set[vroot].parent = uroot;
		dsj_set[uroot].rank++;
		dsj_set[uroot].cnt += dsj_set[vroot].cnt;
		dsj_set[uroot].weight += (dsj_set[vroot].weight + (long long)e->key);
	}
}
