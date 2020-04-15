/*******************************************************************************
					  		Written by Anat Wax
						 	April fth-6th, 2020
						   Reviewer: Noffar Gil
*******************************************************************************/
#include <stdio.h> /* printf() */
#include <assert.h> /* assert() */ 
#include <stdlib.h> /* malloc() */

#define STACK_SIZE (5)

struct stack
{
	int data;
	struct stack *next;
};

/*************** utility function to creat and manage the stack: **************/

void initStack(struct stack **s);

int isEmpty(struct stack *s);

void push(struct stack **s, int x);

int pop(struct stack **s);

int top(struct stack *s);

void printStack(struct stack *s);

/***********************************************/

/*
 * Sorting the stack one element at a time (Recursive).
 * Recieve: s - Pointer to the stack.
 * Time Complexity: O(n)
 */
void sortStack(struct stack **s);

/*
 * Pushing the the element back into the stack.
 * Recieve: s - Pointer to the stack.
 * 			x - The number of elements to put back in the stack.
 * Time Complexity: O(n)
 */
void sortedInsert(struct stack **s, int x);

/******************************************************************************/

int main ()
{
	int data1 = 1;
	int data2 = 9;
	int data3 = 5;
	int data4 = 2;
	int data5 = 7;
	struct stack *top = NULL;
	
	initStack(&top); 
    push(&top, data1); 
    push(&top, data2); 
    push(&top, data3); 
    push(&top, data4); 
    push(&top, data5); 
	
	printf("Stack elements before sorting:\n"); 
	printStack(top);
	
	sortStack(&top);
	printf("Stack elements after sorting:\n"); 
	printStack(top);
	
	return (0);
}

/* Utility function to initialize stack */
void initStack(struct stack **stack)
{ 
    *stack = NULL; 
} 
  
/* Utility function to chcek if stack is empty */
int isEmpty(struct stack *stack) 
{ 
    if (stack == NULL) 
    {
        return 1;
    }
    
    return 0; 
} 
  
/* Utility function to push an item to stack */
void push(struct stack **stack, int num) 
{ 
    struct stack *new_stack = (struct stack *)malloc(sizeof(*new_stack)); 
  
    if (new_stack == NULL) 
    {  
        return; 
    } 
  
    new_stack->data = num; 
    new_stack->next = *stack; 
    *stack = new_stack; 
} 
  
/* Utility function to remove an item from stack */
int pop(struct stack **stack) 
{ 
    int num; 
    struct stack *temp; 
  
    num = (*stack)->data; 
    temp = *stack; 
    (*stack) = (*stack)->next; 
    free(temp); 
  
    return (num); 
} 
  
/* Function to find top item */
int top(struct stack *stack) 
{ 
    return (stack->data); 
} 

/* Utility function to print contents of stack */
void printStack(struct stack *stack) 
{ 
    while (stack) 
    { 
        printf("%d-> ", stack->data); 
        stack = stack->next; 
    }
    
    printf("Base\n\n"); 
} 

/***********************************************/

/* Recursive function to insert an item x in sorted way */
void sortedInsert(struct stack **stack, int num) 
{ 
	int temp = 0;
	
    /* Base case: stack is empty */
    /* item is greater than top (more than all existing) */ 
    if (isEmpty(*stack) || num > top(*stack)) 
    { 
        push(stack, num); 
        return; 
    } 
  
    /* If top is greater, remove the top item and recur */
    temp = pop(stack); 
    sortedInsert(stack, num); 
  
    /* Put back the top item removed earlier */
    push(stack, temp); 
} 
  
/* Function to sort stack */
void sortStack(struct stack **stack) 
{ 
	int num = 0;
	
    /* If stack is not empty */
    if (!isEmpty(*stack)) 
    { 
        /* Remove the top item */
        num = pop(stack); 
  
        /* Sort remaining stack */
        sortStack(stack); 
  
        /* Push the top item back in sorted stack */
        sortedInsert(stack, num); 
    } 
} 



/*************************** functions graveyard ******************************/
/*
stack_t *StackSorter(stack_t *stack)
{
	int *temp = 0;
	stack_t *sorted_stack = StackCreate(StackSize(stack));
	
	if (1 != StackIsEmpty(stack))
	{
		temp = StackPeek(stack);
		StackPop(stack);
		StackSorter(stack);
		InsertToSorted(temp, sorted_stack);
	}
	
	return (sorted_stack);
}

void InsertToSorted(int *temp, stack_t *sorted_stack)
{
	int *data = 0;
	if (1 == StackIsEmpty(sorted_stack) || *temp > *(int *)StackPeek(sorted_stack))
	{
		StackPush(&temp, sorted_stack);
	}

	data = (int *)StackPeek(sorted_stack);
	StackPop(sorted_stack);
	InsertToSorted(data, sorted_stack);
	StackPush(data, sorted_stack);
}

void StackPrintAndDestroy(stack_t *sorted_stack)
{
	while (1 != StackIsEmpty(sorted_stack))
	{
		printf("data: %d\n", *(int *)(StackPeek(sorted_stack)));
		StackPop(sorted_stack);
	}
}
*/
