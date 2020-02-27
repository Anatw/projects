#ifndef STACK_H
#define STACK_H

typedef struct stack stack_t;

/*get size and create stack whith a capacity of size,
 return a pointer to stack ds*/
stack_t *StackCreate(size_t size);

/*get a pointer to stack and free the stack*/
void Stackdestroy(stack_t *stack);

/*get a pointer to stack and pops the top argument*/
void StackPop(stack_t *stack);

/*get a pointer to stack and a pointer to value 
 and pushs the value to the top of the stack*/
void StackPush(stack_t *stack, void *val);

/*get a pointer to stack and terurns the top value*/
void *StackPeek(stack_t *stack);

/*get a pointer to stack and returns the current size of the stack*/
size_t StackSize(stack_t *stack);

/*get a pointer to stack, returns 1 if the stack is empty and 0 if not empty*/
int StackIsEmpty(stack_t *stack);

/*get a pointer to stack and returns its capacity*/
size_t StackCapacity(stack_t *stack);

#endif
