insert:
check if malloc failed

create->destroy->size->isempty

#include <stdio.h> /* printf() */

#include "scheduler.c"

int main()
{
	scheduler_t *sched = SchedulerCreate();
	printf("The size of the scheduler is: %ld\n", SchedulerSize(sched));
	printf("The scheduler %s\n", (SchedulerIsEmpty(sched) ? "is not empty" :
		   "is empty");
	
		
	
	
	SchedulerDestroy(sched);
		
	return (0);
}

void InsertData(scheduler_t *sched)
{
	
}
