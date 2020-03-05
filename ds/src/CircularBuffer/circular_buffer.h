#ifndef CIRCULAR_BUFFER_H
#define CIRCULAR_BUFFER_H

#include <unistd.h> /* ssize_t */

typedef struct cb circularbuffer_t;

/* Create an new circular buffer array */
/* Complexity: */
circularbuffer_t *CBCreate(size_t capacity);

/* Delete the array */
void CBDestroy(circularbuffer_t *cb);

ssize_t CBRead(circularbuffer_t *cb, void *buf, size_t count);

/* buf - pointer to the data you'de like to enter */
/* count - the number of cells you are entering to (in case of string this */
/* will be strlen(string) */
ssize_t CBWrite(circularbuffer_t *cb, const void *buf, size_t count);

size_t CBFreeSpace(circularbuffer_t *cb);

size_t CBSize(circularbuffer_t *cb);

/* return value: 1 if empty, 0 if full */
int CBIsEmpty(circularbuffer_t *cb);

#endif /* CIRCULAR_BUFFER_H */
