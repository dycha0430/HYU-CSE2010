#include <stdio.h>
#include <stdlib.h>
#include <time.h>

FILE* fi;
FILE* fo;

typedef struct _DisjointSet{
	int size_maze;
	int* ptr_arr;
}DisjointSets;

void init(DisjointSets* sets, DisjointSets* maze_print, int num);
void Union(DisjointSets* sets, int i, int j);
int find(DisjointSets* sets, int i);
void createMaze(DisjointSets* sets, DisjointSets* maze_print, int num);
void printMaze(DisjointSets* sets, int num);
void freeMaze(DisjointSets* sets, DisjointSets* maze_print);

void init(DisjointSets* sets, DisjointSets* maze_print, int num){
	for (int i = 1; i <= num*num; i++)
		sets->ptr_arr[i] = 0;
	
	for (int i = 0; i < 2*num*(num-1); i++)
		maze_print->ptr_arr[i] = -1;
}

void Union(DisjointSets* sets, int i, int j){
	int iroot = find(sets, i);
	int jroot = find(sets, j);
	
	sets->ptr_arr[jroot] = iroot;
}

int find(DisjointSets* sets, int i){
	while (sets->ptr_arr[i] > 0){
		i = sets->ptr_arr[i];
	}

	return i;
}

void createMaze(DisjointSets* sets, DisjointSets* maze_print, int num){
	srand((unsigned int)time(NULL));
	
	int edge, rest, quotient, x;

	while (find(sets, 1) != find(sets, num*num)){			
		edge = rand()%(maze_print->size_maze);
		rest = edge % (2*num-1);
		quotient = edge / (2*num-1);

		if (rest >= 0 && rest <= num-2){
			x = num*quotient + 1 + rest;

			if (find(sets, x) != find(sets, x+1)){
				Union(sets, x, x+1);
				maze_print->ptr_arr[edge] = 0;
			}
		}
		else {
			x = num*quotient + 1 + (rest-num+1);

			if (find(sets, x) != find(sets, x+num)){
				Union(sets, x, x+num);
				maze_print->ptr_arr[edge] = 0;
			}
		}
	}
}

void printMaze(DisjointSets* sets, int num){
	int i, j;
	
	fprintf(fo, "+");
	for (i = 0; i < num; i++)
		fprintf(fo, "-+");
	fprintf(fo, "\n ");
	
	for (i = 0; i < num - 1; i++){
		if (sets->ptr_arr[i] == -1)
			fprintf(fo, " |");
		else
			fprintf(fo, "  ");
	}
	fprintf(fo, " |\n");
	
	for (i = 0; i < num - 1; i++){
		int k = (2*num -1)*i;
		fprintf(fo, "+");
		for (j = 0; j < num; j++){
			if (sets->ptr_arr[num - 1 + k + j] == -1)
				fprintf(fo, "-+");
			else
				fprintf(fo, " +");
		}

		fprintf(fo, "\n|");
		for (j = 0; j < num-1; j++){
			if (sets->ptr_arr[2*num - 1 + k + j] == -1)
				fprintf(fo, " |");
			else
				fprintf(fo, "  ");
		}
		if (i == num - 2)
			fprintf(fo, "  \n");
		else	
			fprintf(fo, " |\n");
	}
	
 	fprintf(fo, "+");
        for (i = 0; i < num; i++)
                fprintf(fo, "-+");
        fprintf(fo, "\n ");
}

void freeMaze(DisjointSets* sets, DisjointSets* maze_print){
		free(sets->ptr_arr);
		free(sets);
		free(maze_print->ptr_arr);
		free(maze_print);
}



int main(int argc, char* argv[]){
	DisjointSets* sets;
	DisjointSets* maze_print;

	fi = fopen(argv[1], "r");
	fo = fopen(argv[2], "wt");

	int num;
	fscanf(fi, "%d", &num);

	sets = (DisjointSets*)malloc(sizeof(DisjointSets));
        sets->ptr_arr = (int*)malloc((num*num+1)*sizeof(int));
        sets->size_maze = num;

        maze_print = (DisjointSets*)malloc(sizeof(DisjointSets));
       	maze_print->ptr_arr = (int*)malloc(2*num*(num-1)*sizeof(int));
	maze_print->size_maze = 2*num*(num-1);

	init(sets, maze_print, num);
	createMaze(sets, maze_print, num);
	printMaze(maze_print, num);
	freeMaze(sets, maze_print);
}
