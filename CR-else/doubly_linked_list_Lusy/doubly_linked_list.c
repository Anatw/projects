#include <stddef.h>  /* size_t */
#include <assert.h>  /* assert() */
#include <stdlib.h>  /* malloc(), free() */
#include <stdio.h>   /* printf() */

#include "doubly_linked_list.h"

typedef struct dll_node
{
	void *data;
	struct dll_node *next;
	struct dll_node *prev;
	
} dll_node_t;

struct doubly_linked_list
{
	dll_node_t head;
	dll_node_t tail;
};	

/*****************************************************************************/
	
iter_t DLLNext(const iter_t iter)
{	
	assert (iter);
	
	return (iter->next);
}

/*****************************************************************************/

iter_t DLLPrev(const iter_t iter)
{
	assert (iter);
	
	return (iter->prev);
}		

/*****************************************************************************/
	
iter_t DLLBegin(const dll_t *dll)
{
	assert (dll);
		
	return (dll->head.next);
}

/*****************************************************************************/

iter_t DLLEnd(dll_t *dll)
{
	assert (dll);
	
	return (dll->tail.prev);
}		
	
/*****************************************************************************/	
	
dll_t *DLLCreate()
{
	dll_t *new_list = (dll_t *)malloc(sizeof(dll_t));
	
	if (NULL == new_list)
	{
		return (NULL);
	}
	
	new_list->head.next = &new_list->tail;
	new_list->tail.prev = &new_list->head;
	new_list->head.prev = NULL;
	new_list->tail.next = NULL;
	new_list->head.data = NULL;
	new_list->tail.data = NULL;
	
	return (new_list);
}	
	
/*****************************************************************************/	

void DLLDestroy(dll_t *dll)
{
	assert (dll);
	
	while (!DLLIsEmpty(dll))
	{
		DLLRemove(DLLBegin(dll));
	}
		
	free (dll);
	dll = NULL;
}		
	
/*****************************************************************************/	
	
iter_t DLLInsert(iter_t node, void *data)
{
	dll_node_t *new_node = NULL;
	
	assert (node);
	
	new_node = (dll_node_t *)malloc(sizeof(dll_node_t));
	
	if (NULL == new_node)
	{
		while (NULL != node->next)
		{
			node = DLLNext(node);
		}
		
		return (node);
	}
	
	new_node->data = data;
	new_node->next = node;
	new_node->prev = node->prev;
	node->prev = new_node;
	new_node->prev->next = new_node;
	
	return (new_node);
}

/*****************************************************************************/	
	
int DLLIsEmpty(const dll_t *list)
{
	assert (list);
	
	return (list->head.next == &list->tail);	
}	
	
/*****************************************************************************/

size_t DLLSize(const dll_t *list)
{
	size_t count = 0;
	dll_node_t *node_num = NULL;
	
	assert (list);
	
	node_num = DLLBegin(list);
		
	while (NULL != DLLNext(node_num))
	{
		++count;
		node_num = DLLNext(node_num);
	}
	
	return (count);
}	

/*****************************************************************************/

int DLLIsSameIter(iter_t iter1, iter_t iter2)	
{
	assert (iter1);
	assert (iter2);
	
	return (iter1 == iter2);
}		
	
/*****************************************************************************/
	
iter_t DLLRemove(iter_t where)
{
	dll_node_t *next_node = NULL;	
	dll_node_t *prev_node = NULL;
	
	assert (where);
	assert (where->next);
	assert (where->prev);
		
	next_node = DLLNext(where);
	prev_node = DLLPrev(where);
	
	prev_node->next = next_node;
	next_node->prev = prev_node;
	
	free(where);
	where = NULL;
	
	return (next_node);
}	
	
/*****************************************************************************/
	
iter_t DLLPushBack(dll_t *list, void *data)
{	
	assert (list);
	
	DLLInsert(&list->tail, data);
	
	return (DLLEnd(list));
}	
	
/*****************************************************************************/

void *DLLPopFront(dll_t *list)
{
	void *deleted = NULL;
	
	assert (list);
	
	deleted = DLLBegin(list)->data;
	DLLRemove(DLLBegin(list));
	
	return (deleted);
}		
	
/*****************************************************************************/

void *DLLPopBack(dll_t *list)
{
	void *deleted = NULL;
	
	assert (list);
	
	deleted = DLLEnd(list)->data;
	DLLRemove(DLLEnd(list));
	
	return (deleted);	
}	
	
/*****************************************************************************/
	
iter_t DLLPushFront(dll_t *list, void *data)
{
	assert (list);
	
	DLLInsert(DLLBegin(list), data);
	
	return (DLLBegin(list));	
}	
	
/*****************************************************************************/

void *DLLGetData(const iter_t where)
{
	assert (where);
	
	return (where->data);
}		
	
/*****************************************************************************/

void DLLSetData(iter_t where, void *new_data)
{
	assert (where);
	
	where->data = new_data;
}		
	
/*****************************************************************************/	
	
iter_t DLLFind(const iter_t from, const iter_t to, 
			int (*match_func)(const void *data1, void *data2), void *data)
{
	iter_t iter = NULL;
	
	assert (from);
	assert (to);
	assert (match_func);
	
	/* compares the data of each node with the given data until a match
	  is found or until the end of the list is encountered */
	for(iter = from; 0 == DLLIsSameIter(iter, to); iter = DLLNext(iter))
	{
		if(1 == match_func(iter->data, data))
		{
			return (iter);
		}	
	}
	
	/* if there was no matches return iterator to */
	return (iter);
}	

/*****************************************************************************/

int DLLForEach(const iter_t from, const iter_t to, 										int (*act_func)(void *operand1, void *operand2), void *param)
{
	iter_t iter = NULL;
	int status = 1; 
	
	assert (from);
	assert (to);
	assert (act_func);
	
	for(iter = from; iter != DLLNext(to); iter = DLLNext(iter))
	{
		status = act_func(iter->data, param);
	}
	
	return (status);	
}
	
/*****************************************************************************/	
	
iter_t DLLSplice(iter_t from, iter_t to, iter_t where)
{	
	assert(from);
	assert(to);
	assert(where);
	
	DLLPrev(from)->next = DLLNext(to);
	DLLNext(to)->prev = DLLPrev(from);
	
	where->prev->next = from;
	to->next = where;
	from->prev = where->prev;
	where->prev = to;
	
	return (to);
}	
		
/*****************************************************************************/	
	
size_t DLLMultiFind(const iter_t from, const iter_t to, void *data, 
				int (*match_func)(const void *data1, void *data2), dll_t *dest)
{
	dll_node_t *i = NULL;
	size_t count = 0;
	
	assert (from);
	assert (to);
	assert (match_func);
	assert (dest);
	
	for(i = from; i != to; i = DLLNext(i))
	{
		if (0 != match_func(data, i->data))
		{
			DLLPushFront(dest, i->data);
			++count;
		}
	}
	
	return (count);
}			
							
/*****************************************************************************/	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
		
