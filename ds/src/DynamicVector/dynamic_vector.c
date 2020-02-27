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
#define DOUBLE (2)

struct dynamic_vector
{
	void **array; 	  /* pointer to the beggining of the dynamic_array */
	size_t capacity;  /* current possible length				 	   */
	size_t size;	  /* actual dynamic_array length 				   */
};

vector_t *VectorCreate(size_t capacity)
{
	vector_t *dynamic_array = (vector_t *)malloc(sizeof(vector_t));
	(dynamic_array->array) = (void *)malloc(capacity * sizeof(void *));
	(dynamic_array->capacity) = capacity;
	(dynamic_array->size) = 0;
	
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
	
	return(vector->capacity);
}

/******************************************************************************/

size_t VectorSize(vector_t *vector)
{
	assert(NULL != vector);
	
	return(vector->size);
}

/******************************************************************************/

int VectorPushBack(vector_t *vector, void *value)
{
	assert(NULL != vector);
	assert(NULL != value);
	
	if(vector->size == vector->capacity)
	{
		vector->capacity *= DOUBLE;
		(vector->array) = (void *)realloc(vector->array,
							vector->capacity * sizeof(size_t));
	}
	else
	{
		++(vector->size);
		vector->array[(vector->size)] = value;
	}
		
	return (SUCCESS);
}

/******************************************************************************/

int VectorReserve(vector_t *vector, size_t capacity)
{
	assert(NULL != vector);
	
	vector->capacity = capacity;
	(vector->array) = realloc(vector->array, capacity * sizeof(size_t));
		
	return ((NULL != (vector->array))? SUCCESS : ERROR);
}

/******************************************************************************/

void *VectorGetElement(vector_t *vector, size_t index)
{
	assert(NULL != vector);
	
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
	
	vector->array[index] = value;
}

/******************************************************************************/

int VectorShrinkToFit(vector_t *vector)
{
	int succedded = VectorReserve(vector, vector->size);
	assert(NULL != vector);
	
	if(0 != succedded)
	{
		return (SUCCESS);
	}

	return (ERROR);
}
