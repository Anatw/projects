/*******************************************************************************
					  	   Written by Anat Wax
						  23-27 of April, 2020
						Reviewer: Yonathan Berdugo
*******************************************************************************/
#include <stdio.h> /* printf() */

#include "heap_priority_queue.h"

void TESTPQueueEnqueue6(pqueue_t *pq_list);

void TESTPQueueEnqueue2(pqueue_t *pq_list);

void TESTPQueueDequeue(pqueue_t *pq_list);

void TESTPQueuePeek(pqueue_t *pq_list);

void TESTPQueueSize(pqueue_t *pq_list);

void TESTPQueueIsEmpty(pqueue_t *pq_list);

void TESTPQueueClear(pqueue_t *pq_list);

void TESTPQueueErase(pqueue_t *pq_list);

void PQByHeapPrint(pqueue_t *pq_list);

int main()
{
	int data1 = 7;
	int data2 = 6;
	int data3 = 2;
	int data4 = 7;
	int data5 = 6;
	int data6 = 2;

	pqueue_t *pq_list = PQueueByHeapCreate(PQByHeapCompare);
	/*printf("size of list: %ld ", sizeof(pq_list));*/
	TESTPQueueIsEmpty(pq_list);
	PQueueByHeapEnqueue(pq_list, &data1);
	PQueueByHeapEnqueue(pq_list, &data2);
	PQueueByHeapEnqueue(pq_list, &data3);
	PQueueByHeapEnqueue(pq_list, &data4);
	PQueueByHeapEnqueue(pq_list, &data5);
	PQueueByHeapEnqueue(pq_list, &data6);

	PQByHeapPrint(pq_list);
	TESTPQueueErase(pq_list);
	PQByHeapPrint(pq_list);

	TESTPQueuePeek(pq_list);
	TESTPQueueSize(pq_list);
	TESTPQueueIsEmpty(pq_list);
	TESTPQueueClear(pq_list);
	TESTPQueueSize(pq_list);

	PQueueByHeapDestroy(pq_list);

	return (0);
}

void TESTPQueueEnqueue6(pqueue_t *pq_list)
{
	const int data = 6;
	int status = PQueueByHeapEnqueue(pq_list, &data);

	if (0 == status)
	{
		printf("data was added to the queue\n");
	}
}

void TESTPQueueEnqueue2(pqueue_t *pq_list)
{
	const int data = 2;
	int status = PQueueByHeapEnqueue(pq_list, &data);

	if (0 == status)
	{
		printf("data was added to the queue\n");
	}
}

void TESTPQueueDequeue(pqueue_t *pq_list)
{
	printf("commiting one dequeue from the queue\n");
	PQueueByHeapDequeue(pq_list);
}

void TESTPQueuePeek(pqueue_t *pq_list)
{
	printf("the data in first element of the queue is %d\n",
		   *(int *)PQueueByHeapPeek(pq_list));
}

void TESTPQueueSize(pqueue_t *pq_list)
{
	printf("The size of the queue is %lu\n", PQueueByHeapSize(pq_list));
}

void TESTPQueueIsEmpty(pqueue_t *pq_list)
{
	printf("The queue is %s\n", (PQueueByHeapIsEmpty(pq_list) ? "empty" : "not empty"));
}

void TESTPQueueClear(pqueue_t *pq_list)
{
	printf("Running PQueueClear.\n");
	PQueueByHeapClear(pq_list);
}

void TESTPQueueErase(pqueue_t *pq_list)
{
	const int param = 2;
	printf("Running PQueueErase (param = 2).\n");
	PQueueByHeapErase(pq_list, PQByHeapCompare, &param);
}