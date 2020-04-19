
#include "sorts.h"

/*utility functions*/

static void swap(int *x, int *y);

static int GetMax(int *arr, size_t size);

static void CountSort(int *arr, size_t size, int dgt);

/*main functions*/
void BubbleSort(int *arr, size_t size)
{
    size_t i = 0; 
    size_t j = 0;

    for (i = 0; i < size - 1; i++)
    {
        for ( j = 0; j < size -1 - i; j++)
        {
            if (arr[j] > arr[j + 1])
            {
                swap(&arr[j] , &arr[j + 1]);
            }
        }
        
    }
}

void SelestionSort(int *arr, size_t size)
{
    size_t i = 0; 
    size_t j = 0;
    int min_index = 0;

    for (i = 0; i < size - 1; i++)
    {
        min_index = i;

        for ( j = i + 1; j < size; j++)
        {
            if (arr[j] < arr[min_index])
            {
                min_index = j;
            }
        }
        swap(&arr[i] , &arr[min_index]);
    }
}

void InsertionSort(int *arr, size_t size)
{
    size_t i = 0; 
    int j = 0;
    int key = 0;

    for (i = 1; i < size; i++)
    {
        key = arr[i]; 
        j = i - 1; 

        while (0 <= j && arr[j] > key) 
        { 
            arr[j + 1] = arr[j]; 
            --j; 
        } 
        arr[j + 1] = key; 
    }
}

void RadixSort(int *arr, size_t size)
{
    int dgt = 1;
    int max = GetMax(arr, size);

    for (dgt = 1; max/dgt > 0; dgt *= 10) 
    {
        CountSort(arr, size, dgt);
    }    
}

/*utility functions*/

static void swap(int *x, int *y) 
{ 
    int temp = *x; 
    *x = *y; 
    *y = temp;  
} 

static int GetMax(int *arr, size_t size)
{
    size_t i = 0;
    int max = 0;

    for (i = 0; i < size; i++)
    {
        if (arr[i] > max)
        {
            max = arr[i];
        }
    }

    return (max);
}

static void CountSort(int *arr, size_t size, int exp)
{
    int output[size];  
    int i, count[10] = {0}; 
  
    for (i = 0; i < size; i++) 
    {
        count[ (arr[i]/exp)%10 ]++; 
    }
     
    for (i = 1; i < 10; i++) 
    {
        count[i] += count[i - 1]; 
    }

    for (i = size - 1; i >= 0; i--) 
    { 
        output[count[ (arr[i]/exp)%10 ] - 1] = arr[i]; 
        count[ (arr[i]/exp)%10 ]--; 
    } 
  
    for (i = 0; i < size; i++) 
    {
        arr[i] = output[i];
    }
} 
