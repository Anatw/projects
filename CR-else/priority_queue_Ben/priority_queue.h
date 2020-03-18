/******************************************************************************/
/*                                                                            */
/*                       User Identifier Functions                            */
/*                            Data Structures                                 */
/*                              11/03/2020                                    */
/*                        Author: Ben David Zikri                             */
/*                          Reviwer: Anat Wax                                 */
/*                                                                            */
/******************************************************************************/

#ifndef PQUEUE_H__
#define PQUEUE_H__

#include <stddef.h> /* size_t */

#include "sorted_linked_list.h"

typedef struct PQ pqueue_t;

/*  Allocates memory for new Priority Queue  
 *  Return: pointer to newly created queue 'pq', if fails return NULL 
 *  Time Complexity: O(1)  */
pqueue_t *PQueueCreate(int (*cmp)(void *, void *)); /*return 0/1/-1*/

/*  Free all allocation for given queue 
 *  Get: pointer to pqueue_t 'pq' 
 *  Time Complexity: O(1) */
void PQueueDestroy(pqueue_t *pq);

/* A function to add element in ascending order
 * Return: a pointer to newly created element 
 * Get: pointer to pqueue_t 'pq', and void pointer 'data'
 * if allocation failed returns end element, which does not hold any data
 * Time Complexity O(N) */
int PQueueEnqueue(pqueue_t *pq, const void* data);

/* A function to remove element at the top of the queue
 * Get: pointer to pqueue_t 'pq'
 * Time Complexity: O(1) */
void PQueueDequeue(pqueue_t *pq);

/* A function to return data of element at the top of the queue
 * Return: void pointer to data  
 * Get: pointer to pqueue_t 'pq'
 * Time Complexity: O(1) */
void *PQueuePeek(const pqueue_t *pq);

/* A function to count number of elements in given queue
 * Return: size_t number of elements 
 * Get: pointer to pqueue_t 'pq'
 * Time Complexity: O(N) */
size_t PQueueSize(const pqueue_t *pq);

/* A function that check if given queue is empty
 * Return 1 if 'pq' is empty 1, else return 0 
 * Get: pointer to pqueue_t 'pq'
 * Time Complexity: O(1) */
int PQueueIsEmpty(const pqueue_t *pq);

/* A function erases all elements in queue, leaves the queue empty
 * Get: pointer to pqueue_t 'pq'
 * Time Complexity: O(N) */
void PQueueClear(pqueue_t *pq);	

/* A function that erases specific element in queue
 * Get: pointer to pqueue_t 'pq', a function to check equality 
 * and param function usage
 * Time Complexity: O(N) */
void PQueueErase(pqueue_t *pq, int (*match_func)(void *,void *), const void* param);

/*******************************************************************************
                             Helper Functions
*******************************************************************************/

void PrintPQ(pqueue_t *pq);

#endif /* PQUEUE_H_ */

