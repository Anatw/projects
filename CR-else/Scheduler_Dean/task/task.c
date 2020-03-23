/******************************************************************************/
/* 					Task function definition for working with scheduler	  	  */
/*														 				 	  */
/*					Autor - Dean Oron									 	  */
/*					Date - 17.03.20									     	  */
/*					Reviewer - 	Anat Wax						         	  */
/*					Open Lab 86											  	  */
/******************************************************************************/

#include <assert.h> /* assert() */
#include <stdio.h>
#include <stdlib.h> /* malloc(), free() */

#include "task.h"

struct task
{
	Uid_t  uid;
	size_t interval;
	int (*func)(void *param);
	void *param;
	time_t next_operation_time;
};

/*****************************************************************************/

task_t *TaskCreate(size_t interval, int (*func)(void *param), void *param)
{
	task_t *new_task = NULL;
	
	assert(func);
	assert(param);
	
	new_task = (task_t *)malloc(sizeof(task_t));
	
	if (!new_task)
	{
		return (NULL);
	}
	
	new_task->uid = UIDCreate();
	new_task->interval = interval;
	new_task->func = func;
	new_task->param = param;
	new_task->next_operation_time = time(NULL) + (time_t)interval;
	
	return (new_task);
}

/*****************************************************************************/

void TaskDestroy(task_t *task)
{
	free(task);
	task = NULL;
}

/*****************************************************************************/

void TaskUpdateTime(task_t *task)
{
	task->next_operation_time = (time(NULL) + task->interval);
}

/*****************************************************************************/

Uid_t TaskGetUID(task_t *task)
{
	return (task->uid);
}

/*****************************************************************************/

int TaskExecute(task_t *task)
{
	return (task->func(task->param));
}

/*****************************************************************************/

int TaskCompareTime(const void *task1, const void *task2)
{	
	task_t *task_1 = (task_t*)task1;
	task_t *task_2 = (task_t*)task2;
	
	if (task_1->next_operation_time < task_2->next_operation_time)
	{
		return (1);
	}
	else if (task_1->next_operation_time == task_2->next_operation_time)
	{
		return (0);
	}
	
	return (-1);
}

/*****************************************************************************/

time_t TaskGetOperationTime(task_t *task)
{
	return (task->next_operation_time);
}

size_t TaskGetInterval(task_t *task)
{
	return (task->interval);
}
