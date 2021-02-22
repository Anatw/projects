/*******************************************************************************
					  	 Written by Anat Wax
						  March 3, 2020
						Reviewer: Yoni Naor
*******************************************************************************/
#include <stdlib.h>
#include <stdio.h> 		/* printf() */
#include <assert.h>		/* assert() */

#define MATCH (1)
				 /******* MORE FUNCTIONS TO IMPLEMENT ********/
typedef struct sll_node
{
	void *data;
	struct sll_node *next;
}node_t;


typedef struct sll
{
	node_t *head;
	node_t *tail;
}sll_t;


void SLLFlip(sll_t *list);
size_t Count(node_t *head);
node_t *FindIntersectionKnownLen(node_t *head_longer, node_t *head_shorter, 
								 size_t len);
node_t *FindIntersection(node_t *head1, node_t *head2);
int HasLoop(const node_t *head);
node_t *CreateNode(void *data);


int main()
{
	int var1 = 5;
	int var2 = 565;
	int var3 = 13;
	int var4 = 67;
	int var5 = 734;
	int var6 = 345;
	int var7 = 1234;
	
	node_t *head = CreateNode(&var1);
	node_t *elem1 = CreateNode(&var2);
	node_t *elem2 = CreateNode(&var3);
	node_t *elem3 = CreateNode(&var4);
	node_t *head2 = CreateNode(&var5);
	node_t *elem4 = CreateNode(&var6);
	node_t *elem5 = CreateNode(&var7);
	
	node_t *intersection = NULL;
	node_t *intersection2 = NULL;
	
	head->next = elem1;
	elem1->next = elem2;
	elem2->next = elem3;
	elem3->next = elem4;
	
	head2->next = elem4;
	elem4->next = elem5;
	
	intersection = FindIntersection(head2, head);
	intersection2 = FindIntersection(head, head2);
	
	assert(intersection == intersection2);
	printf("Intersection value is 345: %d\n", *(int *)intersection->data);
	
	elem3->next = head2;
	intersection = FindIntersection(head2, head);
	intersection2 = FindIntersection(head, head2);
	
	assert(intersection == intersection2);
	printf("Intersection value is 734: %d\n", *(int *)intersection->data);
	
	elem3->next = NULL;
	intersection = FindIntersection(head2, head);
	intersection2 = FindIntersection(head, head2);
	
	assert(intersection == intersection2);
	assert(intersection == NULL);
	
	printf("Has loop? %s\n", (HasLoop(head) ? "yes" : "no"));
	elem3->next = head;
	printf("Has loop? %s\n", (HasLoop(head) ? "yes" : "no"));
	return (0);
}

			

void SLLFlip(sll_t *list)
{
	node_t *current_node = list->head;
	node_t *next_node = list->head->next;
	node_t *last_node = NULL;
	list->head->next = list->tail;

	while (NULL != next_node->next)
	{
		last_node = current_node;
		current_node = next_node;
		next_node = next_node->next;

		current_node->next = last_node;
	}

	list->head = current_node;
}

/******************************************************************************/
							 
node_t *FindIntersection(node_t *head1, node_t *head2)
{
	size_t list1_len = Count(head1);
	size_t list2_len = Count(head2);
	
	/* check which is longer and call FindIntersectionKnownLen with the delta */
	if (list1_len > list2_len)
	{
		return (FindIntersectionKnownLen(head1, head2, list1_len - list2_len));
	}
	else
	{
		return (FindIntersectionKnownLen(head2, head1, list2_len - list1_len));
	}
}

/******/
size_t Count(node_t *head)
{
	size_t counter = 0;
	
	while(NULL != head->next)
	{
		head = head->next;
		++counter;
	}
	
	++counter;
	
	return (counter);
}

/******/
node_t *FindIntersectionKnownLen(node_t *head_longer, node_t *head_shorter, 
								 size_t length)
{
	size_t i = 0;
	
	/* step 1: promote the longer for 'length' (delta   */
	/* 		   from previous function) elements 		*/
	for (; i < length; i++)
	{
		head_longer = head_longer->next;
	}
	
	/* step 2: promote the heads until equal or end 	*/
	while ((head_longer != head_shorter) && (head_longer != NULL))
	{
		head_longer = head_longer->next;
		head_shorter = head_shorter->next;
	}
	
	/* final step: if equal and not at the end 				*/
	if (NULL != head_longer)
	{
		return (head_longer);
	}
	else
	{
		return (NULL);
	}
}

/******************************************************************************/
/* Floyd’s Cycle-Finding Algorithm: */
int HasLoop(const node_t *head)
{	
	node_t *slow_p = (head->next) ;
	node_t *fast_p = (head->next->next);
	
	while (NULL != fast_p)
	{
		if (slow_p == fast_p)
		{
			return (1);
		}
		
		slow_p = (slow_p->next);
		fast_p = (fast_p->next->next);
	}
	
	return (0);
}

node_t *CreateNode(void *data)
{
	node_t *new_node = (node_t *)malloc(sizeof(node_t));
	new_node->data = data;
	
	return (new_node);
}
