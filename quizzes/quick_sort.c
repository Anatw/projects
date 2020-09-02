/*******************************************************************************
Comment and un-comment the defines to see both phases (one at a time).

WS name
Templates + STL (Histo)
Written by Anat Wax, anatwax@gmail.com
Created: 15.6.20
Reviewer:
*******************************************************************************/
#include <stdio.h>  /* printf(), size_t */
#include <stdlib.h> /* malloc(), free(), abs(), size_t */
#include <string.h> /* size_t, atoi(), memset() */

void Swap(int* a, int* b)
{
    int temp = *a;

    *a = *b;
    *b = temp;
}

int Partition(int array[], int left, int right,
              int pivot) /* Function to sort the receieved part of the array */
{
    while (left < right)
    {
        while (array[left] < pivot)
        {
            ++left;
        }

        while (array[right] > pivot)
        {
            --right;
        }

        if (array[left] >= array[right])
        {
            Swap(&array[left], &array[right]);
            ++left;
            --right;
        }
    }

    /* Swap(&array[pivot], &array[right]);*/

    return (left);
}
/* 1 5 9 6 7 2 4  | pivot = 4*/
/* 1 2 4 6 7 5 9 */

void PrintArray(int array[], size_t size)
{
    size_t i = 0;
    for (i = 0; i < size; ++i)
    {
        printf("%d, ", array[i]);
    }
    printf("\n");
}

/* recursive function to part the array into partition */
void QuickSort(int array[], int left, int right)
{
    int pivot = 0;
    int to_part = 0;

    if (left >= right)
    {
        return;
    }

    pivot = (left + right) / 2;
    to_part = Partition(array, left, right, array[pivot]);
    QuickSort(array, left, (to_part - 1));
    QuickSort(array, to_part, right);
}

int main()
{
    int array[] = {1, 5, 9, 6, 7, 2, 4};
    int size = sizeof(array) / sizeof(array[0]);
    int left = 0;

    PrintArray(array, size);

    QuickSort(array, left, (size - 1));

    PrintArray(array, size);

    return (0);
}

/*printf("\narray->right\n");
PrintArray(array, right);

 printf("array->to_part\n");
 PrintArray(array, to_part);*/
