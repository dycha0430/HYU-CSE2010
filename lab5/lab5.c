#include <stdio.h>
#include <stdlib.h>

FILE* fi;
FILE* fo;

typedef struct BinarySearchTree* Tree;

struct BinarySearchTree{
	int value;
	Tree left;
	Tree right;
};

Tree insertNode(Tree root, int key);
Tree findNode(Tree root, int key);
void printInorder(Tree root);
Tree deleteNode(Tree root, int key);
void deleteTree(Tree root);

Tree insertNode(Tree root, int key){
	if (root == NULL){
		root = (Tree)malloc(sizeof(struct BinarySearchTree));
		root->value = key;
		root->left = root->right = NULL;
	}
	else if (key < root->value){
		root->left = insertNode(root->left, key);
	}
	else if (key > root->value){
		root->right = insertNode(root->right, key);
	}
	else{
		fprintf(fo, "%d already exists\n", key);
	}
	
	return root;
}

Tree findNode(Tree root, int key){
	if (root == NULL)
		return NULL;
	if (key < root->value){
		return findNode(root->left, key);
	}
	if (key > root->value){
		return findNode(root->right, key);
	}

	return root;
}

void printInorder(Tree root){
	if (root){
		printInorder(root->left);
		fprintf(fo, "%d ", root->value);
		printInorder(root->right);
	}
}

Tree Min(Tree root){
	if (root == NULL){
		return NULL;
	}
	if (root->left == NULL){
		return root;
	}

	return Min(root->left);
}

Tree deleteNode(Tree root, int key){
	Tree temp;
	if (root == NULL){
		fprintf(fo, "Deletion Error : %d is not in the tree.\n", key);
	}
	else if (key < root->value){
		root->left = deleteNode(root->left, key);
	}
	else if (key > root->value){
		root->right = deleteNode(root->right, key);
	}
	else if (root->right && root->left){
		temp = Min(root->right);
		root->value = temp->value;
		root->right = deleteNode(root->right, root->value);
	}
	else {
		temp = root;
		if (root->right == NULL){
			root = root->left;
		}
		else {
			root = root->right;
		}

		free(temp);
	}

	return root;
}

void deleteTree(Tree root){
	if (root){
		deleteTree(root->left);
		deleteTree(root->right);
		free(root);
	}
}

int main(int argc, char* argv[]){
	fi = fopen(argv[1], "r");
	fo = fopen(argv[2], "wt");

	char ord;
	int key;

	Tree tree = NULL;
	

	while (EOF != fscanf(fi, "%c", &ord)){
		if (ord == 'i'){
			fscanf(fi, "%d", &key);
			tree = insertNode(tree, key);
		}
		else if (ord == 'd'){
			fscanf(fi, "%d", &key);
			tree = deleteNode(tree, key);
		}
		else if (ord == 'f'){
			fscanf(fi, "%d", &key);
			if (findNode(tree, key) == NULL){
				fprintf(fo, "Find Error : %d is not in the tree.\n", key);
			}
			else {
				fprintf(fo, "%d is in the tree.\n", key);
			}
		}
		else if (ord == 'p'){
			fgetc(fi);
			printInorder(tree);
			fprintf(fo, "\n");
		}
	}

	deleteTree(tree);
}
