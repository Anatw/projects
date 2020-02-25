#ifndef STACK_H
#define STACK_H

/* This data structure policy is LIFO. */
typedef struct stack stack_t;

/* vreate the stack */
stack_t *StackCreate(size_t size);

/* free the memory of the sack. if char is empty = do nothing */
void StackDestroy(stack_t *stack);

/* push an element to the first cel in the stack */
void StackPush(void *value, stack_t *stack);

/* pop the firs element in the stack */
void StackPop(stack_t *stack);

void *StackPeak(int *value);

size_t StackSize(char *stack);

/* in c99 if = bool, if c89 = int */
int StackIsEmpty(char *stack);

size_t StackICapacity(char *stack);

#endif
