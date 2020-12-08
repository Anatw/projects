/*******************************************************************************
Given an array nums, there is a sliding window of size k which is moving from
the very left of the array to the very right. You can only see the k numbers in
the window. Each time the sliding window moves right by one position. Return the
max sliding window. Example: Input: nums = [1,3,-1,-3,5,3,6,7], and k = 3
Output: [3,3,5,5,6,7]
Explanation:
Window position Max
--------------- -----
[1 3 -1] -3 5 3 6 7 3
1 [3 -1 -3] 5 3 6 7 3
1 3 [-1 -3 5] 3 6 7 5
1 3 -1 [-3 5 3] 6 7 5
1 3 -1 -3 [5 3 6] 7 6
1 3 -1 -3 5 [3 6 7] 7
Note:
You may assume k is always valid, 1 ≤ k ≤ input array's size for non-empty
array. Could you solve it in linear time?

Written by Anat Wax, anatwax@gmail.com
Created: 15.6.20
Reviewer:
*******************************************************************************/
#include <stdio.h>  /* printf(), size_t */
#include <stdlib.h> /* malloc(), free(), abs(), size_t */
#include <string.h> /* size_t, atoi(), memset() */

int* MaxSlidingWindow(int array[], size_t size, size_t k)
{
    int current_max = 0;
    size_t i = k;
    size_t j = 1;
    size_t left = 0;
    int result_index = 0;
    int* result = (int*)malloc(sizeof(int) * (size - 2));

    /* check max of first window: */
    for (j = 0; j < k; ++j)
    {
        if (array[j - 1] > array[j])
        {
            current_max = array[j - 1];
        }
        else
        {
            {
                current_max = array[j];
            }
        }
    }

    result[result_index++] = current_max;

    while (i < size) /* i starts after first window */
    {
        /* if last window's max is bigger than current and is still relevant to
         * the current window: */
        if ((current_max < array[i]) && (j != left))
        {
            current_max = array[i];
        }
        else /* (current_max > array[i]) */
        {
            ;
        }

        result[result_index++] = current_max;

        ++left;
        ++j;
        ++i;
    }

    return (result);
}

int main()
{
    int array[] = {1, 3, -1, -3, 5, 3, 6, 7};
    size_t k = 3;

    size_t size = sizeof(array) / sizeof(array[0]);
    int* result = MaxSlidingWindow(array, size, k);

    for (k = 0; k < (size - 2); ++k)
    {
        printf("%d, ", result[k]);
    }
    printf("\n");

    return (0);
}
