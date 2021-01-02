#include <stdio.h>
#define MAX_LEN 101

int main(){
	FILE *input_file;
	FILE *output_file;

	input_file = fopen("lab1_1_input.txt", "r");
	output_file = fopen("lab1_1_output.txt", "wt");

	int arrayLen, first_index, last_index, sum = 0;
	int array[MAX_LEN];
	fscanf(input_file, "%d", &arrayLen);

	for (int i = 0; i < arrayLen; i++){
		fscanf(input_file, "%d", &array[i]);
	}

	fscanf(input_file, "%d %d", &first_index, &last_index);
	for (int i = first_index; i <= last_index; i++){
		sum += array[i];
	}
	fprintf(output_file, "%d", sum);

	fclose(input_file);
	fclose(output_file);
	return 0;
}
