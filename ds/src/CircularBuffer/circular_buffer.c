/*******************************************************************************
					  	 Written by Anat Wax
						    March 5-8, 2020
						Reviewer: Amir Saraf
*******************************************************************************/
#include <stddef.h> /* offsetof(), size_t */
#include <unistd.h> /* ssize_t */
#include <stdlib.h> /* malloc() */
#include <assert.h> /* assert */

#include "circular_buffer.h"

struct cb
{
	size_t front;
	size_t size;
	size_t capacity;
	char array[1];
};


circularbuffer_t *CBCreate(size_t capacity)
{
	circularbuffer_t *buffer = (circularbuffer_t *)malloc
							   (sizeof(circularbuffer_t) +
	 				 		   (capacity * sizeof(buffer->array)));

	buffer->front = 0;
	buffer->size = 0;
	buffer->capacity = capacity;
		
	return (buffer);
}

circularbuffer_t *CBCreate_offset(size_t capacity)
{
	circularbuffer_t *buffer = (circularbuffer_t *)malloc
							   (offsetof(circularbuffer_t, array) +
							   (capacity * sizeof(buffer->array)));
							   
	buffer->size = 0;
	buffer->capacity = capacity;
		
	return (buffer);
}


void CBDestroy(circularbuffer_t *cb)
{
	free(cb);
}


ssize_t CBWrite(circularbuffer_t *cb, const void *buf, size_t count)
{
	unsigned int index = 0;
	char *p_buf = (char *)buf;
	
	assert(NULL != cb);
	assert(NULL != buf);
	assert(count > 0);
	
	/* in order to read from buf i need to cast it into a pointer
	to char so it will move in char units, the same as array */
	while(index < count)
	{
		if (cb->size == cb->capacity)
		{
			return (1);
		}
	
		cb->array[(cb->front + cb->size) % cb->capacity] = p_buf[index];
		++index;
		++cb->size;
	}
	
	return (0);
}


ssize_t CBRead(circularbuffer_t *cb, void *buf, size_t count)
{
	unsigned int index = 0;
	char *p_buf = (char *)buf;
	
	assert(count < cb->capacity);
	assert(count <=  cb->size);
	assert(count > 0);
	
	/* front moves only in the Read() function. */
	/* if front is now at the last cell, it	    */
	/* should move to position 0 of the array;  */
	while(index < count && (0 != cb->size))
	{
		p_buf[index] = cb->array[cb->front];
		
		if ((cb->front + 1) == cb->capacity)
		{
			cb->front = 0;
		}
		else
		{
			++cb->front;
		}
		
		++index;
		--cb->size;
	}
	
	return (index);
}


size_t CBSize(circularbuffer_t *cb)
{
	assert(NULL != cb);
	
	return (cb->size);
}


size_t CBFreeSpace(circularbuffer_t *cb)
{
	assert(NULL != cb);
	
	return (cb->capacity - cb->size);
}


int CBIsEmpty(circularbuffer_t *cb)
{
	assert(NULL != cb);
	
	return (0 == cb->size ? 1 : 0);
}
