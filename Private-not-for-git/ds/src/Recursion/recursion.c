/*******************************************************************************
					  		Written by Anat Wax
						 	April fth-6th, 2020
						   Reviewer: Noffar Gil
*******************************************************************************/
#include <assert.h> /* assert() */
#include <stdlib.h> /* malloc() */

#include "recursion.h"

typedef struct sll_node
{
	int data;  /* pointer to the data the node contain */
	struct sll_node *next; /* pointer to the next node */
};


/******************************************************************************/

int FibonacciRecursive(int element_index)
{	
	if (1 >= element_index)
	{
		return (element_index);
	}
		
	return (FibonacciRecursive(element_index - 1) + 
			FibonacciRecursive(element_index - 2));
}

/*******************************************/

int FibonacciNonRecursive(int element_index)
{
	int prev = 1;
	int current = 1;
	int fibonacci_number = 1;
	/* because actual changes in the Fibonaccy */
	/* system starts from index number 2:      */
	int counter = 2;
	
	if (1 >= element_index)
	{
		return (0);
	}
	
	for (; counter < element_index; ++counter)
	{
		fibonacci_number = current + prev;
		
		prev = current;
		current = fibonacci_number;
	}
	return (fibonacci_number);
}

struct sll_node *FlipList(struct sll_node *node)
{
	struct sll_node *return_node = NULL;

	assert(node);

	if (NULL == node || NULL == node->next)
	{
		return (node);		
	}
	
	return_node = FlipList(node->next);
	node->next->next = node;
	node->next = NULL;
	
	return (return_node);
}


