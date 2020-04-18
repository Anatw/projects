/*******************************************************************************
File Name: sorts.h
Author: Lusy Volkov
Date: 31.3.20
Rewiever: Yaacov, Anat
*******************************************************************************/
#include <stddef.h>  /* size_t */

#ifndef __SORTS_H__
#define __SORTS_H__

void BubbleSort(void *arr, size_t size);

void SelectionSort(void *base, size_t nmemb, size_t size,
								int (*compar)(const void *, const void *));

void InsertionSort(void *arr, size_t size);

void CountingSort(void *arr, size_t num_of_elements, size_t range);
										
void RadixSort(void *arr, size_t num_of_elements, size_t elem_size, 
	size_t (*key_to_num)(const void *,const void *params), void *params);

/* Receives a pointer to a data base, the number of elements in the data base.
 * Sorts the data according to the sorting function using Merge Sort Algorithm.
 * Returns 1 in case of allocation failure, otherwise returns 0. */	
int MergeSort(int *arr_to_sort, size_t num_of_elements);

/* The function sorts an array with nmemb elements. 
   The contents of the array are sorted in ascending order according to a 
   comparison function pointed to by compar, which is called with two arguments
   that point to the objects being compared. */
void QuickSort(int *array, int num_of_elements, 
								int (*compare)(const void *, const void *));	
	
#endif /* __SORTS_H__ */

/******************************************************************************/
