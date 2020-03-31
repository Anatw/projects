#include <stddef.h> /* size_t */
#include <assert.h> /* assert() */
#include <time.h> /* time() */
#include <stdlib.h> /* srand(), rand() */
#include <stdio.h> /* printf() */

#include "sorts.h"

#define ARRAY_SIZE (5000)

void PrintArray(int array[], size_t array_length);

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
	
	
	SelectionSort(array, ARRAY_SIZE);
	InsertionSort(array, ARRAY_SIZE);
	BubbleSort(array, ARRAY_SIZE);
	
	/*printf("after: \n\n\n\n\n\n\n");
	PrintArray(array, ARRAY_SIZE);*/
	
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
