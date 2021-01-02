#include <stdio.h>
#include <stdlib.h>

FILE* fi;
FILE* fo;

typedef struct HeapStruct{
	int Capacity;
	int Size;
	int *Element;
}Heap;

Heap* CreateHeap(int heapSize);
void Insert(Heap *heap, int value);
int Find(Heap *heap, int value);
int DeleteMax(Heap *heap);
void PrintHeap(Heap *heap);

Heap* CreateHeap(int heapSize){
	Heap* heap = (Heap*)malloc(sizeof(Heap));
	
	heap->Capacity = heapSize;
	heap->Size = 0;
	heap->Element = (int*)malloc((heapSize+1)*sizeof(int));

	return heap;	
}

void Insert(Heap *heap, int value){
	int i;
	
	if (heap->Size >= heap->Capacity){
		fprintf(fo, "Insert Error : heap is full\n");
		return;
	}
	else if (Find(heap, value)){
		fprintf(fo, "%d is already in the heap\n", value);
		return;
	}
	
	for (i = ++heap->Size; i > 1 && heap->Element[i/2] < value; i /= 2){
		heap->Element[i] = heap->Element[i/2]; 
	}
	heap->Element[i] = value;
	fprintf(fo, "insert %d\n", value);
}

int Find(Heap *heap, int value){
	for (int i = 1; i <= heap->Size; i++){
		if (heap->Element[i] == value)
			return 1;
	}
	return 0;
}

int DeleteMax(Heap *heap){
	int max_element, last_element, child_element, i;

	max_element = heap->Element[1];
	last_element = heap->Element[heap->Size--];

	for (i = 1; i * 2 <= heap->Size; i = child_element){
		child_element = i * 2;
		if (child_element < heap->Size && heap->Element[child_element + 1] > heap->Element[child_element]){
			child_element++;
		}

		if (last_element < heap->Element[child_element])
			heap->Element[i] = heap->Element[child_element];
		else 
			break;
	}
	heap->Element[i] = last_element;
	return max_element;
}

void PrintHeap(Heap *heap){
	if (heap == NULL || heap->Size == 0){
		fprintf(fo, "Print Error : heap is empty\n");
		return;
	}

	for (int i = 1; i <= heap->Size; i++){
		fprintf(fo, "%d ", heap->Element[i]);
	}
	fprintf(fo, "\n");
}

int main(int argc, char* argv[]){
	fi = fopen(argv[1], "r");
	fo = fopen(argv[2], "wt");

	Heap* heap;
	char comm;
	int key;

	while (EOF != fscanf(fi, "%c", &comm)){
		if (comm == 'n'){
			fscanf(fi, "%d", &key);
			heap = CreateHeap(key);
		}
		else if (comm == 'i'){
			fscanf(fi, "%d", &key);
			Insert(heap, key);
		}
		else if (comm == 'f'){
			fscanf(fi, "%d", &key);
			if (Find(heap, key))
				fprintf(fo, "%d is in the heap\n", key);
			else
				fprintf(fo, "%d is not in the heap\n", key);
		}
		else if (comm == 'd'){
			if (heap == NULL || heap->Size == 0){
				fprintf(fo, "Delete Error : heap is empty\n");
			}
			else {
				fprintf(fo, "%d deleted\n", DeleteMax(heap));
			}
		}
		else if (comm == 'p'){
			PrintHeap(heap);
		}
	}

	free(heap->Element);
	free(heap);

	return 0;
}
