#include <stddef.h> /* size_t */
#include "sorts.h"
#include <unistd.h> /* ssize_t */
#include <time.h> /* clock_t, clock() */
#include <stdio.h> /* printf() */

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
	printf("BubbleSort: Total time taken by CPU: %f\n", (double)(end_t - start_t));
	
}

/* Find the minimum element in the array and swap it with the element in the 1st position */
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
        /* Find the minimum element in unsorted array */
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
	printf("SelectionSort: Total time taken by CPU: %f\n", (double)(end_t - start_t));
}

void Swap(int *xp, int *yp) 
{ 
    int temp = *xp; 
    *xp = *yp;
    *yp = temp;
} 

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
	printf("InsertionSort: Total time taken by CPU: %f\n", (double)(end_t - start_t));
}







