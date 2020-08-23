/*******************************************************************************
write a function that receives an array of integers (will not include then
number 0), each number in the array appear twice except *two* that appear only
once. find these two numbers and return them.

Written by Anat Wax, anatwax@gmail.com
Created: 18.8.20
*******************************************************************************/
#include <assert.h> /* assert() */
#include <stddef.h> /* offsetof(), size_t */
#include <stdio.h>  /* printf(), size_t */
#include <stdlib.h> /* malloc(), free(), abs(), size_t */
#include <string.h> /* size_t, atoi(), memset() */
#include <time.h>   /* time, size_t, srand() */
#include <unistd.h> /* ssize_t, sleep(), execvp(), fork() */

#include <stdio.h>

int* FindSingular(int array[], size_t size)
{
    int result1 = 0;
    int result2 = 0;
    size_t i = 0;
    int* return_arr = (int*)malloc(sizeof(int) * 2);

    for (i = 0; i < size; ++i)
    {
        result1 ^= array[i];
    }

    i = 1;
    i <<= 1;

    while (!(result1 & i))
    {
        i <<= 1;
        ++i;
    }

    result1 = 0;

    while (size)
    {
        if (*(array + size - 1) & (1 << i))
        {
            result1 ^= *(array + size - 1);
        }
        else
        {
            result2 ^= *(array + size - 1);
        }

        --size;
    }

    return_arr[0] = result1;
    return_arr[1] = result2;

    return (return_arr);
}

int main()
{
    int array[] = {5, 9, 9, 7, 5, 3, 3, 2, 6, 2, 6, 1};
    int* result_array = FindSingular(array, 12);

    printf("%d, %d\n", result_array[0], result_array[1]);

    return (0);
}
