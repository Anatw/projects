#ifndef PRODUCER_CONSUMER_QUEUE_H
#define PRODUCER_CONSUMER_QUEUE_H

#include <unistd.h> /* ssize_t */

typedef struct cb circularbuffer_t;

circularbuffer_t *CBCreate(size_t capacity);
void CBDestroy(circularbuffer_t *cb);
int CBWrite(circularbuffer_t *cb, int *data);
int CBRead(circularbuffer_t *cb);


#endif /* PRODUCER_CONSUMER_QUEUE_H */