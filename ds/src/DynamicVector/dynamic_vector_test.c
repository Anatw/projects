/*******************************************************************************
					  	 Written by Anat Wax
						  February 27, 2020
						Reviewer: Yehuda Levavi
*******************************************************************************/

#include <stdio.h>		/* printf() */

#include "dynamic_vector.h"

int main()
{
	size_t capacity = 10;
	vector_t *dynamic_array = NULL;
	int value = 7;
	int *p_value = &value;
	size_t new_capacity = 102;
	int push = 0;
	int reserve = 0;
	int new_value = 777;
	int *p_nvalue = &new_value;
				
	dynamic_array = VectorCreate(capacity);
	
	printf("the address of my new dynamic array is: %p\n",
		   (void *)dynamic_array);

	printf("capacity: %ld\n", VectorCapacity(dynamic_array));
	
	printf("size: %ld\n", VectorSize(dynamic_array));
	
	push = VectorPushBack(dynamic_array, p_value);
	if(0 == push)
	{
		printf("size: %ld\n", VectorSize(dynamic_array));
	}
	else
	{
		printf("error");
	}
	
	printf("the requested index content is: %d\n",
		   *(int *)VectorGetElement(dynamic_array, 1));
	
	VectorReserve(dynamic_array, new_capacity);
	if(0 == reserve)
	{
		printf("capacity: %ld\n", VectorCapacity(dynamic_array));
	}
	else
	{
		printf("error");
	}
	
	VectorSetElement(dynamic_array, 1, p_nvalue);
	printf("the requested index content is: %d\n",
		   *(int *)VectorGetElement(dynamic_array, 1));
	
	VectorShrinkToFit(dynamic_array);
	printf("size after shrink: %ld\n", VectorSize(dynamic_array));
	printf("capacity after shrink: %ld\n", VectorCapacity(dynamic_array));
	
	VectorSetElement(dynamic_array, 3, p_nvalue);
	printf("the requested index content is: %d\n",
		   *(int *)VectorGetElement(dynamic_array, 3));
	
	VectorDestroy(dynamic_array);
	
	return (0);
}
