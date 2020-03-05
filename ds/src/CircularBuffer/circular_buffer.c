/*******************************************************************************
					  	 Written by Anat Wax
						    March 5, 2020
						Reviewer: 
*******************************************************************************/
#include <stddef.h> /* offsetof(), size_t */
#include <unistd.h> /* ssize_t */
#include <stdlib.h> /* malloc() */

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
	circularbuffer_t *buffer = (circularbuffer_t *)malloc(sizeof(circularbuffer_t) +
	 				 		   (capacity * sizeof(buffer->array)));
	
	buffer->front = 0;
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
	/* in rdr to read from buf i need to cast it into a pointer
	to char so it will move in char units, the same as array */
	char *p_buf = (char *)buf;
	
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
	
	/* if front is now at the last cell, it	   */
	/* should move to position 0 of the array; */
	while(index < count)
	{
		if ((cb->front + 1) == cb->capacity)
		{
			cb->front = 0;
		}
		
		if (cb->front == cb->size)
		{
			return (1);
		}
	
		p_buf[index] = cb->array[cb->front];
		++cb->front;
		++index;
		--cb->size;
	}
	
	return (0);
}



