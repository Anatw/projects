#include <stdlib.h>
#include <stdio.h> /* printf() */

#include "queue.h"
#include "singly_linked_list.h"

int main()
{
	queue_t *new_queue = NULL;
	queue_t *another_queue = NULL;
	int data = 7;
	int data2 = 12;
	int status = 0;
	
	new_queue = QueueCreate();
	
	printf("is queue empty? %s\n", (1 == QueueIsEmpty(new_queue) ? "YES" : "NO"));
	printf("insreting a new data (7)\n");
	status = QueueEnqueu(new_queue, &data);
	printf("insreting a new data (7)\n");
	status = QueueEnqueu(new_queue, &data);
	printf("insreting a new data (7)\n");
	status = QueueEnqueu(new_queue, &data);
	printf("insreting a new data (7)\n");
	status = QueueEnqueu(new_queue, &data);
	printf("insreting a new data (7)\n");
	status = QueueEnqueu(new_queue, &data);
	
	printf("is queue empty? %s\n", (1 == QueueIsEmpty(new_queue) ? "YES" : "NO"));
	printf("peek into head: %d\n", *(int *)QueuePeek(new_queue));
	
	printf("one dequeue\n");
	printf("before dequeue: the size of the new_queue is %ld\n", QueueSize(new_queue));
	QueueDequeu(new_queue);
	printf("is queue empty? %s\n", (1 == QueueIsEmpty(new_queue) ? "YES" : "NO"));
	printf("after dequeue: the size of the new_queue is %ld\n", QueueSize(new_queue));
	
	printf("creating 'another_queue'\n");
	another_queue = QueueCreate();
	printf("insreting a new data (12)\n");
	status = QueueEnqueu(another_queue, &data2);
	printf("insreting a new data (12)\n");
	status = QueueEnqueu(another_queue, &data2);
	printf("insreting a new data (12)\n");
	status = QueueEnqueu(another_queue, &data2);

	printf("the size of the another_queue is %ld\n", QueueSize(another_queue));
	printf("the size of new_queue before appending is %ld\n", QueueSize(new_queue));

	printf("appending...\n");
	QueueAppend(new_queue, another_queue);
	printf("the size of new_queue after appending is %ld\n", QueueSize(new_queue));
	QueueDestroy(new_queue);
	
	return (0);
}
