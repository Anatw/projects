/*******************************************************************************
This program is ment to create and manage a priority queue based on the API of
sorted-duobly-linked-list.
			   Written by Anat Wax
			     March 14-15, 2020
		  	  Reviewer: Haim sa'adia
*******************************************************************************/
#ifndef PRIORITY_QUEUE_H
#define PRIORITY_QUEUE_H

#include <stddef.h> /* size_t */

/* Priority Queue type */
typedef struct Priority_queue pqueue_t;

/* 
 * Priority Queue Create: allocate memory and create manager struct.
 * Recieve: pointer to priority_func:
 * 	Recieve: 2 pointers to data to compare their priority.
 * Return: -1 if data1's priority is higher than data2.
 * 	   0 if their priority is equal.
 * 	   1 if data2's priority is higher than data1.
 * Return: pointer to a new pqueue_t struct.			  
 * Errors: return NULL if can't allocate memory. 		    	  
 * Time Complexity: O(1) 
 */
pqueue_t *PQueueCreate(int (*priority_func)(const void *data1,
                                            const void *data2));

/* 
 * Priority Queue Destroy: destroy the queue and free its memory.
 * Recieve: pointer to pqueue_t struct.  	    	  
 * Time Complexity: O(n) 
 */
void PQueueDestroy(pqueue_t *pqueue);

/* 
 * Priority Queue Enqueue: insert new item to the queue by its priority.
 * Recieve: pointer to pqueue_t struct.
 *          pointer to data to insert.
 * Return: 0 for success, 1 for failure.		  	    	  
 * Time Complexity: O(n) 
 */
int PQueueEnqueue(pqueue_t *pqueue, const void *data);

/* 
 * Priority Queue Dequeue: dequeue the first item from the queue.
 * Recieve: pointer to pqueue_t struct.
 * Time Complexity: O(1) 
 */
void PQueueDequeue(pqueue_t *pqueue);

/* 
 * Priority Queue Peek: get the data of the first item in the queue.
 * Recieve: pointer to pqueue_t struct.
 * Return: pointer to the data of the first item.
 * Time Complexity: O(1) 
 */
void *PQueuePeek(const pqueue_t *pqueue);

/* 
 * Priority Queue Size: retrieve the size (number of members) of the queue.
 * Recieve: pointer to pqueue_t struct.
 * Return: size_t with the current size of the queue.
 * Time Complexity: O(n) 
 */
size_t PQueueSize(const pqueue_t *pqueue);

/* 
 * Priority Queue Is Empty: check whether the queue is empty.
 * Recieve: pointer to pqueue_t struct.
 * Return: 1 for empty queue, 0 for not empty.
 * Time Complexity: O(1) 
 */
int PQueueIsEmpty(const pqueue_t *pqueue);

/* 
 * Priority Queue Clear: remove and free all the elements from the queue, but
 * 	saves the structure of the queue.
 * Recieve: pointer to pqueue_t struct.
 * Time Complexity: O(n) 
 */
void PQueueClear(pqueue_t *pqueue);

/* 
 * Priority Queue Erase: remove the first element that answers a condition.
 * Return - 0 if cond_func succedded, 1 if it failed.
 * Recieve: 1. pointer to pqueue_t struct.
 *          2. pointer to cond_func:
 *               * Recieve: pointer to data and pointer for parameter.
 *               * Return: 1 if the condition returns true, 0 if false.
 *          3. pointer to the parameter
 * Time Complexity: O(n) 
 */
int PQueueErase(pqueue_t *pqueue, int (*cond_func)(const void *data,
		 const void *param), const void *param);


/* helping functions: */
int Compare(const void *data1, const void *data2);
#endif /* PRIORITY_QUEUE_H */

