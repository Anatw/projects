/*******************************************************************************
Rotate an array of chars in place.

Written by Anat Wax, anatwax@gmail.com
*******************************************************************************/
#include <assert.h> /* assert() */
#include <stddef.h> /* offsetof(), size_t */
#include <stdio.h>  /* printf(), size_t */
#include <stdlib.h> /* malloc(), free(), abs(), size_t */
#include <string.h> /* size_t, atoi(), memset() */
#include <time.h>   /* time, size_t, srand() */
#include <unistd.h> /* ssize_t, sleep(), execvp(), fork() */

void Reverse(char* array, size_t num)
{
    /*size_t len = strlen(array);*/
    size_t i = 0;
    char temp = 0;
    size_t from_end = num - 1;
    /*num -= 1;*/

    for (; i <= from_end; ++i, --from_end)
    {
        temp = array[i];
        array[i] = array[from_end];
        array[from_end] = temp;
    }
}

void RotateLeft(char* array, size_t n)
{
    size_t len = strlen(array);

    Reverse(array, (n - 1));
    Reverse(array + n, (len - n));
    Reverse(array, len);
}

int main()
{
    char string[] = "alhambra";
    printf("before:\n%s\n", string);

    RotateLeft(string, 3);
    printf("after:\n%s\n", string);

    return (0);
}
