/*******************************************************************************
main.c is the program.
Under it you have the main_funcs.c that run the iteration over the array.
Under it there are the struct_funcs, called by the main_funcs.

This file was written by Anat Wax on February 18, 2020. reviewer: Lusy Volkov.
*******************************************************************************/

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "main_funcs.h"

#define arraySize 5

int main(int argc, char *argv[])
{
	char *p = NULL;
	element *array = malloc(sizeof(struct Element) * arraySize);
	int intFromUser = 0;
	
	if (argc == 1) /*the user didn't supply any intiger */
	{
		intFromUser = 0;
	}
	else
	{
		intFromUser = (int)strtol(argv[1], &p, 10);
	}
	
		
	array[0].element_type = FLOAT;
	array[0].element_value.float_num = 4.2;
	/*struct   union        member  	*/
	
	array[1].element_type = FLOAT;
	array[1].element_value.float_num = 6.7;
	
	array[2].element_type = STRING;
	array[2].element_value.string = malloc(10 * sizeof(char));
	strcpy(array[2].element_value.string, "chapter");
	
	
	array[3].element_type = INTEGER;
	array[3].element_value.integer_num = 12;
	
	array[4].element_type = FLOAT;
	array[4].element_value.float_num = 56.32;
	
	
	printf("This is the original array:\n");
	PrintArray(array, arraySize);
	
	AddToArray(array, arraySize, intFromUser);
	
	printf("\n\nThis is the array after adding he intiger:\n");
	PrintArray(array, arraySize);
	
	printf("\n\n");
	FreeMemory(array, arraySize);
	
	return (0);
}
