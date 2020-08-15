/*******************************************************************************
Given an array A of integers of size n. Build another array B of the same size,
such that each element B[i] is the multiplication of all elements from array A,
except from A[i]. Time complexity: O(n).

Good luck, should be super easy for you guys!
Answer should be a function that receives two pointers representing a and b.
(and whatever else you think it should receive)

Written by Anat Wax, anatwax@gmail.com
Created: 11.8.20

*******************************************************************************/
#include <assert.h> /* assert() */
#include <stddef.h> /* offsetof(), size_t */
#include <stdio.h>  /* printf(), size_t */
#include <stdlib.h> /* malloc(), free(), abs(), size_t */
#include <string.h> /* size_t, atoi(), memset() */
#include <time.h>   /* time, size_t, srand() */
#include <unistd.h> /* ssize_t, sleep(), execvp(), fork() */

void MultipleArray(int array_a[], int array_b[], size_t n)
{
    size_t total_sum = 1;
    unsigned int i = 0;
    int count_zeros = 0;
    int first_zero = (-1);

    for (i = 0; i < n; ++i)
    {
        if (0 == array_a[i])
        {
            if ((-1) == first_zero)
            {
                first_zero = i;
            }

            ++count_zeros;
            ++i;
        }

        total_sum *= array_a[i];
    }

    if (0 == count_zeros)
    {
        for (i = 0; i < n; ++i)
        {
            array_b[i] = total_sum / array_a[i];
        }
    }
    else if (1 < count_zeros) /* at least 1 zero */
    {
        for (i = 0; i < n; ++i)
        {
            array_b[i] = 0;
        }
    }
    else /* count_zeros = 1 - all should be 0s, and the one how is '0' should be
            the rest */
    {
        for (i = 0; i < n; ++i)
        {
            if (i != first_zero)
            {
                array_b[i] = 0;
            }
            else
            {
                array_b[i] = total_sum;
            }
        }
    }
}

void PrintArray(int array[], size_t n)
{
    unsigned int i = 0;

    for (i = 0; i < n; ++i)
    {
        printf("%d, ", array[i]);
    }

    printf("\n");
}

int main()
{
    /*size_t size = 8;
    int array[] = {1, 2, 3, 4, 0, 5, 0, 6};
    int result[8] = {0};*/

    size_t size = 7;
    int array[] = {1, 2, 3, 4, 0, 5, 6};
    int result[7] = {0};

    printf("array:\n");
    PrintArray(array, size);

    MultipleArray(array, result, size);

    printf("result:\n");
    PrintArray(result, size);

    return (0);
}

/* Changes needed:
 comparison between signed and unsigned integer expressions.
*/
