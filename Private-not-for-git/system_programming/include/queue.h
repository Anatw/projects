/*******************************************************************************
			      Written by Anat Wax
				 March 4, 2020
			     Reviewer: Esti Binder
*******************************************************************************/
#include <stddef.h>

#ifndef QUEUE_H
#define QUEUE_H

typedef struct queue queue_t;

/* Functionality: create a new queue 					*/
/* Complexity: O(1)							*/
queue_t *QueueCreate();

/* Functionality: delete all members in the queue			*/
/* 'queue': the queue whose members you'd like to delete	  	*/
/* Complexity: O(n) 							*/
void QueueDestroy(queue_t *queue);

/* Functionality: allow to user to add a member to the queue 		*/
/* 'queue': the queue to which you'd like to add to member 		*/
/* 'data' - void pointer to the data you'd like to add to the queue 	*/
/* Complexity: O(1) 							*/
/* Enqueue = add a new node to the tail of the list 			*/
int QueueEnqueu(queue_t *queue, void *data);

/* Functionality: remove a node from the head of the list 		*/
/* 'queue': the queue from which you'd like to delete a member		*/
/*  Complexity: O(1) 							*/
void QueueDequeu(queue_t *queue);

/* Functionality: check the data stored in the queue (the data 		*/
/* of the next member to dequeue 					*/
/* 'queue': the queue in which you'd like to peek 			*/
/* Complexity: O(1) 							*/
void *QueuePeek(queue_t *queue);

/* Functionality: return the size (number of members) in thr queue 	*/
/* 'queue': the queue whose members you'd like to count 		*/
/* Complexity: O(n) 							*/
size_t QueueSize(queue_t *queue);

/* Functionality: check whther the queue is empty (doesn't include	*/
/* any members) 							*/
/* 'queue': the queue you'd like to check 				*/
/* Complexity: O(1) 							*/
int QueueIsEmpty(queue_t *queue);

/* Functionality: appent the 'src' list right after the '*dest' list. the function dows not 
 * destroy the empty string - it is the costumers responsibility to free that list	*/
/* '*dest' - the list which will be start the new list 			*/
/* '*src' - the appended list (after '*dest') 				*/
/* Complexity: O(1) 							*/
void QueueAppend(queue_t *dest, queue_t *src);


#endif
