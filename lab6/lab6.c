#include <stdio.h>
#include <stdlib.h>

typedef struct AVLNode* Position;
typedef struct AVLNode* AVLTree;
typedef int ElementType;

FILE* fi;
FILE* fo;

struct AVLNode{
	ElementType Element;
	AVLTree left;
	AVLTree right;
	int Height;
};

int max(int a, int b);
int returnHeight(Position p);
AVLTree Insert(ElementType X, AVLTree T);
Position SingleRotateWithLeft(Position node);
Position SingleRotateWithRight(Position node);
Position DoubleRotateWithLeft(Position node);
Position DoubleRotateWithRight(Position node);
void printInorder(AVLTree T);
void deleteTree(AVLTree T);

int max(int a, int b){
	if (a >= b)
		return a;
	return b;
}

int returnHeight(Position p){
	if(p == NULL)
		return -1;
	return p->Height;
}

AVLTree Insert(ElementType X, AVLTree T){
	if(T == NULL){
		T = (AVLTree)malloc(sizeof(struct AVLNode));
		T->Element = X;
		T->Height = 0;
		T->left = NULL;
		T->right = NULL;
	}
	else if (X == T->Element){
		fprintf(fo, "[Error] %d already in the tree!\n" ,X);
	}
	else if (X < T->Element){
		T->left = Insert(X, T->left);

		if (returnHeight(T->left) - returnHeight(T->right) >= 2) {
			if (X < T->left->Element)
				T = SingleRotateWithLeft(T);
			else
				T = DoubleRotateWithLeft(T);
		}
	}
	else if (X > T->Element){
		T->right = Insert(X, T->right);

		if (returnHeight(T->right) - returnHeight(T->left) >= 2) {
			if (X > T->right->Element)
				T = SingleRotateWithRight(T);
			else
				T = DoubleRotateWithRight(T);
		}
	}
	
	T->Height = max(returnHeight(T->left), returnHeight(T->right)) + 1;
	return T;
}

Position SingleRotateWithLeft(Position node){
	Position newNode;
	newNode = node->left;
	node->left = newNode->right;
	newNode->right = node;

	node->Height = max(returnHeight(node->left), returnHeight(node->right)) + 1;
	newNode->Height = max(returnHeight(newNode->left), returnHeight(newNode->right)) + 1;

	return newNode;
}

Position SingleRotateWithRight(Position node){
	Position newNode;
	newNode = node->right;
	node->right = newNode->left;
	newNode->left = node;

	node->Height = max(returnHeight(node->left), returnHeight(node->right)) + 1;
	newNode->Height = max(returnHeight(newNode->left), returnHeight(newNode->right)) +1;

	return newNode;
}

Position DoubleRotateWithLeft(Position node){
	node->left = SingleRotateWithRight(node->left);

	return SingleRotateWithLeft(node);
}

Position DoubleRotateWithRight(Position node){
	node->right = SingleRotateWithLeft(node->right);

	return SingleRotateWithRight(node);
}

void printInorder(AVLTree T){
	if (T){
		printInorder(T->left);
		fprintf(fo, "%d(%d) ", T->Element, returnHeight(T));
		printInorder(T->right);
	}	
}

void deleteTree(AVLTree T){
	if (T){
		deleteTree(T->left);
		deleteTree(T->right);
		free(T);
	}
}

int main(int argc, char* argv[]){
	fi = fopen(argv[1], "r");
	fo = fopen(argv[2], "wt");

	int key;
	AVLTree T = NULL;

	while (EOF != fscanf(fi, "%d", &key)){
		T = Insert(key, T);
		printInorder(T);
		fprintf(fo, "\n");
	}

	deleteTree(T);
	
	fclose(fi);
	fclose(fo);

	return 0;
}
