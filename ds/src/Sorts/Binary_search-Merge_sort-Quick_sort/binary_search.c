/*******************************************************************************
					  		 Written by Anat Wax
						   14-15 of April 3rd, 2020
							Reviewer: Haim Sa'adia
*******************************************************************************/
#include <stdio.h> /* printf(), size_t */

#define NOT_FOUND (101010101)

/*
 * Algorithem to recursuvely find data in a binary search.
 * Return: if found - the index in the array where the data was found. If not,
 *         the number: 1010101010101.
 * Arguments: array - array to search data in.
 *            base - element in the array from which to start the search from. 
 *            size - number of elements in the array.
 *            data - the data to search for in the array.
 * Complexity: O(n log n)
 */
int RecursiveBinarySearch(int array[], size_t base, size_t size, int data);

/*
 * Algorithem to iterativly find data in a binary search.
 * Return: if found - the index in the array where the data was found. If not,
 *         the number: 1010101010101.
 * Arguments: array - array to search data in.
 *            base - element in the array from which to start the search from. 
 *            size - number of elements in the array.
 *            data - the data to search for in the array.
 * Complexity: O(n log n)
 */
int IterativeBinarySearch(int array[], size_t base, size_t size, int data);

int main()
{
   int array[] = {1, 3, 5, 6, 8, 9, 10, 49, 50, 88};
   size_t size = sizeof(array) / sizeof(array[0]);
   int data = 1;
   printf("%d\n", RecursiveBinarySearch(array, 0, size, data));
   printf("%d\n", IterativeBinarySearch(array, 0, size, data));

    return (0);
}

/**********************************/

int RecursiveBinarySearch(int array[], size_t base, size_t size, int data)
{
    int middle = base + ((size - base) / 2);

    if (base <= size)
    {
        if (data == array[middle])
        {
            return (middle);
        }

        if (data < array[middle])
        {
            return (RecursiveBinarySearch(array, base, (middle - 1), data));
        }
        else
        {
            return (RecursiveBinarySearch(array, (middle + 1), size, data));
        }
    }

    return (NOT_FOUND);
}

/**********************************/

int IterativeBinarySearch(int array[], size_t base, size_t size, int data)
{
    int middle = 0;
    
    while (base <= size)
    {
        middle = base + ((size - base) / 2);

        if (data == array[middle])
        {
            return (middle);
        }
        else if (data < array[middle])
        {
           size = middle - 1;
        }
        else
        {
            base = middle + 1;
        }   
    }

    return (NOT_FOUND);
}