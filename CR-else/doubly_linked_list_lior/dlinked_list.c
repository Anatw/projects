/****************************************************************************
* File Name: dlinked_list.c													*
* Writer: Lior Cohen														*
* Date: 08/03/2020														    *
* Purpose: The functions for the double linked list assignement				*
* Code reviewer: Haim Saadia 												*
*****************************************************************************/

#include <stdlib.h> /* malloc, free */
#include <assert.h> /* assert */

#include "dlinked_list.h"

/* basic node for the linked list */
struct dll_node
{
	void *data;			  	/* data to be stored */
	struct dll_node *next;	/* pointer to next node */
	struct dll_node *prev;	/* pointer to prev node */
};

/* New name for the dll_node struct */
typedef struct dll_node node_t;

/* basic doubly list struct */
struct doubly_linked_list
{
	node_t head;
	node_t tail;
};

/*****************************************************************************/

/* Utility function - at end of file */
static node_t *CreateNode(void *data);

/*****************************************************************************/

dll_t *DLLCreate()
{
	dll_t *new_dll = (dll_t *)malloc(sizeof(dll_t));
	
	if (new_dll == NULL) 
	{
		return (NULL);
	}
	
	new_dll->head.data = NULL;
	new_dll->head.next = &new_dll->tail;
	new_dll->head.prev = NULL;
	
	new_dll->tail.data = NULL;
	new_dll->tail.next = NULL;
	new_dll->tail.prev = &new_dll->head;

	return (new_dll);
}

/*****************************************************************************/

void DLLDestroy(dll_t *list)
{
	assert(NULL != list);

	while ((!DLLIsEmpty(list)) && (NULL != DLLRemove(list->head.next)))
	{
		; /* empty loop */
	}

	free(list);
	list = NULL;
}

/*****************************************************************************/

iter_t DLLPushFront(dll_t *list, void *data)
{
	node_t *new_node = CreateNode(data);

	assert(data);

	/* new_node points to the head */
	new_node->prev = &list->head;

	/* new_node points to the one before it */
	new_node->next = list->head.next;

	/* The previous 'next' points to the new node */	
	list->head.next->prev = new_node;

	/* Head prev points to new_node */	
	list->head.next = new_node;			

	return (new_node);
}

/*****************************************************************************/

void *DLLPopFront(dll_t *list)
{
	void *data = list->head.next->data;
	node_t *temp_ptr = list->head.next;
	iter_t iter = DLLBegin(list);
	
	DLLNext(iter)->prev = &list->head;
	list->head.next = list->head.next->next;
		
	free(temp_ptr);
	temp_ptr = NULL;
	
	return (data);
}

/*****************************************************************************/

iter_t DLLPushBack(dll_t *list, void *data)
{
	node_t *new_node = CreateNode(data);

	assert(data);
	
	/* new_node points to the tail */
	new_node->next = &list->tail;
	
	/* new_node points the one after it */
	new_node->prev = list->tail.prev;
	
	/* Next one prev points to new_node */
	list->tail.prev->next = new_node;
	
	/* Tail next points to new_node */
	list->tail.prev = new_node;

	return (new_node);
}

/*****************************************************************************/

void *DLLPopBack(dll_t *list)
{
	void *data = list->tail.prev->data;
	node_t *temp_ptr = list->tail.prev;
	iter_t iter = DLLPrev(DLLEnd(list));
	
	list->tail.prev = list->tail.prev->prev;
	DLLPrev(iter)->next = &list->tail;
		
		free(temp_ptr);
	temp_ptr = NULL;

	return (data);
}

/*****************************************************************************/

status DLLInsert(iter_t current, void *data)
{
	node_t *new_node = CreateNode(data);
	
	assert(data);
	
	current->prev->next = new_node;
	new_node->next = current;
	new_node->prev = current->prev;
	current->prev = new_node;

	return (SUCCESS);
}

