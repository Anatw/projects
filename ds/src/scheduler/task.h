/*******************************************************************************
			   Written by Anat Wax
			     March 16-17, 2020
		  	  Reviewer: 
*******************************************************************************/
#ifndef TASK_H
#define TASK_H
#include <time.h> /* time() */

#include "uid.h"

typedef struct task task_t;

/* Create a new task_t.
 * Return: pointer to the newly created task_t.
 * Operation_func - the client function to 
 *	return 0 in case of success and  1 in case of failure.
 * Complexity:
 */
task_t *TaskCreate(size_t interval,
				   int (*operation_func)(void *param),
				   void *param);
/* Delete the entire task (free all allocated memory).
 * Return: 0 - if succedded, 1 - if failed.
 * Task - the task you want to delete.
 * Complexity:
 */
void TaskDestroy(task_t *task);

/* Update the time after which the task will be re-executed (if needed).
 * Return: -
 * Task - the task whose time execution you want to update.
 * Complexity:
 */
void TaskUpdateTimeToExecute(task_t *task);

/* retrieve the task's uid.
 * Return: uid of the requested task.
 * task - the task whose uid you wish to know.
 * Complexity: O(1)
 */
Uid_t TaskGetUID(task_t *task);

/* Send the task to the queue to be executed.
 * Return: 0 - success. 
 *
 * Complexity:
 */
int TaskExecute(task_t *task); /* returns the returned value */

/* Compare two tasks to check which one should be executed first.
 * Return: 
 * Return: 1 = task1 should be executed first.
 	   0 = they are equal. task1 should be executed first.
 	   -1 = task2 should be executed first.
 * Complexity: O(1)
 */
int TaskCompareTime(task_t *task1, task_t *task2);

/* 
 * Return: 
 *
 * Complexity:
 */
time_t TaskGetOperationTime(task_t *task);

#endif /* TASK_H */
