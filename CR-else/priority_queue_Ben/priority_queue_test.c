/******************************************************************************/
/*                                                                            */
/*                       Priority Queue Test File                             */
/*                            Data Structures                                 */
/*                              11/03/2020                                    */
/*                        Author: Ben David Zikri                             */
/*                          Reviwer: Anat Wax                                 */
/*                                                                            */
/******************************************************************************/

#include <stdio.h>
#include <stdlib.h>

#include "priority_queue.h"

int Compare(void *num1, void *num2);
int CompareTwoNumbers(void *num1, void *num2);


int main()
{
	int a = 1;
	int b = 2;
	int c = 3;
	int d = 4;

	pqueue_t *pq = PQueueCreate(Compare);
	printf("Current state:\n");
	printf("\tPQueueIsEmpty: %d\n",PQueueIsEmpty(pq));
	printf("\tPQueueSize: %ld\n",PQueueSize(pq));
	printf("\n");

	printf("Populating queue...\n");
	PQueueEnqueue(pq, &c);
	PQueueEnqueue(pq, &a);
	PQueueEnqueue(pq, &b);
	PQueueEnqueue(pq, &d);
	PrintPQ(pq);
	printf("\n");

	printf("\tPQueuePeek: %d\n", *(int *)PQueuePeek(pq));
	printf("\tPQueueIsEmpty: %d\n",PQueueIsEmpty(pq));
	printf("\tPQueueSize: %ld\n",PQueueSize(pq));
	printf("\n");

	printf("PQueueErase(%d)\n", c);
	PQueueErase(pq, CompareTwoNumbers, &c);
	PrintPQ(pq);
	printf("\n");

	printf("PQClear:\n");
	PQueueClear(pq);
	PrintPQ(pq);
	printf("\tPQueueIsEmpty: %d\n",PQueueIsEmpty(pq));
	printf("\tPQueueSize: %ld\n",PQueueSize(pq));
	printf("\n");

	printf("Repopulating queue...\n");
	PQueueEnqueue(pq, &c);
	PQueueEnqueue(pq, &a);
	PQueueEnqueue(pq, &b);
	PQueueEnqueue(pq, &d);

	PrintPQ(pq);
	PQueueDestroy(pq);
	return (0);
}

int Compare(void *num1, void *num2)
{
	if ((*(int *)num1 < *(int *)num2))
	{
		return (1);
	}
	else if ((*(int *)num1 > *(int *)num2))
	{
		return (-1);
	}

	return (0);
}


int CompareTwoNumbers(void *num1, void *num2)
{
	return (*(int*)num1 == *(int*)num2);
}
