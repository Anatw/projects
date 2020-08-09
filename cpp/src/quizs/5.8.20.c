/*******************************************************************************
Write a function that receives a sorted array of integers and an integer sum,
and finds if 2 values in the array sums to the given value.
Example: for the array { 2,5,7,8,11,15 } and the sum 16,
the function should return 5, 11

Templates + STL (Histo)
Written by Anat Wax, anatwax@gmail.com
Created: 5.8.20
Reviewer:
*******************************************************************************/
#include <assert.h> /* assert() */
#include <stddef.h> /* offsetof(), size_t */
#include <stdio.h>  /* printf(), size_t */
#include <stdlib.h> /* malloc(), free(), abs(), size_t */
#include <string.h> /* size_t, atoi(), memset() */
#include <time.h>   /* time, size_t, srand() */
#include <unistd.h> /* ssize_t, sleep(), execvp(), fork() */

int HasSum(int array[], size_t size, const int sum, int result[2])
{
    int left = 0;
    int right = size - 1;
    int current_sum = 0;

    while (left < right)
    {
        current_sum = array[left] + array[right];

        if (sum == current_sum)
        {
            result[0] = left;
            result[1] = right;

            return (1);
        }
        else if (sum < current_sum)
        {
            --right;
        }
        else
        {
            ++left;
        }
    }

    return (0);
}

int main()
{
    int array[] = {2, 5, 7, 8, 11, 15};
    int array_len = (sizeof(array) / sizeof(array[0]));
    int sum = 16;
    int result[2] = {0};
    int has_sum = 0;

    printf("array length = %d\n", array_len);

    has_sum = HasSum(array, array_len, sum, result);

    printf("sum was%sfound\n", (has_sum == 1) ? " " : " not ");
    if (has_sum)
    {
        printf("first index = %d, int = %d\nsecond index = %d, int = %d\n",
               result[0], array[result[0]], result[1], array[result[1]]);
    }

    return (0);
}

/*
Needed to chenge for correctnes:
1. int right need to be "size-1" and not "size";
(2. I think i should return the indexes and not the numbers inside indexes, as
the question applys)
*/
