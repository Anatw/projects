/****************************************************************************
main.c is the interface between te program and the user.

this file was written by Anat Wax on February 18, 2020.
****************************************************************************/

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "main_funcs.h"

#define arraySize 5

int main()
{
	int intFromUser = 10;
	
	element *array = malloc(sizeof(struct Element) * arraySize);
	
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
	
	PrintArray(array, arraySize);
	
	AddToArray(array, arraySize, intFromUser);
	
	PrintArray(array, arraySize);
	
	FreeMemory(array, arraySize);
	
	return (0);
}
