#include <stdio.h>

#include "task.h"

int OperationFunc(const void *param);

int main()
{
	int data = 2;
	int data2 = 10;
	
	task_t *task1 = TaskCreate(20, OperationFunc, &data);
	task_t *task2 = TaskCreate(3, OperationFunc, &data2);
	printf("TaskCompareTime: %d\n", TaskCompareTime(task1, task2));
	printf("TaskGetOperationTime: %jd\n", TaskGetOperationTime(task1));
	TaskExecute(task1);
	
	TaskUpdateTimeToExecute(task1);
	
	TaskExecute(task1);
	
	return (0);
}

int OperationFunc(const void *param)
{
	int p_param = *(int *)param;
	p_param *= 2;
	
	printf("%d\n", p_param);
	
	return (0);
}
