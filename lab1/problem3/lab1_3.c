#include <stdio.h>
#define MAX_LEN 31
#define MAX_ST 11
#define SWAP(x, y, temp) ((temp) = (x), (x) = (y), (y) = (temp))

typedef struct{
        char name[MAX_LEN];
        int id;
}student;


void selection_sort(student array[], int arrayLen){
        int min;
	student temp;

        for (int i = 0; i < arrayLen-1; i++){
                min = i;

                for (int j = i+1; j < arrayLen; j++){
                        if (array[j].id < array[min].id)      min = j;
                }

                SWAP(array[i], array[min], temp);
        }
}

int main(){
	FILE *input_file;
	FILE *output_file;

	input_file = fopen("lab1_3_input.txt", "r");
	output_file = fopen("lab1_3_output.txt", "wt");

	int st_num;
	student st_array[MAX_ST];
	
	fscanf(input_file, "%d", &st_num);
	for (int i = 0; i < st_num; i++){
		fscanf(input_file, "%s %d", st_array[i].name, &st_array[i].id);
	}

	selection_sort(st_array, st_num);
	for (int i = 0; i < st_num; i++){
		fprintf(output_file, "%s %d\n", st_array[i].name, st_array[i].id);
	}

	fclose(input_file);
	fclose(output_file);

	return 0;

}
