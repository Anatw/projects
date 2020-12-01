/*******************************************************************************
*Given an array of n unique integers where each element in the array is in range [1, n]. The array has all distinct elements and size of array is (n-2). Hence Two numbers from the range are missing from this array. Find the two missing numbers.

static void findTwoMissingNumbers(int arr[], int n)  {}


**find all triplets with zero sum in the array.
for example:
Input : arr[] = {0, -1, 2, -3, 1}
Output : (0 -1 1), (2 -3 1)

static void findTriplets(int arr[], int n) {}


Authour: Anat Wax anatwax@gmail.com
Datecreation: 27.10.2020
*******************************************************************************/
#include <iostream> // cout
#include <limits> // interger min + max values


static void findTwoMissingNumbers(int array[], int n)
{
    int array_sum = 0;
    int n_factorial = 0;
    int i = 1;
    int array_half = ((n - 2) / 2) - 1;
    int n_half = n / 2;
    int first_half = array[0];
    int n_first_half = 0;

    for (; i < (n-2); ++i)
    {
        array_sum += array[i - 1];
        n_factorial += i;

        if (i <= array_half)
        {
            first_half += array[i];
        }
        
        if (i <= n_half)
        {
            n_first_half += i;
        }
    }

    for (; i < n; ++i)
    {
        n_factorial += i;
    }

    std::cout << n_factorial - array_sum << std::endl;

    int difference = n_factorial - array_sum;

    int first = n_first_half - first_half;
    int second = difference - first;

    std::cout << "first = " << first << std::endl;
    std::cout << "second = " << second << std::endl;

}

static void findTwoMissingNumber(int array[], int n)
{
    int array_sum = 0;
    int n_factorial = 0;
    int i = 1;


    for (; i < (n-1); ++i)
    {
        array_sum += array[i - 1];
        n_factorial += i;

    }

    for (; i < n; ++i)
    {
        n_factorial += i;
    }

    std::cout << "Missing number is " << n_factorial - array_sum << std::endl;
}

int main()
{
    int array[] = {1, 2, 3, 5, 6, 7, 8, 10};
    // findTwoMissingNumber(array, 10);
    findTwoMissingNumbers(array, 10);
    return 0;
}