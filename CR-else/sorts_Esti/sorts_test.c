#include <stdio.h> /*printf()*/
#include <stdlib.h>  /*rand()*/
#include <time.h> 

#include "sorts.h" 

#define ARR_SIZE (5000)

/*test functions decleration*/

void BubbleSortTest(int *arr, size_t size);

void SelestionSortTest(int *arr, size_t size);

void InsertionSortTest(int *arr, size_t size);

/*Print Array*/

void PrintArr(int *arr, size_t size);

/*main*/

int main()
{
    int arr1[ARR_SIZE];
    int arr2[ARR_SIZE];
    int arr3[ARR_SIZE];   
    int rand_num = 0; 
    size_t size = ARR_SIZE;
    size_t i = 0;

    for (i = 0; i < size; i++)
    {
        rand_num = rand() % 100 + 1;
        arr1[i] = rand_num;
        arr2[i] = rand_num;
        arr3[i] = rand_num;
    }
    
    BubbleSortTest(arr1, size);

    SelestionSortTest(arr2, size);

    InsertionSortTest(arr3, size);

    return (0);
}

/*test functions implementation*/

void BubbleSortTest(int *arr, size_t size)
{
    clock_t difference = 0;
    int msec = 0;
    clock_t before = clock();
    
    /*PrintArr(arr, size);*/

    BubbleSort(arr, size);

    /*PrintArr(arr, size);*/

    difference = clock() - before;
    msec = difference * 1000 / CLOCKS_PER_SEC;

    printf("Time taken for bubble sort %d seconds %d milliseconds\n", (msec / 1000), (msec % 1000));
}

void SelestionSortTest(int *arr, size_t size)
{
    clock_t difference = 0;
    int msec = 0;
    clock_t before = clock();
    
    /*PrintArr(arr, size);*/
    
    SelestionSort(arr, size);

    /*PrintArr(arr, size);*/

    difference = clock() - before;
    msec = difference * 1000 / CLOCKS_PER_SEC;

    printf("Time taken for selestion sort %d seconds %d milliseconds\n", (msec / 1000), (msec % 1000));
}

void InsertionSortTest(int *arr, size_t size)
{
    clock_t difference = 0;
    int msec = 0;
    clock_t before = clock();

    /*PrintArr(arr, size);*/

    InsertionSort(arr, size);

    /*PrintArr(arr, size);*/

    difference = clock() - before;
    msec = difference * 1000 / CLOCKS_PER_SEC;

    printf("Time taken for insertion sort %d seconds %d milliseconds\n", (msec / 1000), (msec % 1000));
}


void PrintArr(int *arr, size_t size)
{
    size_t i = 0;

    for (; i < size; i++)
    {
        printf("%d ", arr[i]);
    }
    printf("\n");
}
