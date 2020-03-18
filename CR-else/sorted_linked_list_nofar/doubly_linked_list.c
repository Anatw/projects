/*******************************************************************************
Worksheet Data Structur exercise - doubly linked list		                              
Author - Noffar Gil
Reviewer - 	Yoni Naor				  
Date - 08.03.20									    	                 										  
*******************************************************************************/
#include <stdio.h> /* size_t */
#include <stdlib.h> /* malloc(), free() */
#include <assert.h> /* assert() */

#include "doubly_linked_list.h"

typedef struct dll_node dll_node_t;

struct dll_node
{
	void *data;
	struct dll_node *prev;
	struct dll_node *next;
	 
};

struct doubly_linked_list
{
	dll_node_t head;
	dll_node_t tail;
};

/* declaration of utility functions: */
static dll_node_t *CreateNodeHelp(void *new_data);

dll_t *DLLCreate()
{
	/* allocate memory for struct maneger */
	dll_t *new_dll = (dll_t *)malloc(sizeof(dll_t));
	
	if (NULL == new_dll)
	{
		return (NULL);
	}
	/* initialize head and tail */ 
	new_dll->head.next = &new_dll->tail;
	new_dll->head.data = NULL;
	new_dll->head.prev = NULL;
	new_dll->head.data = NULL;
	new_dll->tail.prev = &new_dll->head;
	new_dll->tail.next = NULL;
	
	return (new_dll);
}

void DLLDestroy(dll_t *list)
{	
	assert(NULL != list);
	
	/* run node till list is empty and remain only 'head' and 'tail'
		free each node and move to the next iterator */
	while (FALSE == DLLIsEmpty(list)) 
	{
		DLLRemove(DLLBegin(list));
	}

	free(list);
	list = NULL;
}

dll_iter_t DLLRemove(dll_iter_t where)
{	
	dll_node_t *next_node = DLLNext(where);
	
	/* do not remove head or tail */
	assert (NULL != where->next); 
	assert (NULL != where->prev);
	
	/*update prev and next value for values after 'where' will be free */
	where->prev->next = where->next;
	where->next->prev = where->prev;

	free(where);
	where = NULL;

	return (next_node);
}

bool DLLIsEmpty(const dll_t *list)
{
	assert(NULL != list);

	return (list->head.next->next == NULL? TRUE : FALSE);
}

dll_iter_t DLLBegin(const dll_t *list)
{
	assert(NULL != list);

	return (list->head.next);
}

dll_iter_t DLLEnd(dll_t *list)
{
	assert(NULL != list);
	
	return (&list->tail);
}

dll_iter_t DLLNext(const dll_iter_t iter)
{
	assert(NULL != iter);
	
	return (iter->next);
}

dll_iter_t DLLPrev(const dll_iter_t iter)
{
	assert(NULL != iter);
	
	return (iter->prev);
}

size_t DLLSize(const dll_t *list)
{
	size_t counter = 0;
	dll_node_t *current = list->head.next;

	/* count node till get to dummy whitch point to NULL */
	while (NULL != current->next) 
	{
		counter++;
		current = DLLNext(current);
	}

	return (counter);
}

void *DLLPopBack(dll_t *list)
{
	void *tail_prev_data = list->tail.prev->data;

	assert(NULL != list);
	
	/* prev- because we should not get to tail! */
	DLLRemove(DLLPrev(DLLEnd(list)));
	
	return (tail_prev_data);
}

void *DLLPopFront(dll_t *list)
{
	void *data_of_first_element = list->head.next->data;
	
	assert(NULL != list->head.next->next);
	
	DLLRemove(DLLBegin(list));

	return (data_of_first_element);
}

void *DLLGetData(const dll_iter_t where)
{
	assert(NULL != where->next);
	assert(NULL != where->prev);
	
	return (where->data);
}

void DLLSetData(dll_iter_t where, void *new_data)
{
	assert(NULL != where);
	
	where->data = new_data;
}

