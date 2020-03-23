/******************************************************************************/
/* 					Test file for task									  	  */
/*														 				 	  */
/*					Autor - Dean Oron									 	  */
/*					Date - 17.03.20									     	  */
/*					Reviewer - 	Anat Wax						         	  */
/*					Open Lab 86											  	  */
/******************************************************************************/

#include <stdio.h> /* printf() */
#include <assert.h> /* assert() */

#include "task.h"

/*************************** Utility Functions *******************************/

/*
 * Just for practice func
 * Return: 0 for succes, 1 for failure
 * Receive: Pointer to parameter
 */
int PrintToParam(void *param);

int main()
{
	size_t interval1 = 1;
	size_t interval2 = 2;
	int a = 3;
	int b = 6;
	
	task_t *first_task = TaskCreate(interval1, PrintToParam, &a);
	task_t *second_task = TaskCreate(interval2, PrintToParam, &b);
	
	
	TaskGetUID(first_task);
	TaskGetOperationTime(first_task);
	
	/*while (interval1 != interval2)
	{
		TaskUpdateTime(first_task);
		TaskExecute(first_task);
		TaskExecute(second_task);
	}*/
	
	TaskCompareTime(first_task, second_task);
	TaskGetOperationTime(first_task);
	
	TaskDestroy(first_task);
	TaskDestroy(second_task);
	
	return (0);
}

/******************************************************************************/
/******************************************************************************/

int PrintToParam(void *param)
{
	int i = 0;
	assert(param);
	
	if (*(int *)param <= 0)
	{
		return (1);
	}
	
	for (i = 0; i < *(int *)param; ++i)
	{
		printf("%d, ", i);
	}
	printf("\n");
	
	return (0);
}









