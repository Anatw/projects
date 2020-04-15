/*****************************************************************************
* File Name: recursion.c													 *
* Writer: Lior Cohen														 *
* Date: 05/04/2020														     *
* Purpose: The file for the exercise about recursion						 *
* Code reviewer: Anat Wax												 	 *
******************************************************************************/

#include <stdio.h> /* printf() */
#include <assert.h> /* assert */
#include <stdlib.h> /* malloc() */

#include "recursion.h"

struct list_node
{
	int data;
	struct list_node *next;
};

/******************************************************************************/

struct stack
{
	int data;
	struct stack *next;
};

/******************************************************************************/

void PrintList(Node *node);

/************************* Sorting Stack Functions ****************************/

void initStack(struct stack **s);

int isEmpty(struct stack *s);

void push(struct stack **s, int x);

int pop(struct stack **s);

int top(struct stack *s);

void sortedInsert(struct stack **s, int x);

void sortStack(struct stack **s);

void printStack(struct stack *s);

/******************************************************************************/
/******************************************************************************/

int main()
{
	int index = 9;
	char *str1 = "Liorcohen";
	char *str2 = "LiorCohen";
	char str3[20] = "MyNameIs";
	char str4[20] = {0};
	char str5[100] = "ABCDEFGHIJKLMNOPQRSTUVWXYS";
	char *str6 = "LMNOP";
	int a = 1;
	int b = 2;
	int c = 3;
	int d = 4;
	int e = 5;
	int i = 0;
	
	struct stack *top;
	
	/* Creating a very simple singly linked list */
	Node *list_head = (Node *)malloc(sizeof(Node));
	Node *list_second = (Node *)malloc(sizeof(Node));
	Node *list_third = (Node *)malloc(sizeof(Node));
	Node *list_forth = (Node *)malloc(sizeof(Node));
	Node *list_last = (Node *)malloc(sizeof(Node));
	
	list_head->next = list_second;
	list_second->next = list_third;
	list_third->next = list_forth;
	list_forth->next = list_last;
	list_last->next = NULL;
	
	list_head->data = a;
	list_second->data = b;
	list_third->data = c;
	list_forth->data = d;
	list_last->data = e;
	/* Done creating the list */

	/* Before fliping the list */
	printf("Before fliping the list: \n");
	PrintList(list_head);
	
	FlipList(list_head);
	
	/* After fliping the list */
	printf("After fliping the list: \n");
	PrintList(list_last);
	
	/* Creating a basic stack */
    initStack(&top); 
    push(&top, b); 
    push(&top, e); 
    push(&top, c); 
    push(&top, d); 
    push(&top, a); 
  
    printf("Stack elements before sorting:\n"); 
    printStack(top); 
  
    sortStack(&top); 
  
    printf("Stack elements after sorting:\n"); 
    printStack(top); 
	
	printf("Fibonacci in the 9th place should be (21):\n");
	printf("Iterations: %d\n", FibonacciI(index));
	
	printf("Recursive: %d\n", FibonacciR(index));
	
	printf("The length of 'LiorCohen' is (9): ");
	printf("%ld\n\n", Strlen(str1));
	
	printf("Comparing between the two strings should be (32): ");
	printf("%d\n\n",Strcmp(str1, str2));
	
	printf("Playing with the last three str fucntions:\n");
	printf("%s\n", Strcat(str3, str1));
	
	printf("%s\n", Strcpy(str4, str3));
	
	printf("%s\n", Strstr(str5, str6));
	
	return (0);
}

/******************************************************************************/
/******************************************************************************/

int FibonacciR(int element_index)
{
	if (1 == element_index)
	{
		return (0);
	}
	else if (2 == element_index)
	{
		return (1);
	}
	
	return (FibonacciR(element_index - 1) + FibonacciR(element_index - 2));
}


int FibonacciI(int element_index)
{
	int first = 0;
	int second = 1;
	int result = 0;
	int i = 0;

	if (1 == element_index)
	{
		return (first);
	}
	else if (2 == element_index)
	{
		return (second);
	}

	for (i = 2; i < element_index; ++i)
	{
		result = first + second;
		first = second;
		second = result;
	}
	
	return (result);
}

/******************************************************************************/

