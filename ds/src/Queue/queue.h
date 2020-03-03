#include <stddef.h>

#ifndef QUEUE_H
#define QUEUE_H

typedef struct queue queue_t;


queue_t *QueueCreate();

void QueueDestroy(queue_t *queue);

int QueueEnqueu(queue_t *queue);

void QueueDequeu(queue_t *queue);

void *QueuePeek(queue_t *queue);

size_t QueueSize(queue_t *queue);

int QueueIsEmpty(queue_t *queue);

/* O(1) */
void QueueAppend(queue_t *dest, queue_t *src);


#endif
