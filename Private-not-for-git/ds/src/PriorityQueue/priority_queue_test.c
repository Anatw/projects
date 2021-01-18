/*******************************************************************************
			   Written by Anat Wax
			     March 14-15, 2020
		  	  Reviewer: Haim sa'adia
*******************************************************************************/
#include <stdio.h> /* printf() */

#include "priority_queue.h"



void TESTPQueueEnqueue6(pqueue_t *pq_list);

void TESTPQueueEnqueue2(pqueue_t *pq_list);

void TESTPQueueDequeue(pqueue_t *pq_list);

void TESTPQueuePeek(pqueue_t *pq_list);

void TESTPQueueSize(pqueue_t *pq_list);

void TESTPQueueIsEmpty(pqueue_t *pq_list);

void TESTPQueueClear(pqueue_t *pq_list);

void TESTPQueueErase(pqueue_t *pq_list);

void PQPrint(pqueue_t *pq_list);

int main()
{
	int data1 = 7;
	int data2 = 6;
	int data3 = 2;
	int data4 = 7;
	int data5 = 6;
	int data6 = 2;
	
	pqueue_t *pq_list = PQueueCreate(Compare);
	/*printf("size of list: %ld ", sizeof(pq_list));*/
	TESTPQueueIsEmpty(pq_list);
	PQueueEnqueue(pq_list, &data1);
	PQueueEnqueue(pq_list, &data2);
	PQueueEnqueue(pq_list, &data3);
	PQueueEnqueue(pq_list, &data4);
	PQueueEnqueue(pq_list, &data5);
	PQueueEnqueue(pq_list, &data6);
	
	PQPrint(pq_list);
	TESTPQueueErase(pq_list);
	PQPrint(pq_list);

	TESTPQueuePeek(pq_list);
	TESTPQueueSize(pq_list);
	TESTPQueueIsEmpty(pq_list);
	TESTPQueueClear(pq_list);
	TESTPQueueSize(pq_list);
	
	PQueueDestroy(pq_list);
	
	return (0);
}


void TESTPQueueEnqueue6(pqueue_t *pq_list)
{
	const int data = 6;
	int status = PQueueEnqueue(pq_list, &data);
	
	if (0 == status)
	{
		printf("data was added to the queue\n");
	}
}

void TESTPQueueEnqueue2(pqueue_t *pq_list)
{
	const int data = 2;
	int status = PQueueEnqueue(pq_list, &data);
	
	if (0 == status)
	{
		printf("data was added to the queue\n");
	}
}

void TESTPQueueDequeue(pqueue_t *pq_list)
{
	printf("commiting one dequeue from the queue\n");
	PQueueDequeue(pq_list);
}

void TESTPQueuePeek(pqueue_t *pq_list)
{
	printf("the data in first element of the queue is %d\n",
		*(int *)PQueuePeek(pq_list));
}


void TESTPQueueSize(pqueue_t *pq_list)
{
	printf("The size of the queue is %lu\n", PQueueSize(pq_list));
}

void TESTPQueueIsEmpty(pqueue_t *pq_list)
{
	printf("The queue is %s\n", (PQueueIsEmpty(pq_list) ? "empty" : "not empty"));
}

void TESTPQueueClear(pqueue_t *pq_list)
{
	printf("Running PQueueClear.\n");
	PQueueClear(pq_list);
}

void TESTPQueueErase(pqueue_t *pq_list)
{
	const int param = 2;
	printf("Running PQueueErase (param = 2).\n");
	PQueueErase(pq_list, Compare, &param);
}





