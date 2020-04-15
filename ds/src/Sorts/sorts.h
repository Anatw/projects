/*******************************************************************************
Since this is in no way a document a client will get, but merely an exercise
to understand sorting functions, I added more explanation on the functions
algorithm than usual.
					  	 Written by Anat Wax
						  March 30-31, 2020
						Reviewer: Amir Saraf
*******************************************************************************/
#ifndef SORTS_H
#define SORTS_H

/* 
 * Sorting algorithm that works by repeatedly swapping the adjacent elements if
 * they are in wrong order.
 * Arguments: array - pointer to an unsorted array to be sorted.
 *			  array_length - the length of the array.
 * Compexity: O(n) - O(n^2)
 */
void BubbleSort(int array[], size_t array_length);

/* 
 * Sorts an array by repeatedly finding the minimum element (considering
 * ascending order) from unsorted part and putting it at the beginning. 
 * Arguments: array - pointer to an unsorted array to be sorted.
 *			  array_length - the length of the array.
 * Compexity: O(n^2)
 */
void SelectionSort(int array[], size_t array_length);

/* 
 * Sort an array by comparing every two consecutive elements, placing the
 * smaller in it's correct place in the array.
 * Arguments: array - pointer to an unsorted array to be sorted.
 *			  array_length - the length of the array.
 * Compexity: O(n) - O(n^2)
 */
void InsertionSort(int array[], size_t array_length);

/*
 * counting the number of objects having distinct key values (using a lut
 * table), adding the numbers and than placing the values using the arithmatic
 * made in the previous steps.
 * Arguments: array - pointer to an unsorted array to be sorted.
 *			  array_length - the length of the array.
 * Compexity: O(n)
 */
void CountingSort(int array[], size_t array_length);

/* 
 * Sort the array digit by digit starting from least significant digit to most
 * significant one. Number of passes on the array is as the number of digits in
 * the element with the biggest value (most digits) in the array.
 * Arguments: array - pointer to an unsorted array to be sorted.
 *			  array_length - the length of the array.
 * Compexity: O(n * k)
 */
void RadixSort(int array[], size_t array_length);

#endif /* SORTS_H */
