#include <stddef.h>

#ifndef SLINGLY_LINKED_LIST_H
#define SLINGLY_LINKED_LIST_H

typedef struct SLL SLL_t;
typedef struct sll_node *iter_t;

/* create a the last element of the list  - this function create a SLL_t *list
ant a node_t *stab (dummy). the list->head and tail will points at stab and
every new member that will be added to the list will point at stab */
SLL_t *SLLCreate();

/* free all the memory thet was allocated in the program */
void SLLDestroy(SLL_t *list);

/* insert a new node before the head. It returns status if failes returns the last element */
iter_t SLLInsert(iter_t where, void *data);

iter_t SLLRemove(iter_t who);

/* count the number of nodes in the list (without the stab...) */
size_t SLLCount(const SLL_t *list);

/* check if a the list is empty (compares head to end, if they are equal = empty) */
int SLLIsEmpty(const SLL_t *); /* cons because we don't want to change the sll */

/* return the data */
void *SLLGetData(const iter_t);

/* set changes the data in a specific node */
void SLLSetData(const iter_t iterator, void *data);

/* move the iterator to the next node */
iter_t SLLNext(const iter_t);

/* returns an iterator to te head of the list. if empty returns the last element */
iter_t SLLBegin(const SLL_t *);

/* returns an iterator to te end of the list */
iter_t SLLTail(const SLL_t *);

/* check if two iterators point at the same node */
int SLLIsSameIter(const iter_t iter1, const iter_t iter2);

/* check if any node econtain the searched data * pointer to a function wS8 */
iter_t SLLFind(const iter_t from, const iter_t to, void *data, int (*match_func)(void *, void *));

/* receieves a function (action_func()) and assign it to all the */
/* memners of the list											 */
iter_t SSLForEach(iter_t from, iter_t to, void *param, int (*action_func)());


#endif