Node *FlipList(Node *node)
{
	/* Only one node or nothing at all */
	if (NULL == node || NULL == node->next)
	{
		return (node);
	}
	
	Node *list = FlipList(node->next);
	node->next->next = node;
	
	node->next = NULL;
	
	return (list);	
}

void PrintList(Node *node)
{
	Node *temp_node = node;

	while (NULL != temp_node)
	{
		printf("%d->", temp_node->data);
		temp_node = temp_node->next;
	}
	printf("NULL\n\n");
}

/**************************** Sorting Stack **********************************/

// Utility function to initialize stack 
void initStack(struct stack **stack)
{ 
    *stack = NULL; 
} 
  
// Utility function to chcek if stack is empty 
int isEmpty(struct stack *stack) 
{ 
    if (stack == NULL) 
        return 1; 
    return 0; 
} 
  
// Utility function to push an item to stack 
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
  
// Utility function to remove an item from stack 
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
  
// Function to find top item 
int top(struct stack *stack) 
{ 
    return (stack->data); 
} 
  
// Recursive function to insert an item x in sorted way 
void sortedInsert(struct stack **stack, int num) 
{ 
	int temp = 0;
	
    // Base case: Either stack is empty or newly inserted 
    // item is greater than top (more than all existing) 
    if (isEmpty(*stack) || num > top(*stack)) 
    { 
        push(stack, num); 
        return; 
    } 
  
    // If top is greater, remove the top item and recur 
    temp = pop(stack); 
    sortedInsert(stack, num); 
  
    // Put back the top item removed earlier 
    push(stack, temp); 
} 
  
// Function to sort stack 
void sortStack(struct stack **stack) 
{ 
	int num = 0;
	
    // If stack is not empty 
    if (!isEmpty(*stack)) 
    { 
        // Remove the top item 
        num = pop(stack); 
  
        // Sort remaining stack 
        sortStack(stack); 
  
        // Push the top item back in sorted stack 
        sortedInsert(stack, num); 
    } 
} 
  
// Utility function to print contents of stack 
void printStack(struct stack *stack) 
{ 
    while (stack) 
    { 
        printf("%d-> ", stack->data); 
        stack = stack->next; 
    }
    
    printf("Base\n\n"); 
} 

/******************************************************************************/

size_t Strlen(const char *str)
{
	static size_t counter = 0;
	size_t result = 0;
	
	if (*str != '\0')
	{
		++counter;
	}
	else
	{
		str -= counter;
		result = counter;
		counter = 0;
		return (result);
	}
	
	return (Strlen(++str));
}

int Strcmp(const char *str1, const char *str2)
{
	static int difference = 0;
	
	if (*str1 == '\0' || *str2 == '\0')
	{
		return (0);
	}
	
	if (*str1 == *str2)
	{
		difference += 0;
	}
	else if (*str1 < *str2)
	{
		difference += *str1 - *str2;
		return (difference);
	}
	else
	{
		difference += *str1 - *str2;
		return (difference);
	}
	
	return (Strcmp(++str1, ++str2));
}

char *Strcpy(char *dest, const char *src)
{
	static size_t counter = 0;
	
	if (*src == '\0')
	{
		return (dest - counter);
	}
	
	*dest = *src;
	++counter;
	
	return (Strcpy(++dest, ++src));	
}

char *Strcat(char *dest, const char *src)
{
	static size_t counter = 0;
	
	if (*src == '\0')
	{
		return (dest - counter);
	}
	if (*dest != '\0')
	{
		++counter;
		return (Strcat(++dest, src));
	}
	++counter;
	
	*dest = *src;

	return (Strcat(++dest, ++src));
}

char *Strstr(const char *haystack, const char *needle)
{
	static size_t count_reset = 0;
	static size_t counter = 0;
		
	assert(haystack);
	assert(needle);
	
	if (*needle == '\0')
	{
		return (haystack - counter);
	}
	
	if (*haystack == *needle)
	{
		++counter;
		return (Strstr(++haystack, ++needle));
	}
	else
	{
		count_reset = counter;
		counter = 0;
		return (Strstr(++haystack, needle - count_reset));
	}
}

/******************************************************************************/
/******************************************************************************/











