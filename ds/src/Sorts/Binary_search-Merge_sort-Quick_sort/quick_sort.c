/*******************************************************************************
					  		 Written by Anat Wax
						    14-15 of April, 2020
						   Reviewer: Haim Sa'adia
*******************************************************************************/
#include <stdio.h> /* printf(), size_t */
#include <assert.h> /* assert() */

#define UNUSED(x) (void)(x)

/*
 * Algorithem devides the list to two based on a pivot point (last element).
 * than each half (left - smaller than pivot, and right - larger than pivot)
 * is quick-sorted recursivly.
 * Arguments: base - array to sort.
 *            nmemb - number of elements in array.
 *            size - size of an element of the array.
 *            compar - return int:
 *                   - smaller than 0 if  first < second.
 *                   - bigger than zero if first > second.
 *                   - 0 if first == second. in that case, the order of sorting
 *                          is undefined.
 *            arg - argument fo the Compar function.
 * Complexity: O(n log n) - O(n^2) (best case scenario - the pivot is always 
 *             the mid-size element in the array. Worst case scenario -
 *             the pivot is always the smallest/larggest element in the array).
 */
void Qsort(void *base, size_t nmemb, size_t size,
           int (*Compar)(const void *first, const void *second,
           void *arg), void *arg);

/************* utility functions: ****************/

static void QuickSortRecursive(int array[], int base, int top,
                        int (*Compar)(const void *first, const void *second,
                        void *arg), void *arg);

static int Compar(const void *first, const void *second, void *arg);

static int Partition (int array[], int base, int top,
               int (*compar)(const void *first, const void *second,
               void *arg), void *arg);

static void PrintArray(int array[], size_t num_elements);

static void Swap(int *a, int *b);

/*****************************/

int main()
{
    int array[] = {1, 30, 5, 699, 8, 9, 180, 49, 150, 88};
    size_t size = sizeof(array) / sizeof(array[0]);
    printf("Before Qsort:\n");
	PrintArray(array, size);
	
	printf("After Qsort:\n");	
    Qsort(array, size, sizeof(array[0]), Compar, NULL);
    PrintArray(array, size);

    return (0);
}

/*****************************/

void Qsort(void *base, size_t nmemb, size_t size,
           int (*Compar)(const void *first, const void *second,
           void *arg), void *arg)
{
    UNUSED(size);
    QuickSortRecursive(base, 0, (nmemb - 1), Compar, arg);
}

/*****************************/

static void QuickSortRecursive(int array[], int base, int top,
                        int (*Compar)(const void *first, const void *second,
                        void *arg), void *arg)
{
    int partition = 0;

    assert(array && Compar);

    if (base < top)
    {
        partition = Partition(array, base, top, Compar, arg);
        
        QuickSortRecursive(array, base, (partition - 1), Compar, arg);
        QuickSortRecursive(array, (partition + 1), top, Compar, arg);
    }
}

/*****************************/

static int Partition (int array[], int base, int top,
               int (*compar)(const void *first, const void *second,
               void *arg), void *arg)
{
    int pivot = array[top];
    int index = (base - 1);
    int array_index = 0;

    for (array_index = base; array_index <= (top - 1); ++array_index)
    {
        /* if current element is smaller the pivot - swap to left */
        if (0 > (compar(&array[array_index], &pivot, arg)))
        {
            ++index;
            Swap(&array[index], &array[array_index]);
        }
    }
    /* insert pivot to place: */
    Swap(&array[index + 1], &array[top]);
    return (index + 1);
}

/*****************************/

static void PrintArray(int array[], size_t num_elements)
{
	size_t iterator = 0;
	
	for (iterator = 0; iterator < num_elements; ++iterator)
	{
		printf("%d->", array[iterator]);
	}
	printf("NULL\n");
}

/*****************************/

static int Compar(const void *first, const void *second, void *arg)
{
    UNUSED(arg);
    return (*(int *)first - *(int *)second);
}

/*****************************/

static void Swap(int *a, int *b)
{
	int temp = *a;
	*a = *b;
	*b = temp;
}