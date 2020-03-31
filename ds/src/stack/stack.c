/*******************************************************************************
					  	 Written by Anat Wax
						  February 25, 2020
						Reviewer: Amir Saraf
*******************************************************************************/

#include <stdlib.h> /* sizeof(), malloc() */
#include <stdio.h>

#include "stack.h"

struct stack
{
	void **container;
	void **stack_top;
	size_t stack_capacity;
};


/* O(1) */
stack_t *StackCreateTwoMalloc(size_t size)
{
	stack_t *new_stack = (stack_t *)malloc(sizeof(stack_t));
	(new_stack->container) = (void *)malloc(size * sizeof(void *));
	(new_stack->stack_top) = new_stack->container;
	
	return (new_stack);
}


/* O(1) */
stack_t *StackCreate(size_t size)
{
	stack_t *new_stack = (stack_t *)malloc(sizeof(stack_t) +
		(size * sizeof(void *)));
		
	(new_stack->container) = (void *)(new_stack + sizeof(stack_t));
	(new_stack->stack_top) = new_stack->container;
	(new_stack->stack_capacity) = size;
	
	return (new_stack);
}

/* O(1) */
void StackPush(void *value, stack_t *stack)
{
	*(stack->stack_top) = value;
	(stack->stack_top) += 1; /* move top pointer to the next free cell */
}

/* O(1) */
void StackPop(stack_t *stack)
{
	*(stack->stack_top) = 0;
	--(stack->stack_top);
}

/* O(1) */
size_t StackSize(stack_t *stack)
{
	size_t stack_size = (stack->stack_top) - (stack->container);
	
	return (stack_size);
}

/* O(1) */
stack_t *StackPeek(stack_t *stack)
{	
	return (*((stack->stack_top) - 1));
}

/* O(1) - is the entire stack empty or full */
int StackIsEmpty(stack_t *stack)
{
	return ((StackSize(stack) > 0) ? 0 : 1);
}

/* O(1) */
size_t StackCapacity(stack_t *stack)
{
	return (stack->stack_capacity);
}

/* O(1) */
void StackDestroy(stack_t *stack)
{
	/* free(stack->container);		to use when StackCreateTwoMalloc is used */
	/* stack->container = NULL;		to use when StackCreateTwoMalloc is used */
		
	free(stack);
	stack = NULL;
}

