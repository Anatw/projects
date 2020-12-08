/*******************************************************************************
Title & Description: Master Storage Manager - part of the Master in the 
final project.
This part is in charge of all the documentation and maintenance of the 
mapping between the offsets of the memory and the Minion responsible to 
operate


NOT FINISHED!!!! the quick sort here is working great (Ivana tought me this algorithm).

Authour: Anat Wax, anatwax@gmail.com
Reviewer: 
Datecreation: 15.11.2020
Version: 1
*******************************************************************************/
#include <stdio.h> /* printf */


int *InsertSorted(int *left, int *pivot);

void QuickSort(int *left, int *right)
{
  int *pivot = right;

  if (left >= (right - 1))
  {
    return;
  }
  
  pivot = InsertSorted(left, pivot);
  QuickSort(left, pivot - 1);
  QuickSort(pivot + 1, right);
}

void Swap(int *first, int *second)
{
  int temp = *first;
  *first = *second;
  *second = temp;
}

int *InsertSorted(int *left, int *pivot)
{
    int *temp_smaller = left;
    int *temp_bigger = left;

    while (temp_smaller < pivot)
    {
        if (*temp_smaller < *pivot)
        {
            Swap(temp_smaller, temp_bigger);
            ++temp_bigger;
        }

        ++temp_smaller;
    }

    Swap(temp_bigger, pivot);

    return (temp_bigger);
}

void wave_sort(int arr[], int arr_size)
{
  int i = 0;
  int j = 0;

  QuickSort(&arr[0], &arr[arr_size - 1]);
  
  for(i = 0; i < arr_size; ++i)
   {
    printf("%d, ", arr[i]);
  }
  i = 1;
  
  printf("\n\n");

  while (arr[j] == arr[i])
  {
     ++i;
  }

  for (; i < arr_size;)
  {
    Swap(&arr[i - 1], &arr[i]);
  
    i += 2;
    /*if (arr[i] == arr[i-1])
    {
      ++i;
    }*/
  }

  for(i = 0; i < arr_size; ++i)
   {
    printf("%d, ", arr[i]);
  }
}

int main()
{
    int arr[] = {9, 47, 22, 23, 33, 14, 46, 9, 29, 39, 13, 29, 44, 91};
    int n = sizeof(arr) / sizeof(arr[0]);

    /*int array[] = {1, 5, 9, 6, 7, 2, 4};
    int nn = sizeof(array) / sizeof(array[0]);

    wave_sort(array, nn);*/
    wave_sort(arr, n);


    return 0;
}