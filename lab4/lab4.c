#include <stdio.h>
#include <stdlib.h>

FILE* fi;
FILE* fo;

struct CompleteTree{
	int Size;
	int nodeNum;
	int* Element;
};
typedef struct CompleteTree* Tree;

void Insert(Tree tree, int value);
void printPreorder(Tree tree, int index);
void printInorder(Tree tree, int index);
void printPostorder(Tree tree, int index);
void FreeTree(Tree tree);

void Insert(Tree tree, int value){
	if (tree->nodeNum == tree->Size){
		fprintf(fo, "Error! Tree is Full\n");
	}
	else {
		tree->Element[++tree->nodeNum] = value;
	}
}

void printPreorder(Tree tree, int index){
	if (index <= tree->nodeNum){
		fprintf(fo, "%d ", tree->Element[index]);
		printPreorder(tree, index*2);
		printPreorder(tree, index*2 + 1);
	}
}

void printInorder(Tree tree, int index){
	if (index <= tree->nodeNum){
		printInorder(tree, index*2);
		fprintf(fo, "%d ", tree->Element[index]);
		printInorder(tree, index*2 + 1);
	}
}

void printPostorder(Tree tree, int index){
	if (index <= tree->nodeNum){
		printPostorder(tree, index*2);
		printPostorder(tree, index*2 + 1);
		fprintf(fo, "%d ", tree->Element[index]);
	}
}

void FreeTree(Tree tree){
	free(tree->Element);
	free(tree);
}

int main(int argc, char* argv[]){
	fi = fopen(argv[1], "r");
	fo = fopen(argv[2], "wt");

	Tree tree = (Tree)malloc(sizeof(struct CompleteTree));
	int max, value;
	fscanf(fi, "%d", &max);
	tree->Element = (int*)malloc(sizeof(int)*(max+1));
	tree->Size = max;
	tree->nodeNum = 0;
	while (EOF != fscanf(fi, "%d", &value)){
		Insert(tree, value);
	}
	
	fprintf(fo, "Preorder: ");
	printPreorder(tree, 1);
	fprintf(fo, "\n");

	fprintf(fo, "Inorder: ");
	printInorder(tree, 1);
	fprintf(fo, "\n");

	fprintf(fo, "Postorder: ");
	printPostorder(tree, 1);
	fprintf(fo, "\n");
	FreeTree(tree);
}
