/******************************************************************************/
/* 					Task function definition for working with scheduler	  	  */
/*														 				 	  */
/*					Autor - Dean Oron									 	  */
/*					Date - 17.03.20									     	  */
/*					Reviewer - 	Anat Wax						         	  */
/*					Open Lab 86											  	  */
/******************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "task.h"
#include "scheduler.h"

int PrintNames(void *param);
int PrintTime(void *param);
int PrintParam(void *param);
int CheckEmptiness(void *param);

int main()
{
	
	Uid_t uid1 = UIDGetBadUID();
	Uid_t uid2 = UIDGetBadUID();
	Uid_t uid3 = UIDGetBadUID();
	Uid_t uid4 = UIDGetBadUID();
	Uid_t uid5 = UIDGetBadUID();
	int x = 7;
	int y = 8;
	int z = 9;
	
	
	scheduler_t *schedule = SchedulerCreate();
	
	printf("Is empty: %d\n", SchedulerIsEmpty(schedule));
	uid1 = SchedulerInsertTask(schedule, 1, PrintNames, schedule);
	uid2 = SchedulerInsertTask(schedule, 3, PrintTime, &x);
	uid3 = SchedulerInsertTask(schedule, 1, PrintParam, &y);	
    uid4 = SchedulerInsertTask(schedule, 6, PrintParam, &z);
	uid5 = SchedulerInsertTask(schedule, 4, CheckEmptiness, schedule);
	
 	
	printf("Size: %ld\n", SchedulerSize(schedule));
	
/* remove comment mark to test SchedulerRemove*/ 	

 	SchedulerRun(schedule);
 	SchedulerRemoveTask(schedule, uid4);
 	SchedulerRun(schedule);
 	

	printf("Is empty: %d\n", SchedulerIsEmpty(schedule));
	printf("Size: %ld\n", SchedulerSize(schedule));
	
	printf("%d\n", uid1.SN);
	printf("%d\n", uid2.SN);
	printf("%d\n", uid3.SN);
	printf("%d\n", uid4.SN);
	printf("%d\n", uid5.SN);

	SchedulerDestroy(schedule);

	return (0);
}

int PrintNames(void *param)
{
	static int count = 0;
	const char *names[] = {"dana", "moshe", "david", "ran", "shmuel"};

	if (count == 5)
	{	
		printf("last name has reached and exit\n");
		SchedulerStop((scheduler_t*)param);
		count = 0;
		return (0);
	}
	
		printf("%s\n", names[count]);
		++count;
	
	return (0);
}

int PrintTime(void *param)
{
	if (*(int*)param == 7)
	{
		printf("the time is %lu\n", (size_t)time(NULL));
	}

	return (0);
}

int PrintParam(void *param)
{
	int i = 0;
	
	for (i = 0; i < 2; ++i)
	{
		printf("param is: %d\n", *(int *)param);
	}
	
	return (0);
}

int CheckEmptiness(void *param)
{
	printf("IsEmpty returns %d\n", SchedulerIsEmpty(param));
	
	return (0);
}


