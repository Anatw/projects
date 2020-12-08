/*******************************************************************************
                          Written by Anat Wax
                            June 7th, 2020
*******************************************************************************/
#include <stddef.h> /* offsetof(), size_t */
#include <stdlib.h> /* malloc(), free(), abs(), size_t */
#include <assert.h> /* assert() */
#include <time.h>   /* time, size_t, srand() */
#include <unistd.h> /* ssize_t, sleep(), execvp(), fork() */
#include <stdio.h>  /* printf(), size_t */
#include <string.h> /* size_t, atoi(), memset() */

#include "utility.h"

void SwapChar(char *x, char *y)
{
    char temp = *x;
    *y = *x;
    *x = temp;
}

void CircularShift(char array[], int shift_by, int length)
{
    int remain = 0;
    int i = 0;

    printf("length: %d\n", length);

    shift_by = shift_by % length;
    remain = length - shift_by;

    printf("shift_by: %d\n", shift_by);
    printf("remain: %d\n", length);

    for (i = 0; i < (length - remain); ++i, ++remain)
    {
        SwapChar(&array[i], &array[shift_by]);
    }

    for (i = shift_by; i < length; ++i)
    {
        SwapChar(&array[i], &array[i + 1]);
    }
}

int main()
{
    char array[] = "metabolism";
    int length = (int)sizeof(array) - 1;
    int shift_by = 7;

    system("clear");
    printf("\n\nArray before shift: %s\n", array);

    CircularShift(array, shift_by, length);
    printf("Array after shift: %s\n", array);

    return (0);
}
