/*******************************************************************************
Written by Anat Wax, anatwax@gmail.com
March 5-8, 2020
*******************************************************************************/
#include <stddef.h> /* offsetof(), size_t */
#include <unistd.h> /* ssize_t */
#include <stdlib.h> /* malloc() */
#include <assert.h> /* assert */

#include "producer_consumer_queue.h"

struct cb
{
	size_t read;
    size_t write;
	size_t capacity;
	char array[1];
};


circularbuffer_t *CBCreate(size_t capacity)
{
	circularbuffer_t *buffer = (circularbuffer_t *)malloc
							   (sizeof(circularbuffer_t) +
	 				 		   (capacity * sizeof(buffer->array)));
	if (NULL == buffer)
	{
		return (NULL);
	}
	
	buffer->read = 0;
	buffer->write = 0;
	buffer->capacity = capacity;
		
	return (buffer);
}


void CBDestroy(circularbuffer_t *cb)
{
	free(cb);
	cb = NULL;
}

int CBWrite(circularbuffer_t *cb, int *data)
{
	assert(NULL != cb);
	assert(NULL != data);
	
    cb->array[cb->write] = *data;
    cb->write = (cb->write + 1) % cb->capacity;

    ++cb->write;
	
	return (0);
}

int CBRead(circularbuffer_t *cb)
{
	int temp = 0 ;
    
    cb->read = (cb->read + 1) % cb->capacity;
    temp = cb->array[cb->read];

	--cb->read;
	
	return (temp);
}
