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

/*  Allocates memory for new doubly linked list. 
 *  Return: pointer to the newly created list.
 *  Time Complexity: O(1) */
dsll_t *DSLLCreate(int (*is_before)(const void *, const void *));

/*  Free all allocation for given circular buffer.
 *  List: a pointer to a sorted list of type dsll_t.
 *  Time Complexity: O(1) */
void DSLLDsetroy(dsll_t *list);

/* Inert a new node in a specific location within the list. The node will be
 * 	added before the node you enter to the function.
 * Return a pointer to the new member (node) (the new iterator).
 * Where: the node before which you'de like to enter the new node.
 * Data: the data you'de like to set in the new node.
 * Time Complexity: O(n) */
dsll_iter_t DSLLInsert(dsll_t *list, void *data);

/* Helping funcion to DSLLInsert */
dsll_iter_t DSLLCompare(dsll_t *list, void *data, dsll_iter_t data2);

/* Remove a selected node.
 * Where: the node you wish to remove.
 * Return: iter_t to the next node after the one you've removed.
 * Time Complexity: O(1) */
dsll_iter_t DSLLRemove(dsll_iter_t current);

/* Return the number of occupied elements in the list.
 * List: a pointer to list 'list'.
 * Time Complexity: O(N) */
size_t DSLLSize(dsll_t *list);

/* Return a pointer to the iterator that begin the list (the head).
 * List: a pointer to list 'list'.
 * Time Complexity: O(1) */
dsll_iter_t DSLLBegin(dsll_t *list);

/* Return a pointer to the iterator that ends the list (the tail).
 * List: a pointer to list 'list'.
 * Time Complexity: O(1) */
dsll_iter_t DSLLEnd(dsll_t *list);

/* Remove the first node in the list.
 * Returns the data of the poped element.
 * List: a pointer to list 'list'.
 * Time Complexity: O(1) */
void *DSLLPopFront(const dsll_t *list);

/* Remove the last node in the list.
 * Returns the data of the poped element.
 * List: a pointer to list 'list'
 * Time Complexity: O(1) */
void *DSLLPopBack(const dsll_t *list);

/* Function that Check whether the list is empty (no occupied elements).
 * Return 1 if 'list' is empty, else return 0.
 * List: a pointer to a list of type dsll_t.
 * Time Complexity: O(1) */
int DSLLIsEmpty(dsll_t *list);

/* Merges two sorted lists into the one list.
 * List2 will be merged into list1. Every member merged will be removed from
 * 	list2.
 * Compexity: */
void DSLLMerge(dsll_t *list1, dsll_t *list2);

/* Functionality: receieves a function (action_func()) and assign it to all 
 * 	the members in the requested range.
 * Teturns 0 if successful and 1 if failed.
 * From - the member from which the action will be commited (including 'from').			  
 * To - the member until which the action will be commited (not including 'to').			 
 * '*param' - the parameter you sent to the action_func.				
 * '*action_func' - a pointer to the function who's action you'd like to 
 * 	conduct on the 'from'-'to' members						
 * Complexity: O(n) */
int DSLLForEach(const dsll_iter_t from, const dsll_iter_t to,
		int (*action_fun)(void *param, void *data),
		const void *param);

/* Functionality: Search the list for specific data.
 * From - the member from which the action will be commited (including 'from').			  
 * To - the member until which the action will be commited (not including 'to').
 * Data: the data you wish to search for in the list.
 * MatchFunc: pointer to a function that received two void pointer to any data.
 * Time Complexity: O(n) */
/* dsll_iter_t DSLLFind(dsll_iter_t from, dsll_iter_t to, void *data);*/
dsll_iter_t DSLLFind(dsll_t *list, dsll_iter_t from,
		     dsll_iter_t to, void *data);

/* Functionality: Search the list for specific data.
 * From - the member from which the action will be commited (including 'from').			  
 * To - the member until which the action will be commited (not including 'to').
 * Return: the first member equal to the data you searched for. If the data
 * 	couldn't be found in the list, the function returns null.
 * Data: the data you wish to search for in the list.
 * MatchFunc: pointer to a function that received two void pointer to any data.
 * Time Complexity: O(n) */
dsll_iter_t DSLLFindIf(dsll_iter_t from, dsll_iter_t to,
		     int (*cond_func)(const void *, const void *), void *param);
					   
/* Function that retrieve the next iterator.
 * Return: pointer to the next iterator.
 * Iter: the iterator whose next value you wish to recieve.
 * Time Complexity: O(1) */
dsll_iter_t DSLLNext(dsll_iter_t current);

/* Function that retrieve the previous iterator.
 * Return:  pointer to the previous iterator.
 * Iter: the iterator whose previous value you wish to recieve.
 * Time Complexity: O(1) */
dsll_iter_t DSLLPrev(dsll_iter_t current);

/* The function check if the data of two iterator is equal = meaning if
 * 	they are both entwered to the list from the same variable
 * 	(for example '&data1').
 * Return value: 1 if the value is equal. 0 if it is not equal.
 * Iter1, iter2: the iterators whose value you wish to compare.
 * Complexity: O(1) */
int DSLLIsEqual(dsll_iter_t iter1, dsll_iter_t iter2);

/* Function that retrieve the data the iterator points to.
 * Returns a pointer to the data inside the requested iterator.
 * Where: the iterator whose data you wish to retrieve.
 * Time Complexity: O(1) */
void *DSLLGetData(dsll_iter_t current);

#endif /* SORTED_LINKED_LIST_H */
