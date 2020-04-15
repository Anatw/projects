/*******************************************************************************
			   Written by Anat Wax
			     March 14-15, 2020
		  	  Reviewer: Haim sa'adia
*******************************************************************************/
#include <stdlib.h> /* malloc(), free() */
#include <assert.h> /* assert() */
#include <stdio.h> /*printf() */

#include "priority_queue.h"
#include "sorted_linked_list.h"


struct Priority_queue
{
	dsll_t *pqueue;
	int (*priority_func)(const void *data1, const void *data2);
}; /* pqueue_t */

pqueue_t *PQueueCreate(int (*priority_func)(const void *data1,
                                            const void *data2))
{
	pqueue_t *new_pqueue = NULL;
	dsll_t *qlist = NULL;
	
	assert(priority_func);
	
	new_pqueue = (pqueue_t *)malloc(sizeof(pqueue_t));
	
	if (NULL == new_pqueue)
	{
		return (NULL);
	}
	
	qlist = DSLLCreate(priority_func);
	
	if (NULL == qlist)
	{
		free(new_pqueue);
		new_pqueue = NULL;
		
		return (NULL);
	}
	
	new_pqueue->pqueue = qlist;
	new_pqueue->priority_func = priority_func;
	
	return (new_pqueue);
}

void PQueueDestroy(pqueue_t *pqueue)
{
	assert(pqueue);
	
	DSLLDsetroy(pqueue->pqueue);
	
	free (pqueue);
	pqueue = NULL;
}

int PQueueEnqueue(pqueue_t *pqueue, const void *data)
{
	void *p_data = (void *)data;
	dsll_iter_t new_member = DSLLInsert(pqueue->pqueue, p_data);
	
	assert(pqueue);
	
	if (NULL == new_member)
	{
		return (1);
	}
	
	return (0);
}

void PQueueDequeue(pqueue_t *pqueue)
{
	assert(pqueue);
	
	DSLLRemove(DSLLBegin(pqueue->pqueue));
}

void *PQueuePeek(const pqueue_t *pqueue)
{
	assert(pqueue);
	
	return (DSLLGetData(DSLLBegin(pqueue->pqueue)));
}


size_t PQueueSize(const pqueue_t *pqueue)
{
	assert(pqueue);
	
	return (DSLLSize(pqueue->pqueue));
}

int PQueueIsEmpty(const pqueue_t *pqueue)
{
	assert(pqueue);
	
	return (DSLLIsEmpty(pqueue->pqueue));
}

void PQueueClear(pqueue_t *pqueue)
{
	dsll_iter_t point_to = DSLLBegin(pqueue->pqueue);
	dsll_iter_t to_delete = point_to;
	
	assert(pqueue);
	
	while (!DSLLIsEmpty(pqueue->pqueue))
	{
		to_delete = point_to;
		point_to = DSLLNext(point_to);
		
		DSLLRemove(to_delete);
		to_delete = NULL;
	}
}
/*
int PQueueErase(pqueue_t *pqueue,
				int (*cond_func)(const void *data,
								 const void *param),
				const void *param)
{
	dsll_iter_t point_to = DSLLBegin(pqueue->pqueue);
	iter_t to_delete = point_to;
	
	assert(pqueue);
	assert(cond_func);
	
	while (!DLLIsSameIter(point_to, DSLLEnd(pqueue->pqueue)))
	{
		if (0 == cond_func(DSLLGetData(point_to), param))
		{
			to_delete = point_to;
			point_to = DSLLNext(point_to);
			DSLLRemove(to_delete);
			
			point_to = DSLLEnd(pqueue->pqueue);
			
			return (0);
		}
	}
	
	return (1);
}
*/
int PQueueErase(pqueue_t *pqueue,
				int (*cond_func)(const void *data,
								 const void *param),
				const void *param)
{
    dsll_iter_t found = NULL;

    assert(pqueue);
    assert(cond_func);

    found = DSLLFindIf(DSLLBegin(pqueue->pqueue), DSLLEnd(pqueue->pqueue), cond_func, (void *)param);

    if (found == DSLLEnd(pqueue->pqueue))
    {
        return (1);
    }

    DSLLRemove(found);
    
    return (0);
}
/*
void PQueueErase(pqueue_t *pqueue, int (*cond_func)(const void *data,
		 const void *param), const void *param)
{
	dsll_iter_t to_delete = NULL;
	
	assert(pqueue);
	assert(cond_func);
	
	to_delete = DSLLFindIf(DSLLBegin(pqueue->pqueue), DSLLEnd(pqueue->pqueue), cond_func, (void *)param);
	
	if(to_delete)
	{
		DSLLRemove(to_delete);
	}
}
*/
void PQPrint(pqueue_t *pq_list)
{
	dsll_iter_t i = 0;
	/*printf("Elements: %lu\n", DSLLSize(list));
	printf("Is Empty: %s\n\n", (DSLLIsEmpty(list) ? "yes" : "no"));*/
	for (i = DSLLBegin(pq_list->pqueue); i != DSLLEnd(pq_list->pqueue);
	     i = DSLLNext(i))
	{
		printf("%d->", *(int *)DSLLGetData(i));
	}

	printf("NULL");
	printf("\n\n");
}


/* helping functions: */
int Compare(const void *data1, const void *data2)
{
	if (*(int *)data1 < *(int *)data2)
	{
		return (1);
	}
	else if (*(int *)data1 > *(int *)data2)
	{
		return (-1);
	}
	return (0);
}

