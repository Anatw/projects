/******************************************************************************/
/*                                                                            */
/*                    Priority Queue Functions File                           */
/*                            Data Structures                                 */
/*                              11/03/2020                                    */
/*                        Author: Ben David Zikri                             */
/*                          Reviwer:                                          */
/*                                                                            */
/******************************************************************************/

#include <stdio.h>
#include <stdlib.h>

#include "priority_queue.h"
#include "sorted_linked_list.h"
#define FREE(p) (free((p)), (p) = NULL)

struct PQ
{
	dsll_t *list;
	int (*cmp)(void *data1, void *data2);	
};

pqueue_t *PQueueCreate(int (*cmp)(void *, void *))
{
	pqueue_t *pq = (pqueue_t *)malloc(sizeof(pqueue_t));

	if(NULL == pq)
	{
		FREE(pq);
		return (NULL);
	}

	pq->cmp = cmp;
	pq->list = DSLLCreate(cmp);

	if (NULL == pq->list)
	{
		FREE(pq->list);
		FREE (pq);
	}

	return (pq);
}

void PQueueDestroy(pqueue_t *pq)
{
	DSLLDestroy(pq->list);
	FREE(pq);
}

int PQueueEnqueue(pqueue_t *pq, const void* data)
{
	if(DSLLInsert(pq->list, data) != DSLLEnd(pq->list))
	{
		return (0);
	} 

	return (1);
}

void PQueueDequeue(pqueue_t *pq)
{
	DSLLPopFront(pq->list);
}

void *PQueuePeek(const pqueue_t *pq)
{
	return (DSLLGetData(DSLLBegin(pq->list)));
}

size_t PQueueSize(const pqueue_t *pq)
{
	return (DSLLSize(pq->list));
}

int PQueueIsEmpty(const pqueue_t *pq)
{
	return (DSLLIsEmpty(pq->list));
}

void PQueueClear(pqueue_t *pq)
{	
	dsll_iter_t i = DSLLBegin(pq->list);
	dsll_iter_t to_remove = NULL;

	while (DSLLNext(i))
	{
		to_remove = i;
		i = DSLLNext(i);
		DSLLRemove(to_remove);
	}

}

void PQueueErase(pqueue_t *pq, int (*match_func)(void *,void *), 
															  const void* param)
{
	dsll_iter_t where = NULL;
	where = DSLLFindIf(pq->list, DSLLBegin(pq->list), DSLLEnd(pq->list), 
															 match_func, param);
	DSLLRemove(where);	
}

/*******************************************************************************
                             Helper Functions
*******************************************************************************/

void PrintPQ(pqueue_t *pq)
{
	PrintSorted(pq->list);
}


