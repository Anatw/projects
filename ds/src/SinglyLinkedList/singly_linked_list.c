#include <stdlib.h>

#include "singly_linked_list.h"

#define MATCH (1)

typedef struct sll_node
{
	void *data;
	struct sll_node *next_node;
}node_t;


struct SLL
{
	node_t *head;
	node_t *tail;
};

node_t *CreateNode(void *data)
{
	node_t *new_node = (node_t *)malloc(sizeof(node_t));
	new_node->data = data;
	
	return (new_node);
}

SLL_t *SLLCreate()
{
	SLL_t *list = (SLL_t *)malloc(sizeof(SLL_t));
	node_t *stab = CreateNode(list);
	
	if(NULL == stab || NULL == list) /* if mallocs failed */
	{
		return (NULL);
	}
	
	stab->next_node = NULL;

	list->head = stab;
	list->tail = stab;
	
	return (list);
}

iter_t SLLBegin(const SLL_t *list)
{
	return (list->head);
}

iter_t SLLTail(const SLL_t *list)
{
	return (list->tail);
}

int SLLIsSameIter(const iter_t iter1, const iter_t iter2)
{
	return (iter1 == iter2 ? 0 : 1);
}

iter_t SLLNext(const iter_t member)
{
	return (member->next_node);
}
		
iter_t SLLInsert(iter_t where, void *data)
{
	node_t *new_node = CreateNode(where->data);
	
	if(new_node == NULL) /* rotate over the entire array until stab and return stab */
	{
		while(NULL == where->next_node)
		{
			SLLNext(where);
		}
		
		return (where);
	}
	
	/* if we point at stab, point tail->next to the new node: */
	if(NULL == where->next_node)
	{
		((SLL_t *)where->data)->tail = new_node;	
	}
	
	new_node->next_node = where->next_node;
	new_node->data = where->data;
	where->data = data;
	where->next_node = new_node;
		
	return (new_node);
}

size_t SLLCount(const SLL_t *list)
{
	node_t *i = SLLBegin(list);
	size_t count = 0;
	
	for(; NULL != i->next_node; i = SLLNext(i))
	{
		++count;
	}
	
	return (count);
}

void *SLLGetData(const iter_t node)
{
	return (node->data);
}

void SLLSetData(const iter_t iterator, void *data)
{
	iterator->data = data;
}

iter_t SLLFind(const iter_t from, const iter_t to, void *data, int (*match_func)(void *, void *))
{
	iter_t i = from;
	
	for(; 0 == SLLIsSameIter(i, to); i = SLLNext(i))
	{
		if(0 == match_func(data, i->data)) /* found a match! */
		{
			return (i);
		}
	}
	
	return (i);
}

int SLLIsEmpty(const SLL_t *list)
{
	if(list->head == list->tail) /* the list is empty */
	{
		return (1);
	}
	
	return (0);
}





