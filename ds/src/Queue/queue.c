/*******************************************************************************
			      Written by Anat Wax
				 March 4, 2020
			     Reviewer: Esti Binder
*******************************************************************************/

/* I'm using the struct of node (node_t) from the Singly Linked List exersize */
#include <stdlib.h>
#include <assert.h> /* assert() */

#include "queue.h"
#include "singly_linked_list.h"

/* left here for aid. The real code is in the "silngly linked list" library
struct SLL
{
	node_t *head;
	node_t *tail;
}SLL_t;

typedef struct sll_node *iter_t;
*/

struct queue
{
	SLL_t *list;
};


queue_t *QueueCreate()
{
	SLL_t *queue_list = SLLCreate(); /*create a new SLL struct list */
	queue_t *new_queue = NULL;
	
	if (NULL == queue_list) /* if malloc failed */
	{
		return (NULL);
	}
	
	new_queue = (queue_t *)malloc(sizeof(queue_t)); /* create a new queue */
	
	if (NULL == new_queue) 	/* if malloc failed */
	{
		return (NULL);
		free(queue_list);
		queue_list = NULL;
	}
	
	new_queue->list = queue_list;	
	
	return (new_queue);
}

int QueueEnqueu(queue_t *queue, void *data)
{
	iter_t new_data = SLLInsert(SLLEnd(queue->list), data);
	
	/* if queue is full (new iter == tail) - return 1 (error) */
	if (1 == SLLIsSameIter(new_data, SLLBegin(queue->list)))
	{
		return (1);
	}
	
	return (0);
}

void QueueDequeu(queue_t *queue)
{
	assert(NULL != queue);
	
	SLLRemove(SLLBegin(queue->list));
}

void *QueuePeek(queue_t *queue)
{
	assert(NULL != queue);
	
	return (SLLGetData(SLLBegin(queue->list)));
}

int QueueIsEmpty(queue_t *queue)
{
	assert(NULL != queue);
	
	return (SLLIsEmpty(queue->list));
}

size_t QueueSize(queue_t *queue)
{
	assert(NULL != queue);
	
	return(SLLCount(queue->list));
}

void QueueDestroy(queue_t *queue)
{
	assert(NULL != queue);
	
	SLLDestroy(queue->list);

	free(queue);
	queue = NULL;
}

void QueueAppend(queue_t *dest, queue_t *src)
{
	assert(NULL != dest);
	assert(NULL != src);
	
	SLLAppend(dest->list, src->list);
}
