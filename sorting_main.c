#include <stdio.h>
#include <string.h>
#include <time.h>
#include <stdlib.h>
#include "sorting_bst.h"
/*
Parses the integers in a file and puts them to numbers
*/
void parse_integers(char filename[], int numbers[][1000])
{
	FILE* numbers_file = fopen(filename, "r");
	int line_index = 0;
	int int_index = 0; // parsed number's index for determining its location for numbers array
	int number; // Parsed single number where its digits is between [1,6]
	char ch;
	do
	{
		ch = fgetc(numbers_file);
		if (ch == '\n')
		{
			numbers[line_index][int_index] = number;
			line_index++;			
			int_index = 0;
			number = 0;
		}
		else if (ch == ' ')
		{
			numbers[line_index][int_index] = number;			
			int_index++;
			number = 0;
		}
		else
		{
			number *= 10;
			number += (ch - 48);
		}
	} while (ch != EOF);
	numbers[line_index][int_index] = number;
	fclose(numbers_file);
}
/*
Copy src_arr to dest_arr
*/
void arr_cpy(int dest_arr[], int src_arr[], int size)
{
	for (int i = 0; i < size; i++)
	{
		dest_arr[i] = src_arr[i];
	}
}
/*
Sorts numbers to sorted_numbers
Also fills the corresponding build times of binary search tree
*/
void sort_arrays(int numbers[][1000], int sorted_numbers[][1000], double build_times[])
{
	clock_t start;
	clock_t end;
	int bst[16383]; // a binary tree with height 14 has size 16383
	int tmp_array[1000];
	for(int i = 0; i < 5; i++)
	{
		start = clock();
		finalize_bst(bst, numbers[i]);
		end = clock();
		double time_passed = (double)(end - start) / CLOCKS_PER_SEC; // this code is from stackoverflow
		build_times[i] = time_passed * 1000; // converting to miliseconds
		bst_to_array(bst, sorted_numbers[i]);
	}
}
/*
Writes the sorted numbers and build times to files.
*/
void export_results(double build_times[], int sorted_arrays[][1000])
{
	FILE* build_times_file = fopen("c_build_times.txt", "w");;
	FILE *sorted_numbers_file;
	char build_time[50];
	char number_as_string[6];
	char filename[14];
	// For each number set
	for(int i = 0; i < 5; i++)
	{
		sprintf(filename, "c_sorted_%d.txt", i+1);
		sorted_numbers_file = fopen(filename, "w");
		// For each number
		for(int j = 0; j < 1000; j++)
		{
			sprintf(number_as_string, "%d ", sorted_arrays[i][j]);
			fputs(number_as_string, sorted_numbers_file);
		}
		fclose(sorted_numbers_file);
		sprintf(build_time, "Build time of %d is %f miliseconds\n", i, build_times[i]);
		fputs(build_time, build_times_file);
	}
	fclose(build_times_file);
}

int main()
{
	int numbers[5][1000]; // Multidimensional array that will hold the parsed integer values
	char filename[18] = "number_samples.txt";
	parse_integers(filename, numbers);
	int sorted_numbers[5][1000];
	double build_times[5];
	sort_arrays(numbers, sorted_numbers, build_times); // Sorts numbers to the sorted_numbers and saves the build times
	export_results(build_times, sorted_numbers); // Sorted numbers and build times will be writed to seperate files
	return 0;
}