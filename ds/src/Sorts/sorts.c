/*******************************************************************************
					  	 Written by Anat Wax
						  March 30-31, 2020
						Reviewer: Amir Saraf
*******************************************************************************/
#include <stddef.h> /* size_t */
#include <unistd.h> /* ssize_t */
#include <time.h> /* clock_t, clock() */
#include <stdio.h> /* printf() */
#include <assert.h> /* assert() */
#include <stdlib.h> /* malloc(), calloc() ,free() */

#include "sorts.h"

#define BASE (10)

/*************************** helping functions ********************************/
/* 
 * sorting function for the redix function - sirt the array by a specific digit.
 * Arguments: array - pointer to an unsorrted array to be sorted.
 *			  array_length - the length of the array.
 *			  position - position of the digit we chekc at each round (Units,
 *			  tens, hundreds and so on and so forth).
 */
static void RadixCountSort(int arr[], int array_length, int position);

/* Function to swap the value of two pointers using a temporary variable */
void Swap(int *xp, int *yp) 
{ 
    int temp = *xp; 
    *xp = *yp;
    *yp = temp;
} 

/* function that return the maximum value in an array of ints */
int GetMax(int array[], int array_length)
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
  	clock_t start_t, end_t;
		
	start_t = clock();
	
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
    
    end_t = clock();
	printf("SelectionSort: Total time taken by CPU: %f\n",
		   (double)(end_t - start_t));
}

/******************************************************************************/

void InsertionSort(int array[], size_t array_length)
{
	size_t index = 1;
	ssize_t prev = 0;
	size_t current = *(array + index);
	clock_t start_t, end_t;
		
	start_t = clock();
	
	for (index = 1; index < array_length; ++index)
	{
		prev = index - 1;
		current = *(array + index);
		
		while (prev >= 0 && *(array + prev) > *(array + index))
		{
			Swap((array + prev), (array + index));
			
			prev -= 1;
			index = prev + 1;
		}
		
		*(array + prev + 1) = current;
	}
	
	end_t = clock();
	printf("InsertionSort: Total time taken by CPU: %f\n",
		   (double)(end_t - start_t));
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
		count[ (array[index]/position)%10 ]++;
	}
		  
	for (index = 1; index < 10; ++index)
	{
		count[index] += count[index - 1];
	} 

	for (index =array_length- 1; index >= 0; --index) 
	{ 
		output[count[(array[index] / position) % 10 ] - 1] = array[index]; 
		count[(array[index] / position) % 10]--; 
	} 

	for (index = 0; index < array_length; ++index)
    {
		array[index] = output[index];
	}
	
	free(output);
}

/************************ functions gravwyard: ********************************/
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
