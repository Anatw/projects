/*******************************************************************************
					  	 Written by Anat Wax
						  March 3, 2020
						Reviewer: Yoni Naor
*******************************************************************************/
#include <stddef.h>

#ifndef SLINGLY_LINKED_LIST_H
#define SLINGLY_LINKED_LIST_H

typedef struct SLL SLL_t;
typedef struct sll_node *iter_t;

/* create a the last element of the list */
SLL_t *SLLCreate();

/* free all the memory thet was allocated in the program */
void SLLDestroy(SLL_t *list);

/* insert a new node before the head. It returns status if failes returns the last element */
iter_t SLLInsert(iter_t where, void *data);

iter_t SLLRemove(iter_t who);

size_t SLLCount(const SLL_t *list);

/* check if a the list is empt (compares head to end, if they are equal = empty) */
int SLLIsEmpty(const SLL_t *list); /* cons because we don't want to change the sll */

/* return the data */
void *SLLGetData(const iter_t node);

/* set changes the data in a specific node */
void SLLSetData(const iter_t iterator, void *data);

/* move the iterator to the next node */
iter_t SLLNext(const iter_t);

/* returns an iterator to te head of the list. if empty returns the last element */
iter_t SLLBegin(const SLL_t *list);

/* returns an iterator to te end of the list */
iter_t SLLTail(const SLL_t *list);

/* check if two iterators point at the same node */
int SLLIsSameIter(const iter_t iter1, const iter_t iter2);

iter_t SLLNext(const iter_t member);

/* check if any node econtain the searched data * pointer to a function wS8 */
iter_t SLLFind(const iter_t from, const iter_t to, void *data,
		int (*match_func)(void *, void *));

/* receieves a function (action_func()) and assign it to all the 		 */
/* members of the list	-	returns 0 is successed and 1 if failed		 */
int SLLForEach(iter_t from, iter_t to, void *param, int action_func( void *param, void *data));


#endif
