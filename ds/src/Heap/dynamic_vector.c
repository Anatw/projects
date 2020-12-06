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
#define FAILURE (1)
#define TWO (2)

struct dynamic_vector
{
	void **array; 	  /* pointer to the beggining of the dynamic_array */
	size_t capacity;  /* current possible length				 	   */
	size_t size;	  /* actual current dynamic_array length 		   */
}; /* vector_t */

vector_t *VectorCreate(size_t capacity)
{
	vector_t *dynamic_array = NULL;
	assert(0 < capacity);

	dynamic_array = (vector_t *)malloc(sizeof(vector_t));
	
	if (NULL == dynamic_array)
	{
		return (NULL);
	}
	
	dynamic_array->array = (void **)malloc(capacity * sizeof(void *));
	if (NULL == dynamic_array->array)
	{
		free(dynamic_array);
		dynamic_array = NULL;
		return (NULL);
	}
	
	dynamic_array->capacity = capacity;
	dynamic_array->size = 0;
	
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
	int status = 0;

	assert(NULL != vector);
	assert(NULL != value);
	
	if (vector->size == vector->capacity)
	{
		status = VectorReserve(vector, (vector->capacity * TWO));
		/*vector->capacity *= TWO; 
		(vector->array) = (void *)realloc(vector->array,
							vector->capacity * sizeof(size_t)); */
	}
	
	if (SUCCESS == status)
	{
		++vector->size;
		vector->array[(vector->size) - 1] = value;
	}
	
	return (status);
}

/******************************************************************************/

int VectorReserve(vector_t *vector, size_t capacity)
{
	void **temp_array = NULL;
	assert(NULL != vector);
	assert(0 < capacity);
	
	vector->capacity = capacity;
	temp_array = (void **)realloc(vector->array, (capacity * sizeof(void *)));
	if (NULL == temp_array)
	{
		return (ERROR);
	}
	
	vector->array = temp_array;
	vector->capacity = capacity;
	
	return (SUCCESS);
}

/******************************************************************************/

void *VectorGetElement(vector_t *vector, size_t index)
{
	assert(NULL != vector);
	assert(index < vector->size);
	
	return (vector->array[index]);
}

/******************************************************************************/

void VectorPopBack(vector_t *vector)
{
	assert(NULL != vector);
	
	--vector->size;
}

/******************************************************************************/

void VectorSetElement(vector_t *vector, int index, void *value)
{
	assert(NULL != vector);
	/*assert((size_t)index < vector->size);*/
	
	vector->array[index] = value;
}

/******************************************************************************/

int VectorShrinkToFit(vector_t *vector)
{
	assert(NULL != vector);

	return (VectorReserve(vector, (vector->size) - 1));
}