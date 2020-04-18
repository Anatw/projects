/*******************************************************************************
					  	 Written by Anat Wax
						  March 30-31, 2020
						Reviewer: Amir Saraf
*******************************************************************************/
#include <stddef.h> /* size_t */
#include <assert.h> /* assert() */
#include <time.h> /* time() */
#include <stdlib.h> /* srand(), rand() */
#include <stdio.h> /* printf() */

#include "sorts.h"

#define ARRAY_SIZE (5000)
#define COUNTING_ARRAY_SIZE (100)
#define DIGITS_NUM (7)
#define BASE (10)

void PrintArray(int array[], size_t array_length);

static int Compar(const void *first, const void *second, void *arg);

/*******************************/

int main()
{
	int array[ARRAY_SIZE] = {0};
	int index = 0;
	
	srand(time(NULL));
	/* random numbers ranging from 1 to ARRAY_SIZE */
	for (index = 0; index < ARRAY_SIZE; ++index)
	{
		array[index] = rand() % ARRAY_SIZE + 1; 
	}
	
	PrintArray(array, ARRAY_SIZE);
	
	
	/*SelectionSort(array, ARRAY_SIZE);
	InsertionSort(array, ARRAY_SIZE);
	BubbleSort(array, ARRAY_SIZE);*/
	printf("performing CountingSort:\n\n\n\n\n");
	CountingSort(array, ARRAY_SIZE);
	
	/*RadixSort(array, ARRAY_SIZE);
	printf("after: \n\n\n\n\n\n\n");*/
	PrintArray(array, ARRAY_SIZE);
	
	return (0);
}

void PrintArray(int array[], size_t array_length)
{
	size_t index = 0;
	
	for (index = 0; index < array_length; ++index)
	{
		printf("%d\n", array[index]);
	}
}

/*****************************/

static int Compar(const void *first, const void *second, void *arg)
{
    UNUSED(arg);
    return (*(int *)first - *(int *)second);
}