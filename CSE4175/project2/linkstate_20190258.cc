#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

#define INFINIT 999
#define NEXT 0
#define COST 1

typedef struct node {
	int id;
	int cost;
	struct node* next;
}NODE;

typedef struct graph {
	int size;
	NODE** adj_list;
}GRAPH;

NODE* createNode(int id, int cost); 
GRAPH* createNetwork(FILE* tf);
int*** createRoutingTable(GRAPH* network);

void deleteNetwork(GRAPH* network);
void deleteTable(int size, int*** table);

int checkAllVisited(int *visited, int size);
int getMinNode(int **table, int *visited, int size);
void setRoutingTable(GRAPH* network, int*** table);

void transmit(FILE* of, int src, int dst, char* msg, int*** table);

void changeAdjacencyList(NODE **adj_list, int id, int cost);
void changeNetwork(GRAPH* network, int u, int v, int cost);

int readMessage(FILE* mf, int* p_src, int* p_dst, char* msg);
int readChangeInfo(FILE* cf, int* p_u, int* p_v, int* p_cost);

void printNetwork(GRAPH *network);
void printRoutingTable(int*** table, int size);
void writeRoutingTable(FILE* of, int*** table, int size);

int main(int argc, char** argv)
{
	if (argc != 4){
		fprintf(stderr, "usage: distvec topologyfile messagesfile changesfile\n");
		return -1;
	}

	FILE *tf, *mf, *cf, *of;
	
	tf = fopen(argv[1], "r");
	mf = fopen(argv[2], "r");
	cf = fopen(argv[3], "r");
	of = fopen("output_ls.txt", "w");
	if(tf==NULL || mf==NULL || cf==NULL) {
		fprintf(stderr, "Error: open input file.\n");
		return -1;
	}

	GRAPH *network;
	int ***table;
	
	network = createNetwork(tf);
	table = createRoutingTable(network);
	setRoutingTable(network, table);

	while(1){
		writeRoutingTable(of, table, network->size);
		int src, dst;
		char msg[1005];
		fseek(mf, 0, SEEK_SET);
		while(readMessage(mf, &src, &dst, msg) != -1){
			transmit(of, src, dst, msg, table);
		}
		fprintf(of, "\n");
		int u, v, cost;
		if(readChangeInfo(cf, &u, &v, &cost) != -1){
			changeNetwork(network, u, v, cost);
			deleteTable(network->size, table);
			table = createRoutingTable(network);
			setRoutingTable(network, table); 
		}
		else break;
	}

	printf("Complete. Output file written to output_ls.txt.\n");

	fclose(tf);
	fclose(mf);
	fclose(cf);
	fclose(of);	

	deleteTable(network->size, table);
	deleteNetwork(network);

	return 0;
}

NODE* createNode(int id, int cost){
	NODE* tmp = (NODE*)malloc(sizeof(NODE));
	tmp->id = id;
	tmp->cost = cost;
	tmp->next = 0;
	return tmp;
}

GRAPH* createNetwork(FILE* tf) {
	GRAPH* network = (GRAPH*)malloc(sizeof(GRAPH));
	int size, u, v, cost;

	fscanf(tf, "%d", &size);
	network->size = size;
	network->adj_list = (NODE**)calloc(size, sizeof(NODE*));
	NODE *tmp, **end_addr;
	
	end_addr = (NODE**)calloc(size, sizeof(NODE*));

	while(fscanf(tf, "%d %d %d", &u, &v, &cost) != -1){
		tmp = createNode(v, cost);
		if(end_addr[u]==0) network->adj_list[u] = tmp;
		else end_addr[u]->next = tmp;
		end_addr[u]=tmp;
		
		tmp = createNode(u, cost);
		if(end_addr[v]==0) network->adj_list[v] = tmp;
		else end_addr[v]->next = tmp;
		end_addr[v]=tmp;
	}
	
	free(end_addr);
	return network;
}

int*** createRoutingTable(GRAPH* network) {
	int i,j,***table, size=network->size;
	table = (int***)malloc(sizeof(int**)*size);
	for(i=0; i<size; i++){
		table[i] = (int**)malloc(sizeof(int*)*size);
		for (j=0; j<size; j++){
			table[i][j] = (int*)malloc(sizeof(int)*2);
			table[i][j][NEXT] = INFINIT;
			table[i][j][COST] = INFINIT;
			if(i==j){
				table[i][j][NEXT] = i;
				table[i][j][COST] = 0;
			}
		}
	}

	NODE *tmp;
	for(i=0; i<network->size; i++){
		tmp = network->adj_list[i];
		while(tmp != 0){
			table[i][tmp->id][NEXT] = tmp->id;
			table[i][tmp->id][COST] = tmp->cost;
			tmp = tmp->next;
		}
	}

	return table;
}

void deleteNetwork(GRAPH* network) {
	NODE *tmp, *tmp2;
	for(int i=0; i<network->size; i++)
	{
		tmp = network->adj_list[i];
		while(tmp != 0){
			tmp2 = tmp;
			tmp = tmp->next;
			free(tmp2);
		}
	}
	free(network);
}

void deleteTable(int size, int*** table) {
	for(int i=0; i<size; i++){
		for(int j=0; j<size; j++){
			free(table[i][j]);
		}
		free(table[i]);
	}
	free(table);
}

int checkAllVisited(int *visited, int size){
	for(int i=0; i<size; i++){
		if(visited[i] == 0) return 0;
	}
	return 1;
}

