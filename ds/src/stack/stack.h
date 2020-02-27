/*******************************************************************************
This program build a stack (an array pointers) in the size requested by the user
(using malloc on run-time). the user can push or pop to the stack, peek, cheack
if empty and destroy the stack (free all malloc).

					  	 Written by Anat Wax
						  February 25, 2020
						Reviewer: Amir Saraf
*******************************************************************************/

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

/* pop the first element in the stack */
void StackPop(stack_t *stack);

/* operation that returns the value of the top most element of */
/* the stack without deleting that element from the stack 	   */
stack_t *StackPeek(stack_t *stack);

size_t StackSize(stack_t *stack);

/* is the specific cell empty (0) or has value inside (1) */
/* for later improvement: in c99 if = bool, if c89 = int  */
int StackIsEmpty(stack_t *stack);

/* equal to he size (size_t) the user asked for when running the program */
size_t StackCapacity(stack_t *stack);

#endif