dll_iter_t DLLInsert(dll_iter_t iter, void *data)
{
	dll_node_t *new_node = CreateNodeHelp(data);

	assert(NULL != iter);

	if (!new_node)
	{
		while (NULL != iter->next)
		{
			iter = DLLNext(iter);
		}

		return (iter);
	}

	/* initialize new node's values and its neighbours's values */
	new_node->next = iter;
	new_node->prev = iter->prev;
	iter->prev = new_node;
	new_node->prev->next = new_node;

	return (new_node);
}

dll_iter_t DLLPushBack(dll_t *list, void *data)
{	
	assert (NULL != list);
	assert (NULL != data);

	return (DLLInsert(DLLEnd(list), data));
}

dll_iter_t DLLPushFront(dll_t *list, void *data)
{
	assert (NULL != list);
	assert (NULL != data);
	
	return (DLLInsert(DLLBegin(list), data));	
}

bool DLLIsSameIter(const dll_iter_t iter1, const dll_iter_t iter2)
{
	return (iter1 == iter2 ? TRUE : FALSE);
}

dll_iter_t DLLFind(const dll_iter_t from, const dll_iter_t to, 
				bool (*match_func)(const void *data1, const void *data2), 
				const void *data)
{
	bool status = 0;
	dll_iter_t i_iter = 0;
	
	assert(NULL != to);
	assert(NULL != from); 

	for (i_iter = from; !DLLIsSameIter(i_iter, to); i_iter = DLLNext(i_iter))
	{
		status = match_func(i_iter->data, data);
		
		if (status == TRUE)
		{
			return (i_iter);
		}
	}
	
	/* if data was not found return "to" iter */
	return(i_iter);				
}

status DLLForEach(const dll_iter_t from, const dll_iter_t to, 
				status (*opr_func)(void *operand1, const void *operand2), 
				const void *param)
{
	status opr_func_status = 0;
	dll_iter_t i_iter = 0;

	assert(NULL != from);
	assert(NULL != to);
	
	for (i_iter = from; !DLLIsSameIter(i_iter, to); i_iter = DLLNext(i_iter))
	{
		opr_func_status = opr_func(i_iter->data, param);
		
		if (SUCCESS != opr_func_status)
		{
			break;
		}
	}
	
	return (opr_func_status); 	
}

dll_iter_t DLLSplice(dll_iter_t from, dll_iter_t to, dll_iter_t where)
{
	dll_node_t *temp_for_swap = to->prev;

	assert(NULL != from);
	assert(NULL != to);
	assert(NULL != where);

	/* initialize 'from', 'to', 'where' values and there neighbours's values */
	to->prev->next = where;
	to->prev = from->prev;
	from->prev->next = to;	
	from->prev = where->prev;
	where->prev->next = from;
	where->prev = temp_for_swap;
	
	return (where->prev);	
}
	
size_t DLLMultiFind(const dll_iter_t from, const dll_iter_t to,
					bool (*match_func)(const void *data1, const void *data2),
					const void *data, dll_t *dest)
{
	/* basic iterator to loop on */
	dll_iter_t i_iter = NULL;
	size_t count = 0;

	assert(from);
	assert(to);
	assert(dest);

	/* iterate 'to'-'from' and if there's a match copy node to the dest list */
	for (i_iter = from; !DLLIsSameIter(i_iter, to); i_iter = DLLNext(i_iter))
	{
		if (TRUE == match_func(i_iter->data, data))
		{
			DLLInsert(DLLBegin(dest), i_iter->data);
			++count;
		}
	}

	return (count);
}

/***********utility functions************/

/* the function recieve void pointer to data.
	allocate memory for new node and initialize: 
	data- with reciving data argument 
	pointer to next node- with NULL
	pointer to prev node- with NULL.
	return pointer to the new node */
static dll_node_t *CreateNodeHelp(void *new_data)
{
	dll_node_t *new_node = (dll_node_t *)malloc(sizeof(dll_node_t));
	
	/* check if allocation failed */
	if (NULL == new_node)
	{
		return (NULL);
	}
	
	new_node->data = new_data;
	new_node->prev = NULL;
	new_node->next = NULL;
	
	return (new_node);	
}




