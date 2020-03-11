/*******************************************************************************
					  	 Written by Anat Wax
						    March 9-11, 2020
						Reviewer: Lior Cohen
*******************************************************************************/
#ifndef SORTED_LINKED_LIST_H
#define SORTED_LINKED_LIST_H

#include <unistd.h> /* size_t */

#include "doubly_linked_list.h"

typedef struct sorted_linked_list dsll_t;
typedef struct dll_node *dsll_iter_t;

/*  Allocates memory for new doubly linked list  
 *  return: pointer to newly created list 
 *  Time Complexity: O(1) */
dsll_t *DSLLCreate(int (*is_before)(void *, void *));

/*  Free all allocation for given circular buffer  
 *  list: a pointer to list 'list'  
 *  Time Complexity: O(1) */
void DSLLDsetroy(dsll_t *list);

/* inert a new node in a specific location within the list. The node will be
 * added before the node you enter to the function.
 * return a pointer to the new cell (the new iterator).
 * where: the node before which you'de like to enter the new node.
 * data: the data you'de like to set in the new node.
 * Time Complexity: O(n) */
dsll_iter_t DSLLInsert(dsll_t *list, void *data);
/* helping funcion to DSLLInsert */
dsll_iter_t DSLLCompare(dsll_t *list, void *data, dsll_iter_t data2);

/* remove a selected node.
 * where: the node you wish to remove.
 * return: iter_t to the next node after the one you've removed.
 * Time Complexity: O(1) */
dsll_iter_t DSLLRemove(dsll_iter_t current);

/* return the number of occupied cells in the list
 * list: a pointer to list 'list'
 * Time Complexity: O(N) */
size_t DSLLSize(dsll_t *list);

/* return a pointer to the iterator that begin the list (the head)
 * list: a pointer to list 'list'
 * Time Complexity: O(1) */
dsll_iter_t DSLLBegin(dsll_t *list);

/* return a pointer to the iterator that ends the list (the tail)
 * list: a pointer to list 'list'
 * Time Complexity: O(1) */
dsll_iter_t DSLLEnd(dsll_t *list);

/* remove the first node in the list.
 * returns the data of the poped element.
 * list: a pointer to list 'list'
 * Time Complexity: O(1) */
void *DSLLPopFront(const dsll_t *list);

/* remove the last node in the list.
 * returns the data of the poped element.
 * list: a pointer to list 'list'
 * Time Complexity: O(1) */
void *DSLLPopBack(const dsll_t *list);

/* chech whether the list is empty (no occupied cells).
 * Return 1 if 'list' is empty 0 else return 1 
 * list: a pointer to list 'list'
 * Time Complexity: O(1) */
int DSLLIsEmpty(dsll_t *list);

/* merges two sorted isted into the first list.
 * list1 - the 
 * Compexity: */
void DSLLMerge(dsll_t *list1, dsll_t *list2);

/* Functionality: receieves a function (action_func()) and assign it to all 
 * the members of the list.
 * returns 0 if successful and 1 if failed.
 * 'from' - the member from which you'd like to commit the action 			  
 * 'to' - the member until which you'de like to commit the action 			 
 * '*param' - the parameter you senf to the action_func 				
 * '*action_func' - a pointer to the function who's action you'd like to 
 * conduct on the 'from'-'to' members						
 * Complexity: O(n) */
int DSLLForEach(const dsll_iter_t from, const dsll_iter_t to,
		int (*action_fun)(void *param, void *data),
		const void *param);

/* search in the list for specific data
 * from, to: the iterator you want to search in between. Including the 'from',
 * not encloding the 'to'.
 * data: the data you wish to search for in the list.
 * MatchFunc: pointer to a function that received two void pointer to any data.
 * Time Complexity: O(n) */
/*dsll_iter_t DSLLFind(dsll_iter_t from, dsll_iter_t to, void *data);*/
dsll_iter_t DSLLFind(dsll_t *list, dsll_iter_t from, dsll_iter_t to, void *data);
/* search in the list for specific data.
 * from, to: the iterator you want to search in between. Including the 'from',
 * not encloding the 'to'.
 * return: the first member equal to the data you searched for. If the data
 * cound'nt be found in the list, the function returns null.
 * data: the data you wish to search for in the list.
 * MatchFunc: pointer to a function that received two void pointer to any data.
 * Time Complexity: O(n) */
dsll_iter_t DSLLFindIf(dsll_iter_t from, dsll_iter_t to,
					   int (*cond_func)(const void *, const void *), void *param);
					   
/* the function returns the pointer to the next iterator.
 * iter: the iterator whose next value you wish to recieve.
 * Time Complexity: O(1) */
dsll_iter_t DSLLNext(dsll_iter_t current);

/* the function returns the pointer to the previous iterator.
 * iter: the iterator whose previous value you wish to recieve.
 * Time Complexity: O(1) */
dsll_iter_t DSLLPrev(dsll_iter_t current);

/* the function check if the data of two iterator is equal = meaning if
 * they are both entwered to the list from the same variable
 * (for example '&data1').
 * return value: 1 if the value is equal. 0 if it is not equal.
 * iter1, iter2: the iterators whose value you wish to compare.
 * Complexity: O(1) */
int DSLLIsEqual(dsll_iter_t iter1, dsll_iter_t iter2);

/* returns a pointer to the data inside the requested iterator.
 * where: the iterator whose data you wish to retrieve.
 * Time Complexity: O(1) */
void *DSLLGetData(dsll_iter_t current);

#endif /* SORTED_LINKED_LIST_H */

