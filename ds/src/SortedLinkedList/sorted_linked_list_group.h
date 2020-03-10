/****************************************************************************
* File Name: sorted_linked_list.h											*
* Writer: Lior Cohen														*
* Date: 08/03/2020														    *
* Purpose: The header file for the sorted linked list assignment			*
* Code reviewer: 												*
*****************************************************************************/

#ifndef SORTED_LINKED_LIST_H
#define SORTED_LINKED_LIST_H

#include <unistd.h> /* size_t */

#include "utility.h"

typedef struct dll_node *dsll_iter_t;

typedef struct sorted_linked_list dsll_t;

dsll_t *DSLLCreate(int (*is_before)(void *, void *));

void DSLLDsetroy(dsll_t *list);

dsll_iter_t DSLLInsert(dsll_t *list, void *data);

dsll_iter_t DSLLRemove(dsll_iter_t current); /*return the next iter*/

size_t DSLLSize(dsll_t *list);

dsll_iter_t DSLLBegin(dsll_t *list);

dsll_iter_t DSLLEnd(dsll_t *list);

void *DSLLPopFront(const dsll_t *list);

void *DSLLPopBack(const dsll_t *list);

dsll_iter_t DSLLIsEmpty(dsll_t *list);

void DSLLMerge(dsll_t *list1, dsll_t *list2);

int DSLLForEach(dsll_iter_t from,
				dsll_iter_t to,
				int (*action_fun)(void *param, void *data),
				void *param);

dsll_iter_t DSLLFind(sll_t *list, dsll_iter_t from, dsll_iter_t to, void *data);

dsll_iter_t DSLLFindIf(dsll_t *list,
					   dsll_iter_t from,
					   dsll_iter_t to,
					   int (*cond_func)(void *, void *),
					   void *param);

dsll_iter_t DSLLNext(iter_t current);

dsll_iter_t DSLLPrev(dsll_iter_t current);

int DSLLIsEqual(dsll_iter_t iter1, dsll_iter_t iter2);

void *DSLLGetData(dsll_iter_t current);

#endif /* SORTED_LINKED_LIST_H */











