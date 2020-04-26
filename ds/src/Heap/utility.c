#include <stdio.h> /* printf(), size_t */

#include "utility.h"

/*********************** utility functions: **************************/
 
void PrintArray(int array[], size_t num_elements)
{
	size_t iterator = 0;
	
	for (iterator = 0; iterator < num_elements; ++iterator)
	{
		printf("%d->", array[iterator]);
	}
	printf("NULL\n");
}

void Swap(int *a, int *b)
{
	int temp = *a;
	*a = *b;
	*b = temp;
}


int CmpFunc(const void *first, const void *second)
{
	if (*(int *)first > *(int *)second)
	{
		return (1);
	}
	else if (*(int *)first < *(int *)second)
	{
		return (-1);
	}
	else
	{
		return (0);
	}
}