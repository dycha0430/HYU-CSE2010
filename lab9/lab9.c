#include <stdio.h>
#include <stdlib.h>
#include <string.h>

FILE *fi, *fo;
int nodeNum;

typedef struct _Queue* Queue;
typedef struct _Graph* Graph;

struct _Queue{
	int* key;
	int first;
	int rear;
	int qsize;
	int max_queue_size;
};

struct _Graph{
	int* node;
	int size;
	int** matrix;
};

void SequenceSort(int* arr, int n, Graph G);
Graph CreateGraph(int* nodes);
void InsertEdge(Graph G, int a, int b);
void TopSort(Graph G);
Queue MakeNewQueue(int X);
void Enqueue(Queue Q, int X);
int Dequeue(Queue Q);
void CheckIndegree(Graph G, int* in_degrees);

void SequenceSort(int* arr, int n, Graph G){
	int tmp;
	for (int i = 0; i < n; i++){
		for (int j = i; j < n; j++){
			if (G->node[arr[i]]>G->node[arr[j]]){
				tmp = arr[i];
				arr[i] = arr[j];
				arr[j] = tmp;
			}
		}
	}
}

Graph CreateGraph(int* nodes){
	Graph graph = (Graph)malloc(sizeof(struct _Graph));
	graph->node = nodes;
	graph->size = nodeNum;

	graph->matrix = (int**)malloc(graph->size*sizeof(int*));
	for (int i = 0; i < graph->size; i++){
		graph->matrix[i] = (int*)malloc(graph->size*sizeof(int));
		memset(graph->matrix[i], 0, sizeof(int)*graph->size);
	}

	return graph;
}


void InsertEdge(Graph G, int a, int b){
	int ai, bi;

	for (int i = 0; i < G->size; i++){
		if (G->node[i] == a)
			ai = i;
		else if (G->node[i] == b)
			bi = i;
	}
	G->matrix[ai][bi] = 1;
}

void TopSort(Graph G){
	Queue Q = MakeNewQueue(G->size);
	int a, b, dequeue_num, enqueue_num = 0;
	int node_num = G->size;
	int* EnqueueNodes = (int*)malloc(node_num*sizeof(int));
	int* in_degrees = (int*)malloc(node_num*sizeof(int));
	memset(in_degrees, 0, sizeof(int)*node_num);
	
	CheckIndegree(G, in_degrees);

	for (int i = 0; i < node_num; i++){
		if (in_degrees[i] == 0){
			EnqueueNodes[enqueue_num++] = i;
		}
	}

	SequenceSort(EnqueueNodes, enqueue_num, G);
	for (int i = 0; i < enqueue_num; i++){
		Enqueue(Q, EnqueueNodes[i]);
		in_degrees[EnqueueNodes[i]] = -1;
	}

	while (Q->qsize != 0){
		enqueue_num = 0;
		dequeue_num = Dequeue(Q);
		for (int i = 0; i < node_num; i++){
			if (G->matrix[dequeue_num][i] == 1){
				in_degrees[i]--;
			}
		}
		fprintf(fo, "%d ", G->node[dequeue_num]);

		for (int i = 0; i < node_num; i++){
			if (in_degrees[i] == 0){
				EnqueueNodes[enqueue_num++] = i;
			}
		}
		SequenceSort(EnqueueNodes, enqueue_num, G);
		for (int i = 0; i < enqueue_num; i++){
			Enqueue(Q, EnqueueNodes[i]);
			in_degrees[EnqueueNodes[i]] = -1;
		}
	}
	free(EnqueueNodes);
	free(in_degrees);
}

Queue MakeNewQueue(int X){
	Queue queue = (Queue)malloc(sizeof(struct _Queue));
	queue->max_queue_size = X;
	queue->first = 0;
	queue->rear = -1;
	queue->qsize = 0;
	queue->key = (int*)malloc(X*sizeof(int));
	
	return queue;
}

void Enqueue(Queue Q, int X){
	if (Q->rear == Q->max_queue_size - 1){
		fprintf(fo, "Queue is Full\n");
		return;
	}
	Q->key[++Q->rear] = X;
	Q->qsize++;
}

int Dequeue(Queue Q){
	if (Q->first > Q->rear){
		fprintf(fo, "Queue is Empty\n");
	}
	Q->qsize--;
	return Q->key[Q->first++];
}

void CheckIndegree(Graph G, int* in_degrees){
	int inDegree;

	for (int i = 0; i < G->size; i++){
		inDegree = 0;
		for (int j = 0; j < G->size; j++){
			if (G->matrix[j][i] == 1){
				inDegree++;
			}
		}
		in_degrees[i] = inDegree;
	}
}

int main(int argc, char* argv[]){
	fi = fopen(argv[1], "r");
	fo = fopen(argv[2], "wt");

	Graph G;
	int i = 0, j = 0, a, b, *nodes;
	char node, *edges, *ac, *bc;
	
	edges = (char*)malloc(5*sizeof(char));
	nodes = (int*)malloc(9*sizeof(int));
	nodeNum = 0;

	while (fscanf(fi, "%c", &node) && node != '\n' && node != 13){
		if (node != ' '){
			nodes[i++] = node - '0';
			nodeNum++;
		}
	}

	G = CreateGraph(nodes);
	
	while (fscanf(fi, "%s", edges) != EOF){
		ac = strtok(edges, "-");
		bc = strtok(NULL, "-");
		a = atoi(ac);
		b = atoi(bc);
		InsertEdge(G, a, b);
	}

	fprintf(fo, "  ");
	for (i = 0; i < nodeNum; i++){
		fprintf(fo, "%d ", G->node[i]);
	}
	fprintf(fo, "\n");

	for (i = 0; i < nodeNum; i++){
		fprintf(fo, "%d ", G->node[i]);
		for (j = 0; j < nodeNum; j++){
			fprintf(fo, "%d ", G->matrix[i][j]);
		}
		fprintf(fo, "\n");
	}
	fprintf(fo, "\n");

	TopSort(G);

	free(nodes);
	free(edges);
}

