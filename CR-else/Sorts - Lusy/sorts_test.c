/*******************************************************************************
File Name: sorts_test.c
Author: Lusy Volkov
Date: 31.3.20
Rewiever: Yaacov, Anat
*******************************************************************************/

#include <stdio.h> 		/* printf */
#include <time.h>		/* time */
#include <stdlib.h>		/* srand */
#include <string.h>		/* memcpy, memcmp */

#include "sorts.h"

/******************************utility functions*******************************/

int IsBefore(const void *a, const void *b);
void Swap(int *a, int *b);
void PrintIntArr(int *arr, size_t size);
size_t KeyToNum(const void *data, const void *args);

/* utility to compare two integer numbers */
static int CompNums(const void *num_1, const void *num_2)
{
	return (*(int *)num_1 - *(int *)num_2);
}

static void TestBubblesortEazy();
static void TestBubble();
static void TestSelectionsortEazy();
static void TestSelectionsort();
static void TestInsentionsortEazy();
static void TestInsentionsort();
static void TestCountingSortEazy();
static void TestCountingSort();
static void TestRadixSortEazy();
static void TestRadixSort();
static void TestMergeSort();
static void TestQuickSort();

/******************************************************************************/

int main()
{
	printf("\n");
	printf("BubbleSort Test\n");
	TestBubblesortEazy();
	TestBubble();
	
	printf("\n");
	printf("SelectionSort Test\n");
	TestSelectionsortEazy();
	TestSelectionsort();
	
	printf("\n");
	printf("InsertionSort Test\n");
	TestInsentionsortEazy();
	TestInsentionsort();
	
	printf("\n");
	printf("CountingSort Test\n");
	TestCountingSortEazy();
	TestCountingSort();
	
	printf("\n");
	printf("RadixSort Test\n");
	TestRadixSortEazy();
	TestRadixSort();
	
	printf("\n");
	printf("MergeSort Test\n");
	TestMergeSort();
	
	printf("\n");
	printf("QuickSort Test\n");
	TestQuickSort();
	
	return (0);
}


/******************************************************************************/
/* a very simple test */
static void TestBubblesortEazy()
{
	int arr[] = {5, 2, 3, 0, 10};
	size_t arr_size = 5;
	
	printf("Before sort:\n");
	PrintIntArr(arr, arr_size);
	
	BubbleSort(arr, arr_size);
	
	printf("After sort:\n");
	PrintIntArr(arr, arr_size);
}
/******************************************************************************/

static void TestBubble()
{
	size_t arr_size = 5000;
	size_t size_of_element = sizeof(int);
	int i = 0;
	
	clock_t bubble_time = 0;
	clock_t qsort_time = 0;
	clock_t end_time = 0;
	
	int *test_arr = (int *)malloc(arr_size * size_of_element);
	int *test_arr_sorted = (int *)malloc(arr_size * size_of_element);
	
	if (!test_arr || !test_arr_sorted)
	{
		printf("allocation failed\n");
	}
	
	i = 0;
	
	while (i < arr_size)
	{
		test_arr[i] = rand() % 30;
		++i;		
	}
	
	test_arr_sorted = memcpy(test_arr_sorted, test_arr, 
											arr_size * size_of_element);
	bubble_time = clock();
	BubbleSort(test_arr, arr_size);
	
	qsort_time = clock();
	qsort(test_arr_sorted, arr_size, sizeof(int), IsBefore);
	
	end_time = clock();
	
	if (0 == memcmp(test_arr, test_arr_sorted, arr_size * size_of_element))
	{
		printf("Bubblesort Passed\n");
		printf("the time diffrece is: %lu\n", (qsort_time-bubble_time) - 
												(end_time-qsort_time));
		printf("the proportion is: %lu\n", (qsort_time-bubble_time) /
														(end_time-qsort_time));
	}
	else
	{
		printf("Bubblesort Failed\n");
	}
	
	free(test_arr);
	free(test_arr_sorted);
}	
/******************************************************************************/

static void TestSelectionsortEazy()
{
	int arr[] = {5, 2, 3, 0, 10};
	size_t arr_size = 5;
	size_t size_of_element = sizeof(int);
	
	printf("Before sort:\n");
	PrintIntArr(arr, arr_size);
	
	SelectionSort(arr, arr_size, size_of_element, IsBefore);
	
	printf("After sort:\n");
	PrintIntArr(arr, arr_size);
}
/******************************************************************************/

