#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#define inf 1000000000
FILE* fo;
typedef struct Node{
	int vertex;
	int dist;
	int prev;
}Node;

typedef struct Graph{
	int size;
	int** vertices;
	Node* nodes;
}Graph;

typedef struct Heap{
	int Capacity;
	int Size;
	Node* Element;
}Heap;

Graph* CreateGraph(int size);
void printShortestPath(Graph* g);
Heap* createMinHeap(int heapSize);
void insertToMinHeap(Heap* minHeap, int vertex, int distance);
Node deleteMin(Heap* minHeap);

Graph* CreateGraph(int size){
	Graph* G = (Graph*)malloc(sizeof(Graph));
	G->size = size;
	G->vertices = (int**)malloc(sizeof(int*)*size);
	for (int i = 0; i < size; i++){
		G->vertices[i] = (int*)malloc(sizeof(int)*size);
	}

	G->nodes = (Node*)malloc(sizeof(Node)*size);
	for (int i = 1; i < size; i++){
		G->nodes[i].vertex = i;
		G->nodes[i].dist = inf;
		G->nodes[i].prev = -1;
	}
	G->nodes[1].dist = 0;
	
	for (int i = 1; i < size; i++){
		for (int j = 1; j < size; j++){
			G->vertices[i][j] = inf;
		}
	}

	return G;
}

void printShortestPath(Graph* g){
	Heap *h = createMinHeap(g->size);
	Node u;
	int* found = (int*)malloc(sizeof(int)*g->size);
	for (int i = 0; i < g->size; i++){
		found[i] = 0;
	}
	found[1] = 1;

	for (int i = 2; i < g->size; i++){
		if (g->vertices[1][i] != inf){
			g->nodes[i].dist = g->vertices[1][i];
			g->nodes[i].prev = 1;
			insertToMinHeap(h, g->nodes[i].vertex, g->nodes[i].dist);
		}
	}

	while(h->Size != 0){
		u = deleteMin(h);
		found[u.vertex] = 1;
		for (int i = 2; i < g->size; i++){
			if (u.dist + g->vertices[u.vertex][i] < g->nodes[i].dist && !found[i]){
				g->nodes[i].dist = u.dist + g->vertices[u.vertex][i];
				g->nodes[i].prev = u.vertex;
				insertToMinHeap(h, g->nodes[i].vertex, g->nodes[i].dist);
			}
		}
	}

	for (int i = 2; i < g->size; i++){
		int this = i, j = 0;
		int* path = (int*)malloc(sizeof(int)*g->size);
		while (g->nodes[this].prev != -1){
			path[j++] = g->nodes[this].vertex;
			this = g->nodes[this].prev;
		}
		
		if (j == 0){
			fprintf(fo, "Cannot reach to node %d.\n", this);
		}
		else{
			path[j] = 1;
			for (int k = j; k > 0; k--){
				fprintf(fo, "%d->", path[k]);	
			}
			fprintf(fo, "%d ", path[0]);
			fprintf(fo, "(cost : %d)\n", g->nodes[i].dist);
		}
	}
}

Heap* createMinHeap(int heapSize){
        Heap* heap = (Heap*)malloc(sizeof(Heap));

        heap->Capacity = heapSize;
        heap->Size = 0;
        heap->Element = (Node*)malloc((heapSize+1)*sizeof(Node));

        return heap;
}

void insertToMinHeap(Heap* minHeap, int vertex, int distance){
        int i;

        for (i = ++minHeap->Size; i > 1 && minHeap->Element[i/2].dist > distance; i /= 2){
                minHeap->Element[i] = minHeap->Element[i/2];
        }
        minHeap->Element[i].vertex = vertex;
	minHeap->Element[i].dist = distance;
}

Node deleteMin(Heap* minHeap){
        int child_element, i;
	Node min_element, last_element;

        min_element = minHeap->Element[1];
        last_element = minHeap->Element[minHeap->Size--];

        for (i = 1; i * 2 <= minHeap->Size; i = child_element){
                child_element = i * 2;
                if (child_element < minHeap->Size && minHeap->Element[child_element + 1].dist < minHeap->Element[child_element].dist){
                        child_element++;
                }

                if (last_element.dist > minHeap->Element[child_element].dist)
                        minHeap->Element[i] = minHeap->Element[child_element];
                else
                        break;
        }
        minHeap->Element[i] = last_element;
        return min_element;
}

void main(int argc, char* argv[]){
	FILE *fi = fopen(argv[1], "r");
	fo = fopen(argv[2], "wt");
	Graph* g;

	int size;
	fscanf(fi, "%d\n", &size);
	g = CreateGraph(size+1);
	char temp = 0;
	while (temp != EOF){
		int node1, node2, weight;
		fscanf(fi, "%d-%d-%d", &node1, &node2, &weight);
		g->vertices[node1][node2] = weight;
		temp = fgetc(fi);
	}
	printShortestPath(g);
}
