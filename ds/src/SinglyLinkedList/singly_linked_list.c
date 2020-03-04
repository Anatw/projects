/*******************************************************************************
					  	 Written by Anat Wax
						  March 3, 2020
						Reviewer: Yoni Naor
*******************************************************************************/
#include <stdlib.h>
#include <assert.h> 	/* assert() */

#include "singly_linked_list.h"

typedef struct sll_node
{
	void *data;
	struct sll_node *next;
}node_t;


struct SLL
{
	node_t *head;
	node_t *tail;
};

/******************************************************************************/

node_t *CreateNode(void *data)
{
	node_t *new_node = NULL;
	
	new_node = (node_t *)malloc(sizeof(node_t));
	new_node->data = data;
	
	return (new_node);
}

/******************************************************************************/

SLL_t *SLLCreate()
{
	SLL_t *list = NULL;
	node_t *stab = NULL;
	
	list = (SLL_t *)malloc(sizeof(SLL_t));
	
	if (NULL == list)
	{
		return (NULL);
	}
	
	stab = CreateNode(list);
	
	if (NULL == stab) /* if mallocs failed */
	{
		return (NULL);
		free(list);
		list = NULL;
	}
	
	stab->next = NULL;

	list->head = stab;
	list->tail = stab;
	
	return (list);
}

/******************************************************************************/

iter_t SLLBegin(const SLL_t *list)
{
	assert(NULL != list);
	
	return (list->head);
}

/******************************************************************************/

iter_t SLLTail(const SLL_t *list)
{
	assert(NULL != list);
	
	return (list->tail);
}

/******************************************************************************/

int SLLIsSameIter(const iter_t iter1, const iter_t iter2)
{
	return (iter1 == iter2 ? 1 : 0);
}

/******************************************************************************/

iter_t SLLNext(const iter_t member)
{
	return (member->next);
}

/******************************************************************************/
	
iter_t SLLInsert(iter_t where, void *data)
{
	node_t *new_node = CreateNode(where->data);
	
	/* rotate over the entire array until stab and return stab: */
	if (new_node == NULL)
	{
		while (NULL == where->next)
		{
			SLLNext(where);
		}
		
		return (where);
	}
	
	new_node->next = where->next;
	
	/* if we point at stab, point tail->next to the new node: */
	if (NULL == where->next)
	{
		((SLL_t *)where->data)->tail = new_node;	
	}
	
	where->data = data;
	where->next = new_node;
		
	return (where);
}

/******************************************************************************/

size_t SLLCount(const SLL_t *list)
{
	node_t *i = SLLBegin(list);
	size_t count = 0;
	
	assert(NULL != list);
		
	for (; NULL != i->next; i = SLLNext(i))
	{
		++count;
	}
	
	return (count);
}

/******************************************************************************/

void *SLLGetData(const iter_t node)
{
	return (node->data);
}

/******************************************************************************/

void SLLSetData(const iter_t iterator, void *data)
{
	iterator->data = data;
}

/******************************************************************************/

iter_t SLLFind(const iter_t from, const iter_t to, void *data,
			   int (*match_func)(void *, void *))
{
	iter_t i = from;
	
	for (; 0 == SLLIsSameIter(i, to); i = SLLNext(i))
	{
		if (1 == match_func(data, i->data)) /* found a match! */
		{
			return (i);
		}
	}
	
	return (i);
}

/******************************************************************************/

int SLLIsEmpty(const SLL_t *list)
{
	assert(NULL != list);
	
	if (list->head == list->tail) /* the list is empty */
	{
		return (1);
	}
	
	return (0);
}

/******************************************************************************/

iter_t SLLRemove(iter_t who)
{
	node_t *temp = who->next;
	
	/* if you are pointing at dummy, meaning list is empty */
	if (NULL == temp->next)
	{
		((SLL_t *)temp->data)->tail = who;	/* point tail to temp */
	}
	
	who->data = who->next->data;
	who->next = who->next->next;
		
	free(temp);
	temp = NULL;
	
	return (who);
}

/******************************************************************************/

void SLLDestroy(SLL_t *list)
{
	iter_t temp = list->head;
	iter_t temp2 = NULL;
	
	assert(NULL != list);
		
	/* go over the entire list and free the node temp is pointing at */
	for (; (temp->next); (temp = temp2))
	{
		temp2 = SLLNext(temp);
		free(temp);
		temp = NULL;
	}
	
	free(temp); /* free stab */
	free(list);
	list = NULL;
}

/******************************************************************************/

int SLLForEach(iter_t from, iter_t to, void *param, int (*action_func)
			   (void *param, void *data))
{
	iter_t i = from;
	int status = 0;
	
	for (; 0 == SLLIsSameIter(i, to); i = SLLNext(i))
	{
		status = action_func(param, i->data);
	}
	
	return (status);
}


/******************************************************************************/
/******************************************************************************/
/******************************************************************************/

void SLLAppend(SLL_t *dest, SLL_t *src)
{
	assert(NULL != dest);
	assert(NULL != src);
	
	/* redefining the dummy of dest to be the head of src: */
	dest->tail->data = src->head->data;
	dest->tail->next = src->head->next;
	
	/* assigning pointers to the the new big list */
	dest->tail = src->tail;
	src->tail->data = dest;
	
	free(src->head);
	src->head = NULL;
	
	free(src); /* src is not needed anymore... */
	src = NULL;
}
