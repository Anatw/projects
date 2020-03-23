/******************************************************************************/
/* 					Task function definition for working with scheduler	  	  */
/*														 				 	  */
/*					Autor - Dean Oron									 	  */
/*					Date - 17.03.20									     	  */
/*					Reviewer - 	Anat Wax						         	  */
/*					Open Lab 86											  	  */
/******************************************************************************/

#include <stdlib.h> 
#include <assert.h> 
#include <time.h>	
#include <unistd.h> 

#include "scheduler.h"
#include "pqueue.h"
#include "task.h"

static int FindUidAndDestroy(const void *param1, const void *param2);

struct scheduler
{
    pqueue_t *pqueue;
    int to_stop; 				
    task_t *current_task; 
};

scheduler_t *SchedulerCreate()
{
	scheduler_t *new_schedule;
	pqueue_t *new_pqueue = NULL;

	new_schedule = (scheduler_t *)malloc(sizeof(scheduler_t));

	if (!new_schedule)
	{
		return (NULL);
	}

	new_pqueue = PQueueCreate(TaskCompareTime);

	if (NULL == new_pqueue)
	{
		free(new_schedule);
		new_schedule = NULL;
		return (NULL);
	}

	new_schedule->to_stop = 0;
	new_schedule->pqueue = new_pqueue;
	new_schedule->current_task = NULL;
	
	return (new_schedule);
}

void SchedulerStop(scheduler_t *schedule)
{
	assert(schedule);
	
	schedule->to_stop = 1;
}

size_t SchedulerSize(scheduler_t *schedule)
{
	assert(schedule);
	
	return (PQueueSize((const pqueue_t*)schedule->pqueue));
}

int SchedulerIsEmpty(scheduler_t *schedule)
{
	assert(schedule);
	
	if(schedule->current_task)  
	{						
		return(0);
	}
	
	return (PQueueIsEmpty(schedule->pqueue));
}

void SchedulerClear(scheduler_t *schedule)
{
	task_t *to_remove = NULL;

	while (!SchedulerIsEmpty(schedule)) /* as long as schedule still contained task*/
	{	
		to_remove = (task_t*)PQueuePeek(schedule->pqueue);
		TaskDestroy(to_remove);
		PQueueDequeue(schedule->pqueue);
	}
}

Uid_t SchedulerInsertTask(scheduler_t *schedule, size_t interval,
						 	 int (*operation_func)(void *param), void *param)
{
	task_t *to_insert;
	int status = 0;

	assert(schedule && operation_func);

	to_insert = TaskCreate(interval, operation_func, param);

	if (NULL == to_insert)
	{
		return (UIDGetBadUID());
	}

	status = PQueueEnqueue(schedule->pqueue, to_insert);

	if (status != 0)
	{
		TaskDestroy(to_insert);

		return (UIDGetBadUID());
	}

	return (TaskGetUID(to_insert));
}

int SchedulerRun(scheduler_t *schedule) 
{
	task_t *next_task = NULL;
	int status = 0;

	assert(schedule);

	schedule->to_stop = 0;

	while (!schedule->to_stop  && !SchedulerIsEmpty(schedule))
	{
		next_task = (task_t *)PQueuePeek(schedule->pqueue);

		if (TaskGetOperationTime(next_task) > time(NULL))
		{
			sleep(TaskGetOperationTime(next_task) - time(NULL));
		}

		schedule->current_task = next_task;
		PQueueDequeue(schedule->pqueue);

		status = TaskExecute(next_task);
		
		if (TaskGetInterval(next_task) == 0)
		{
			TaskDestroy(next_task);
		}
		else if (status != 0)
		{
			TaskDestroy(next_task);
		}
		else
		{
			TaskUpdateTime(next_task);
			status = PQueueEnqueue(schedule->pqueue, next_task);

			if (status != 0)
			{
				return (2);
			}
		}
	}

	schedule->current_task = NULL;
	/* return 0 if exited by command, 1 if scheduler empty */
	return (SchedulerIsEmpty(schedule));
}

void SchedulerDestroy(scheduler_t *schedule)
{
	/* empty and free the scheduler */
	SchedulerClear(schedule);

	/* destroy its queue */
	PQueueDestroy(schedule->pqueue);

	free(schedule);
	schedule = NULL;
}

int SchedulerRemoveTask(scheduler_t *schedule, Uid_t uid)
{
	return (PQueueErase(schedule->pqueue, FindUidAndDestroy, &uid));
}

/********************************Utility func**********************************/

static int FindUidAndDestroy(const void *param1, const void *param2)
{
	int found = UIDIsSame(TaskGetUID((task_t *)param1), *(Uid_t *)param2);
	task_t *to_remove = (task_t *)param1; 

	if (found)
	{
		TaskDestroy(to_remove); /* Destroy the specific task */
	}

	return (found);
}

