/*******************************************************************************
Written by Anat Wax, anatwax@gmail.com
Created: 21.9.20

Question 1:
You have pairs of strings – such as  aa , cf , df , rt, cf , bb, aa, cd , cf, rt

how would u design a system / what would u use in order to get :

- the frequency of each pair
- max frequency of the pairs

(write detaild explanations + runtimes)

Answer 1:
Psaudo:
1. create a map in the size of english alphabet * 2 (26 * 2)
2. use the combination as a key, and when inserting the map increase num in one
(a counter). complexity O(1)
3. create a stack caled "max". each time you increment a number in the map,
check if it is higher than the top of "max". if it is - push, else, do nothing.
complexity O(1)



Question 2:
Given the array of IDs, which contains many duplicate integers and one unique
integer, find the unique integer. All integers have one duplicate except the
unique integer. (write actual code) Input => [1,1,2,2,3,3,4] Output => 4
*******************************************************************************/
#include <stdio.h>  /* printf(), size_t */
#include <stdlib.h> /* malloc(), free(), abs(), size_t */
#include <string.h> /* size_t, atoi(), memset() */

int FindUnique(int array[], size_t length)
{
    int result = array[0];
    size_t i = 1;

    for (i = 1; i < length; ++i)
    {
        result ^= array[i];
    }

    return (result);
}

int main()
{
    int array[] = {1, 1, 2, 2, 3, 3, 4, 5, 7, 8, 7, 4, 8};
    size_t size = sizeof(array) / sizeof(array[0]);

    printf("%d\n", FindUnique(array, size));
    return (0);
}
