/******************************************************************************/
/*                                                                            */
/*                         Sorted Linked List API                             */
/*                            Data Structures                                 */
/*                              09/03/2020                                    */
/*                        Author: Ben David Zikri                             */
/*                          Reviwer:                                          */
/*                                                                            */
/******************************************************************************/

#ifndef SORTEDLINKEDLIST_H
#define SORTEDLINKEDLIST_H

#include <stddef.h> /* size_t */

typedef struct sorted_linked_list dsll_t;
typedef struct dll_node *dsll_iter_t;


/*  Allocates memory for new sorted linked list  
 *  Return: pointer to newly created list 
 *  Time Complexity: O(1)  */
dsll_t *DSLLCreate(int (*IsBefore)(void *, void *));

/*  Free all allocation for given sorted linked list  
 *  Get: a pointer to list 'list'  
 *  Time Complexity: O(1) */
void DSLLDestroy(dsll_t *list);

/* A function that return the first element of given list
 * Return dll_iter_t to first element
 * Get: pointer to dsll_t 'list'
 * Time Complexity: O(1) */
dsll_iter_t DSLLBegin(const dsll_t *list);

/* A function that returns end of given list
 * Rerurn a pointer to the end element in list 
 * Get: pointer to dsll_t 'list'
 * Time Complexity: O(1) */
dsll_iter_t DSLLEnd(const dsll_t *list);

/* A function to count number of elements in given list
 * number of elements in size_t type
 * Get: pointer to dsll_t 'list'
 * Time Complexity: O(N) */
size_t DSLLSize(const dsll_t *list);

/* A function that check if given list is empty
 * Return 1 if 'list' is empty 0 else return 1 
 * Get: pointer to dsll_t 'list'
 * Time Complexity: O(1) */
int DSLLIsEmpty(const dsll_t *list);

/* A function to get data of given element
 * Return: void pointer to data  
 * Get: pointer to element 'where'
 * Time Complexity: O(1) */
void *DSLLGetData(const dsll_iter_t where);

/* A function to add element in ascending order
 * Get: a pointer to element 'where'
 * Return: a pointer to newly created element 
 * if allocation failed returns end element, which does not hold any data
 * Time Complexity: O(n) */
dsll_iter_t DSLLInsert(dsll_t *sorted, const void *data);

/* A function to remove element at a specific location
 * Get: a pointer to element 'where'
 * Return: the next element after 'where' removed
 * Time Complexity: O(1) */
dsll_iter_t DSLLRemove(dsll_iter_t where);

/* A function that removes element at the end of the list
 * Get: pointer to dsll_t 'list'
 * Return: the data that have beed removed from element
 * Time Complexity: O(1) */
void *DSLLPopBack(dsll_t *sorted);

/* A function that removes element at the begining of the list
 * Return: the data that have beed removed from element 
 * Get: pointer to dsll_t 'list'
 * Time Complexity: O(1) */
void *DSLLPopFront(dsll_t *sorted);

/* A function to get next element in list
 * Return: pointer to the next element
 * Get: a pointer to element 'iter'
 * Time Complexity: O(1) */
dsll_iter_t DSLLNext(const dsll_iter_t);

/* A function to get previous element in list
 * Return: pointer to the previuos element
 * Get: a pointer to element 'iter'
 * Time Complexity: O(1) */
dsll_iter_t DSLLPrev(const dsll_iter_t);

/* A function to check if data equality of 2 elements
 * Return: 1 if their data is equal are identical else return 0
 * Get: pointers to elements 'iter1', 'iter2'
 * Time Complexity: O(1) */
int DSLLIsEqual(const dsll_iter_t iter1, const dsll_iter_t iter2);

/* A function that searches for specific data in range of elements
 * Return: pointer to found element, if not found return the end of range
 * Get: list (for IsBefore function) 2 pointers that represnt range 'from' 
 * and 'to', a function that can compare returning 1 upon success, 
 * and param to check. 
 * Time Complexity: O(N) */
dsll_iter_t DSLLFind(dsll_t *list, const dsll_iter_t from, const dsll_iter_t to, 
					const void *data);

/* A function that searches for specific condition in range of elements
 * Return: pointer to found element, if not found return the end of range
 * Get: list, 2 pointers that represnt range 'from' and 'to', a function that 
 * can check for certain condition returning 1 upon success, and param to check. 
 * Time Complexity: O(N) */
dsll_iter_t DSLLFindIf(dsll_t *list, const dsll_iter_t from, const dsll_iter_t to, 
				   int (*CondFunc)(void *data1, void *data2), const void *param);

/* A function that manipulates data in range of elements using given function
 * Return: the return value of given function
 * Get: 2 pointers that represnt range 'from' and 'to', a function that can
   manipulate data returning 0 upon success, and param for the function usage. 
 * Time Complexity: O(N) */
int DSLLForEach(const dsll_iter_t from, const dsll_iter_t to, 
				int (*OprFunc)(void *operand1, void *operand2), 
				const void *param);

/* Merges 2 given lists to one list, while preserving the ascending order
 * Get: 2 lists - 'list1' is the destination to merge, and 'list2' to merge 
 * Time Complexity: O(N) */
void DSLLMerge(dsll_t *list1, dsll_t *list2);

/*******************************************************************************
							 Helper Functions
*******************************************************************************/

/* Helper Function to print list 
 * Get: pointer to dsll_t 'list'
 * Time Complexity: O(N) */
void PrintSorted(dsll_t *sorted);

#endif /* SORTEDLINKEDLIST_H */
