/* returns status (why functions stopped? 0:stopped, 1:nothing to run */
/* execute first task-> enqueue (with updated next operation) */

#include <stddef.h>
#include "uid.h"

typedef struct scheduler scheduler_t; 

/*
 * Function that start the running of a schdule
 * Argumrnt: A specific schedule
 * Return: 0 if stopped on purpose
 * Time complexity O(n)
*/
int SchedulerRun(scheduler_t *schedule);

/*  
 * A function to stop a certain schedule
 * Argument: A specific schedule
 * Return: void 
 * Time complexity O(1)
*/
void SchedulerStop(scheduler_t *schedule); 

/*
 * A function to create a new schedule with priority queue 
 * Return a pointer to the new schedule struct
 * Time complexity O(1)
*/
scheduler_t *SchedulerCreate();

/*
 * A function to free the memory was allocated by the schedule
 * Arguments: A specific schedule
 * Return: void
 * Time complexity O(1)
*/
void SchedulerDestroy(scheduler_t *schedule);

/*
 * A function to insert a new task within the schedule 
 * Arguments: func will insert as a new task to schedule with an interval time
 * to repeat the task and param to be sent to the task
 * Return: The new task uid
*/
Uid_t SchedulerInsertTask(scheduler_t *schedule, size_t interval, int (*func)(void *param), void *param);

/*
 * A function to remove certain task 
 * Arguments: the schedule am=nd the task to be removed
 * Return: 0 for success and 1 for failure
 * Time complexity O(n)
*/
int SchedulerRemoveTask(scheduler_t *schedule, Uid_t); 

/*
 * A function to get the current number of tasks within schedule
 * Arguments: a spesific schedule
 * Return: the current amount of tasks
 * Time complexity O(n)
*/
size_t SchedulerSize(scheduler_t *schedule);

/*
 * A function that tells the user whether schedule is empty from tasks or not 
 * Arguments: A specific schedule
 * Return: 1 if true and 0 if false
 * Time Complexity: O(1)
*/
int SchedulerIsEmpty(scheduler_t *schedule);

/*
 * A function to clear all schedule from tasks
 * Arguments: A specific schedule
 * Return: void
 * Time complexity: O(n)
*/
void SchedulerClear(scheduler_t *schedule);

