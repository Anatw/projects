/*******************************************************************************
			  			 	Written by Anat Wax
			     			 March 16-19, 2020
		  	  				Reviewer: Yoni Naor
*******************************************************************************/
#ifndef TASK_H
#define TASK_H
#include <time.h> /* time() */

#include "uid.h"

typedef struct task task_t;

/*
 * Create a new task_t.
 * Return: pointer to the newly created task_t.
 * Arguments: Operation_func - pointer to a function this task will execute.
 * 				 	(func) Returns: int - status:
 *					 					0 - keep running the scheduler.
 *									    stop the scheduler:
 *									 		1 - no more items to run.
 *									 		2 - peoblem in allocatinon inside a
 *											 	task function. 
 * 			  		 (func) Argument: param - void pointer to data func need to 
 * 											  proccess.
 * 			   param - void pointer to data func function need to proccess.
 * 					   param may be a pointer to a scheduler.
 * Complexity: O(1)
 */
task_t *TaskCreate(size_t interval,
				   int (*operation_func)(void *param),
				   void *param);

/* 
 * Delete the entire task (free all allocated memory).
 * Return: -
 * Argument: task - the task you want to delete.
 * Complexity: O(n)
 */
void TaskDestroy(task_t *task);

/* 
 * Update the time after which the task will be re-executed (if needed).
 * Return: -
 * Argument: task - the task whose time execution you want to update.
 * Complexity: O(1)
 */
void TaskUpdateTimeToExecute(task_t *task);

/* 
 * Retrieve the task's uid.
 * Return: uid_t of the requested task.
 * Argument: task - the task whose uid you wish to receive.
 * Complexity: O(1)
 */
Uid_t TaskGetUID(task_t *task);

/* 
 * Send the task to the queue to be executed.
 * Return: int status: 0 - keep running the scheduler.
 *					   stop the scheduler: 1 - no more items to run.
 *									 	   2 - peoblem in allocatinon inside a
 *											   task function. 
 * Argument: task - a pointer to the task you want to execute.		  		
 * Complexity: O(1) - O(n) (amortize) - depends on the task (function)
 * 										you execute.
 */
int TaskExecute(task_t *task); /* returns the returned value */

/* Compare two tasks to check which one should be executed first (entered 
 * first to the queue). 
 * Return: 1 = task1 should be executed first.
 *	       0 = they are equal. task1 should be executed first.
 *	       -1 = task2 should be executed first.
 * Complexity: O(1)
 */
int TaskCompareTime(task_t *task1, task_t *task2);

/* Retrieve the next time the test should be executed (relevant only if task 
 * has interval).
 * Return: time_t - the next execution time of the task (if current time is less
 * than the 'next_operation_time' of the task - it means the task doesn't need
 * to be executed again and can be dequeued).
 * Atrument: task - the task who'se next operation time you want to recieve.
 * Complexity: O(1)
 */
time_t TaskGetOperationTime(task_t *task);

#endif /* TASK_H */