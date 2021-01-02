#include <stdio.h>
#include <stdlib.h>
#include <string.h>

FILE *fo;

typedef struct ListNode *Position;
typedef Position List;
typedef struct HashTbl *HashTable;

struct ListNode{
	int Element;
};

struct HashTbl{
	int TableSize;
	List* TheLists;
};

void Insert(HashTable H, int value, int solution);
void Delete(HashTable H, int value, int solution);
int Find(HashTable H, int value, int solution);
void printTable(HashTable H);
int Hash(int value, int Size, int i, int solution);

void Insert(HashTable H, int value, int solution){
	int hashKey, i = 0;
	if (Find(H, value, solution) != -1){
		fprintf(fo, "Already exists.\n");
		return;
	}
	
	hashKey = Hash(value, H->TableSize, i, solution);

	while (H->TheLists[hashKey]->Element != 0 && H->TheLists[hashKey]->Element != -1){
		hashKey = Hash(value, H->TableSize, ++i, solution);
	}
	
	H->TheLists[hashKey]->Element = value;
	fprintf(fo, "Inserted %d\n", value);
}

void Delete(HashTable H, int value, int solution){
	int hashKey;

	hashKey = Find(H, value, solution);
	if (hashKey == -1){
		fprintf(fo, "%d not exists.\n", value);
		return;
	}

	H->TheLists[hashKey]->Element = -1;
	
	fprintf(fo, "Deleted %d\n", value);
}

int Find(HashTable H, int value, int solution){
	int hashKey, i = 0, k = 0;

	hashKey = Hash(value, H->TableSize, i, solution);
	
	while (H->TheLists[hashKey]->Element != value && H->TheLists[hashKey]->Element != 0 && k < H->TableSize){
		hashKey = Hash(value, H->TableSize, ++i, solution);
		k++;
	}
	
	if (H->TheLists[hashKey]->Element != value){
		hashKey = -1;
	}

	return hashKey;
}

void printTable(HashTable H){
	for (int i = 0; i < H->TableSize; i++){
		if (H->TheLists[i]->Element == -1 || H->TheLists[i]->Element == 0)
			fprintf(fo, "0 ");
		else
			fprintf(fo, "%d ", H->TheLists[i]->Element);
	}
	fprintf(fo, "\n");
}

int Hash(int value, int Size, int i, int solution){
	int hashKey = value;

	if (solution == 1){
		hashKey += i;
	}
	else if (solution == 2){
		hashKey += (i*i);
	}

	hashKey = hashKey % Size;
	return hashKey;
}

void main(int argc, char* argv[]){
	FILE *fi = fopen(argv[1], "r");
	fo = fopen(argv[2], "wt");
	
	char ord;
	char solution[10];
	int size, value, sol, found;
	HashTable H = (HashTable)malloc(sizeof(struct HashTbl));

	fgets(solution, sizeof(solution), fi);
	fscanf(fi, "%d", &size);

	H->TableSize = size;
	H->TheLists = (List*)malloc(sizeof(List)*size);
	
	for (int i = 0; i < size; i++){
		H->TheLists[i] = (List)malloc(sizeof(struct ListNode));
		H->TheLists[i]->Element = 0;
	}
	
	if (!strcmp(solution, "Linear")) sol = 1;
        else sol = 2;
	
	while (EOF != fscanf(fi, "%c", &ord)){
		if (ord == 'i'){
			fscanf(fi, "%d", &value);
			Insert(H, value, sol);
		}
		else if (ord == 'd'){
			fscanf(fi, "%d", &value);
			Delete(H, value, sol);
		}
		else if (ord == 'f'){
			fscanf(fi, "%d", &value);
			found = Find(H, value, sol);
			if (found == -1)
				fprintf(fo, "Not found.\n");
			else
				fprintf(fo, "found in %d.\n", found); 
		}
		else if (ord == 'p'){
			printTable(H);
		}
	}
	
	for (int i = 0; i < size; i++){
		free(H->TheLists[i]);
	}
	free(H->TheLists);
	free(H);
}
