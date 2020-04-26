/*******************************************************************************
					  	 Written by Anat Wax
						    March 9-10, 2020
						Reviewer: Haim Sa'adia
*******************************************************************************/
#ifndef DOUBLY_LINKED_LIST_H
#define DOUBLY_LINKED_LIST_H

#include <stddef.h> /* size_t */

typedef struct doubly_linked_list dll_t;
typedef struct dll_node *iter_t;

/*  Allocates memory for new doubly linked list  
 *  return: pointer to newly created list 
 *  Time Complexity: O(1) */
dll_t *DLLCreate(void);

/*  Free all allocation for given circular buffer  
 *  list: a pointer to list 'list'  
 *  Time Complexity: O(1) */
void DLLDestroy(dll_t *list);

/* return a pointer to the iterator that begin the list (the head)
 * list: a pointer to list 'list'
 * Time Complexity: O(1) */
iter_t DLLBegin(dll_t *list);

/* return a pointer to the iterator that ends the list (the tail)
 * list: a pointer to list 'list'
 * Time Complexity: O(1) */
iter_t DLLEnd(dll_t *list);

/* return the number of occupied cells in the list
 * list: a pointer to list 'list'
 * Time Complexity: O(N) */
size_t DLLSize(const dll_t *list);

/* chech whether the list is empty (no occupied cells).
 * Return 1 if 'list' is empty 0 else return 1 
 * list: a pointer to list 'list'
 * Time Complexity: O(1) */
int DLLIsEmpty(const dll_t *list);

/* remove the last node in the list.
 * returns the data of the poped element.
 * list: a pointer to list 'list'
 * Time Complexity: O(1) */
void *DLLPopBack(dll_t *list);

/* insert a new node to the end of the list
 * Return 0 if successfully pushed, else return 1 
 * list: a pointer to list 'list'
 * data: the data the user wish to enter to he new node.
 * Time Complexity: O(1) */
iter_t DLLPushBack(const dll_t *list, void *data);

/* remove the first node in the list.
 * returns the data of the poped element.
 * list: a pointer to list 'list'
 * Time Complexity: O(1) */
void *DLLPopFront(dll_t *list);

/* insert a new node to the beginning of the list
 * Return: pointer to the iterator entered. if fails - returns pointer
 * 		   to the last node.
 * list: a pointer to list 'list'
 * data: the data the user wish to enter to he new node.
 * Time Complexity: O(1) */
iter_t DLLPushFront(const dll_t *list, void *data);

/* returns a pointer to the data inside the requested iterator.
 * where: the iterator whose data you wish to retrieve.
 * Time Complexity: O(1) */
void *DLLGetData(const iter_t where);

/* set a diffrenet data to a specific cell
 * Get: pointer to dll_node_t 'where' and void pointer to 'new_data'
 * Time Complexity: O(1) */
void DLLSetData(iter_t where, const void *new_data);

/* inert a new node in a specific location within the list. The node will be
 * added before the node you enter to the function.
 * return a pointer to the new cell (the new iterator).
 * where: the node before which you'de like to enter the new node.
 * data: the data you'de like to set in the new node.
 * Time Complexity: O(1) */
iter_t DLLInsert(iter_t where, void *data);

/* remove a selected node.
 * where: the node you wish to remove.
 * return: iter_t to the next node after the one you've removed.
 * Time Complexity: O(1) */
iter_t DLLRemove(iter_t where);

/* the function returns the pointer to the next iterator.
 * iter: the iterator whose next value you wish to recieve.
 * Time Complexity: O(1) */
iter_t DLLNext(const iter_t iter);

/* the function returns the pointer to the previous iterator.
 * iter: the iterator whose previous value you wish to recieve.
 * Time Complexity: O(1) */
iter_t DLLPrev(const iter_t iter);

/* check wether both iterators entered point to the same member (cell).
 * iter1, iter2: the iterators you wish to compare.
 * return 1 if they point to the same member and 0 if not.
 * Time Complexity: O(1) */
int DLLIsSameIter(const iter_t iter1, const iter_t iter2);

/* search in the list for specific data
 * from, to: the iterator you want to search in between. Including the 'from',
 * not encloding the 'to'.
 * data: the data you wish to search for in the list.
 * MatchFunc: pointer to a function that received two void pointer to any data.
 * Time Complexity: O(n) */
iter_t DLLFind(const iter_t from, const iter_t to, const void *data, 
				int (*MatchFunc)(const void *data1, const void *data2));

/* Functionality: receieves a function (action_func()) and assign it to all 
 * the members of the list.
 * returns 0 if successful and 1 if failed.
 * 'from' - the member from which you'd like to commit the action 			  
 * 'to' - the member until which you'de like to commit the action 			 
 * '*param' - the parameter you senf to the action_func 				
 * '*action_func' - a pointer to the function who's action you'd like to 
 * conduct on the 'from'-'to' members						
 * Complexity: O(n) */
int DLLForEach(const iter_t from, const iter_t to, int (*OprFunc)(void 
			   *operand1, void *operand2), const void *param);
/* the function insert a number of connected nodes into a different list. The
 * function re-connect the list from which the nodes were taken from.
 * returns: the last member (cell) that was coppied.
 * 'from' - the member from which you'd like to commit the action, including
 * the 'from' (in the first list).
 * 'to' - the member until which you'de like to commit the action, not 
 * encloding the 'to' (in the first list).		
 * where: the place where you wish to enter the new set of nodes (in the second list).			 
 * Complexity: */
iter_t DLLSplice(iter_t from, iter_t to, iter_t where);

/* allows you to search using different conditions (different functions).
 * return: the number of elements it has found (the size of dest).
 * 'from' - the member from which you'd like to commit the action 			  
 * 'to' - the member until which you'de like to commit the action
 * MatchFunc: pointer to a function that received two void pointer to any data.
 * dest: pointer to a list containing the iterators found
 * Complexity: */
size_t DLLMultiFind(const iter_t from, const iter_t to, const void *data, 
				int (*MatchFunc)(const void *data1, const void *data2), dll_t *dest);

/* Helper Function to print list 
 * list: a pointer to list 'list'
 * Time Complexity: O(n) */
void PrintList(const dll_t *list);

/* aiding function to print the list: */
void DLLPrint(const dll_t *list);

#endif /* DOUBLY_LINKED_LIST_H */
