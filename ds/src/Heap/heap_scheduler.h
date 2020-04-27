/*******************************************************************************
					  	   Written by Anat Wax
						  23-27 of April, 2020
						Reviewer: Yonathan Berdugo
*******************************************************************************/
#ifndef SCHEDULER_H
#define SCHEDULER_H

#include "task.h"
#include "heap_priority_queue.h"

typedef struct scheduler scheduler_t;

/*
 * after you've built the schedualer, this function will run it in cicles until
 * stoped.
 * Returns status (why functions stopped?):
 * 					0:stopped
 *					1:nothing to run
 *					2: problem in allocation
 * Argument: schd - the scheduler you want to run.
 * Complexity: O(n)
 */
int SchedulerRun(scheduler_t *schd);

/* 
 * Stop the run of the schedualer.
 * Returns: -
 * Argument: schd - the scheduler you want to stop.
 * Complexity: O(1)
 */
void SchedulerStop(scheduler_t *schd); /* stops program */

/* 
 * Creat a new schedualer (including allocating space).
 * Returns: scheduler_t - pointer to the newly created scheduler.
 * Argument: -
 * Complexity: O(1)
 */
scheduler_t *SchedulerCreate();

/* 
 * Delete a schedualer (including freeing any allocated space).
 * Returns: -
 * Argument: schd - pointer to the scheduler you want to delete.
 * Complexity: O(n)
 */
void SchedulerDestroy(scheduler_t *schd);

/* 
 * Insert a new task into a scheduler.
 * Returns: Uid_t - a pointer to the newly created task.
 * Arguments: schd - pointer to the scheduler you want to insert task to.
 * 			  interval - if the task will be executed repitedly, what is the
 * 						 interval (in seconds) in which you want it to execute.
 *			  func - pointer to a function you want this task to execute.
 *					 (func) Returns: int - status:
 *					 				 0 - keep running the scheduler.
 *									 stop the scheduler:
 *									 		1 - no more items to run.
 *									 		2 - peoblem has occured (for 
 *												example: in allocatinon inside 
 *											 	a task function. 
 * 			  		 (func) Argument: param - void pointer to data func need to 
 * 											  proccess.
 * 			  param - void pointer to data func function need to proccess. param
 * 					  may be a pointer to a scheduler.
 * Complexity: O(n)
 */
Uid_t SchedulerInsertTask(scheduler_t *schd,
						  size_t interval,
						  int (*func)(void *param),
						  void *param);

/* 
 * Function to remove (completly delete and free) a task from the scheduler.
 * The user can not remove the task that is now beeing run, It he want to remove
 * the task from the shcedular the functioni should return 1.
 * Returns: int status: 1: success
 * 			 			0: error has occured (for example: failure in 
 *						   locating the task).
 * Arguments: schd - pointer to the scheduler you want to remove task from.
 * 			  Uid_t - the uid of the task you want to remove.
 * Complexity: O(n)
 */
int SchedulerRemoveTask(scheduler_t *schd, Uid_t);

/*
 * See how many tasks are in the schedualer.
 * Returns: size_t of the amount of tasks in the sechdual.
 * Argument: schd - pointer to the scheduler you want to check size.
 * Complexity: O(n)
 */
size_t SchedulerSize(scheduler_t *schd);

/*
 * See if a schedualer is empty (has no tasks).
 * Returns: int status: 1 - empty
 * 						0 - not empty
 * Argument: schd - pointer to the scheduler you want to check if empty.
 * Complexity: O(n)
 */
int SchedulerIsEmpty(scheduler_t *schd);

/*
 * Clear a scheduler - delete all tasks, but keep the scheduler struct.
 * Returns: -
 * Argument: schd - pointer to the scheduler you want to clear.
 * Complexity: O(n)
 */
void SchedulerClear(scheduler_t *schd);

#endif /* SCHEDULER_H */