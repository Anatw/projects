#include <stdlib>

#include "queue.h"
#include "../SinglyLinkedList/singly_linked_list.h"

/*
struct SLL
{
	node_t *head;
	node_t *tail;
};
*/

typedef struct queue
{
	SLL_t *list;
};

queue_t *QueueCreate()
{
	SLL_t *queue_list = SLLCreate(); /*create a new list */
	
	if(NULL == queue_list)
	{
		return (NULL);
	}
	
	SLL_t *queue = (SLL_t *)malloc(sizeof(SLL_t)); /* create a new queue */
	
	if(NULL == queue) 	/* if mallocs failed */
	{
		return (NULL);
	}
	SLL_t *queue_list
	
}


/*int QueueEnqueu(queue_t *queue)
Enqueue: Adds an item to the queue. If the queue is full, then it is said to be an Overflow condition.*/