iter_t DLLRemove(iter_t current)
{
	node_t *temp_ptr = current;
	
	current->next->prev = current->prev;
	current->prev->next = current->next;
	
	free(temp_ptr);
	temp_ptr = NULL;

	return (DLLNext(current));
}

/*****************************************************************************/

iter_t DLLBegin(const dll_t *list)
{
	assert(list);

	return (list->head.next);	/* points to the first node after the head */
}

iter_t DLLNext(iter_t current)
{
	assert(current->next);

	return (current->next);
}

iter_t DLLPrev(const iter_t current)
{
	assert(current->prev);

	return (current->prev);
}

iter_t DLLEnd(dll_t *list)
{
	assert(list);

	return (&list->tail);	/* points to tail data which is NULL */
}

bool DLLIsSameIter(const iter_t iter1, const iter_t iter2)
{
	return (iter1 == iter2);
}

/*****************************************************************************/

void *DLLGetData(iter_t current)
{
	assert(current);

	return (current->data);
}	
	
void DLLSetData(iter_t current, void *data)
{
	assert(data);

	current->data = (void *)data;
}

/*****************************************************************************/

size_t DLLSize(dll_t *list)
{
	node_t *current = DLLBegin(list);
	size_t size = 0;
	
	assert(list);
	
	/* while we don't reach the end of the list */
	while (NULL != current->next)
	{
		++size;
		current = current->next;
	}

	return (size);
}


bool DLLIsEmpty(dll_t *list)
{
	assert(list);
	
	return (0 == DLLSize(list));
}

/*****************************************************************************/

iter_t DLLFind(const iter_t from,
				   const iter_t to,
				   const void *data,
                   int (*match_func)(void *, void *))
{
	iter_t i = NULL; /* basic iterator to loop on */

	assert(data);
	assert(match_func);

	/* iterate the whole list */
	for (i = from; !DLLIsSameIter(i, DLLPrev(to)); i = DLLNext(i))
	{
		/* if there's a match return the iterator */
		if (match_func((void *)data, i->data))
		{
			return (i);
		}
	}

	/* if there were no matches return iterator at the 'to' argument */
	return (i);
}

int DLLForEach(iter_t from,
			   iter_t to,
			   void *param,
			   int (*action_func)(void *param, void *data))
{
	iter_t i = NULL; /* basic iterator to loop on 				 */
	int status = 0;		 /* status returned from the action function */

	assert(action_func);

	/* iterate the whole list and invoke the action function on each element */
	for (i = from; !DLLIsSameIter(i, DLLPrev(to)); i = DLLNext(i))
	{
		status = action_func(i->data, (void *)param);
	}

	return (status);
}

/*****************************************************************************/

void DLLSplice(iter_t where1, iter_t begin2, iter_t end2)
{
	end2->next->prev = begin2->prev;
	begin2->prev->next = end2->next;
	
	where1->prev->next = begin2;
	begin2->prev = where1;
	
	where1->prev = end2;
	end2->next = where1;
}

/*****************************************************************************/

size_t DLLMultiFind(iter_t from,
					iter_t to,
					void *data,
					int (*match_func)(void *, void *),
					dll_t *new_list)
{
	iter_t iter = NULL;
	size_t counter = 0;
	
	for (iter = from; !DLLIsSameIter(from, DLLPrev(to)); iter = DLLNext(iter))
	{
		if (match_func((void *)data, iter->data))
		{
			DLLPushBack(new_list, iter->data);
			++counter;
		}
	}

	return (counter);
}













/***** Utility Functions! *****/

static node_t *CreateNode(void *data)
{
	node_t *new_node = (node_t *)malloc(sizeof(node_t));

	/* check if allocation failed */
	if (NULL == new_node)
	{
		return (NULL);
	}

	new_node->data = data;
	new_node->next = NULL;
	new_node->prev = NULL;

	return (new_node);
}

















