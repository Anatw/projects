/*******************************************************************************
GCD = freatest common devisor
*******************************************************************************/
#include <stdio.h>  /* printf(), size_t */
#include <stdlib.h> /* malloc(), free(), abs(), size_t */
#include <assert.h> /* assert() */
#include <stddef.h> /* offsetof(), size_t */
#include <time.h>   /* time, size_t, srand() */
#include <unistd.h> /* ssize_t, sleep(), execvp(), fork() */
#include <string.h> /* size_t, atoi(), memset() */
/*
int FindGDC(int first, int second)
{
    int r = first;
    int q = first;
    int temp = 0;

    if (second > first)
    {
        temp = first;
        first = second;
        second = temp;
    }

    while (0 != r)
    {
        q = second / first;
        r = second % first;
        temp = r;
        second = first * q + r;
        second = first;
        first = r;
    }

    return (temp);
}*/

void FindGDC(int first, int second)
{
    first = (first < 0 ? -first : first);
    second = (second < 0 ? -second : second);

    while (first != second)
    {
        if (first > second)
        {
            first -= second;
        }
        else
        {
            second -= first;
        }
    }

    printf("%d\n", first);
}

int main()
{
    int first = 1701;
    int second = 3768;

    FindGDC(first, second); /* should be 3 */

    return (0);
}
