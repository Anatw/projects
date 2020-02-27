/******************************************************************************
* File: stack_test.c
* Auther: Esti Binder
* Reviewed by: Anat Wax
* Description: test manipulation functions on stack 
*******************************************************************************/

#include <stdio.h>
#include <stdlib.h> 

#include "stack.h"


int main()
{
	int num = 5;
	char c = 'e';
	char *string = "esti";
	size_t sizy = 0;
	
	stack_t *stack = StackCreate(10);          /*Create*/
	
	printf("%lu\n", StackSize(stack));	  /*size*/
		
	printf("%d\n", StackIsEmpty(stack));	/*IsEmpty*/
	
	StackPush(stack, &num);              /*Push*/
	printf("%d\n", *(int *)(StackPeek(stack)));    /*Peek*/
	
	StackPush(stack, &c);                 /*Push*/
	printf("%c\n", *(char *)(StackPeek(stack)));   /*Peek*/
	
	StackPush(stack, &string);             /*Push*/
	printf("%s\n", *(char **)(StackPeek(stack)));  /*Peek*/
	
	StackPop(stack);                      /*Pop*/
	printf("%c\n", *(char *)(StackPeek(stack)));  /*Peek*/
	
	StackPush(stack, &string);             /*Push*/
	printf("%s\n", *(char **)(StackPeek(stack)));  /*Peek*/
	
	printf("%lu\n", StackSize(stack));	  /*size*/
	
	printf("%d\n", StackIsEmpty(stack));	/*IsEmpty*/
	
	sizy = StackSize(stack);
	printf("sizy: %ld\n", sizy);
	    
	StackPop(stack); 
	sizy = StackCapacity(stack);
	printf("StackCapacity: %ld\n", sizy);
	
	StackPop(stack);     
	sizy = StackSize(stack);
	printf("sizy: %ld\n", sizy);
	
	StackPop(stack);     
	sizy = StackSize(stack);
	printf("sizy: %ld\n", sizy);
	
	StackPop(stack);     
	Stackdestroy(stack);
	
	
	return (0);
}


