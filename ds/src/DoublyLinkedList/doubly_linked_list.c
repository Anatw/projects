#include <stdio.h>
#include <stdlib.h> /* malloc() */
#include <assert.h>

#include "doubly_linked_list.h"

/* type of node in the list */
typedef struct dll_node
{
	void *data; /* pointer to the data the node contain */
	struct dll_node *next; /* pointer to the next node */
	struct dll_node *prev; /* pointer to the previous node */
} dll_node_t;

/*****************/

struct doubly_linked_list
{
	dll_node_t head;
	dll_node_t tail;
}/* dll_t */;

/***************************************************/

static dll_node_t *DLLCreateNode(void *data)
{
	dll_node_t *new_node = NULL;
	
	new_node = (dll_node_t *)malloc(sizeof(dll_node_t));
	new_node->data = data;
	new_node->next = NULL;
	
	return (new_node);
}


dll_t *DLLCreate()
{
	dll_t *list = (dll_t *)malloc(sizeof(dll_t));
	
	if (NULL == list)
	{
		return (NULL);
	}
	
	list->head.next = &list->tail;
	list->tail.prev = &list->head;
	list->tail.next = NULL;
	list->head.prev = NULL;
	
	return (list);
}

void DLLDestroy(dll_t *list)
{
	while (!DLLIsEmpty(list))
	{
		DLLRemove(DLLBegin(list));
	}

	free(list);
	list = NULL;
}

iter_t DLLBegin(dll_t *list)
{
	return (list->head.next);
}

iter_t DLLEnd(dll_t *list)
{
	return (&list->tail);
}

void *DLLGetData(const iter_t where)
{
	return (where->data);
}

iter_t DLLInsert(iter_t where, void *data)
{
	dll_node_t *new_node = DLLCreateNode(data);;
	
	if (new_node == NULL)
	{
		while (NULL != where->next)
		{
			DLLNext(where);
		}
		
		return (where);
	}
	
	new_node->prev = where->prev;
	new_node->next = where;
	where->prev = new_node;
	new_node->prev->next = new_node;
		
	return (new_node);
}

iter_t DLLPushFront(const dll_t *list, void *data)
{
	dll_t *list_p = (dll_t *)list;
	
	return (DLLInsert(DLLBegin(list_p), data));
}

void *DLLPopFront(dll_t *list)
{
	void *data = list->head.next->data;
	
	DLLRemove(list->head.next);
	
	return (data);
}

iter_t DLLPushBack(const dll_t *list, void *data)
{	
	dll_t *p_list = (dll_t *)list;
	
	return (DLLInsert(DLLEnd(p_list), data));
}

void *DLLPopBack(dll_t *list)
{
	void *data = list->tail.prev->data;
	
	DLLRemove(DLLPrev(DLLEnd(list)));
	
	return (data);
}

iter_t DLLNext(const iter_t iter)
{
	return (iter->next);
}

iter_t DLLPrev(const iter_t iter)
{
	return (iter->prev);
}

size_t DLLSize(const dll_t *list)
{
	size_t count = 0;
	dll_t *list_p = (dll_t *)list;
	iter_t next_node = &list_p->head;
	
	while (NULL != DLLNext(next_node)->next)
	{
		next_node = DLLNext(next_node);
		++count;
	}
	
	return (count);
}

/*
size_t DLLSize(const dll_t *list)
{
	size_t count = 0;
	dll_t *list_p = (dll_t *)list;
	dll_node_t *i = &list_p->head;

	assert(NULL != list);
		
	for (; NULL != i->next; i = DLLNext(i))
	{
		++count;
	}
	
	return (count);
}
*/

int DLLIsEmpty(const dll_t *list)
{
	return ((0 == DLLSize(list) ? 1 : 0));
}

iter_t DLLRemove(iter_t where)
{
	iter_t next = DLLNext(where);
	where->prev->next = where->next;
	where->next->prev = where->prev;
		
	free (where);
	where = NULL;

	return (next);
}

int DLLIsSameIter(const iter_t iter1, const iter_t iter2)
{
	return (iter1 == iter2 ? 1 : 0);
}

iter_t DLLFind(const iter_t from, const iter_t to, const void *data, 
				int (*MatchFunc)(const void *data1, const void *data2))
{
	iter_t i = from;
	void *p_data =  (void *)data;
	
	assert(NULL != MatchFunc);
	
	for (i = from; 0 == DLLIsSameIter(i, to); i = DLLNext(i))
	{
		if (1 == MatchFunc(p_data, i->data)) /* found a match! */
		{
			return (i);
		}
	}
	
	return (i);
}

size_t DLLMultiFind(const iter_t from, const iter_t to, const void *data, 
					int (*MatchFunc)(void *data1, void *data2), dll_t *dest)
{
	iter_t i = from;
	dll_t *dest_dll = DLLCreate();
	void *p_data =  (void *)data;
	
	assert(NULL != MatchFunc);
	
	for (i = from; 0 == DLLIsSameIter(i, to); i = DLLNext(i))
	{
		if (1 == MatchFunc(p_data, i->data)) /* found a match! */
		{
			return (i);
		}
	}
	
	while
	{
		dest_dll->next.data
	}
	
	return (i);
}


void DLLPrint(const dll_t *list)
{
	dll_t *list_p = (dll_t *)list;
	iter_t point_to = DLLBegin(list_p);
	
	printf("%d\n", *(int *)DLLGetData(point_to));
	
	while (!DLLIsSameIter(point_to, (DLLEnd(list_p)->prev)))
	{
		point_to = DLLNext(point_to);
		printf("%d\n", *(int *)DLLGetData(point_to));
	}
}

int DLLForEach(const iter_t from, const iter_t to,
			   int (*DLLAddParam)(void *operand1, void *operand2),
			   const void *param)
{
	void *param_p = (void *)param;
	iter_t i = from;
	int status = 0;
	
	for (; 0 == DLLIsSameIter(i, to); i = DLLNext(i))
	{
		status = DLLAddParam(param_p, i->data);
		
		if (1 == status)
		{
			return (status);
		}
	}
	
	return (status);
}






