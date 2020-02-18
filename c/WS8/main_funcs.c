/****************************************************************************

this file was written by Anat Wax on February 18, 2020.
****************************************************************************/

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "main_funcs.h"
#include "struct_funcs.h"

void Clear(element *member)
{
	printf("I am clear\n");
}


void PrintArray(element *array, int arraySize)
{
	int i = 0;
	
	for(i = 0; i < arraySize; ++i)
	{
		printush(&array[i]);
	}
}


void addToArray(element *array, int arraySize)
{
	int i = 0;
	
	for(i = 0; i < arraySize; ++i)
	{
		printush(&array[i]);
	}
}
