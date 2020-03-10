/*******************************************************************************
					  	 Written by Anat Wax
						    March 9-10, 2020
						Reviewer: 
*******************************************************************************/
#include <stdio.h> /* printf() */
#include <stdlib.h> /* malloc() */
#include <assert.h> /* assert() */

#include "sorted_linked_list.h"

struct sorted_linked_list
{
	dll_t *list;
	int (*is_before)(void *data1, void *data2);
}; /* dsll_t */



dsll_t *DSLLCreate(int (*is_before)(void *, void *))
{
	dsll_t *slist = (dsll_t *)malloc(sizeof(dsll_t));
	dll_t *new_list = DLLCreate();
	
	slist->list = new_list;
	slist->is_before = is_before;
	
	return (slist);
}

void DSLLDsetroy(dsll_t *list)
{
	DLLDestroy(list->list);
	
	free(list);
	list = NULL;
}

void *DSLLGetData(dsll_iter_t current)
{
	return (DLLGetData(current));
}

dsll_iter_t DSLLInsert(dsll_t *list, void *data)
{
	dsll_iter_t index = DLLBegin(list->list);
	dsll_iter_t result = NULL;
	
	if (0 == DSLLSize(list))
	{
		result = DLLPushFront(list->list, data);
		
		return (result);
	}
	/*
	while (1 != (list->is_before(data, DLLGetData(index))))
	{
		result = DSLLCompare(list, data, index);
	}
	*/
	/* run over the list until you reach the end */
	for (index; 1 == DLLIsSameIter(index, DLLEnd(list->list)); index = DLLNext(index)) 
	{
		/* it is either data > or = index*/
		if (0 == (list->is_before(data, DLLGetData(index)))) 
		{
			/* data is = to index! */
			if (0 == (list->is_before(DLLGetData(index), data))) 
			{
				result = DLLInsert(index, data);
				return (index);
			}
		}
		else /* data > index, move forward */
		{
			result = DLLInsert(index, data);
		}
	}
	
	result = DLLPushFront(list->list, data);
	
	return (result); /* data should come bedore index */
}
/*
dsll_iter_t DSLLCompare(dsll_t *list, void *data, dsll_iter_t index)
{
	if (0 == (list->is_before(data, DLLGetData(index))))
	{
		if (0 == (list->is_before(DLLGetData(index), data)))
		{
			return (index);
		}
		else
		{
			index = DLLNext(index);
			DSLLCompare(list, data, index);
		}
	}
	
	return (index);
}
*/	
dsll_iter_t DSLLBegin(dsll_t *list)
{
	return (DLLBegin(list->list));
}

dsll_iter_t DSLLEnd(dsll_t *list)
{
	return (DLLEnd(list->list));
}

dsll_iter_t DSLLNext(dsll_iter_t current)
{
	return (DLLNext(current));
}

dsll_iter_t DSLLPrev(dsll_iter_t current)
{
	return (DLLPrev(current));
}

size_t DSLLSize(dsll_t *list)
{
	return (DLLSize(list->list));
}

int DSLLIsEmpty(dsll_t *list)
{
	return (DLLIsEmpty(list->list));
}

dsll_iter_t DSLLRemove(dsll_iter_t current)
{
	return (DLLRemove(current));
}

void *DSLLPopFront(const dsll_t *list)
{
	return (DLLPopFront(list->list));
}

void *DSLLPopBack(const dsll_t *list)
{
	return (DLLPopBack(list->list));
}






