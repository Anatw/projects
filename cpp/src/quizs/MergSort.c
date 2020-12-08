/*******************************************************************************
Comment and un-comment the defines to see both phases (one at a time).

WS name
Templates + STL (Histo)
Written by Anat Wax, anatwax@gmail.com
Created: 15.6.20
Reviewer:
*******************************************************************************/
#include <stdio.h>  /* printf(), int */
#include <stdlib.h> /* malloc(), free(), abs(), int */
#include <string.h> /* int, atoi(), memset() */

void Merge(int array[], int left, int middle, int right)
{
    /*
    INITIALIZATION:
    Create three indexes - one for each of the three arrays - general, temp
    right and temp left:
    */
    int left_index = 0;
    int right_index = 0;
    int index = left;

    /*
    PHASE A:
    Prepare to make two temp arrays for the left and right parts of the
    array.
    */
    int left_size = middle - left + 1;
    int right_size = right - middle;

    int* array_left = (int*)malloc(sizeof(int) * left_size);
    int* array_right = (int*)malloc(sizeof(int) * right_size);

    for (; left_index < left_size; ++left_index)
    {
        array_left[left_index] = array[left + left_index];
    }

    for (; right_index < right_size; ++right_index)
    {
        array_right[right_index] = array[middle + 1 + right_index];
    }

    /*
    PHASE B-1:
    Actual sorting and merging back the two halfs in tow steps:
    1. While there are elements in BOTH arrays - compering and inserting to the
    sortes array.
    2. Inserting any elements remaining in ONE of the arrays (the other one will
    not have any elements left in it).
    */
    left_index = 0;
    right_index = 0;

    while (left_index < left_size && right_index < right_size)
    {
        if (array_left[left_index] <= array_right[right_index])
        {
            array[index] = array_left[left_index];
            ++left_index;
        }
        else
        {
            array[index] = array_right[right_index];
            ++right_index;
        }

        ++index;
    }

    /*
    PHASE B-2:
    while there is anything left in any of the halfs - copy it into sorted:
    */
    while (left_index < left_size)
    {
        array[index] = array_left[left_index];
        ++left_index;
        ++index;
    }

    while (right_index < right_size)
    {
        array[index] = array_right[right_index];
        ++right_index;
        ++index;
    }

    free(array_left);
    array_left = NULL;

    free(array_right);
    array_right = NULL;
}

void MergSort(int array[], int left, int right)
{
    int middle = 0;

    if (left >= right)
    {
        return;
    }

    middle = (left + right) / 2;
    MergSort(array, left, middle);
    MergSort(array, (middle + 1), right);

    Merge(array, left, middle, right);
}

void PrintArray(int array[], int size)
{
    int index = 0;

    for (; index < size; ++index)
    {
        printf("%d, ", array[index]);
    }

    printf("\n");
}

int main()
{
    int array[] = {1, 7, 4, 8, 0, 3, 45, 89, 66};
    int size = sizeof(array) / sizeof(array[0]);

    printf("Before:\n");
    PrintArray(array, size);
    MergSort(array, 0, (size - 1));

    printf("After:\n");
    PrintArray(array, size);

    return (0);
}
