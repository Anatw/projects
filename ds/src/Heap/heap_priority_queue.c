/*******************************************************************************
					  	   Written by Anat Wax
						  23-27 of April, 2020
						Reviewer: Yonathan Berdugo
*******************************************************************************/
#include <stdlib.h> /* malloc(), free() */
#include <assert.h> /* assert() */
#include <stdio.h> /*printf() */

#include "heap_priority_queue.h"
#include "heap.h"


struct Priority_queue
{
	heap_t *heap;
	int (*priority_func)(const void *data1, const void *data2);
}; /* pqueue_t */

pqueue_t *PQueueByHeapCreate(int (*priority_func)(const void *data1,
                                            const void *data2))
{
	pqueue_t *new_pqueue = NULL;
	heap_t *new_heap = NULL;
	
	assert(priority_func);
	
	new_pqueue = (pqueue_t *)malloc(sizeof(pqueue_t));
	
	if (NULL == new_pqueue)
	{
		return (NULL);
	}
	
	new_heap = HeapCreate(priority_func);
	
	if (NULL == new_heap)
	{
		free(new_pqueue);
		new_pqueue = NULL;
		
		return (NULL);
	}
	
	new_pqueue->heap = new_heap;
	new_pqueue->priority_func = priority_func;
	
	return (new_pqueue);
}

void PQueueByHeapDestroy(pqueue_t *pqueue)
{
	assert(pqueue);
	
	HeapDestroy(pqueue->heap);
	
	free (pqueue);
	pqueue = NULL;
}

int PQueueByHeapEnqueue(pqueue_t *pqueue, const void *data)
{
	void *p_data = (void *)data;
	int status = 0;
	
	assert(pqueue);
	status = HeapPush(pqueue->heap, p_data);
	
	return (status);
}

void PQueueByHeapDequeue(pqueue_t *pqueue)
{
	assert(pqueue);
	
	HeapPop(pqueue->heap);
}

void *PQueueByHeapPeek(const pqueue_t *pqueue)
{
	assert(pqueue);
	
	return (HeapPeek(pqueue->heap));
}


size_t PQueueByHeapSize(const pqueue_t *pqueue)
{
	assert(pqueue);
	
	return (HeapSize(pqueue->heap));
}

int PQueueByHeapIsEmpty(const pqueue_t *pqueue)
{
	assert(pqueue);
	
	return (HeapIsEmpty(pqueue->heap));
}

void PQueueByHeapClear(pqueue_t *pqueue)
{
	size_t size = 0;;
	
	assert(pqueue);

	size = HeapSize(pqueue->heap);

	for (; size > 0; --size)
	{
		HeapPop(pqueue->heap);
	}
}


int PQueueByHeapErase(pqueue_t *pqueue,
				int (*cond_func)(const void *data,
								 const void *param),
				const void *param)
{
	void *found_data = NULL;

    assert(pqueue);
    assert(cond_func);

	found_data = HeapRemove(pqueue->heap, cond_func, param);

    if (NULL == found_data)
    {
        return (1);
    }

    return (0);
}

void PQByHeapPrint(pqueue_t *pq_list)
{
	PrintHeap(pq_list->heap);

	printf("NULL");
	printf("\n\n");
}


/* helping functions: */
int PQByHeapCompare(const void *data1, const void *data2)
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