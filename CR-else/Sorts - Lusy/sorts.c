/*******************************************************************************
File Name: sorts.c
Author: Lusy Volkov
Date: 31.3.20
Rewiever: Yaacov, Anat
*******************************************************************************/

#include <stdio.h>    /* printf */
#include <assert.h>   /* assert */
#include <string.h>	  /* memcpy, memcmp */
#include <stdlib.h>	  /* malloc */

#include "sorts.h"

#define ELEM_SIZE (sizeof(int))
#define SWAP(a, b) {*a ^= *b; *b ^= *a; *a ^= *b;}

/* struct for RadixSort function */
typedef struct radix
{
	void *data;
	size_t key;
}radix_t;

/******************************************************************************/

void Swap(int *a, int *b)
{ 
	int temp;
	 
	temp = *a; 
	*a = *b; 
	*b = temp; 
} 
/******************************************************************************/

int IsBefore(const void *a, const void *b)
{
	return(*(int *)a > *(int *)b);
}
/******************************************************************************/

size_t KeyToNumImp(const void *data,const void *params)
{
	return(((radix_t*)data)->key & *(size_t*)params);
}
/******************************************************************************/

size_t KeyToNum(const void *data, const void *args)
{
	return (*(int*)data);	
}
/******************************************************************************/

int CountingSortForRadix(void *base, size_t num_of_elements, 
		size_t element_size, size_t(*key_to_num)(const void *,const void *args), 
		const void *args, size_t range);
									
/******************************************************************************/
																
/* utility to compare two integer numbers */
static int CompNums(const void *num_1, const void *num_2)
{
	return (*(int *)num_1 - *(int *)num_2);
}
/******************************************************************************/

static void MergeSortRec(int *buffer, int *arr_to_sort, size_t
				num_of_elements, int(*comp_func)(const void *, const void *));
				
/******************************************************************************/
				
static void MergeHalves(int *buffer, int *first_element, int *second_element,
						size_t num_of_elems_1, size_t num_of_elems_2,
						int (*comp_func)(const void *, const void *));

/******************************************************************************/


									
/******************************************************************************/
/******************************************************************************/
/* Function to print an array */
void PrintIntArr(int *arr, size_t size)
{
	int i = 0;
	int *arr_int = arr;
	
	for(i = 0; i < size; ++i)
	{
		printf("%d   ", arr_int[i]);
	}
	
	printf("\n");
}
/******************************************************************************/

void BubbleSort(void *arr, size_t size)
{
	void *current_elem = NULL;
	void *next_elem = NULL;
	void *end = NULL;
	
	assert(arr);
	
	end =(void *)((char *)arr +(size - 1) * ELEM_SIZE);
	--size;
		
	while(size)
	{
		current_elem = arr;
	    next_elem =(void *)((char *)arr + ELEM_SIZE);
	
		while(current_elem < end)
		{
			if(IsBefore(current_elem, next_elem))
			{
				Swap(current_elem, next_elem);
			}
		
			current_elem = next_elem;
			next_elem =(void *)((char *)next_elem + ELEM_SIZE);
		}
		
		/* the rightest element is in order */
		--size;
		end = current_elem;
	}	
}		
/******************************************************************************/
		
void SelectionSort(void *arr, size_t size, size_t elem,
								int(*compar)(const void *, const void *))
{
	int i = 0;
	int j = 0;
	int min_index = 0;
	char *base = arr;
	
	for(i = 0; i < size; ++i)
	{
		min_index = i;
		
		for(j = i + 1; j < size; ++j)
		{
			if(IsBefore(base + min_index * elem, base  + j * elem) > 0)
			{
				min_index = j;
			}
		}
		
		Swap((int *)(base + i * elem),(int *)(base + min_index * elem));	
	}
}
/******************************************************************************/
		
void InsertionSort(void *arr, size_t size)
{
	int current = 1;
	int runner = 0;
	
	void *current_elem = malloc(ELEM_SIZE);
	
	assert(current_elem);
	assert(arr);
	
	for(current = 1; current < size; ++current)
	{
		memcpy(current_elem,(char *)arr + current * ELEM_SIZE, ELEM_SIZE);
		
		for(runner = current - 1; runner >= 0 && 
			(IsBefore((char *)arr + runner * ELEM_SIZE, current_elem)); 
																	--runner)
		{
			memcpy((char *)arr +(runner + 1) * ELEM_SIZE,(char *)arr + 
											runner * ELEM_SIZE, ELEM_SIZE);
		}
		
		memcpy((char *)arr +(runner + 1) * ELEM_SIZE, current_elem, ELEM_SIZE);
	}
	
	free(current_elem);
}		
/******************************************************************************/
		
