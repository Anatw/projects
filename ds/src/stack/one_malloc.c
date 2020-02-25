#include <stdlib.h> /* sizeof() */

#include "stack.h"

struct stack
{
	void **container;
	void **stack_top;
};

/* O(1) */
stack_t *StackCreate(size_t size)
{
	stack_t *new_stack = (stack_t *)malloc(sizeof(stack_t) +
		(size * sizeof(void *)));
		
	(new_stack->container) = (void *)(new_stack + sizeof(stack_t));
	(new_stack->stack_top) = new_stack->container;
	
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

/* O(1) */
int StackIsEmpty(stack_t *stack)
{
	int value = 0;
	
	if(0 != *(stack->stack_top))
	{
	value = 1;
	}
	
	return (value);
}

/* O(1) */
size_t StackCapacity(stack_t *stack)
{
	size_t stack_size = (stack->stack_top) - (stack->container);
	stack_size *= (sizeof(void *));
	
	return (stack_size);
}

/* O(1) */
void StackDestroy(stack_t *stack)
{
	free(stack);
	stack = NULL;
}

