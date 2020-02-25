#include <stdlib.h>
#include <stdio.h>	/* printf() */

#include "stack.h"

int main()
{
	size_t requiredsize = 50;
	stack_t *stack_base = StackCreate(requiredsize);
	int value = 5;
	int value2 = 6;
	int value3 = 7;
	int value4 = 8;
	int *p_value = &value;
	int *p_value2 = &value2;
	int *p_value3 = &value3;
	int *p_value4 = &value4;
	size_t stack_size = 0;
	size_t stack_capacity = 0;
	int is_empty = 0;
	
	
	printf("'stack' address is: %p\n", (void *)stack_base);
	
	StackPush(p_value, stack_base);
	stack_size = StackSize(stack_base);
	printf("size of stack: %ld\n", stack_size);
	printf("value of stack_top is: %d\n", *(int *)
		(StackPeek(stack_base)));
	
	StackPush((p_value2), stack_base);
	stack_size = StackSize(stack_base);
	printf("size of stack: %ld\n", stack_size);
	printf("value of stack_top is: %d\n", *(int *)
		(StackPeek(stack_base)));
	
	StackPush((p_value3), stack_base);
	stack_size = StackSize(stack_base);
	printf("size of stack: %ld\n", stack_size);
	printf("value of stack_top is: %d\n", *(int *)
		(StackPeek(stack_base)));
	
	StackPush((p_value4), stack_base);
	stack_size = StackSize(stack_base);
	printf("size of stack: %ld\n", stack_size);
	printf("value of stack_top is: %d\n", *(int *)
		(StackPeek(stack_base)));
	
	StackPop(stack_base);
	
	stack_size = StackSize(stack_base);
	
	printf("size of stack: %ld\n", stack_size);
	printf("value of stack_top is: %d\n", *(int *)
		(StackPeek(stack_base)));

	is_empty = StackIsEmpty(stack_base);
	printf("is top cell empty?: %s\n", ((1 == is_empty) ? "not empty" : "empty"));
	
	stack_capacity = StackCapacity(stack_base);
	printf("capacity of stack: %ld\n", stack_capacity);

	StackDestroy(stack_base);
	
	stack_size = StackSize(stack_base);
	printf("size of stack: %ld\n", stack_size);
	
	printf("value of stack_top is: %d\n", *(int *)
		(StackPeek(stack_base)));

	return (0);
}