int getMinNode(int **table, int *visited, int size){
	int i, id = -1, min_cost = INFINIT;
	for(i=0; i<size; i++){
		if(visited[i]) continue;
		if(table[i][COST] == INFINIT) continue;
		// tie-breaking rule2
		if(table[i][COST] < min_cost){
			id = i;
			min_cost = table[i][COST];
		}
	}
	return id;
}

void setRoutingTable(GRAPH* network, int*** table) {
	int i, j, size=network->size, *visited, next, tmp_cost, *parent;
	NODE *tmp;

	for(i=0; i<size; i++){
		parent = (int*)malloc(sizeof(int)*size);
		for(j=0; j<size; j++) parent[j] = table[i][j][NEXT];
		visited = (int*)calloc(size, sizeof(int));
		visited[i] = 1;
		while(checkAllVisited(visited, size) != 1){
			next = getMinNode(table[i], visited, size);
			if(next == INFINIT) break;
			visited[next] = 1;
			// update table
			tmp = network->adj_list[next];
			tmp_cost = table[i][next][COST];
			while(tmp != 0){
				if(tmp->id != i && visited[tmp->id]==0){
					if(tmp_cost + tmp->cost <= table[i][tmp->id][COST]){
						// tie-breaking rule3
						if(tmp_cost + tmp->cost == table[i][tmp->id][COST]){
							if(next < parent[tmp->id]){
								table[i][tmp->id][NEXT] = table[i][next][NEXT];
								parent[tmp->id] = next;
							}
						}else{
							table[i][tmp->id][NEXT] = table[i][next][NEXT];
							table[i][tmp->id][COST] = tmp_cost + tmp->cost;
							parent[tmp->id] = next;
						}
					}
				} 
				tmp = tmp->next;
			}
		}
		free(visited);
	}
	
}

void transmit(FILE* of, int src, int dst, char* msg, int*** table) {
	fprintf(of, "from %d to %d ", src, dst);
	int cost = table[src][dst][COST], hop = src;
	if (cost == INFINIT) {
		fprintf(of, "cost infinite hops unreachable message %s\n", msg);
		return;
	}
	fprintf(of, "cost %d hops %d ", cost, hop);
	while(1){
		hop = table[hop][dst][NEXT];
		if(hop == dst) break;
		fprintf(of, "%d ", hop);
	}
	fprintf(of, "message %s", msg);
}

void changeAdjacencyList(NODE **adj_list, int id, int cost){
	NODE *tmp = *adj_list, *pre = NULL;
	while(tmp != 0){
		if(tmp->id == id) break;
		pre = tmp;
		tmp = tmp->next;
	}
	if(cost + INFINIT == 0){
		if(pre!=NULL) {
			pre->next = tmp->next;
		}
		else *adj_list = tmp->next;
		free(tmp);
		return;
	}
	if(tmp == 0){
		tmp = createNode(id, cost);
		if(pre!=NULL) pre->next = tmp;
	}	
	else tmp->cost = cost;
}

void changeNetwork(GRAPH* network, int u, int v, int cost){
	changeAdjacencyList(&(network->adj_list[u]), v, cost);
	changeAdjacencyList(&(network->adj_list[v]), u, cost);
}

int readMessage(FILE* mf, int* p_src, int* p_dst, char* msg) {
	int cnt = 0;
	char buf[1005], *arg1=NULL, *arg2=NULL, *ptr=NULL;

	ptr = fgets(buf, 100, mf);
	if(ptr==NULL) return -1;
	ptr = buf;
	arg1 = buf;
	for(;*ptr!='\0';ptr++){
		if(*ptr == ' ') {
			*ptr = '\0';
			cnt++;
		}
		if(cnt == 1) arg2 = ptr;
		if(cnt == 2) break;
	}

	if(p_src == NULL || p_dst == NULL) return -1; 
	*p_src = atoi(arg1);
	*p_dst = atoi(arg2);

	strcpy(msg, ptr+1);
	return 0;
}

int readChangeInfo(FILE* cf, int* p_u, int* p_v, int* p_cost) {
	int u, v, cost;

	if(fscanf(cf, "%d %d %d", &u, &v, &cost) != -1){
		*p_u = u;
		*p_v = v;
		*p_cost = cost;
		return 0;
	}
	
	return -1;
}

void printNetwork(GRAPH *network){
	NODE *tmp;
	printf("the number of hops: %d\n", network->size);
	for(int i=0; i<network->size; i++){
		printf("< %d's adj list>\n", i);
		tmp = network->adj_list[i];
		while(tmp != 0){
			printf("  id: %d cost: %d\n", tmp->id, tmp->cost);
			tmp = tmp->next;
		}
	}
}

void printRoutingTable(int*** table, int size) {
	int i, j;
	for(i=0; i<size; i++){
		for(j=0; j<size; j++){
			printf("%d %d %d\n", j, table[i][j][NEXT], table[i][j][COST]);
		}
		printf("\n");
	}
}

void writeRoutingTable(FILE* of, int*** table, int size) {
	int i, j;
	for(i=0; i<size; i++){
		for(j=0; j<size; j++){
			if(table[i][j][COST] == INFINIT) continue;
			fprintf(of, "%d %d %d\n", j, table[i][j][NEXT], table[i][j][COST]);
		}
		fprintf(of, "\n");
	}
}