/*******************************************************************************
					  	 Written by Anat Wax
			    March 30-31, 2020 - Reviewer: Amir Saraf
		MergeSort + Qsort: 14-15 of April, 2020 - Reviewer: Haim Sa'adia
*******************************************************************************/
#include <stddef.h> /* size_t */
#include <unistd.h> /* ssize_t */
#include <time.h> /* clock_t, clock() */
#include <stdio.h> /* printf(), size_t */
#include <assert.h> /* assert() */
#include <stdlib.h> /* malloc(), calloc() ,free() */

#include "sorts.h"

#define BASE (10)
#define FREE(x) ((free(x), (x = NULL)))
#define UNUSED(x) (void)(x)

/********************* MergeSort utility functions: ***************************/

static int RecursiveMergeSort(int *array, size_t base, size_t upper);

int Merge(int *array, size_t base, size_t middle, size_t upper);

/************************ Qsort utility functions: ****************************/

static void QuickSortRecursive(int array[], int base, int top,
                        int (*Compar)(const void *first, const void *second,
                        void *arg), void *arg);


static int Partition (int array[], int base, int top,
               int (*compar)(const void *first, const void *second,
               void *arg), void *arg);

/*************************** utility functions ********************************/
/* 
 * sorting function for the redix function - sirt the array by a specific digit.
 * Arguments: array - pointer to an unsorrted array to be sorted.
 *			  array_length - the length of the array.
 *			  position - position of the digit we chekc at each round (Units,
 *			  tens, hundreds and so on and so forth).
 */
static void RadixCountSort(int arr[], int array_length, int position);

/* Function to swap the value of two pointers using a temporary variable */
static void Swap(int *xp, int *yp) 
{ 
    int temp = *xp; 
    *xp = *yp;
    *yp = temp;
} 

/* function that return the maximum value in an array of ints */
static int GetMax(int array[], int array_length)
{
	int max_value = 0;
	int index = 0;
	
	max_value = array[index];

	for (index = 0; index < array_length; ++index)
	{
		if (array[index] > max_value)
		{
			max_value = array[index];
		}
	}
	
	return (max_value);
}

/************************* functions from header ******************************/

void BubbleSort(int array[], size_t array_length)
{
	char is_sorted = 0;
	size_t index = 0;
	clock_t start_t, end_t;
	
	start_t = clock();
	array_length -= 1;
	
	while (0 == is_sorted)
	{
		is_sorted = 1;
		
		for (index = 0; index < (array_length); ++index)
		{
			if  (*(array + index) > *(array + index + 1))
			{
				Swap(&array[index], (array + index + 1)); 
				
				is_sorted = 0;
			}
		}

		array_length -= 1;
	}

	end_t = clock();
	printf("BubbleSort: Total time taken by CPU: %f\n",
		   (double)(end_t - start_t));
}

/******************************************************************************/

/* Find the minimum element in the array and swap it with the element in the 1st
position */
void SelectionSort(int array[], size_t array_length)
{
    size_t index = 0;
    size_t next = 0;
    size_t minimum = 0; 
  	/*clock_t start_t, end_t;
		
	start_t = clock();*/
	
    /* One by one move boundary of unsorted subarray */
	for (index = 0; index < array_length - 1; ++index) 
    { 
        /* Find the minimum element in the unsorted array */
        minimum = index;
        
		for (next = index + 1; next < array_length; ++next) 
        {
			if (array[next] < array[minimum]) 
			{
				minimum = next;
			}
  		}
  		
        /* Swap the found minimum element with the first element */
        Swap(&array[minimum], &array[index]); 
    }
    
   /* end_t = clock();
	printf("SelectionSort: Total time taken by CPU: %f\n",
		   (double)(end_t - start_t));*/
}

/******************************************************************************/

void InsertionSort(int array[], size_t array_length)
{
	size_t index = 1;
	ssize_t prev = 0;
	/*clock_t start_t, end_t;
		
	start_t = clock();*/
	
	for (index = 1; index < array_length; ++index)
	{
		prev = index - 1;
		
		/* Swap inside the current couple if needed, and go back till the baggining of the array - swapping as needed: */
		while (prev >= 0 && *(array + prev) > *(array + index))
		{
			Swap((array + prev), (array + index));
			
			prev -= 1;
			index = prev + 1;
		}
	}
	
	/*end_t = clock();
	printf("InsertionSort: Total time taken by CPU: %f\n",
		   (double)(end_t - start_t));*/
}

/******************************************************************************/

