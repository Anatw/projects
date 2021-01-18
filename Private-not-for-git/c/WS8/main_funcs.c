/*******************************************************************************
					  	 Written by Anat Wax
						  February 18, 2020
						Reviewer: Lusy Volkov
*******************************************************************************/

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "main_funcs.h"
#include "struct_funcs.h"

void FreeMemory(element *array, int arraySize)
{
	int i = 0;
	
	for(i = 0; i < arraySize; ++i)
	{
		Cleanup(&array[i]);
	}
	free(array);
}


void PrintArray(element *array, int arraySize)
{
	int i = 0;
	
	for(i = 0; i < arraySize; ++i)
	{
		Printush(&array[i]);
	}
}


void AddToArray(element *array, int arraySize, int intFromUser)
{
	int i = 0;
	
	for(i = 0; i < arraySize; ++i)
	{
		AddInt(&array[i], intFromUser);
	}
}