static void TestSelectionsort()
{
	int *test_arr = NULL;
	int *test_arr_sorted = NULL;
	size_t arr_size = 5000;
	size_t size_of_element = sizeof(int);
	int i = 0;
	
	clock_t selection_time = 0;
	clock_t qsort_time = 0;
	clock_t end_time = 0;
	
	test_arr = (int*)malloc(arr_size * size_of_element);
	test_arr_sorted = (int*)malloc(arr_size * size_of_element);
	if (!test_arr || !test_arr_sorted)
	{
		printf("allocation failed line: %d\n", __LINE__);
		return;
	}
	
	i = 0;
	while (i < arr_size)
	{
		test_arr[i] = rand() % 30;
		++i;		
	}

	test_arr_sorted = memcpy(test_arr_sorted, test_arr, arr_size * 
															size_of_element);
	
	selection_time = clock();
	SelectionSort(test_arr, arr_size, size_of_element, IsBefore);
	
	qsort_time = clock();
	qsort(test_arr_sorted, arr_size, size_of_element, IsBefore);
	
	end_time = clock();
	
	printf("\n");
	
	if (0 == memcmp(test_arr, test_arr_sorted, arr_size * size_of_element))
	{
		printf("Selectionsort Passed\n");
		printf("  the time diffrece is: %lu\n", (qsort_time-selection_time) - 
												(end_time-qsort_time));
		printf("the proportion is: %lu\n", (qsort_time-selection_time) /
														(end_time-qsort_time));
	}
	else
	{
		printf("Selectionsort Failed line %d\n", __LINE__);
	}
	
	free(test_arr);
	free(test_arr_sorted);
}
/******************************************************************************/

static void TestInsentionsortEazy()
{
	int arr[] = {5, 2, 3, 0, 10};
	size_t arr_size = 5;
	
	printf("Before sort:\n");
	PrintIntArr(arr, arr_size);
	
	InsertionSort(arr, arr_size);
	
	printf("After sort:\n");
	PrintIntArr(arr, arr_size);
}
/******************************************************************************/

static void TestInsentionsort()
{
	size_t arr_size = 5000;
	size_t size_of_element = sizeof(int);
	int i = 0;
	
	clock_t insertion_time = 0;
	clock_t qsort_time = 0;
	clock_t end_time = 0;
	
	int *test_arr = (int *)malloc(arr_size * size_of_element);
	int *test_arr_sorted = (int *)malloc(arr_size * size_of_element);
	
	if (!test_arr || !test_arr_sorted)
	{
		printf("allocation failed line: %d\n", __LINE__);
	}
	
	i = 0;
	
	while (i < arr_size)
	{
		test_arr[i] = rand() % 30;
		++i;		
	}

	test_arr_sorted = memcpy(test_arr_sorted, test_arr, 
													arr_size * size_of_element);
	
	insertion_time = clock();
	InsertionSort(test_arr, arr_size);
	
	qsort_time = clock();
	qsort(test_arr_sorted, arr_size, sizeof(int), IsBefore);
	
	end_time = clock();
	
	printf("\n");
	
	if (0 == memcmp(test_arr, test_arr_sorted, arr_size*size_of_element))
	{
		printf("Insertionsort Passed\n");
		printf("  the time diffrece is: %lu\n", (qsort_time-insertion_time) - 
												(end_time-qsort_time));
		printf("the proportion is: %lu\n\n", (qsort_time-insertion_time) /
														(end_time-qsort_time));
	}
	else
	{
		printf("Insertionsort Failed\n");
	}
	
	free(test_arr);
	free(test_arr_sorted);
}
/******************************************************************************/

static void TestCountingSortEazy()
{
	int arr[] = {5, 2, 3, 0, 10};
	size_t arr_size = 5;
	size_t range = 11;
	
	printf("Before sort:\n");
	PrintIntArr(arr, arr_size);
	
	CountingSort(arr, arr_size, range);
	
	printf("After sort:\n");
	PrintIntArr(arr, arr_size);
}
/*****************************************************************************/

