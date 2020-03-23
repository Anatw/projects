/*******************************************************************************
Worksheet Data Structur exercise - sorted linked list		                              
Author - Noffar Gil
Reviewer - Anat Vax					  
Date - 10.03.20									    	                 										  
*******************************************************************************/
#include <stdio.h> /* size_t */
#include <stdlib.h> /* malloc(), free() */
#include <assert.h> /* assert() */

#include "doubly_linked_list.h"
#include "sorted_linked_list.h"

struct sorted_linked_list
{
	dll_t *list;
	int (*compare_func)(const void *data1, const void *data2);
};

dsll_t *DSLLCreate(int (*compare_func)(const void *data1, const void *data2))
{
	/* allocate memory for dll and struct maneger */
	dll_t *new_dll = DLLCreate();
	dsll_t *new_sorted = NULL;
	
	assert(NULL != compare_func);
	
	if (NULL == new_dll)
	{
		return (NULL);
	}
	
	new_sorted = (dsll_t *)malloc(sizeof(dsll_t));
	if (NULL == new_sorted)
	{
		DLLDestroy(new_dll);
		return (NULL);
	}
	
	/* initialize struct manager */ 
	new_sorted->list = new_dll;
	new_sorted->compare_func = compare_func;
	
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
	dsll_iter_t iter = DSLLBegin(list);
	assert(list);

	/* insert the element in the right sorted place */
	while (DSLLNext(iter) && (list->compare_func(DSLLGetData(iter), data) >= 0))
	{
		iter = DSLLNext(iter);
	}

	return (DLLInsert(iter, (void *)data));
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
	dsll_iter_t iter1 = NULL;
	dsll_iter_t iter2_start = NULL;
	dsll_iter_t iter2_end = NULL;

	assert(list1 != list2);
	assert(list1);
	assert(list2);
	assert(list1->compare_func == list2->compare_func);

	iter1 = DSLLBegin(list1);
	iter2_start = DSLLBegin(list2);
	iter2_end = iter2_start;

	/* iterate the lists and copy list2 to list1 in the appropriate places */
	while (!DSLLIsEmpty(list2) && iter1 != DSLLEnd(list1))
	{
		void *iter1_data = DSLLGetData(iter1);

		if (1 == (list1->compare_func)(DSLLGetData(iter2_start), iter1_data))
		{
			/* get iter2_end to the last number that is smaller than iter1 */
			while (iter2_end != DSLLEnd(list2) &&
				   (1 == (list1->compare_func)(DSLLGetData(iter2_end), iter1_data)))
			{
				iter2_end = DSLLNext(iter2_end);
			}

			DLLSplice(iter2_start, iter2_end, iter1);

			iter2_start = iter2_end;
		}

		iter1 = DSLLNext(iter1);
	}

	/* check if iter1 is at the end and there are elements in list2 */
	if (!DSLLIsEmpty(list2))
	{
		DLLSplice(iter2_start, DSLLEnd(list2), iter1);
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
	/* dsll_iter_t new_iter = DSLLGetData(i_iter);
	
		if (list->compare_func(new_iter, (void *)data) ==
		list->compare_func((void *)data, new_iter))*/
		
		if (0 == compare_func(DSLLGetData(i_iter), (void *)data)) 
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
	assert(NULL != iter);
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





