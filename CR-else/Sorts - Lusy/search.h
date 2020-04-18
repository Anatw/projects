/*******************************************************************************
Name: Binary Search Algorithm Implementations - Definitions
Author: Lusy Volkov
Date: 14.4.20
Rewiever: Anat Wax
*******************************************************************************/
#ifndef __SEARCH_H__
#define __SEARCH_H__

/* return location of x in arr, if present, otherwise return -1 */
/* iterative implementation */
int BinarySearchIter(int arr[], int left_index, int right_index, int x);

/* recursive implementation */
int BinarySearchRec(int arr[], int left_index, int right_index, int x);

#endif /* __SEARCH_H__ */
