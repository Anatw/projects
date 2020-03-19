/*******************************************************************************
			   Written by Anat Wax
			     March , 2020
		  	  Reviewer: 
*******************************************************************************/
#ifndef SCHEDULER_H
#define SCHEDULER_H

#include "task.h"
#include "priority_queue.h"

typedef struct scheduler scheduler_t;

/* returns status (why functions stopped? 0:stopped
									1:nothing to run
									2: problem in allocation */
/* execute first task-> enqueue (with updated next operation) */
int SchedulerRun(scheduler_t *schd);
void SchedulerStop(scheduler_t *schd); /* stops program */

scheduler_t *SchedulerCreate();
void SchedulerDestroy(scheduler_t *schd);

/* func returns status (0: keep running, 1: stop) */
/* param may be a pointer to the scheduler */
Uid_t SchedulerInsertTask(scheduler_t *schd,
						  size_t interval,
						  int (*func)(void *param),
						  void *param);

/* status-> 0: found. 1:not found */
int SchedulerRemoveTask(scheduler_t *schd, Uid_t); 

/* Check how many tasks are in the schedualer */
size_t SchedulerSize(scheduler_t *schd);

int SchedulerIsEmpty(scheduler_t *schd);

void SchedulerClear(scheduler_t *schd);

/* helping functions */


/* NOTES */

/* PSEUDO-CODE: in this exercise we suppose to make a sequence diagram (UML)*/
/* pay attention for the run function! */
/* filenames: scheduler.h scheduler_functions.c scheduler_tests  */

/* running process: (pseudo-code)
while(!to_stop)
peek
current_task = peek
dequeue
execute
TaskUpdateTime(currentTask)
Enqueue
*/

#endif /* SCHEDULER_H */
