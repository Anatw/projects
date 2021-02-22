/*******************************************************************************
					  		Written by Anat Wax
						 	April fth-6th, 2020
						   Reviewer: Noffar Gil
*******************************************************************************/
#include <stdio.h> /* printf() */

#include "recursion.h"

#include "/home/anat/git/anat-wax/ds/include/singly_linked_list.h"

/* static void SLLPrint(Node *node); */

/******************************************************************************/

int main ()
{
	int next_fib = 14;
	
	printf("recursive: the next Fibonacci number after %d is: %d\n",
			next_fib, FibonacciRecursive(next_fib));

	printf("non-recursive: the next Fibonacci number after %d is: %d\n",
			next_fib, FibonacciNonRecursive(next_fib));

	return (0);
}
/*

int main ()
{
	int a = 1;
	int b = 2;
	int c = 3;
	int d = 4;
	int e = 5;
	
	/ Creating a very simple singly linked list /
	Node *list_head = (Node *)malloc(sizeof(Node));
	Node *list_second = (Node *)malloc(sizeof(Node));
	Node *list_third = (Node *)malloc(sizeof(Node));
	Node *list_forth = (Node *)malloc(sizeof(Node));
	Node *list_last = (Node *)malloc(sizeof(Node));
	list_last->next = NULL;
	
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
	
	printf("Before fliping the list: \n");
	SLLPrint(list_head);
	
	FlipList(list_head);
	
	/ After fliping the list /
	printf("After fliping the list: \n");
	SLLPrint(list_last);
	
	return (0);
}

static void SLLPrint(Node *node)
{
	while (NULL != node->next)
	{
		printf("%d->", node->data);
		node = node->next;
	}
	printf("%d->", node->data);
	printf("NULL\n\n");
}


*********************************************/




