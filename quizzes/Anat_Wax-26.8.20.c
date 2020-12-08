/*******************************************************************************
Given a set of positive ints, find if it can be divided into two subsets with
equal sum.

For example: S  = {3, 1, 1, 2, 2, 1}
Answer: yes
S1 = { 1,1,1,2 }
S2 = { 2,3 }

Written by Anat Wax, anatwax@gmail.com
Created: 26.8.20
*******************************************************************************/
#include <assert.h> /* assert() */
#include <stdio.h>  /* printf(), size_t */
#include <stdlib.h> /* malloc(), free(), abs(), size_t */
#include <string.h> /* size_t, atoi(), memset() */
#include <unistd.h> /* ssize_t, sleep(), execvp(), fork() */

static void QuickSortRecursive(int array[], int base, int top,
                               int (*compare)(const void* first,
                                              const void* second, void* arg),
                               void* arg);
/* Utility functions: */

void Qsort(void* base, size_t nmemb, size_t size,
           int (*compare)(const void* first, const void* second, void* arg),
           void* arg)
{
    (void)size;
    QuickSortRecursive(base, 0, (nmemb - 1), compare, arg);
}

static int Compare(const void* first, const void* second, void* arg)
{
    (void)arg;
    return (*(int*)first - *(int*)second);
}

static void Swap(int* a, int* b)
{
    int temp = *a;
    *a = *b;
    *b = temp;
}

static int Partition(int array[], int base, int top,
                     int (*compare)(const void* first, const void* second,
                                    void* arg),
                     void* arg)
{
    int pivot = array[top];
    int index = (base - 1);
    int array_index = 0;

    for (array_index = base; array_index <= (top - 1); ++array_index)
    {
        /* if current element is smaller the pivot - swap to left */
        if (0 > (compare(&array[array_index], &pivot, arg)))
        {
            ++index;
            Swap(&array[index], &array[array_index]);
        }
    }
    /* insert pivot to place: */
    Swap(&array[index + 1], &array[top]);
    return (index + 1);
}

static void QuickSortRecursive(int array[], int base, int top,
                               int (*compare)(const void* first,
                                              const void* second, void* arg),
                               void* arg)
{
    int partition = 0;

    assert(array && compare);

    if (base < top)
    {
        partition = Partition(array, base, top, compare, arg);

        QuickSortRecursive(array, base, (partition - 1), compare, arg);
        QuickSortRecursive(array, (partition + 1), top, compare, arg);
    }
}

/******************************************************************************/

int DevideAndEqual(int array[], size_t size)
{
    int sum = array[0];
    int search_sum = 0;
    size_t i = 0;

    size_t end;
    int current_sum = 0;

    for (i = 1; i < size; ++i)
    {
        sum += array[i];
    }

    if (0 != (sum % 2)) /* odd number */
    {
        return 0;
    }

    search_sum = sum / 2;

    Qsort(array, size, sizeof(array[0]), Compare, NULL);
    i = 0;
    end = 1;

    if (array[size] > search_sum)
    {
        return 0;
    }

    current_sum = array[0];
    while (current_sum != search_sum && i < end)
    {
        while (end < size)
        {
            if (current_sum == search_sum)
            {
                return 1;
            }
            else if (current_sum < search_sum)
            {
                current_sum += array[end];
                ++end;
            }
            else
            {
                if (end != 1)
                {
                    current_sum -= array[i];
                    ++i;
                }
                else
                {
                    return 0;
                }
            }
        }
    }

    if (current_sum == search_sum)
    {
        return 1;
    }

    return 0;
}

/******************************************************************************/

int Test1()
{
    int array[] = {3, 1, 1, 2, 2, 1};
    size_t size = sizeof(array) / sizeof(array[0]);

    printf("%d\n", DevideAndEqual(array, size));
    return (DevideAndEqual(array, size));
}

int Test2()
{
    int array[] = {1, 2, 3, 4, 5, 5, 4, 3, 2, 1};
    size_t size = sizeof(array) / sizeof(array[0]);

    printf("%d\n", DevideAndEqual(array, size));
    return (DevideAndEqual(array, size));
}

int Test3()
{
    int array[] = {1, 2};
    size_t size = sizeof(array) / sizeof(array[0]);

    printf("%d\n", DevideAndEqual(array, size));
    return (DevideAndEqual(array, size));
}

int main()
{
    int array[] = {1, 2, 3, 4, 5, 5, 4, 3, 2, 1};
    size_t size = sizeof(array) / sizeof(array[0]);

    printf("%d\n", DevideAndEqual(array, size));

    return (0);
}
