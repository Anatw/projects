/******************************************************************************/
/*                                                                            */
/*                         Doubly Linked List API                             */
/*                            Data Structures                                 */
/*                              08/03/2020                                    */
/*                        Author: Ben David Zikri                             */
/*                        Reviwer: Yaaccov Evenchik                           */
/*                                                                            */
/******************************************************************************/

#ifndef DLINKEDLIST_H
#define DLINKEDLIST_H

#include <stddef.h> /* size_t */

typedef struct doubly_linked_list dll_t;
typedef struct dll_node *dll_iter_t;

/*  Allocates memory for new Doubly linked list  
 *  Return: pointer to newly created list 
 *  Time Complexity: O(1)  */
dll_t *DLLCreate(void);

/*  Free all allocation for given doubly linked list  
 *  Get: a pointer to list 'list'  
 *  Time Complexity: O(1) */
void DLLDestroy(dll_t *list);

/* A function that return the first element of given list
 * Return dll_iter_t to first element
 * Get: pointer to dll_t 'list'
 * Time Complexity: O(1) */
dll_iter_t DLLBegin(const dll_t *list);

/* A function that returns end of given list
 * Rerurn a pointer to the end element in list 
 * Get: pointer to dll_t 'list'
 * Time Complexity: O(1) */
dll_iter_t DLLEnd(const dll_t *list);

/* A function to count number of elements in given list
 * number of elements in size_t type
 * Get: pointer to dll_t 'list'
 * Time Complexity: O(N) */
size_t DLLSize(const dll_t *list);

/* A function that check if given list is empty
 * Return 1 if 'list' is empty 0 else return 1 
 * Get: pointer to dll_t 'list'
 * Time Complexity: O(1) */
int DLLIsEmpty(const dll_t *list);

/* A function that removes element at the end of the list
 * Get: pointer to dll_t 'list'
 * Return: the data that have beed removed from element
 * Time Complexity: O(1) */
void *DLLPopBack(dll_t *list);

/* A function that removes element at the begining of the list
 * Return: the data that have beed removed from element 
 * Get: pointer to dll_t 'list'
 * Time Complexity: O(1) */
void *DLLPopFront(dll_t *list);

/* A function that adds element at the end of the list
 * Return 0 if successfully pushed, else return 1 
 * Get: pointer to dll_t 'list'
 * if allocation failed returns end element, which does not hold any data
 * Time Complexity: O(1); O(n) if allocation failed */
dll_iter_t DLLPushBack(dll_t *list, void *data);

/* A function that adds element at the begining of the list
 * Return: pointer to newlly added element 
 * Get: pointer to dll_t 'list'
 * if allocation failed returns end element, which does not hold any data
 * Time Complexity: O(1); O(n) if allocation failed */
dll_iter_t DLLPushFront(dll_t *list, void *data);

/* A function to get data of given element
 * Return: void pointer to data  
 * Get: pointer to element 'where'
 * Time Complexity: O(1) */
void *DLLGetData(const dll_iter_t where);

/* A function to change data of given element
 * Get: pointer 'where' to change data in and void pointer to 'new_data'
 * Time Complexity: O(1) */
void DLLSetData(dll_iter_t where, const void *new_data);

/* A function to add element at a specific location
 * Get: a pointer to element 'where'
 * Return: a pointer to newly created element BEFORE given 'where' 
 * if allocation failed returns end element, which does not hold any data
 * Time Complexity: O(1); O(n) if allocation failed */
dll_iter_t DLLInsert(dll_iter_t where, void *data);

/* A function to remove element at a specific location
 * Get: a pointer to element 'where'
 * Return: the next element after 'where' removed
 * Time Complexity: O(1) */
dll_iter_t DLLRemove(dll_iter_t where);

/* A function to get next element in list
 * Return: pointer to the next element
 * Get: a pointer to element 'iter'
 * Time Complexity: O(1) */
dll_iter_t DLLNext(const dll_iter_t iter);

/* A function to get previous element in list
 * Return: pointer to the previuos element
 * Get: a pointer to element 'iter'
 * Time Complexity: O(1) */
dll_iter_t DLLPrev(const dll_iter_t iter);

/* A function to check if 2 elements are identical
 * Return: 1 if they are identical else return 0
 * Get: a pointers to elements 'iter1', 'iter2'
 * Time Complexity: O(1) */
int DLLIsSameIter(const dll_iter_t iter1, const dll_iter_t iter2);

/* A function that searches for specific data in range of elements
 * Return: pointer to found element, if not found return the end of range
 * Get: 2 pointers that represnt range 'from' and 'to', a function that can
   compare returning 0 upon succsses, and param to check. 
 * Time Complexity: O(N) */
dll_iter_t DLLFind(const dll_iter_t from, const dll_iter_t to, 
				 int (*MatchFunc)(void *data1, void *data2), const void *param);

/* A function that manipulates data in range of elements using given function
 * Return: the return value of given function
 * Get: 2 pointers that represnt range 'from' and 'to', a function that can
   manipulate data returning 0 upon succsses, and param for the function usage. 
 * Time Complexity: O(N) */
int DLLForEach(const dll_iter_t from, const dll_iter_t to, 
				int (*OprFunc)(void *, void *), const void *param);

/* A function to insert multiple elements in list
 * Return pointer to location of newlly added elements
 * Gets: pointers 'from' and 'to' to indicate range, and pointer 'where' to insert
 * Time Complexity: O(N) */
dll_iter_t DLLSplice(dll_iter_t from, dll_iter_t to, dll_iter_t where);

/* A function that searches for specific data in range of elements
 * Return: the number of insantces found in range
 * Get: 2 pointers that represnt range 'from' and 'to', a function that can
 * compare returning 0 upon succsses, and pointer to list to insert the instances
 * Time Complexity: O(N) */
size_t DLLMultiFind(const dll_iter_t from, const dll_iter_t to, const void *data, 
					   int (*MatchFunc)(void *data1, void *data2), dll_t *dest);

/* Helper Function to print list 
 * Get: pointer to dll_t 'list'
 * Time Complexity: O(N) */
void PrintList(const dll_t *list);

#endif /* DLINKEDLIST_H */
