/*******************************************************************************
					  	   Written by Anat Wax
						  23-27 of April, 2020
						Reviewer: Yonathan Berdugo
*******************************************************************************/
#include <stdlib.h> /* malloc(), free() */
#include <assert.h> /* assert() */
#include <time.h>	/* time */

#include "heap_scheduler.h"
#include "heap_priority_queue.h"
#include "task.h"

#define FREENULL(where) (((free(where)), ((where) = NULL)))

static int TimeCompare(const void *task1, const void *task2);
static int FindAndDestroy(const void *param1, const void *param2);

struct scheduler
{
	pqueue_t *pqueue;
	int to_stop;		  /*to_stop: 1->stop. 0->keep running */
	task_t *current_task; /* points to the task that is running now */
};						  /* scheduler_t */

/***************************** functions: *************************************/

scheduler_t *SchedulerCreate()
{
	scheduler_t *scheduler = (scheduler_t *)malloc(sizeof(scheduler_t));

	if (!scheduler)
	{
		return (NULL);
	}

	scheduler->pqueue = PQueueByHeapCreate(TimeCompare);

	if (!scheduler->pqueue)
	{
		FREENULL(scheduler);

		return (NULL);
	}

	scheduler->to_stop = 0;
	scheduler->current_task = NULL;

	return (scheduler);
}

void SchedulerDestroy(scheduler_t *schd)
{
	SchedulerClear(schd);

	PQueueByHeapDestroy(schd->pqueue);

	FREENULL(schd);
}

void SchedulerClear(scheduler_t *schd)
{
	task_t *point_to = NULL;

	/* if remove doesn't work => peek->destroy->dqueue insted of clear */
	while (0 == PQueueByHeapIsEmpty(schd->pqueue))
	{
		point_to = PQueueByHeapPeek(schd->pqueue);
		TaskDestroy(point_to);

		PQueueByHeapDequeue(schd->pqueue);
	}
}

/* when creating a new task - always check if the uid is not a bad uid */
Uid_t SchedulerInsertTask(scheduler_t *schd,
						  size_t interval,
						  int (*func)(void *param),
						  void *param)
{
	task_t *new_task = TaskCreate(interval, func, param);

	/* The newely created UID is a bad UID */
	if (!new_task)
	{
		return (UIDGetBadUID());
	}

	if (1 == (PQueueByHeapEnqueue(schd->pqueue, new_task)))
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
	return (PQueueByHeapErase(schd->pqueue, FindAndDestroy, &uid));
}

size_t SchedulerSize(scheduler_t *schd)
{
	size_t counter = PQueueByHeapSize(schd->pqueue);

	if (NULL != schd->current_task)
	{
		++counter;
	}

	return (counter);
}

int SchedulerIsEmpty(scheduler_t *schd)
{
	if (schd->current_task)
	{
		return (0);
	}

	return (0 == SchedulerSize(schd) ? 1 : 0);
}

int CompareFunc(void *param1, void *param2)
{
	return (TaskCompareTime((task_t *)param1, (task_t *)param2));
}

/* const void *data  */
static int TimeCompare(const void *data1, const void *data2)
{
	task_t *task1 = (task_t *)data1;
	task_t *task2 = (task_t *)data2;

	return (TaskCompareTime(task1, task2));
}

/*
 * this is a helping func that accepts the availables parameters, and
 * sent the accpected paramters to the compare func
 * Return: 1 - if could find (and destroy) the requested task (uid).
 * 		   0 - if failed to locate the requested task (uid) to destroy. 
 */
static int FindAndDestroy(const void *data, const void *param)
{
	int is_equal = 0;
	Uid_t uid_param = *(Uid_t *)param;
	task_t *task_data = (task_t *)data;

	is_equal = UIDIsSame(uid_param, TaskGetUID(task_data));

	if (is_equal)
	{
		TaskDestroy(task_data);
	}

	return (is_equal);
}

int SchedulerRun(scheduler_t *schd)
{
	int status = 0;
	task_t *next_task = NULL;

	assert(schd);

	/* in case i stoped the scheduler in a previous run */
	schd->to_stop = 0;

	while (!schd->to_stop && !SchedulerIsEmpty(schd))
	{
		next_task = (task_t *)PQueueByHeapPeek(schd->pqueue);
		schd->current_task = next_task;

		/* if there is time left before				  */
		/* first-task-to-execute - sleep until ready  */
		if (TaskGetOperationTime(next_task) > time(NULL))
		{
			sleep(TaskGetOperationTime(schd->current_task) - time(NULL));
		}

		/* first dqueue, then execute - so that if the task should    */
		/* go back to the queue, it won't go twice 					  */
		PQueueByHeapDequeue(schd->pqueue);
		status = TaskExecute(next_task);

		if (0 != status)
		{
			TaskDestroy(next_task);
		}
		else
		{
			TaskUpdateTimeToExecute(next_task);
			status = PQueueByHeapEnqueue(schd->pqueue, next_task);

			/* 2 = exiting because there was a fault in allocation */
			if (0 != status)
			{
				return (2);
			}
		}
	}

	schd->current_task = NULL;

	return (SchedulerIsEmpty(schd));
}

void SchedulerStop(scheduler_t *schd)
{
	schd->to_stop = 1;
}