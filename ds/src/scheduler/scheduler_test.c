/*******************************************************************************
 * File: scheduler_tests.c - tests file				 		           		   *
 * Author: Yehuda Levavi                                                       *
 * Reviewed by: 				                                   			   *
 * Date: 		                                                           	   *
 * Note: Due to efficiency reasons, there are no user protection in the 	   *
 * functions, and all the validations are the responsibility of the user.      *
 ******************************************************************************/

#include <stdio.h>	/* printf */
#include <assert.h> /* assert */
#include <unistd.h> /* getuid */
#include <time.h>	/* time, time_t, ctime */

#include "scheduler.h"

/* Test Functions: */
int BasicTests();

/* Sample Operation Functions */
int PrintFivePlus(void *param);
int PrintUID(void *param);
int PrintTime(void *param);
int ReturnOne(void *param);
int ToStopSched(void *param);

int main()
{
	/*assert(BasicTests() == 0);*/
	return (0);
}

/* Test Functions: */
int BasicTests()
{
	scheduler_t *my_sched = SchedulerCreate();
	int num = 20;
	int status = 0;
	Uid_t task1 = UIDGetBadUID();
	Uid_t task2 = UIDGetBadUID();
	Uid_t task3 = UIDGetBadUID();

	/* check size & IsEmpty when empty: */
	assert(SchedulerIsEmpty(my_sched));
	assert(SchedulerSize(my_sched) == 0);

	/* inserting tasks: */
	task1 = SchedulerInsertTask(my_sched, 5, PrintTime, &my_sched);
	task2 = SchedulerInsertTask(my_sched, 10, PrintUID, NULL);
	task3 = SchedulerInsertTask(my_sched, 0, PrintFivePlus, &num);

	/* check size & IsEmpty when full: */
	assert(!SchedulerIsEmpty(my_sched));
	assert(SchedulerSize(my_sched) == 3);

	/* running the scheduler: */
	printf("expecting PrintTime every 5 sec, PrintUID every 10 sec, and \n");
	printf("one time of PrintFivePlus. scheduler will stop after 5 times \n");
	printf("of PrintTime: \n\n");

	status = SchedulerRun(my_sched);
	assert(0 == status); /* validate that exited by command */

	/* check SchedulerRemoveTask */
	SchedulerRemoveTask(my_sched, task2);
	assert(SchedulerSize(my_sched) == 2);

	printf("\nRunnig again: expecting PrintTime every 5 sec, no Print UID, \n");
	printf("one time of PrintFivePlus. scheduler will stop after 5 times \n");
	printf("of PrintTime: \n\n");
	status = SchedulerRun(my_sched); /* run it again without PrintUID */
	assert(0 == status);			 /* validate that exited by command */

	/* check SchedulerClear */
	SchedulerClear(my_sched);
	assert(SchedulerIsEmpty(my_sched));
	assert(SchedulerSize(my_sched) == 0);

	/* check return status is 1 when scheduler empty */
	status = SchedulerRun(my_sched);
	assert(status == 1);

	SchedulerDestroy(my_sched);

	return (0);
}

/* Sample Operation Functions */
int PrintFivePlus(void *param)
{
	int var = *(int *)param;

	printf("5 + %d = %d\n", var, 5 + var);

	return (0);
}

int PrintUID(void *param)
{
	printf("Current Proccess UID: %d\n", getpid());

	return (0);
}

int PrintTime(void *param)
{
	time_t current = time(NULL);
	static int count = 0;
	scheduler_t *my_sched = (scheduler_t *)param;

	printf("Current Time: %s\n", ctime(&current));

	if (count == 5)
	{
		return (ToStopSched(my_sched));
	}

	++count;

	return (0);
}

int ReturnOne(void *param)
{
	printf("Stopping the scheduler with return 1!\n");
	return (1);
}

int ToStopSched(void *param)
{
	scheduler_t *my_sched = (scheduler_t *)param;

	printf("Stopping the scheduler with SchedulerStop!\n");
	SchedulerStop(my_sched);

	return (0);
}
