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
 * so that the first of every two adjacent elements is smaller than the second.
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
 * Compexity: O(n) - O(n^2)
 */
void InsertionSort(int array[], size_t array_length);

/*
 * Counting the number of objects having distinct key values (using a lut
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

/*
 * Algorithem to recursivly seperate and than merge while sorting of an array.
 * Return - 0 in case of success.
 * 			1 in case of error.
 * Arguments: arr_to_sort - array to be sorted.
 * 			  num_elements - number of elements in the array.
 * Complexity: O(n log n) (going over each half of the array (2(T(n/2)))
 * 			   and merging the entire array (n) => T(n)=2(T(n/2))+n => O(nlogn))
 */
int MergeSort(int *arr_to_sort, size_t num_elements);
int Merge(int *array, size_t base, size_t middle, size_t upper);

/*
 * Algorithem devides the list to two based on a pivot point (last element).
 * than each half (left - smaller than pivot, and right - larger than pivot)
 * is quick-sorted recursivly.
 * Arguments: base - array to sort.
 *            nmemb - number of elements in array.
 *            size - size of an element of the array.
 *            compar - return int:
 *                   - smaller than 0 if  first < second.
 *                   - bigger than zero if first > second.
 *                   - 0 if first == second. in that case, the order of sorting
 *                          is undefined.
 *            arg - argument fo the Compar function.
 * Complexity: O(n log n) - O(n^2) (best case scenario - the pivot is always 
 *             the mid-size element in the array. Worst case scenario -
 *             the pivot is always the smallest/larggest element in the array).
 */
void Qsort(void *base, size_t nmemb, size_t size,
           int (*Compar)(const void *first, const void *second,
           void *arg), void *arg);


#endif /* SORTS_H */
