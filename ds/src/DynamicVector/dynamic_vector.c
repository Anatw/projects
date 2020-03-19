/*******************************************************************************
					  	 Written by Anat Wax
						  February 27, 2020
						Reviewer: Yehuda Levavi
*******************************************************************************/

#include <stdlib.h>  /* malloc(), realloc() */
#include <assert.h>  /* assert() */

#include "dynamic_vector.h"

#define SUCCESS (0)
#define ERROR (1)
#define TWO (2)

struct dynamic_vector
{
	void **array; 	  /* pointer to the beggining of the dynamic_array */
	size_t capacity;  /* current possible length				 	   */
	size_t size;	  /* actual dynamic_array length 				   */
};

vector_t *VectorCreate(size_t capacity)
{
	vector_t *dynamic_array = (vector_t *)malloc(sizeof(vector_t));
	assert(0 < capacity);
	
	if (NULL == dynamic_array)
	{
		return (NULL);
	}
	
	(dynamic_array->array) = (void *)malloc(capacity * sizeof(void *));
	if (NULL == dynamic_array->array)
	{
		return (NULL);
	}
	
	(dynamic_array->capacity) = capacity;
	(dynamic_array->size) = (-1);
	
	return (dynamic_array);
}

/******************************************************************************/

void VectorDestroy(vector_t *vector)
{
	assert(NULL != vector);
	
	free(vector->array);
	(vector->array) = NULL;
	
	free(vector);
	vector = NULL;
}

/******************************************************************************/

size_t VectorCapacity(vector_t *vector)
{
	assert(NULL != vector);
	
	return (vector->capacity);
}

/******************************************************************************/

size_t VectorSize(vector_t *vector)
{
	assert(NULL != vector);
	
	return (vector->size);
}

/******************************************************************************/

int VectorPushBack(vector_t *vector, void *value)
{
	assert(NULL != vector);
	assert(NULL != value);
	
	if (vector->size == vector->capacity)
	{
		vector->capacity = VectorReserve(vector, (vector->capacity * TWO));
		/*vector->capacity *= TWO; 
		(vector->array) = (void *)realloc(vector->array,
							vector->capacity * sizeof(size_t)); */
	}
	
	++(vector->size);
	vector->array[(vector->size)] = value;
	
	return (SUCCESS);
}

/******************************************************************************/

int VectorReserve(vector_t *vector, size_t capacity)
{
	void **temp_array = NULL;
	assert(NULL != vector);
	assert(0 < capacity);
	
	vector->capacity = capacity;
	temp_array = realloc(vector->array, capacity * sizeof(size_t));
	if (NULL == temp_array)
	{
		return (ERROR);
	}
	
	(vector->array) = temp_array;
	
	return (SUCCESS);
}

/******************************************************************************/

void *VectorGetElement(vector_t *vector, size_t index)
{
	assert(NULL != vector);
	assert(index < vector->size);
	
	return (vector->array[index]);
}


void VectorPopBack(vector_t *vector)
{
	assert(NULL != vector);
	
	--(vector->size);
}

/******************************************************************************/

void VectorSetElement(vector_t *vector, int index, void *value)
{
	assert(NULL != vector);
	assert(index < vector->size);
	
	vector->array[index] = value;
}

/******************************************************************************/

int VectorShrinkToFit(vector_t *vector)
{
	int succedded = VectorReserve(vector, vector->size);
	
	assert(NULL != vector);
	
	if (0 != succedded)
	{
		return (ERROR);
	}

	return (SUCCESS);
}