void CountingSort(void *arr, size_t num_of_elements, size_t range)
{
	char *temp_arr = NULL;
	char *arr_runner = arr;
	size_t *count = NULL;
	size_t index = 0;
	int i = 0;
	
	assert(arr);
	assert(range > 0);
	
	count =(size_t *)calloc(sizeof(size_t), range);
	
	if (count)
	{
		temp_arr =(char *)malloc(num_of_elements * ELEM_SIZE);
		
		if (temp_arr)
		{
			/* all allocation worked */
			arr_runner = arr;

			/* first move on the arr, filling the count */
			for (i = 0; i < num_of_elements; ++i, arr_runner += ELEM_SIZE)
			{	
				index = *(int *)arr_runner;
				count[index] += 1;
			}
			
			/* moving on the count adding each cell */
			for (i = 1; i < range; ++i)
			{
				count[i] += count[i - 1]; 
			}

			/* moving on arr from the start, and jumping on temp arr */
			arr_runner = arr;
			
			for (i = 0; i < num_of_elements; ++i)
			{
				index = *(int *)arr_runner;
				--count[index];
				
				memcpy(temp_arr +(count[index]) * ELEM_SIZE, arr_runner,
																ELEM_SIZE);
				arr_runner += ELEM_SIZE;
			}
			
			/* copy the sorted array to the arr */
			memcpy(arr, temp_arr, ELEM_SIZE * num_of_elements);
		}
	}
	
	free(temp_arr);
	free(count);
}	
/******************************************************************************/

void RadixSort(void *arr, size_t num_of_elements, size_t elem_size, 
	size_t(*key_to_num)(const void *,const void *params), void *params)
{
	radix_t *new_arr = NULL;
	char *temp_arr = NULL;
	const int NIBBLE = 4;
	size_t i = 0;
	size_t max_key = 0;
	/* BITS_IN_BYTE = 8; */
	int range =(2 << NIBBLE);
	size_t mask = 0x0fLU;	/* 0000 00... 1111 */
	
	assert(arr);
	assert(key_to_num);
	assert(ELEM_SIZE > 0);
	
	new_arr =(radix_t *)malloc(sizeof(radix_t) * num_of_elements);
	temp_arr =(char *)malloc(ELEM_SIZE * num_of_elements);
	
	if(new_arr && temp_arr)
	{
		/* creating a new array with the currect key according to the user's
		 * key_to_num function */
		for(i = 0; i < num_of_elements; ++i)
		{
			new_arr[i].data =(char*)arr + i * ELEM_SIZE;
			new_arr[i].key = key_to_num(new_arr[i].data, params);
			
			max_key =(max_key <(new_arr[i].key)) ? new_arr[i].key : max_key;
		}

		/* run as long as the max key is not zero */
		while((0 != max_key) && 0 == CountingSortForRadix(new_arr, 
		num_of_elements, sizeof(radix_t), KeyToNumImp, &mask, range))
		{
			/* shifting all the keys 4 bits to the right */
			for(i = 0; i < num_of_elements; ++i)
			{
				new_arr[i].key >>= NIBBLE;
			}
			
			max_key >>= NIBBLE;
		}

		/* copy the result back to arr only the data */
		for(i = 0; i < num_of_elements; ++i)
		{
			memcpy((char *)temp_arr + i * ELEM_SIZE, new_arr[i].data, 
																ELEM_SIZE);
		}
		
		/* copy the sorted array to the arr */
		memcpy(arr, temp_arr, ELEM_SIZE * num_of_elements);
	}

	free(new_arr);
	free(temp_arr);
}
/******************************************************************************/

int CountingSortForRadix(void *base, size_t num_of_elements, size_t element_size,
	size_t(*key_to_num)(const void *,const void *args), const void *args,
																size_t range)
{
	char *temp_base = NULL;
	char *arr_runner = base;
	size_t *histogram = NULL;
	size_t index = 0;
	int return_status = 1;
	int i = 0;
	
	assert(base);
	assert(range > 0);
	
	histogram =(size_t*)calloc(sizeof(size_t), range);
	
	if(histogram)
	{
		temp_base =(char*)malloc(num_of_elements*element_size);
		
		if(temp_base)
		{
			/* all allocation worked */
			return_status = 0;
			arr_runner = base;

			/* first move on the base, filling the histogram */
			for(i = 0; i < num_of_elements; ++i , arr_runner += element_size)
			{
				histogram[key_to_num(arr_runner, args)] += 1; 
			}

			arr_runner -= element_size;
			/* at the end- base runner is pointing to the last element */
			
			/* moving on the histogram adding each cell */
			for(i = 1; i < range; ++i)
			{
				histogram[i] += histogram[i - 1]; 
			}

			/* moving on base from the end, and jumping on temp base */
			for(i = 0 ; i < num_of_elements; ++i)
			{
				/* decreasing the histogram by 1 */
				index = key_to_num(arr_runner, args);
				--histogram[index];
				
				memcpy(temp_base +(histogram[index])*element_size, arr_runner,
																element_size);
				arr_runner -= element_size;
			}
			
			/* copy the sorted array to the base */
			memcpy(base, temp_base, element_size*num_of_elements);
		}
	}
	
	free(temp_base);
	free(histogram);
	
	return (return_status);
}			
/******************************************************************************/
		
