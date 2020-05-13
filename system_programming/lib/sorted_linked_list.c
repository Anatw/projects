/*******************************************************************************
					  	 Written by Anat Wax
						    March 9-11, 2020
						Reviewer: Lior Cohen
*******************************************************************************/
#include <stdlib.h> /* malloc() */
#include <assert.h> /* assert() */

#include "sorted_linked_list.h"

struct sorted_linked_list
{
	dll_t *list;
	int (*Compare)(const void *data1, const void *data2);
}; /* dsll_t */


dsll_t *DSLLCreate(int (*Compare)(const void *, const void *))
{
	dsll_t *slist = (dsll_t *)malloc(sizeof(dsll_t));
	dll_t *new_list = NULL;
	
	assert(Compare);
	
	if (NULL == slist)
	{
		return (NULL);
	}
	
	new_list = DLLCreate();
	
	if (NULL == new_list)
	{
		DSLLDsetroy(slist);
		return (NULL);
	}
	
	slist->list = new_list;
	slist->Compare = Compare;
	
	return (slist);
}

/******************************************************************************/

void DSLLDsetroy(dsll_t *list)
{
	assert(list);
	
	DLLDestroy(list->list);
	
	free(list);
	list = NULL;
}

/******************************************************************************/

void *DSLLGetData(dsll_iter_t current)
{
	return (DLLGetData(current));
}

dsll_iter_t DSLLInsert(dsll_t *list, void *data)
{
	dsll_iter_t index = DSLLBegin(list);
	dsll_iter_t result = NULL;
	
	assert(list);
	
	if (DSLLIsEmpty(list)) /* if the list is empty */
	{
		result = DLLPushFront(list->list, data);
		
		return (result);
	}
	
	if (1 == (list->Compare(data, DLLGetData(index))) ||
	    0 == (list->Compare(data, DLLGetData(index))))
	{
		result = DLLInsert(index, data);
		
		return (result);
	}
	else
	{	
		while ((-1) == (list->Compare(data, DLLGetData(index)))) 
		{
			index = DLLNext(index);
			
			if (DLLIsSameIter(index, DSLLEnd(list)))
			{
				result = DLLPushBack(list->list, data);
			
				return (result);
			}
		}
	}
	
	result = DLLInsert(index, data);
		
	return (result);	
}

/******************************************************************************/

dsll_iter_t DSLLBegin(dsll_t *list)
{
	assert(list);
	
	return (DLLBegin(list->list));
}

/******************************************************************************/

dsll_iter_t DSLLEnd(dsll_t *list)
{
	assert(list);
	
	return (DLLEnd(list->list));
}

/******************************************************************************/

dsll_iter_t DSLLNext(dsll_iter_t current)
{
	return (DLLNext(current));
}

/******************************************************************************/

dsll_iter_t DSLLPrev(dsll_iter_t current)
{
	return (DLLPrev(current));
}

/******************************************************************************/

size_t DSLLSize(dsll_t *list)
{
	assert(list);
	
	return (DLLSize(list->list));
}

/******************************************************************************/

int DSLLIsEmpty(dsll_t *list)
{
	return (DLLIsEmpty(list->list));
}

/******************************************************************************/

dsll_iter_t DSLLRemove(dsll_iter_t current)
{
	return (DLLRemove(current));
}

/******************************************************************************/

void *DSLLPopFront(const dsll_t *list)
{
	assert(list);
	
	return (DLLPopFront(list->list));
}

/******************************************************************************/

void *DSLLPopBack(const dsll_t *list)
{
	assert(list);
	
	return (DLLPopBack(list->list));
}

/******************************************************************************/

dsll_iter_t DSLLFindIf(dsll_iter_t from, dsll_iter_t to,
					   int (*cond_func)(const void *, const void *), void *param)
{
	return (DLLFind(from, to, param, cond_func));
}

/******************************************************************************/

/* without the list: 
dsll_iter_t DSLLFind(dsll_iter_t from, dsll_iter_t to, void *data)
{
	iter_t point_to = from;
	
	for (; 0 == DLLIsSameIter(point_to, to); point_to = DLLNext(point_to))
	{
		if (DSLLGetData(point_to) == data)
		{
			return (point_to);
		}
	}
	
	return (DLLNext(point_to));
}
*/

/*******************/

/* with the list: */
dsll_iter_t DSLLFind(dsll_t *list, dsll_iter_t from, dsll_iter_t to, void *data)
{
	iter_t point_to = from;
	
	for (; 0 == DLLIsSameIter(point_to, to); point_to = DLLNext(point_to))
	{
		if (!list->Compare(DSLLGetData(point_to), data))
		{
			if (!list->Compare(data, DSLLGetData(point_to)))
			{
				return (point_to);
			}
		}
	}
	
	return DLLNext(point_to);
}

/******************************************************************************/

int DSLLForEach(const dsll_iter_t from, const dsll_iter_t to,
		int (*action_fun)(void *param, void *data),
		const void *param)
{
	return (DLLForEach(from, to, action_fun, param));
}

int DSLLIsEqual(dsll_iter_t iter1, dsll_iter_t iter2)
{
	return (DSLLGetData(iter1) == DSLLGetData(iter2));
	
}

/******************************************************************************/

void DSLLMerge(dsll_t *list1, dsll_t *list2)
{
	dsll_iter_t point_to = DSLLBegin(list2);
	dsll_iter_t to_delete = point_to;
	
	while (!DSLLIsEmpty(list2))
	{
		to_delete = point_to;
		DSLLInsert(list1, DSLLGetData(point_to));
		point_to = DSLLNext(point_to);
		
		DSLLRemove(to_delete);
		to_delete = NULL;
	}
}
