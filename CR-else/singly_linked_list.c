/******************************************************************************/
/* 					Worksheet 12 - Singly Linked LIst Implementation		  */
/*					Description - Functions Definitions	  				 	  */
/*					Autor - Dean Oron									 	  */
/*					Date - 03.03.20									     	  */
/*					Reviewer - 	Anat Wax						         	  */
/*					Open Lab 86											  	  */
/******************************************************************************/
#include"singly_linked_list.h"
#include <stdio.h>
#include<stdlib.h>

void SwapPointer(void **p11, void **p22);

typedef struct sll_node
{
	void *data;
	struct sll_node *next;
}node_t;

struct list 
{
	 node_t *head;
	 node_t *tail;	
};

sll_t *SLLCreate()
{
	sll_t *new_list;
	node_t *dummy;
	
	new_list = (sll_t *)malloc(sizeof(sll_t));
	dummy = (node_t *)malloc(sizeof(node_t));
	dummy->data = (void *)new_list;
	dummy->next = NULL;
	dummy->data = (node_t *)new_list;
	
	new_list->head = dummy;
	new_list->tail = dummy;
	
	return(new_list);
	
}

iter_t SLLBegin(const sll_t *list)
{
	return(list->head);	
}

int SLLIsEmpty(const sll_t *list)
{
	if(list->head == list->tail)
	{
		return(1);
	}

	else
	return(0);
}

iter_t SLLInsert(iter_t where, void *data)
{
	node_t *new_node = (node_t *)malloc(sizeof(node_t));
	new_node->data = data;
	SwapPointer(&new_node->data, &where->data);
	
	if(where->next == NULL) /* means the where is dummy */
	{	
		((sll_t *)new_node->data)->tail = new_node;
	}
	
		new_node->next = where->next;
		where->next = new_node;
	
		return(where);
}

void *SLLGetData(const iter_t i)
{
	return(i->data);
}

size_t SLLCount(const sll_t *list)
{
	size_t size = 0;
	node_t *curr;
	
	curr = ((sll_t*)list->tail->data)->head;
	
	while(curr->next)
	{	++size;
		curr = curr->next;
	}
	
	return(size);
}

iter_t SLLRemove(iter_t who)
{	
	node_t *to_free;
	
	
	who->data = who->next->data;
	to_free = who->next;
	who->next = who->next->next;
	free(to_free);
	
	return(who);
}

iter_t SLLEnd(const sll_t * list)
{
	return(list->tail);
}

iter_t SLLNext(const iter_t i)
{
	return(i->next);
}

int SLLIsSameIter(const iter_t iter1, const iter_t iter2)
{
	return((iter1 == iter2) ? 1 : 0);
}

iter_t SLLFind(const iter_t from, const iter_t to, void *data, int match_func(void *, void *))
{	
	iter_t i = NULL;
	
	for(i = from; i != to; i = SLLNext(i))
	{
		if(match_func(data, i->data))
		return(i);
	}

	return(i);
}

void SLLSetData(iter_t i, void *data)
{
	i->data = (void*)data;
}

int SLLForEach(const iter_t from, const iter_t to, void (*act_func)(void *, void *), void *param)
{
	iter_t i = 0;

	for(i = from; !(SLLIsSameIter(i, to)); i = SLLNext(i))
	{
		act_func(i->data, param);
	}

	return(0);
}

void SLLDestroy(sll_t *list)
{
	iter_t i = 0;
	
	for(i = SLLBegin(list); !(SLLIsSameIter(i, SLLEnd(list))); )
	{	
		if(NULL == i -> next)
		{
			free(i);
			break;
		}
		
		i = SLLRemove(i);
	}	
	
	free(list);
}

void SwapPointer(void **p11, void **p22)
{	
	void *tmp;
	
	tmp = *p11;
	*p11 = *p22;
	*p22 = tmp;
}
