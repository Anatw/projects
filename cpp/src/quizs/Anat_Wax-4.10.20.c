/*******************************************************************************
Given an array of elements find the element that occurs more than 50% of the
time. I want you to:
* think brute force / naive o(n^2)
*then think how you can do it in o(nlgn)
*then o(n)
all the above with the necessary space complexity tradeoffs.
Then – please read aobut Moore’s (voting) algo – have another algo in your
tool-kit :) private static void findMajority(int[] arr)


Written by Anat Wax, anatwax@gmail.com
Created: 4.10.20
*******************************************************************************/
#include <stdio.h>  /* printf(), size_t */
#include <stdlib.h> /* malloc(), free(), abs(), size_t */
#include <string.h> /* size_t, atoi(), memset() */

#define VISITED (533422123)
#define DNDBUG

/* If each element appear only once the software will return -1 */
static int findMajority(int arr[], size_t size)
{
    size_t max = 0;
    size_t temp_max = 0;
    size_t former = 0;
    size_t later = 1;
    int max_occur = 0;
    int* array = arr;
#ifdef DNDBUG
    int counter = 0;
#endif

    while (former < size)
    {
        later = former + 1;
        temp_max = 0;

        while (later < size)
        {
            if (array[former] == array[later])
            {
                ++temp_max;
                array[later] = VISITED;
            }

            ++later;
#ifdef DNDBUG
            ++counter;
#endif
        }

        if (temp_max >= max)
        {
            max = temp_max;
            max_occur = former;
        }

        ++former;

        while (VISITED == array[former])
        {
            ++former;
        }
    }

    if (0 == max)
    {
        return (-1);
    }

    if (max <= (size / 2))
    {
        return (-1);
    }

    return (array[max_occur]);
}

void Test1()
{
    int array[] = {1, 2, 3, 4, 1, 1, 2, 3, 4, 1, 1, 6, 6, 6, 6, 2, 2, 5, 5};
    size_t length = sizeof(array) / sizeof(array[0]);

    printf("%d\n", findMajority(array, length));
}

void Test2()
{
    int array[] = {1, 2, 3, 4};
    size_t length = sizeof(array) / sizeof(array[0]);

    printf("%d\n", findMajority(array, length));
}

void Test3()
{
    int array[] = {1, 2, 3, 4, 1, 1, 2, 3, 4, 1, 1, 1, 1,
                   1, 1, 1, 1, 1, 1, 1, 1, 6, 2, 2, 5, 5};
    size_t length = sizeof(array) / sizeof(array[0]);

    printf("%d\n", findMajority(array, length));
}

int main()
{
    Test1();
    Test2();
    Test3();

    return (0);
}

/*
static int findMajority(int array[], size_t size)
{
    int max = 0;
    int temp_max = 0;
    size_t former = 0;
    size_t later = 1;
    int max_occur = 0;

    while (former < size)
    {
        later = former + 1;

        while (later < size)
        {
            if (array[former] == array[later])
            {
                ++temp_max;
            }

            ++later;
        }

        if (temp_max >= max)
        {
            max = temp_max;
            max_occur = former;
        }

        ++former;
    }

    if (0 == max)
    {
        return (-1);
    }

    return (array[max_occur]);
}
*/
