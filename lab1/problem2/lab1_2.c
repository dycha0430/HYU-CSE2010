#include <stdio.h>
#define MAX_SIZE 101
#define SWAP(x, y, temp) ((temp) = (x), (x) = (y), (y) = (temp))

void selection_sort(int array[], int arrayLen){
	int max, temp;

	for (int i = 0; i < arrayLen-1; i++){
		max = i;
		
		for (int j = i+1; j < arrayLen; j++){
			if (array[j] > array[max])	max = j;
		}
		
		SWAP(array[i], array[max], temp);
	}
}

int main(){
	FILE *input_file;
	FILE *output_file;

	input_file = fopen("lab1_2_input.txt", "r");
	output_file = fopen("lab1_2_output.txt", "wt");

	int arrayLen;
	int array[MAX_SIZE];

	fscanf(input_file, "%d", &arrayLen);
	for (int i = 0; i < arrayLen; i++){
		fscanf(input_file, "%d", &array[i]);
	}

	selection_sort(array, arrayLen);

	for (int i = 0; i < arrayLen; i++){
		fprintf(output_file, "%d ", array[i]);
	}

	fclose(input_file);
	fclose(output_file);

	return 0;
}
