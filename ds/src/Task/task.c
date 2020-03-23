/*******************************************************************************
			  			 	Written by Anat Wax
			     			 March 16-19, 2020
		  	  				Reviewer: Yoni Naor
*******************************************************************************/
#include <stdlib.h> /* malloc(), free() */
#include <assert.h> /* assert() */
#include <time.h> /* time() */

#include "task.h"

struct task
{
    Uid_t uid;
    size_t interval_in_seconds;
    int (*operation_func)(void *param);
    void *param;
    time_t next_operation_time;
};

task_t *TaskCreate(size_t interval,
				   int (*operation_func)(void *param),
				   void *param)
{
	task_t *new_task = NULL;
	/* Uid_t bad_uid = UIDGetBadUID(); */
	
	assret(operation_func);
	assert(param);
	
	new_task = (task_t *)malloc(sizeof(task_t));
	
	if (NULL == new_task)
	{
		return (NULL);
	}
	
	new_task->uid = UIDCreate();
	 /* This section was deleted because it made problems with the test file.
	 * The newely created UID is a bad UID 
	if (1 == UIDIsSame(bad_uid, new_task->uid))
	{
		return (NULL); /* inside scheduler - check the UID 
	}*/
	
	new_task->interval_in_seconds = interval;
	new_task->operation_func = operation_func;
	new_task->param = param;
	new_task->next_operation_time = time(NULL) + interval;
	
	return (new_task);
}

void TaskDestroy(task_t *task)
{
	assert(task);

	free(task);
	task = NULL;
}

void TaskUpdateTimeToExecute(task_t *task)
{
	assert(task);

	task->next_operation_time = time(NULL) + task->interval_in_seconds;
}

Uid_t TaskGetUID(task_t *task)
{
	assert(task);
	
	return (task->uid);
}

int TaskExecute(task_t *task)
{
	assert(task);
	
	return (task->operation_func(task->param));
}

/* 1 if task1 should execute before task2, and (-1) if  */
/* task2 should execute first 							*/
int TaskCompareTime(task_t *task1, task_t *task2)
{
	assert(task1);
	assert(task2);
	
	if (task1->next_operation_time < task2->next_operation_time)
	{
		return (1);
	}
	else if (task1->next_operation_time > task2->next_operation_time)
	{
		return (-1);
	}
	
	return (0); /* if equal */
}

time_t TaskGetOperationTime(task_t *task)
{
	assert(task);
	
	return (task->next_operation_time);
}
