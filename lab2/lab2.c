#include <stdio.h>
#include <stdlib.h>
typedef struct _node *PtrToNode;
typedef PtrToNode List;
typedef PtrToNode Position;
typedef int ElementType;
struct _node
{
	ElementType	element;
	Position	next;
} Node;

List MakeEmpty(List L);
int IsEmpty(List L);
int IsLast(Position P, List L);
void DeleteList(List L);

void Insert(ElementType X, List L, Position P);
void PrintList(List L);
void Delete(ElementType X, List L);
Position Find(ElementType X, List L);

FILE *output;

List MakeEmpty(List L){
	L = (List)malloc(sizeof(Node));
	L->next = NULL;
	return L;
}

int IsEmpty(List L){
	return L->next == NULL;
}

int IsLast(Position P, List L){
	return P->next == NULL;
}

Position Find(ElementType X, List L){
	Position p;
	p = L;
	while (p->next != NULL && p->next->element != X) {
		p = p->next;
	}
	
	return p;
}

void Insert(ElementType X, List L, Position P){
	Position tmp;
	tmp = (Position)malloc(sizeof(Node));
	if (tmp == NULL) {
		fprintf(output, "Deletion(%d): Out of space!\n", X);
		return;
	}
	tmp->element = X;
	tmp->next = P->next;
	P->next = tmp;
}

void Delete(ElementType X, List L){
	Position p, DP;
	p = Find(X, L);

	if (IsLast(p, L)) {
		fprintf(output, "Delete(%d): Element %d is not in the list\n", X, X);
		return;
	}
	
	DP = p->next;
	p->next = DP->next;
	free(DP);
}

void PrintList(List L){
	Position p;
	p = L->next;
	while (p != NULL){
		fprintf(output, "key: %d	   ", p->element);
		p = p->next;
	}
	fprintf(output, "\n");
}

void DeleteList(List L){
	Position p, tmp;

	p = L->next;
	L->next = NULL;
	while (p != NULL){
		tmp = p->next;
		free(p);
		p = tmp;
	}
}

int main(int argc, char *argv[]){
	char command;
	int key1, key2;
	FILE *input;
	Position header;
	Position tmp;
	input = fopen(argv[1], "r");
	output = fopen(argv[2], "wt");
	header = MakeEmpty(header);
	while(1) {
		command = fgetc(input);
		if(feof(input)) break;
		switch(command) {
		case 'i':
			fscanf(input, "%d %d", &key1, &key2);
			if (key2 == -1) {
				Insert(key1, header, header);
			}
			else {
				tmp = Find(key2, header);
				if (IsLast(tmp, header)) {
					fprintf(output, "Insertion(%d) Failed: cannot find the location to be inserted\n", key1);
					break;
				}
				Insert(key1, header, tmp->next);
			}
			break;
		case 'd':
			fscanf(input, "%d", &key1);
			Delete(key1, header);
			break;
		case 'f':
			fscanf(input, "%d", &key1);
			tmp = Find(key1, header);
			if(IsLast(tmp, header))
				fprintf(output,"Finding(%d) Failed: Element %d is not in the list\n", key1, key1);
			else {
				if(tmp->element > 0)
					fprintf(output, "Key of the previous node of %d is %d.\n", key1, tmp->element);
				else
					fprintf(output, "Key of the previous node of %d is header.\n", key1);
			}
			break;
		case 'p':
			PrintList(header);
			break;
		default:
			break;
		}
	}

	DeleteList(header);
	fclose(input);
	fclose(output);
	return 0;
}
