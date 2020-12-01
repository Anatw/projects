/****************************************************************************
* File Name: fixed_size_queue.h												*
* Writer: Lior Cohen														*
* Date: 10/05/2020														    *
* Purpose: The header file for the fixed size queue data structure			*
* Code reviewer: Yehuda Levavi												*
*****************************************************************************/

#ifndef FIXED_SIZE_QUEUE_H
#define FIXED_SIZE_QUEUE_H

#include <stddef.h> /* size_t */

typedef struct fixed_size_queue fsq_t;

/******************************************************************************/

/* 
* FSQ Create: create new fixed size queue (**only integers**)
* Return: pointer to the new queue, will return NULL in case of an error
* Receive: size_t - the capacity of the new fixed size queue
* Time Complexity: O(1) 
*/
fsq_t *FSQCreate(size_t capacity);

/*
 * FSQ Destroy: Frees all the memeroy allocated for the fixed size queue
 * Receive: fsq_t - Pointer to the fixed size queue
 * Time Complexity: O(1)
 */
void FSQDestroy(fsq_t *queue);

/*
 * FSQ Enqueue: Push new data into the fixed size queue
 * Return: 0 for success, 1 for failure
 * Receive:
 *          fsq_t - Pointer to the fixed size queue
 *          int - The data to insert
 * Time Complexity: O(1)
 */
int FSQEnqueue(fsq_t *queue, int data);

/*
 * FSQ Dequeue: Pop the element out of the queue
 * Return: 0 for success, 1 for failure
 * Receive: fsq_t - Pointer to the queue
 * Time Complexity: O(1)
 */
int FSQDequeue(fsq_t *queue);

/*
 * FSQ Peek: Gets the data of the next element to pop
 * Return: The data found
 * Receive: fsq_t - Pointer to the queue
 * Time Complexity: O(1)
 */
int FSQPeek(fsq_t *queue);

/*
 * FSQSize: Gets the amount of elements in the fixed size queue
 * Return: The amount of elements in the fixed size queue
 * Receive: fsq_t - Pointer to the queue
 * Time Complexity: O(1)
 */
size_t FSQSize(fsq_t *queue);

/*
 * FSQ Is Empty: Checks if the fixed size queue is empty
 * Return: 1 if it is empty, 0 if it's not
 * Receive: fst_t - Pointer to the queue
 * Time Complexity: O(1)
 */
int FSQIsEmpty(fsq_t *queue);


#endif /* FIXED_SIZE_QUEUE_H */