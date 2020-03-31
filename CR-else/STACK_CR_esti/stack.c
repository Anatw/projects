/******************************************************************************
* File: stack.c
* Auther: Esti Binder
* Reviewed by: Anat Wax
* Description: manipulation functions on stack
*******************************************************************************/

#include <stdio.h>
#include <stdlib.h> 

#include "stack.h"

struct stack{
	void **stackPtr;
	void **top;
	size_t capacity;

};

stack_t *StackCreate(size_t StackSize)
{
	/*allocating memory for stack struc and its arry of pointers */
	stack_t *NewStack = (stack_t *)malloc(sizeof(stack_t) 
					    + sizeof(void *) * StackSize);
		
	/*making stackPtr point to the base of the arry*/				    
	NewStack -> stackPtr = (void *)(NewStack + 1); 
	
	/*making top point to the base of the arry*/				    
	NewStack -> top = (NewStack -> stackPtr);
	
	NewStack -> capacity = StackSize;
	
	return (NewStack);
}

void Stackdestroy(stack_t *stack)
{
	free(stack); /*will free the struc and its arry*/
	stack = NULL;
}

void *StackPeek(stack_t *stack)
{
	/*printf("peek\n");*/
	return (*((stack -> top) - 1));
}

void StackPush(stack_t *stack, void *val)
{
	/*printf("push\n");*/
	*(stack -> top) = val;
	stack -> top += 1;
}

void StackPop(stack_t *stack)
{
	/*printf("pop\n");*/
	stack -> top -= 1;	
}

size_t StackSize(stack_t *stack)
{
	/*printf("size\n");*/
	return ((stack -> top) - (stack -> stackPtr));
}

int StackIsEmpty(stack_t *stack)
{
	/*printf("is_empty\n");*/
	return (StackSize(stack) ? 0 : 1);	
}

size_t StackCapacity(stack_t *stack)
{
	return (stack -> capacity);
}







