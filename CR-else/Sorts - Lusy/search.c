/*******************************************************************************
Name: Binary Search Algorithm Implementations
Author: Lusy Volkov
Date: 14.4.20
Rewiever: Anat Wax
*******************************************************************************/

#include "search.h"

/******************************************************************************/

int BinarySearchIter(int arr[], int left_index, int right_index, int x)
{
	int middle = (left_index + right_index) / 2;
	
	while (left_index <= right_index)
	{
		if (arr[middle] == x)
		{
			return (middle);
		}
		
		if (arr[middle] < x)
		{
			left_index = middle + 1;
			middle = (left_index + right_index) / 2;
		}
		
		else 
		{
			right_index = middle - 1;
			middle = (left_index + right_index) / 2;
		}
	}
	
	return (-1);
}
/******************************************************************************/

int BinarySearchRec(int arr[], int left_index, int right_index, int x)
{
	static int middle = 0;
	
	middle = (left_index + right_index) / 2;
	
	if (right_index >= left_index)
	{
		if (arr[middle] == x)
		{
			return (middle);
		}
		
		if (arr[middle] > x)
		{
			return (BinarySearchRec(arr, left_index, middle - 1, x));
		}
		
		return (BinarySearchRec(arr, middle + 1, right_index, x));
	}
	
	return (-1);
}
/******************************************************************************/




























































