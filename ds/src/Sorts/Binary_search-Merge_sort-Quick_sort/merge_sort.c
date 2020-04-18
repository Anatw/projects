/*******************************************************************************
					  		 Written by Anat Wax
						   14-15 of April 3rd, 2020
							Reviewer: Haim Sa'adia
*******************************************************************************/
#include <stdlib.h> /* malloc(), free(), size_t, abs() */
#include <stdio.h> /* printf(), size_t */
#include <assert.h> /* assert() */

#define FREE(x) ((free(x), (x = NULL)))

/*
 * Algorithem to reqursivly seperate and than merge while sorting of an array.
 * Return - 0 in case of success.
 * 			1 in case of error.
 * Arguments: arr_to_sort - array to be sorted.
 * 			  num_elements - number of elements in the array.
 * Complexity: O(n log n) (going over each half of the array (2(T(n/2)))
 * 			   and merging the entire array (n) => T(n)=2(T(n/2))+n => O(nlogn))
 */
int MergeSort(int *arr_to_sort, size_t num_elements);

/************** utility functions: *****************/

static int RecursiveMergeSort(int *array, size_t base, size_t upper);

static int Merge(int *array, size_t base, size_t middle, size_t upper);

static void PrintArray(int array[], size_t num_elements);

/*******************************/

int main()
{
	int array[] = {1, 6, 8, 4, 9, 80, 2, 5, 10, 3059, 85, 955, 33};
	int size = sizeof(array) / sizeof(array[0]);
	printf("Before MergeSort:\n");
	PrintArray(array, size);
	
	printf("After MergeSort:\n");	
	MergeSort(array, size);
	PrintArray(array, size);
	
return (0);
}

/*******************************/

int MergeSort(int *arr_to_sort, size_t num_elements)
{
	size_t base = 0;
	size_t upper = (num_elements - 1);

	assert(arr_to_sort && num_elements);

	return (RecursiveMergeSort(arr_to_sort, base, upper));
}

/*******************************/

static int RecursiveMergeSort(int *array, size_t base, size_t upper)
{
	if (base < upper) 
	{
		size_t middle = base + ((upper - base) / 2);

		RecursiveMergeSort(array, base, middle);
		
		RecursiveMergeSort(array, (middle + 1), upper);
		
		return (Merge(array, base, middle, upper));
	}

	return (0);
}

/*******************************/

static int Merge(int *array, size_t base, size_t middle, size_t upper)
{
	int index_left = 0;
	int index_right = 0;
	int new_index = 0;
	int left_size = middle - base + 1;
	int right_size = upper - middle;
	/* temp utility arrays to store the two halfs of arr_to_sort:*/
	int *array_left = (int *)calloc(left_size, sizeof(int));
	int *array_right = NULL;

	if (!array_left)
	{
		return (1);
	}

	array_right = (int *)calloc(right_size, sizeof(int));
	if (!array_right)
	{
		FREE(array_left);
		return (1);
	}
	/* Keep deviding left side until reaching to */ 
	/* an element unit. Return for right side:   */
	for (index_left = 0; index_left < left_size; ++index_left)
	{
		array_left[index_left] = array[base + index_left];
	}

	for (index_right = 0; index_right < right_size; ++index_right)
	{
		array_right[index_right] = array[index_right + middle + 1];
	}
	/* preperation for merging state: */
	index_left = 0;
	index_right = 0;
	new_index = base;

	/* inserting the elements into the array in sorted order: */
	while (index_left < left_size && index_right < right_size)
	{
		if (array_left[index_left] <= array_right[index_right])
		{
			array[new_index] = array_left[index_left];
			++index_left;
		}
		else
		{
			array[new_index] = array_right[index_right];
			++index_right;
		}
		
		++new_index;
	}

	/*if there are any remaining elements in one of the arrays - copy tham */
	while (index_left < left_size)
	{
		array[new_index] = array_left[index_left];
		++index_left;
		++new_index;
	}

	while (index_right < right_size)
	{
		array[new_index] = array_right[index_right];
		++index_right;
		++new_index;
	}

	FREE(array_left);
	FREE(array_right);
	
	return (0);
}

/*******************************/

static void PrintArray(int array[], size_t num_elements)
{
	size_t iterator = 0;
	
	for (iterator = 0; iterator < num_elements; ++iterator)
	{
		printf("%d->", array[iterator]);
	}
	printf("NULL\n");
}