/******************************************************************************/
/* 					Task function decleration for working with scheduler	  */
/*														 				 	  */
/*					Autor - Dean Oron									 	  */
/*					Date - 17.03.20									     	  */
/*					Reviewer - 	Anat Wax						         	  */
/*					Open Lab 86											  	  */
/******************************************************************************/

#ifndef TASK_H
#define TASK_H

#include "uid.h"

typedef struct task task_t;

/******************************************************************************/

/* TASK CREATE: Create new task
* Arguments: 
			- Time interval for func execution
			- Function func that will work after the task execution			 
			- Parameter param to be sent to func as an argument
* Return: The new task was allocated			
* Time Complexity: O(1)
*/
task_t *TaskCreate(size_t interval, int (*func)(void *param), void *param);

/*
* TASK DESTROY: Free the allocated task within the heap
* Arguments: Pointer to the task struct
* Time Complexity: O(1)
*/
void TaskDestroy(task_t *task);

/*
* TASK UPDATE TIME: Update the time the task should be execute next 
* Argument:  Pointer to the task
* Time Complexity: O(1)
*/
void TaskUpdateTime(task_t *task);

/*
* TASK GET UID: Get the uniq identification of a task struct
* Arguments: Pointer to the task struct
* Return: The UID of the task
* Time Complexity: O(n)
*/
Uid_t TaskGetUID(task_t *task);

/* TASK EXECUTE
* Argument: Pointer to task
*Return: The status of operation func within task struct
* Time complexity O(1)
 */
int TaskExecute(task_t *task);

/*TASK COMPARE TIME: Decide task execute priority
* Arguments: two pointers for two different task structs
*Return: - 1 if task1 should execute before task2
		 - 0 if both task should execute the same time
		 - -1 if task2 to should execute before task1 
*/
int TaskCompareTime(const void *task1,const  void *task2);/*according to time*/

/* TASK GET OPERATION TIME: Get the time for next execution of task
* Arguments: Pointer to task
*Return: The time in seconds for next execution of task
* Time Complexity: O(1)
*/
time_t TaskGetOperationTime(task_t *task);

#endif /* TASK_H */