void CountingSort(int array[], size_t array_length)
{
	int *output = (int *)malloc(sizeof(int) * array_length);
	int *count = NULL;
	int max = 0;
	int index = 0;

	/* find the largest number in the array */
	max = GetMax(array, array_length);

	/* build count array */
	count = (int *)calloc(max + 1, sizeof(int));
	for (index = 0; index < (int)array_length; ++index)
	{
		++count[array[index]];
	}

	/* update count array to use accumulated values */
	for (index = 1; index < max + 1; ++index)
	{
		count[index] += count[index - 1];
	}

	/* build output array top down - to keep stability */
	for (index = array_length - 1; 0 <= index; --index)
	{
		output[count[array[index]] - 1] = array[index];
		--count[array[index]];
	}

	/* copy output to original array */
	for (index = 0; index < (int)array_length; ++index)
	{
		array[index] = output[index];
	}

	free(count);
	count = NULL;
	free(output);
	output = NULL;
}

/******************************************************************************/

void RadixSort(int array[], size_t array_length)
{
	int num_of_digits = 0;
	int	biggest_value = 0;
	int position = 1;
	
	assert(array);
	
	biggest_value = GetMax(array, array_length);
	
	while (biggest_value)
	{
		biggest_value /= BASE;
		++num_of_digits;
	}
	
	for (position = 1; num_of_digits > 0; --num_of_digits, (position *= BASE))
	{
		RadixCountSort(array, array_length, position);
	}
}

/******************************************************************************/

static void RadixCountSort(int array[], int array_length, int position)
{
    int index = 0;
    int count[10] = {0};
    int *output = (int *)calloc(array_length, sizeof(int));
    
    assert(array);
  
	for (index = 0; index < array_length; ++index)
	{
		++count[(array[index]/position)%10];
	}
		  
	for (index = 1; index < 10; ++index)
	{
		count[index] += count[index - 1];
	} 

	for (index = array_length- 1; index >= 0; --index) 
	{ 
		output[count[(array[index] / position) % 10] - 1] = array[index]; 
		--count[(array[index] / position) % 10]; 
	} 

	for (index = 0; index < array_length; ++index)
    {
		array[index] = output[index];
	}
	
	free(output);
}

/******************************************************************************/

int MergeSort(int *arr_to_sort, size_t num_elements)
{
	size_t base = 0;
	size_t upper = (num_elements - 1);

	assert(arr_to_sort && num_elements);

	return (RecursiveMergeSort(arr_to_sort, base, upper));
}

/*********************** MergeSort utility functions: *************************/

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

int Merge(int *array, size_t base, size_t middle, size_t upper)
{
	int index_left = 0;
	int index_right = 0;
	int new_index = 0;
	int left_size = middle - base + 1;
	int right_size = upper - middle;
	/* temp utility arrays to store the two halfs of arr_to_sort:*/
	int *array_left = (int *)malloc(sizeof(int) * left_size);
	int *array_right = NULL;

	if (!array_left)
	{
		return (1);
	}

	array_right = (int *)malloc(sizeof(int) * right_size);
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

/******************************************************************************/

void Qsort(void *base, size_t nmemb, size_t size,
           int (*Compar)(const void *first, const void *second,
           void *arg), void *arg)
{
    UNUSED(size);
    QuickSortRecursive(base, 0, (nmemb - 1), Compar, arg);
}

/************************* Qsort utility functions: ***************************/

static void QuickSortRecursive(int array[], int base, int top,
                        int (*Compar)(const void *first, const void *second,
                        void *arg), void *arg)
{
    int partition = 0;

    assert(array && Compar);

    if (base < top)
    {
        partition = Partition(array, base, top, Compar, arg);
        
        QuickSortRecursive(array, base, (partition - 1), Compar, arg);
        QuickSortRecursive(array, (partition + 1), top, Compar, arg);
    }
}

/*****************************/

static int Partition (int array[], int base, int top,
               int (*compar)(const void *first, const void *second,
               void *arg), void *arg)
{
    int pivot = array[top];
    int index = (base - 1);
    int array_index = 0;

    for (array_index = base; array_index <= (top - 1); ++array_index)
    {
        /* if current element is smaller the pivot - swap to left */
        if (0 > (compar(&array[array_index], &pivot, arg)))
        {
            ++index;
            Swap(&array[index], &array[array_index]);
        }
    }
    /* insert pivot to place: */
    Swap(&array[index + 1], &array[top]);
    return (index + 1);
}


/************************ functions graveyard: ********************************/
/*
void CountingSort(int array[], size_t array_length)
{
	int *lut = NULL;
	size_t index = 0;
	int bigest_value = GetMax(array, array_length);
	
	assert(array);
	
	lut = (int *)malloc(sizeof(int) * bigest_value);*/
	
	/* set all cells to zero 
	for (index = 0; index < (size_t)bigest_value ; ++index)
	{
		*(lut + index) = 0;
	}*/
	
	/* count number of performanced for each number 
	for (; index < array_length ; ++index)
	{
		*(lut + *(array + index)) += 1;
	}*/
	
	/* set lut for sorting faze 
	for (index = 1; index < (size_t)bigest_value ; ++index)
	{
		*(lut + index) += *(lut + index - 1);
	}
	
	for (index = 0; index < array_length ; ++index)
	{
		*(array + *(lut + index)) = *(lut + index);
		--*(lut + index);
	}
	
	free(lut);
}*/