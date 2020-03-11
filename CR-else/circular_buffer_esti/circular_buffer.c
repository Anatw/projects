/******************************************************************************
* File: circular_buffer.c
* Auther: Esti Binder
* Reviewed by: 
* Description: of operation functions on Queue
*******************************************************************************/

#include <stdlib.h> /*malloc/realloc/free*/

#include "circular_buffer.h"
 

struct circular_buffer {
	size_t front;
	size_t size;
	size_t capacity;
	char arr[1];
};

circular_buffer_t *CBCreate(size_t capacity)
{
	circular_buffer_t *new_cb = NULL;
	new_cb = (circular_buffer_t *)malloc(sizeof(circular_buffer_t) 
	                                             + (capacity - 1));
	         
	new_cb->front = new_cb->arr[0];
	new_cb->size = 0;
	new_cb->capacity = capacity;
	
	return (new_cb);	
}

ssize_t CBWrite(circular_buffer_t *cb, const void *buf, size_t count)
{
	size_t i = 0;
	char *buf_p = (char *)buf;

	for (; i < count; i++, buf_p++)
	{
		if (cb->size == cb->capacity)
		{
			return (i > 0 ? count : -1UL);
		}
		
		cb->arr[(cb->front + cb->size) % cb->capacity] = *buf_p;
		
		cb->size++;
	}
	
	return (count);
}

ssize_t CBRead(circular_buffer_t *cb, void *buf, size_t count)
{
	size_t i = 0;
	char *buf_p = (char *)buf;

	for (; i < count; i++)
	{
		if (cb->size == 0)
		{
			return (i > 0 ? count : -1UL);
		}
		
		*buf_p = cb->arr[cb->front];
		
		--cb->size;
		++buf_p;
		
		++cb->front;
		cb->front %= cb->capacity;
	}
	
	return (count);
}

void CBDestroy(circular_buffer_t *cb)
{
	free(cb);
	cb = NULL;
}

size_t CBFreeSpace(const circular_buffer_t *cb)
{
	return (cb->capacity - cb->size);
}

size_t CBSize(const circular_buffer_t *cb)
{
	return (cb->size);
}

int CBIsEmpty(const circular_buffer_t *cb)
{
	return (0 == cb->size);
}