static void TestCountingSort()
{
	int *test_arr = NULL;
	int *test_arr_sorted = NULL;
	size_t arr_size = 5000;
	size_t range = 100;
	size_t size_of_element = sizeof(int);
	int i = 0;
	int status = 0;
	
	clock_t counting_time = 0;
	clock_t qsort_time = 0;
	clock_t end_time = 0;
	
	test_arr = (int *)malloc(arr_size * size_of_element);
	test_arr_sorted = (int *)malloc(arr_size * size_of_element);
	
	if (!test_arr || !test_arr_sorted)
	{
		printf("allocation failed line: %d\n", __LINE__);
	}
	
	i = 0;
	
	while (i < arr_size)
	{
		test_arr[i] = rand() % range;
		++i;		
	}
	
	test_arr_sorted = memcpy(test_arr_sorted, test_arr, arr_size * size_of_element);
	
	counting_time = clock();
	CountingSort(test_arr, arr_size, range);
	
	qsort_time = clock();
	qsort(test_arr_sorted, arr_size, size_of_element, IsBefore); 
	
	end_time = clock();
	
	if (0 == status)
	{
		if (!memcmp(test_arr, test_arr_sorted, arr_size * size_of_element))
		{
			printf("\nCountingSort Passed\n");
			printf("my time: %lu\n", (qsort_time - counting_time));
			printf("qsort time: %lu\n", (end_time - qsort_time));
			printf("mine is faster: %f\n",(end_time - qsort_time)/
												(double)(qsort_time - counting_time));
		}
		
		else
		{
			printf("CountingSort Failed\n");
		}
	}
	else 
	{
		printf("allocation failed\n");
	}
	
	free(test_arr);
	free(test_arr_sorted);	
}
/******************************************************************************/

static void TestRadixSortEazy()
{
	int arr[] = {5, 2, 3, 255, 1, 16, 0, 2};
	size_t arr_size = 8;
	
	printf("Before sort:\n");
	PrintIntArr(arr, arr_size);
	
	RadixSort(arr, arr_size, sizeof(int), KeyToNum, NULL);
	
	printf("After sort:\n");
	PrintIntArr(arr, arr_size);
}

/*****************************************************************************/

static void TestRadixSort()
{
	int *test_arr = NULL;
	int *test_arr_sorted = NULL;
	size_t arr_size = 500000;
	/*size_t range = 100;*/
	size_t size_of_element = sizeof(int);
	int i = 0;
	int status = 0;
	
	clock_t radix_time = 0;
	clock_t qsort_time = 0;
	clock_t end_time = 0;
	
	test_arr = (int*)malloc(arr_size * size_of_element);
	test_arr_sorted = (int*)malloc(arr_size * size_of_element);
	
	if (!test_arr || !test_arr_sorted)
	{
		printf("allocation failed line: %d\n", __LINE__);
		return;
	}
	
	i = 0;
	while (i < arr_size)
	{
		test_arr[i] = rand();
		++i;		
	}
	
	
	test_arr_sorted = memcpy(test_arr_sorted, test_arr, arr_size*size_of_element);
	
	radix_time = clock();
	RadixSort(test_arr, arr_size, size_of_element, KeyToNum, NULL);

	qsort_time = clock();
	qsort(test_arr_sorted, arr_size, size_of_element, IsBefore); 
	
	end_time = clock();
	
	if (0 == status)
	{
		if (memcmp(test_arr, test_arr_sorted, arr_size*size_of_element) == 0)
		{
			printf("\nRadixSort Passed\n");
			printf("my time: %lu\n", (qsort_time-radix_time));
			printf("qsort time: %lu\n", (end_time-qsort_time));
			printf("mine is faster: %f\n", (end_time-qsort_time)/
												(double)(qsort_time-radix_time));
		}
		else
		{
			printf("RadixSort Failed\n ");
		}
	}
	else 
	{
		printf("allocation failed\n");
	}
	
	free(test_arr);
	free(test_arr_sorted);
}
/*****************************************************************************/

static void TestMergeSort()
{
	int arr[10] = {0};

	size_t i = 0;	
	
/* Initialize arr with random values. */
	for (i = 0; i < 10; ++i)
	{
		arr[i] = rand() % 100;
	}
	
	printf("Before sort:\n");
	PrintIntArr(arr, 10);
	
	/* Sort arr */
	MergeSort(arr, 10);

	printf("After sort:\n");
	PrintIntArr(arr, 10);
}
/*****************************************************************************/

static void TestQuickSort()
{
	int arr[10] = {77, 43, 90, 2, 65, 80, 73, 1, 5, 10};
	
	printf("Before sort:\n");
	PrintIntArr(arr, 10);
	
	/* Sort arr */
	QuickSort(arr, 10, CompNums);

	printf("After sort:\n");
	PrintIntArr(arr, 10);
}
/*****************************************************************************/











