/*******************************************************************************
					  		Written by Anat Wax
						 	April fth-6th, 2020
						   Reviewer: Noffar Gil
*******************************************************************************/
#include <stdio.h> /* printf() */
#include <assert.h> /* assert() */
#include <stdlib.h> /* malloc() */

#include "/home/anat/git/anat-wax/ds/include/singly_linked_list.h"

typedef struct sll_node
{
	int data;  /* pointer to the data the node contain */
	struct sll_node *next; /* pointer to the next node */
} Node;

/*
 * Flip List: Flips a singly linked list from start to end.
 * Return: Pointer to the new beggining of the list.
 * Receive: node - Pointer to the the node to start fliping from.
 * Time Complexity: O(n)
 */
Node *FlipList(Node *node);

static void SLLPrint(Node *node);

int main ()
{
	int a = 1;
	int b = 2;
	int c = 3;
	int d = 4;
	int e = 5;
	
	/* Creating a very simple singly linked list */
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
	
	/* After fliping the list */
	printf("After fliping the list: \n");
	SLLPrint(list_last);
	
	return (0);
}

Node *FlipList(Node *node)
{
	Node *head = NULL;

	assert(node);

	if (NULL == node || NULL == node->next)
	{
		return (node);		
	}
	
	head = FlipList(node->next);
	node->next->next = node;
	node->next = NULL;
	
	return (head);
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
