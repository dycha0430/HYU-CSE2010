#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Stack{
	int* key;
	int top;
	int max_stack_size;
}Stack;

FILE* fi;
FILE* fo;

Stack* CreateStack(int max);
void Push(Stack* S, int X);
int Pop(Stack* S);
int Top(Stack* S);
int Postfix(Stack* S, char input_str);
void DeleteStack(Stack* S);
int IsFull(Stack* S);
int IsEmpty(Stack* S);

Stack* CreateStack(int max){
        Stack* S = NULL;
        S = (Stack*)malloc(sizeof(Stack));
        S->key = (int*)malloc(sizeof(int)*max);
        S->max_stack_size = max;
        S->top = -1;
        return S;
}

void Push(Stack* S, int X){
	if (IsFull(S)) {
		fprintf(fo, "Stack is full\n");	
	}
	else {
		S->key[++(S->top)] = X;
	}
}

int Pop(Stack* S){
	if (IsEmpty(S)) {
		fprintf(fo, "Stack is empty\n");
		return -1;
	}
	else {
		return S->key[S->top--];
	}
}

int Top(Stack* S){
	if (!IsEmpty(S)){
		return S->key[S->top];
	}
	fprintf(fo, "Stack is empty\n");
	return 0;
}

void DeleteStack(Stack* S){
	free(S->key);
	free(S);
}

int IsFull(Stack* S){
	if (S->top + 1 == S->max_stack_size) return 1;
	return 0;
}

int IsEmpty(Stack* S){
	if (S->top == -1) return 1;
	return 0;
}

int Postfix(Stack* S, char input_str){
	int num1, num2, result;

	if (input_str >= '1' && input_str <= '9'){
		Push(S, input_str - '0');
	}
	else {
		num1 = Pop(S);
		num2 = Pop(S);
		
		if (input_str == '+')
			result = num2 + num1;
		else if (input_str == '-')
			result = num2 - num1;
		else if (input_str == '*')
			result = num2 * num1;
		else if (input_str == '/')
			result = num2 / num1;
		else if (input_str == '%')
			result = num2 % num1;
		
		Push(S, result);
	}
	
	fprintf(fo, "%d ", Top(S));

	return Top(S);
}

void main(int argc, char* argv[]){
	
	fi = fopen(argv[1], "r");
	fo = fopen(argv[2], "wt");
	Stack* stack;
	char input_str[101];
	int max, i, result;

	fgets(input_str, 101, fi);
	max = 10;
	stack = CreateStack(max);

	fprintf(fo, "Top numbers :");

	for (i = 0; i < strlen(input_str) && input_str[i] != '#'; ++i){
		result = Postfix(stack, input_str[i]);
	}

	fprintf(fo, "\nevaluation result : %d\n", result);
	fclose(fi);
	DeleteStack(stack);
}
