/******************************************************************************/
/*                                                                            */
/*                    Sorted Linked List Functions file                       */
/*                            Data Structures                                 */
/*                              09/03/2020                                    */
/*                        Author: Ben David Zikri                             */
/*                          Reviwer: Anat Wax                                 */
/*                                                                            */
/******************************************************************************/
#include <stdlib.h>
#include <stdio.h>
#include <assert.h>

#include "sorted_linked_list.h"
#include "doubly_linked_list.h"

#define FREE(p) (free((p)), (p) = NULL)

struct sorted_linked_list
{
	dll_t *list;
	int (*compare)(void *data1, void *data2);	
};

dsll_t *DSLLCreate(int (*compare)(void *, void *))
{
	dsll_t *sorted = (dsll_t *)malloc(sizeof(dsll_t));
	if(NULL == sorted) 
	{
		return (NULL);
	}
	
	sorted->list = DLLCreate();
	sorted->compare = compare;

	if(NULL == sorted->list)
	{
		FREE(sorted); /* If dsll_t list allocation failed, freeing dsll_t list*/
		return (NULL);
	}

	return(sorted);
}

void DSLLDestroy(dsll_t *sorted)
{
	DLLDestroy(sorted->list);
	FREE(sorted);
}

dsll_iter_t DSLLBegin(const dsll_t *sorted)
{
	assert(NULL != sorted);

	return (DLLBegin(sorted->list));
}

dsll_iter_t DSLLEnd(const dsll_t *sorted)
{
	assert(NULL != sorted);

	return (DLLEnd(sorted->list));
}

void *DSLLGetData(const dsll_iter_t iter)
{
	return (DLLGetData(iter));
}

size_t DSLLSize(const dsll_t *sorted)
{
	return(DLLSize(sorted->list));
}

dsll_iter_t DSLLNext(const dsll_iter_t iter)
{
	return(DLLNext(iter));
}

int DSLLIsEmpty(const dsll_t *sorted)
{
	return(DLLIsEmpty(sorted->list));
}

dsll_iter_t DSLLPrev(const dsll_iter_t iter)
{
	return(DLLPrev(iter));
}

dsll_iter_t DSLLInsert(dsll_t *sorted, const void *data)
{
	dll_iter_t i = DSLLBegin(sorted);

	while (DSLLNext(i) && (sorted->compare(DSLLGetData(i), (void *)data)) > 0)
	{
		i = DSLLNext(i);
	}

	return (DLLInsert(i, (void *)data));
}

int DSLLIsEqual(const dsll_iter_t iter1, const dsll_iter_t iter2)
{
	return (DSLLGetData(iter1) == DSLLGetData(iter2));
}

dsll_iter_t DSLLRemove(dsll_iter_t where)
{
	return (DLLRemove(where));
}

void *DSLLPopBack(dsll_t *sorted)
{
	return (DLLPopBack(sorted->list));
}

void *DSLLPopFront(dsll_t *sorted)
{
	return (DLLPopFront(sorted->list));
}

dsll_iter_t DSLLFind(dsll_t *sorted, const dsll_iter_t from, 
	                                    const dsll_iter_t to, const void *param)
{
	dsll_iter_t i = from;

	assert(from && to && param);

	for (; !DLLIsSameIter(i, to); i = DLLNext(i))
	{	/* if 2 numbers are not smaller nor greater, they are equal */
		if(sorted->compare(DSLLGetData(i), (void *)param) == 0)
		{
			return(i);
		}
	}

	return (to); /* If couldn't any find match, return element in range */
}

dsll_iter_t DSLLFindIf(dsll_t *list, const dsll_iter_t from, const 
   dsll_iter_t to, int (*CondFunc)(void *data1, void *data2), const void *param)
{
	return (DLLFind(from, to, CondFunc, param)); 
}

int DSLLForEach(const dsll_iter_t from, const dsll_iter_t to, 
			 int (*OprFunc)(void *operand1, void *operand2), const void *param)
{
	return (DLLForEach(from, to, OprFunc, param));
}

void DSLLMerge(dsll_t *sorted1, dsll_t *sorted2)
{
	dsll_iter_t i = DSLLBegin(sorted1);
	dsll_iter_t j = DSLLBegin(sorted2);
	dsll_iter_t from = NULL;

	for (; DLLNext(i); i = DLLNext(i))
	{
		if(sorted2->compare(DSLLGetData(j),DSLLGetData(i)) == 1)
		{
			from = j; /* Saving location from where to insert */

			while(DSLLNext(j) && sorted2->compare(DSLLGetData(j),
														   DSLLGetData(i)) == 1)
			{
				j = DSLLNext(j);
			}
			/* Inserting multiples element in the right place using splice */
			DLLSplice(from, j, i); 
		}	
	}

	if(!DSLLIsEmpty(sorted2))	/* Adding reamining elements */
	{
		DLLSplice(DSLLBegin(sorted2), DSLLEnd(sorted2), DSLLEnd(sorted1));
	}
}

/*******************************************************************************
                             Helper Functions
*******************************************************************************/

void PrintSorted(dsll_t *sorted)
{
	PrintList(sorted->list);
}


