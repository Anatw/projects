/*******************************************************************************
Name: Binary Search Algorithm Test
Author: Lusy Volkov
Date: 14.4.20
Rewiever: Anat Wax
*******************************************************************************/
#include <assert.h>   /* assert */
#include <stdlib.h>   /* qsort, srand */
#include <time.h>

#include "search.h"

/* receives an array and the size of it, and fills an array with random 
   numbers. returns pointer to the first element of the array */
static int *MakeRandArray(int *array, size_t size);

/* subtracts two integers and returns the result */
int Subtractiont(const void *num1, const void *num2);

/******************************************************************************/

int main ()
{
	int small_array[10]= {1,2,3,4,5,6,7,8,9,10};
	int *array = NULL;
	int to_find1 = 8;
	int to_find2 = 80;
	int to_find3 = 1000;
	int found_index = 0;
	size_t size = 5000;

	found_index = BinarySearchIter(small_array, 0, 9, to_find1) ;

	assert (7 == found_index);
	
	/* look for an element not in the array */
	found_index = BinarySearchIter(small_array, 0, 9, to_find2);

	assert (-1 == found_index);
	
	/* allocate the big array */
	array = malloc(size * sizeof(int));
	
	assert (NULL != array);

	MakeRandArray(array, size);
	
	qsort(array, size, sizeof(int), Subtractiont);

	found_index = BinarySearchRec(array, 0, 4999, to_find3);

	assert (1000 == array[found_index] || -1 == found_index);

	free(array);
	
	return (0);
}
/******************************************************************************/

static int *MakeRandArray(int *array, size_t size) 
{
	srand(time(NULL));

	while (size)
	{
		*array = rand() % 1000;
		++array; 
		--size;
	}
	
	return (array);
}
/******************************************************************************/

int Subtractiont(const void *num1, const void *num2) 
{
	return (*(int *)num1 - *(int *)num2);
}
/******************************************************************************/

































