#include <stdlib.h>

#include "stack.h"

#define POINTER sizeof(void *)

struct stack
{
	void **container;
	void **stack_top;
};


stack_t *StackCreate(size_t size)
{
	stack_t *stack = (stack_t *)malloc(size * POINTER);
	
	return (stack);
}

void StackPush(void *value, stack_t *stack)
{
	
	*(stack_t->stack_top) = value;
	stack_t->stack_top += 1;
}