int MergeSort(int *arr_to_sort, size_t num_of_elements)
{
	int *buffer = NULL;
	
	assert (arr_to_sort);
	
	/* Allocate an array of the same size as the data base. */
	buffer = malloc(num_of_elements * ELEM_SIZE);
	
	assert (buffer);
	
	MergeSortRec(buffer, arr_to_sort, num_of_elements, CompNums);
	
	free(buffer);
	
	return (0);
}
/******************************************************************************/

static void MergeSortRec(int *buffer, int *arr_to_sort, size_t
				num_of_elements, int(*comp_func)(const void *, const void *))
{
	#define LEFT_HALF_PTR (arr_to_sort)
	#define LEFT_HALF_SIZE (num_of_elements/2)
	#define RIGHT_HALF_PTR (arr_to_sort + LEFT_HALF_SIZE)
	#define RIGHT_HALF_SIZE (num_of_elements - (LEFT_HALF_SIZE))
	
	assert(buffer);
	assert(arr_to_sort);
	assert(comp_func);
	
	/* If there is only one element in the array: */
	if (1 == num_of_elements)
	{
		return;
	}
	else
	{
	   /*Call the function recursively for the first half of the current array*/
		MergeSortRec(buffer, LEFT_HALF_PTR, LEFT_HALF_SIZE, comp_func);
		
	  /*Call the function recursively for the second half of the current array*/
		MergeSortRec(buffer, RIGHT_HALF_PTR, RIGHT_HALF_SIZE, comp_func);
		
		/* Merge halves. */
		MergeHalves(buffer, LEFT_HALF_PTR, RIGHT_HALF_PTR, LEFT_HALF_SIZE,
												RIGHT_HALF_SIZE, comp_func);
		
		/* Copy the merged array back to arr_to_sort */
		memcpy(arr_to_sort, buffer, num_of_elements * ELEM_SIZE);
	}
}
/******************************************************************************/

static void MergeHalves(int *buffer, int *first_element, int *second_element,
						size_t num_of_elems_1, size_t num_of_elems_2,
						int (*comp_func)(const void *, const void *))
{
	int comp_result = 0;
	
	assert (buffer);
	assert (comp_func);
	assert (first_element);
	assert (second_element);
	
	/* If only the second half has remained: */
	if (0 == num_of_elems_1)
	{
		/* Copy the second half to buffer. */
		memcpy(buffer, second_element, num_of_elems_2 * ELEM_SIZE);
		
		return;
	}
	
	/* If only the first half has remained: */
	if (0 == num_of_elems_2)
	{
		/* Copy the first half to buffer. */
		memcpy(buffer, first_element, num_of_elems_1 * ELEM_SIZE);
		
		return;
	}
	
	/* Compare between the data of the elements. */
	comp_result = comp_func(first_element, second_element);
	
	/* If second_element should be placed before first_element: */
	if (comp_result > 0)
	{
		/* Copy second_element to buffer. */
		memcpy(buffer, second_element, ELEM_SIZE);
		
   /* Call the function recursively for the next element after second_element */
		MergeHalves((buffer + 1), first_element, 
						(second_element + 1), num_of_elems_1, 
												num_of_elems_2 - 1, comp_func);
	}
	
	else
	{
			/* Copy first_element to buffer. */
		 memcpy(buffer, first_element, ELEM_SIZE);
		
	/*Call the function recursively for the next element after first_element*/
		MergeHalves((buffer + 1), (first_element + 1), second_element,
		num_of_elems_1 - 1, num_of_elems_2, comp_func);
	}
}
/******************************************************************************/

void QuickSort(int *array, int num_of_elements, 
									int (*compare)(const void *, const void *)) 
{
	int i = 0;
	int pivot_index = 0;
	int *pivot = NULL;
	int wall = 0;

	if (num_of_elements == 1 || num_of_elements == 0 )
	{
		return;
	}

	pivot_index = num_of_elements - 1 ;
	pivot = array + pivot_index;

	for (i = 0 ; i < num_of_elements ; ++i)
	{
		if (compare((array + i), pivot) < 0)
		{
		/*if current elemnet is smaller than pivot, move it left to the wall,
		which actually means swap with the element currently to the right
		of the wall*/
			Swap(array + i, array + wall);

			/*move the wall to be on the added element's right*/
			wall += 1; 
		}
	}

	/*after switching all elements to their right position, we drop the pivot
	on the wall- its final position!*/
	Swap(array + wall, pivot);
	QuickSort(array, wall, compare);
	QuickSort(array + (wall + 1), (num_of_elements - wall - 1), compare);
}
/******************************************************************************/

		
		
		
		
		
		
		
		
		
		
		
		
		
		
		
		
		
		
		
		
		
