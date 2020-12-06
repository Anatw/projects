/*******************************************************************************
This program is ment to create and manage a priority queue based on the API of
Heap.

					  	   Written by Anat Wax
						  23-27 of April, 2020
						Reviewer: Yonathan Berdugo
*******************************************************************************/
#ifndef PRIORITY_QUEUE_H
#define PRIORITY_QUEUE_H

#include <stddef.h> /* size_t */

typedef struct Priority_queue pqueue_t;

/* 
 * Priority Queue Create: allocate memory and create manager struct.
 * Recieve: pointer to priority_func:
 * 	Recieve: 2 pointers to data to compare their priority.
 * Return: -1 if data1's priority is higher than data2.
 * 	   		1 if data2's priority is higher than data1.
 * Return: pointer to a new pqueue_t struct.			  
 * Errors: return NULL if can't allocate memory. 		    	  
 * Time Complexity: O(1) 
 */
pqueue_t *PQueueByHeapCreate(int (*priority_func)(const void *data1,
												  const void *data2));

/* 
 * Priority Queue Destroy: destroy the queue and free its memory.
 * Recieve: pointer to pqueue_t struct.  	    	  
 * Time Complexity: O(n) 
 */
void PQueueByHeapDestroy(pqueue_t *pqueue);

/* 
 * Priority Queue Enqueue: insert new item to the queue by its priority.
 * Recieve: pointer to pqueue_t struct.
 *          pointer to data to insert.
 * Return: 0 for success, 1 for failure.		  	    	  
 * Time Complexity: O(n) 
 */
int PQueueByHeapEnqueue(pqueue_t *pqueue, const void *data);

/* 
 * Priority Queue Dequeue: dequeue the first item from the queue.
 * Recieve: pointer to pqueue_t struct.
 * Time Complexity: O(1) 
 */
void PQueueByHeapDequeue(pqueue_t *pqueue);

/* 
 * Priority Queue Peek: get the data of the first item in the queue.
 * Recieve: pointer to pqueue_t struct.
 * Return: pointer to the data of the first item.
 * Tie Complexity: O(1) 
 */
void *PQueueByHeapPeek(const pqueue_t *pqueue);

/* 
 * Priority Queue Size: retrieve the size (number of members) of the queue.
 * Recieve: pointer to pqueue_t struct.
 * Return: size_t with the current size of the queue.
 * Time Complexity: O(n) 
 */
size_t PQueueByHeapSize(const pqueue_t *pqueue);

/* 
 * Priority Queue Is Empty: check whether the queue is empty.
 * Recieve: pointer to pqueue_t struct.
 * Return: 1 for empty queue, 0 for not empty.
 * Time Complexity: O(1) 
 */
int PQueueByHeapIsEmpty(const pqueue_t *pqueue);

/* 
 * Priority Queue Clear: remove and free all the elements from the queue, but
 * 	saves the structure of the queue.
 * Recieve: pointer to pqueue_t struct.
 * Time Complexity: O(n) 
 */
void PQueueByHeapClear(pqueue_t *pqueue);
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
int PQueueByHeapErase(pqueue_t *pqueue, int (*cond_func)(const void *data, const void *param), const void *param);

/* utility functions : */
int PQByHeapCompare(const void *data1, const void *data2);

#endif /* PRIORITY_QUEUE_H */