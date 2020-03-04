#include <stddef.h>

#ifndef QUEUE_H
#define QUEUE_H

typedef struct queue queue_t;

/* Functionality: */
/* */
/* Complexity: */
queue_t *QueueCreate();

/* Functionality: */
/* */
/* Complexity: */
void QueueDestroy(queue_t *queue);

/* Functionality: */
/* */
/* Complexity: */
/* Enqueue = add a new node to the tail of the list */
int QueueEnqueu(queue_t *queue, void *data);

/* Functionality: */
/* */
/* Complexity: */
/* Dequeue = remove a node from the head of the list */
void QueueDequeu(queue_t *queue);

/* Functionality: */
/* */
/* Complexity: */
void *QueuePeek(queue_t *queue);

/* Functionality: */
/* */
/* Complexity: */
size_t QueueSize(queue_t *queue);

/* Functionality: */
/* */
/* Complexity: */
int QueueIsEmpty(queue_t *queue);

/* Functionality: */
/* */
/* Complexity: O(1) */
void QueueAppend(queue_t *dest, queue_t *src);


#endif
