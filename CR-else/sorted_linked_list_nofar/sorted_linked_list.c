/*******************************************************************************
Worksheet Data Structur exercise - sorted linked list		                              
Author - Noffar Gil
Reviewer - Anat Vax					  
Date - 10.03.20									    	                 										  
*******************************************************************************/
#include <stdio.h> /* size_t */
#include <stdlib.h> /* malloc(), free() */
#include <assert.h> /* assert() */

#include "sorted_linked_list.h"
#include "doubly_linked_list.h"

struct sorted_linked_list
{
	dll_t *list;
	bool (*is_before)(const void *data1, const void *data2);
};

dsll_t *DSLLCreate(bool (*is_before)(const void *data1, const void *data2))
{
	/* allocate memory for dll and struct maneger */
	dll_t *new_dll = DLLCreate();
	dsll_t *new_sorted = (dsll_t *)malloc(sizeof(dsll_t));
	
	assert(NULL != is_before);
	
	if (NULL == new_dll)
	{
		return (NULL);
	}
	
	else if (NULL == new_sorted)
	{
		DLLDestroy(new_dll);
		return (NULL);
	}
	
	/* initialize struct manager */ 
	new_sorted->list = new_dll;
	new_sorted->is_before = is_before;
	
	return (new_sorted);
}

void DSLLDestroy(dsll_t *list)
{	
	assert(NULL != list);
	
	DLLDestroy(list->list);
	free(list);
	list = NULL;
}

dsll_iter_t DSLLInsert(dsll_t *list, const void *data)
{

	dll_iter_t i_iter = DSLLBegin(list);
	assert(NULL != list);
	
	/*if list is empty insert at the begining */
	if (TRUE == DSLLIsEmpty(list))
	{
		return (DLLInsert(i_iter, (void *)data));
	}
	/* search the right place to insert */
	for (i_iter = DSLLBegin(list); TRUE != DLLIsSameIter(i_iter, DSLLEnd(list)); 
			i_iter = DSLLNext(i_iter))
	{
		if (FALSE == list->is_before(DSLLGetData(i_iter), data))
		{
			return (DLLInsert(i_iter, (void *)data));
		}
	}
	/* if place was not found insert at the end */
	return (DLLPushBack(list->list, (void *)data));
}
	
dsll_iter_t DSLLRemove(dsll_iter_t iter)
{
	return (DLLRemove(iter));
}

size_t DSLLSize(const dsll_t *list)
{
	assert(NULL != list);
	
	return (DLLSize(list->list));
}

dsll_iter_t DSLLBegin(const dsll_t *list)
{
	assert(NULL != list);
	
	return (DLLBegin(list->list));
}

dsll_iter_t DSLLEnd(const dsll_t *list)
{
	assert(NULL != list);
	
	return (DLLEnd(list->list));
}

bool DSLLIsEmpty(const dsll_t *list)
{
	assert(NULL != list);
	
	return (DLLIsEmpty(list->list));
}

void DSLLMerge(dsll_t *list1, dsll_t *list2)
{
	dsll_iter_t i_iter_list1 = DSLLBegin(list1);
	dsll_iter_t i_iter_list2 = DSLLBegin(list2);
	dsll_iter_t iter2_to = i_iter_list2;
	
	assert(NULL != list1);
	assert(NULL != list2);
	/* loop till there are element at both list */ 
	while ((i_iter_list1 != DSLLEnd(list1)) && (i_iter_list2 != DSLLEnd(list2)))
	{
		if (list1->is_before(DSLLGetData(i_iter_list1), DSLLGetData(i_iter_list2))) 
		{
			i_iter_list1 = DSLLNext(i_iter_list1);
		}
		else
		{
			while (iter2_to != DSLLEnd(list2) && 
			list1->is_before(DSLLGetData(iter2_to), DSLLGetData(i_iter_list1)))
			{
				iter2_to = DSLLNext(iter2_to);
			}
			
			DLLSplice(i_iter_list2, iter2_to, i_iter_list1);
			
			i_iter_list1 = DSLLNext(i_iter_list1);
			i_iter_list2 = iter2_to;
		}
	}
	
	/* condition below deal with the remain list: */
	/* if there are elements remain at list 2 append them to list 1*/
	if (i_iter_list2 != DSLLEnd(list2))
	{
		DLLSplice(i_iter_list2, DSLLEnd(list2), DSLLEnd(list1));
	}
	
	/* if there are elements remain at list 1 move i_iter_list1 to the end */
	if (i_iter_list1 != DSLLEnd(list1))
	{
		i_iter_list1 = DLLPrev(DSLLEnd(list1));
	}	
}

dsll_iter_t DSLLFind(const dsll_t *list, const dsll_iter_t from, 
					const dsll_iter_t to, const void *data)
{
	dsll_iter_t i_iter = NULL;
	assert(NULL != list);
	
	/* loop run 'from' iter - 'to' iter range and check 
		if 2 data are not smaller or bigger then each other - they equal! */
	for (i_iter = from; TRUE != DLLIsSameIter(i_iter, to); 
		i_iter = DSLLNext(i_iter))
	{
		if (list->is_before(DSLLGetData(i_iter), (void *)data) ==
		list->is_before((void *)data, DSLLGetData(i_iter)))
		{
			return (i_iter);
		}	
	}
	
	/* if data was not found return 'to' iterator*/
	return (to);
}

dsll_iter_t DSLLFindIf(const dsll_t *list, 
						bool (*cond_func)(const void *data1, const void *data2),
						const void *param)
{
	assert(NULL != list);
	
	return (DLLFind(DSLLBegin(list), DSLLEnd(list), cond_func, param));
}

dsll_iter_t DSLLNext(const dsll_iter_t iter)
{
	return (DLLNext(iter));
}

dsll_iter_t DSLLPrev(const dsll_iter_t iter)
{
	return (DLLPrev(iter));
}

bool DSLLIsEqual(const dsll_iter_t iter1, const dsll_iter_t iter2)
{
	/*	compare the 2 pointer to data that return from DLLGetData and not 
		the data value! */
	return (DLLGetData(iter1) == DLLGetData(iter2) ? TRUE: FALSE);
}

void *DSLLGetData(const dsll_iter_t iter)
{
	return (DLLGetData(iter));
}

void *DSLLPopBack(dsll_t *list)
{
	assert(NULL != list);
	
	return (DLLPopBack(list->list));
}

void *DSLLPopFront(dsll_t *list)
{
	assert(NULL != list);
	
	return (DLLPopFront(list->list));
}

status DSLLForEach(const dsll_iter_t from, const dsll_iter_t to,
					status (*action_func)(void *data, const void *param), 
					const void *param)
{
	return (DLLForEach(from, to, action_func, param));
}





