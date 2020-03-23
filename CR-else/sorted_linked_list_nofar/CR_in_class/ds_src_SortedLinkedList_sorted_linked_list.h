/******************************************************************************
                        Sorted Linked List                                
                          Data Structures                                 
                             10/03/2020                                    
                       	Author: Noffar Gil                             
                         Reviwer:Anat Vax                                 
                                                                           
******************************************************************************/


#ifndef SORTED_LINKED_LIST_H
#define SORTED_LINKED_LIST_H

#include <stddef.h> /* size_t */

#include "utility.h"
#include "doubly_linked_list.h"

/* Doubly Linked List type */
typedef struct sorted_linked_list dsll_t;
typedef dll_iter_t dsll_iter_t;

/* 
* Sorted Linked List Create: allocate memory and create manager struct		
* Receive: compare_func function that recieves 2 void pointers to data and returns
* 		   returns -1 if data1 is bigger than data2, 1 if data2 is bigger, 
*		   and 0 if they are equal
* Return: pointer to a new dsll_t struct			  
* Errors: return NULL if can't allocate memory 		    	  
* Time Complexity: O(1) 
*/
dsll_t *DSLLCreate(int (*compare_func)(const void *data1, const void *data2));

/* 
* Sorted Linked List Destroy: destroy the list and free its memory
* Recieve: 1. dsll_t *list which points to dsll_t manager struct 	
* Time Complexity: O(n) 
*/
void DSLLDestroy(dsll_t *list);

/* 
* Sorted Linked List Insert: inserts an element to the list in sorted place
* Recieve: 1. dsll_t *list which points to dsll_t manager struct 
*		   2. void *data to insert to the new element
* Return: dll_iter_t that points to the new element from the list
* Errors: if can't insert returns iterator at the end of the list
* Time Complexity: O(1)
*/
dsll_iter_t SortedLinkedListInsert(dsll_t *list, const void *data);

/* 
* Sorted Linked List Remove: removes an element from the list
* Recieve: 1. dsll_iter_t iter that points at an element to remove
* Return: dsll_iter_t that points at the next iterator from the list
* Time Complexity: O(1) 
*/
dsll_iter_t DSLLRemove(dsll_iter_t iter);

/* 
* Sorted Linked List Size: check current size of dsll 
* Recieve: 1. dsll_t *list which points to dsll_t manager struct
* Return: size_t with current size of the list
* Time Complexity: O(n) 
*/
size_t DSLLSize(const dsll_t *list);

/* 
* Sorted Linked List Begin: 
* Recieve: 1. dsll_t *list which points to dsll_t manager struct
* Return: dsll_iter_t that points to the first element from the list
* Time Complexity: O(1) 
*/
dsll_iter_t DSLLBegin(const dsll_t *list);

/* 
* Sorted Linked List End: 
* Recieve: 1. dsll_t *list which points to dsll_t manager struct
* Return: dsll_iter_t that points to the last 'NULL' iterator of the list. 
* notice! do not access it's value.
* Time Complexity: O(1) 
*/
dsll_iter_t DSLLEnd(const dsll_t *list);

/* 
* Sorted Linked List Is Empty: check if the list is empty
* Recieve: 1. dsll_t *list which points to dsll_t manager struct 	
* Return: 1 if empty, 0 if not
* Time Complexity: O(1) 
*/
bool DSLLIsEmpty(const dsll_t *list);

/* 
* Sorted Linked List Merge: merges 2 sorted lists to list1. list2 remains empty.
* Recieve: 1. dsll_t *list1 which points to dsll_t manager struct
*		   2. dsll_t *list2 which points to dsll_t manager struct
* Time Complexity: O(n) 
*/
void DSLLMerge(dsll_t *list1, dsll_t *list2);

/* 
* Sorted Linked List Find: find an element in the list
* Recieve: 1. dsll_t *list to use its is_before function.
*		   2. dsll_iter_t from, sets the start point of searching (include)
*		   3. dsll_iter_t to, sets the end point of searching(not include)
*		   4. const void *data to find in the list
* Return: dsll_iter_t that points to an element if found, 
			if element was not found return 'to' iterator
* Time Complexity: O(n) 
*/
dsll_iter_t DSLLFind(const dsll_t *list, const dsll_iter_t from, 
					const dsll_iter_t to, const void *data);

/* 
* Sorted Linked List Find If: find an element that answers to a condition
* Recieve: 1. dsll_t *list to search in.
*		   2. cond_func - a function that receives 2 pointers to void and 
*			  compares their values, and retuns 1 if the condition is true,
*			  0 if false.
*		   3. const void *data to compare with
* Return: dsll_iter_t that points to an element if found, iterator at end if not
* Time Complexity: O(n) 
*/
dsll_iter_t DSLLFindIf(const dsll_t *list, 
						bool (*cond_func)(const void *data1, const void *data2),
						const void *param);

/* 
* Sorted Linked List Next:
* Recieve: 1. dsll_iter_t iter that points at an element from the list
* Return: the next iterator from the list
* Time Complexity: O(1) 
*/
dsll_iter_t DSLLNext(const dsll_iter_t iter);

/* 
* Sorted Linked List Prev:
* Recieve: 1. dsll_iter_t iter that points at an element from the list
* Return: the previous iterator from the list
* Time Complexity: O(1) 
*/
dsll_iter_t DSLLPrev(const dsll_iter_t iter);

/* 
* Sorted Linked List Is Equal:
* Recieve: 1. dsll_iter_t iter that points at an element from the list
*		   2. dsll_iter_t iter that points at an element from the list
* Return: 1 if their data pointers are equal, 0 if not
* Time Complexity: O(1) 
*/
bool DSLLIsEqual(const dsll_iter_t iter1, const dsll_iter_t iter2);

/* 
* Sorted Linked List Get Data: get data from iterator
* Recieve: 1. dsll_iter_t iter that points at an element from the list
* Return: void * pointer to the data from iter
* Time Complexity: O(1) 
*/
void *DSLLGetData(const dsll_iter_t iter);

/* 
* Sorted Linked List Pop Back: removes the last element in list
* Recieve: 1. dsll_t *list which points to dsll_t manager struct
* Return: void * with the data of the element that poped
* Time Complexity: O(1) 
*/
void *DSLLPopBack(dsll_t *list);

/* 
* Sorted Linked List Pop Front: removed the first element in list
* Recieve: 1. dsll_t *list which points to dll_t manager struct
* Return: void * with the data of the element that poped
* Time Complexity: O(1) 
*/
void *DSLLPopFront(dsll_t *list);

/* 
* Sorted Linked List For Each: commit an action on every list element
* Recieve: 1. dsll_iter_t from that sets the start point of the function
*		   2. dsll_iter_t to that sets the end point of the function
*		   3. action_func function that recieves pointer to void data and 
*		      pointer to void param, and commits an action on the data with the 
*		      param. it returns 0 for success and any other number if else
*		   4. void *param for the use of action_func
* Return: 0 if completed successfuly, the number that returned from action_func
* 		  if the loop stopped by it
* Time Complexity: O(n) 
*/
status DSLLForEach(const dsll_iter_t from, const dsll_iter_t to,
                status (*action_func)(void *data, const void *param), 
                const void *param);

#endif /* SORTED_LINKED_LIST_H */
