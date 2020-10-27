/*******************************************************************************
*Given an array of n unique integers where each element in the array is in range [1, n]. The array has all distinct elements and size of array is (n-2). Hence Two numbers from the range are missing from this array. Find the two missing numbers.

static void findTwoMissingNumbers(int arr[], int n)  {}


**find all triplets with zero sum in the array.
for example:
Input : arr[] = {0, -1, 2, -3, 1}
Output : (0 -1 1), (2 -3 1)

static void findTriplets(int arr[], int n) {}


Authour: Anat Wax anatwax@gmail.com
Datecreation: 20.09.2020
*******************************************************************************/
#include <iostream> // cout
#include <limits> // interger min + max values


static void findTwoMissingNumbers(int array[], int n)
{
    int result = 0;
    for (int i = 1; i < (n-2); ++i)
    {
        result += array[i-1] | array[i];
    }

    std::cout <<  result << std::endl;
}


int main()
{
    int array[] = {1, 2, 3, 5, 7, 8};
    findTwoMissingNumbers(array, 8);
    return 0;
}