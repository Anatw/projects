/*******************************************************************************
			   Written by Anat Wax
			     March , 2020
		  	  Reviewer: 
*******************************************************************************/
#include <stdlib.h> /* malloc(), free() */
#include <assert.h> /* assert() */

#include "scheduler.h"
#include "priority_queue.h"
#include "task.h"

#define FREENULL(where) (((free(where)), ((where) = NULL)))

static int TimeCompare(const void * task1, const void *task2);
static int FindAndDestroy(const void *param1, const void *param2);

struct scheduler
{
    pqueue_t *pqueue;
    int to_stop; /*to_stop: 1->stop. 0->keep running */
    task_t *current_task; /* points to the task that is running now */
}; /* scheduler_t */

/*************************** functions: *********************************/

scheduler_t *SchedulerCreate()
{
	scheduler_t *scheduler = (scheduler_t*)malloc(sizeof(scheduler_t));
	scheduler->pqueue = PQueueCreate(TimeCompare);
	scheduler->to_stop = 0;
	scheduler->current_task = PQueuePeek(scheduler->pqueue);
	
	return (scheduler);
}

void SchedulerDestroy(scheduler_t *schd)
{
	SchedulerClear(schd);

	PQueueDestroy(schd->pqueue);
	
	FREENULL(schd->pqueue);
	FREENULL(schd);
}

void SchedulerClear(scheduler_t *schd)
{
	task_t *point_to = PQueuePeek(schd->pqueue);
	
	/* if remove doesn't work => peek->destroy->dqueue insted of clear */
	while (0 == SchedulerIsEmpty(schd))
	{
		SchedulerRemoveTask(schd, TaskGetUID(point_to));
		point_to = PQueuePeek(schd->pqueue);
	}
}

/* when creating a new task - always check if the uid is not a bad uid */
Uid_t SchedulerInsertTask(scheduler_t *schd,
						  size_t interval, int 							  (*func)(void *param),
						  void *param)
{
	task_t *new_task = TaskCreate(interval, func, param);
	
	 /* The newely created UID is a bad UID */
	if (!new_task)
	{
		return (UIDGetBadUID());
	}
	
	if (1 == (PQueueEnqueue(schd->pqueue, new_task)))
	{
		TaskDestroy(new_task);
		
		return (UIDGetBadUID());
	}
		
	return (TaskGetUID(new_task));
}

/*
 * int - to check inside the loop on run. after execute you check the status
 * the function return. 1 - the task if deleted from the queue. the queue is
 * moving to the next task. if 1 - put back in the queue
 */
int SchedulerRemoveTask(scheduler_t *schd, Uid_t uid)
{
	return (PQueueErase(schd->pqueue, FindAndDestroy, &uid));
}

size_t SchedulerSize(scheduler_t *schd)
{
	size_t counter = PQueueSize(schd->pqueue);
		
	if (NULL != schd->current_task)
	{
		++counter;
	}
	
	return (counter);
}

int SchedulerIsEmpty(scheduler_t *schd)
{
	return (0 == SchedulerSize(schd) ? 1 : 0);
}

int CompareFunc(void *param1, void *param2)
{
	return (TaskCompareTime((task_t *)param1, (task_t *)param2));
}

/* const void *data  */
static int TimeCompare(const void * data1, const void *data2)
{
	task_t *task1 = (task_t *)data1;
	task_t *task2 = (task_t *)data2;
	
	return (TaskCompareTime(task1, task2));
}

/*
 * this is a helping func that accepts the availables parameters, and
 * sent the accpected paramters to the compare func
 */
static int FindAndDestroy(const void *data1, const void *param)
{
	int is_equal = 0;
	task_t *task_data = (task_t *)data1;
	Uid_t *uid_param = (Uid_t *)param;
	
	is_equal = UIDIsSame(*uid_param, TaskGetUID(task_data));
	
	if (is_equal)
	{
		TaskDestroy(task_data);
	}
	
	return (is_equal);
}
  
int SchedulerRun(scheduler_t *schd)
{
	while (!schd->to_stop && !SchedulerIsEmpty(schd))
	{
		task_t *current_task = (task_t *)PQueuePeek(schd->pqueue);
		
		/* if there is time left before first-task-to-execute - sleep until ready */
		if ((TaskGetOperationTime(current_task) > time(NULL)));
		{
			sleep(TaskGetOperationTime(schd->current_task) - time(NULL);
		}
		
		/* first dqueue, then execute - so that if the task should go back to the queue, it won't go twice */
		PQueueDequeue(schd->pqueue);
		
		int status = TaskExecute(current_task);
		
		if (0 != status)
		{
		
		
		TaskUpdateTimeToExecute(current_task);
	
		if (TaskGetOperationTime(current_task) > time(NULL))
		{
			PQueueEnqueue(schd->pqueue, current_task);
		}
		else /* task was ment to execute only once */
		{
			SchedulerRemoveTask(schd, TaskGetUID(current_task));
		}
	}
		
	if (schd->to_stop || SchedulerIsEmpty(schd))
	{
		return (0);
	}
	
	return (1);
}

void SchedulerStop(scheduler_t *schd)
{
	schd->to_stop = 1;
}
