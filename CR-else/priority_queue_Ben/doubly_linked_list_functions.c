/******************************************************************************/
/*                                                                            */
/*                     Doubly Linked List Functions File                      */
/*                           Data Structures                                  */
/*                              09/03/2020                                    */
/*                        Author: Ben David Zikri                             */
/*                        Reviwer: Yaaccov Evenchik                           */
/*                                                                            */
/******************************************************************************/

#include <stdlib.h> /* size_t, malloc(), free() */
#include <assert.h> /* assert() */
#include <stdio.h> /* printf() */

#include "doubly_linked_list.h"

#define FREE(p) (free((p)), (p) = NULL)

typedef struct dll_node {
	void *data;
	struct dll_node *next;
	struct dll_node *prev;
}dll_node_t;

struct doubly_linked_list
{
	dll_node_t head;
	dll_node_t tail;
};

dll_node_t *CreateNode(void *data); /* Helper Function */
void PrintList(const dll_t *list); /* Helper Function */


dll_t *DLLCreate(void)
{								/* Allocating memory to list */
	dll_t *list = (dll_t *)malloc(sizeof(dll_t));

	/* The dummy data member contains the address of the list for further use */
	if(NULL == list) 
	{
		return (NULL);
	}


	list->head.next = &list->tail; /* Set head to point tail */
	list->head.data = list->head.prev = NULL;

	list->tail.prev = &list->head; /* Set tail to point head */
	list->tail.data = list->tail.next = NULL;
	

	return (list);
}

void DLLDestroy(dll_t *list)
{
	assert(NULL != list);

	while(!DLLIsEmpty(list))
	{
		DLLPopFront(list);
	}

	FREE(list); /* Free list itself */
}

dll_iter_t DLLInsert(dll_iter_t iter, void *data)
{
	dll_node_t *new_node = CreateNode(data);

	if (NULL == new_node)
	{			/* If allocation failed traverese untill the end of the list */
		while (NULL != iter->next)
		{
			iter = DLLNext(iter);
		}
		
		return (iter);
	}

	new_node->next = iter;
	new_node->prev = iter->prev;
	iter->prev = new_node;
	new_node->prev->next = new_node;

	return (new_node);
}

dll_iter_t DLLPushFront(dll_t *list, void *data)
{
	return ((DLLInsert(DLLBegin(list), data)));
}

dll_iter_t DLLPushBack(dll_t *list, void *data)
{
	return ((DLLInsert(DLLEnd(list), data)));
}


void *DLLPopFront(dll_t *list)
{
	void *data = DLLGetData(DLLBegin(list));

	DLLRemove(DLLBegin(list));

	return (data);
}


void *DLLPopBack(dll_t *list)
{
	void *data = DLLGetData(DLLPrev(DLLEnd(list)));

	DLLRemove(DLLPrev(DLLEnd(list)));

	return (data);
}

dll_iter_t DLLBegin(const dll_t *list)
{
	assert(NULL != list);

	return (list->head.next);
}

dll_iter_t DLLEnd(const dll_t *list)
{
	assert(NULL != list);

	return ((dll_iter_t)&list->tail);
}

void *DLLGetData(const dll_iter_t iter)
{
	assert(NULL != iter);

	return (iter->data);
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

int DLLIsEmpty(const dll_t *list)
{

	assert(NULL != list);

	return (list->head.next == &list->tail);
}

dll_iter_t DLLRemove(dll_iter_t iter)
{
	dll_iter_t temp = iter->next;

	iter->next->prev = iter->prev;
	iter->prev->next = iter->next;

	FREE(iter);

	return (temp);
}

size_t DLLSize(const dll_t *list)
{
	size_t count = 0;
	dll_iter_t i = DLLBegin(list);

	assert(NULL != list);

	for (; !DLLIsSameIter(i, DLLEnd(list)); i = DLLNext(i), ++count)
		; /* No body loop */

	return (count);
}

void DLLSetData(dll_iter_t iter, const void *new_data)
{
	assert(NULL != iter);

	iter->data = (void *)new_data;
}

int DLLIsSameIter(const dll_iter_t iter1, const dll_iter_t iter2)
{
	assert(NULL != iter1 || NULL != iter2);

	return (iter1 == iter2);
}

dll_iter_t DLLFind(const dll_iter_t from, const dll_iter_t to, 
				 int (*MatchFunc)(void *data1, void *data2), const void *param)
{
	dll_iter_t i = from;

	assert(from && to && param);

	for (; !DLLIsSameIter(i, to); i = DLLNext(i))
	{
		if(MatchFunc(i->data, (void *)param)) /* Check for matching with data */
		{	
			return(i);
		}
	}

	return (to); /* If couldn't find match return the last element in range */
}

int DLLForEach(const dll_iter_t from, const dll_iter_t to, 
				int (*OprFunc)(void *, void *), const void *param)
{
	int status = 1;
	dll_iter_t i = from;

	assert(from && to && param);

	   /* Traverse the list from given iterator 'from' to given iterator 'to' */
	for (; !DLLIsSameIter(i, to); i = DLLNext(i))
	{					                  /* Perform OprFunc for each element */
		status = OprFunc(DLLGetData(i), (void *)param);
	}

	return (status);
}

size_t DLLMultiFind(const dll_iter_t from, const dll_iter_t to, 
	 const void *param, int (*MatchFunc)(void *data1, void *data2), dll_t *dest)
{
	size_t count = 0;
	dll_iter_t i = from;
	
	assert(from && to && dest);

	for (; !DLLIsSameIter(i, to); i = DLLNext(i))
	{
		if(MatchFunc((void *)param, DLLGetData(i)))
		{
			DLLPushFront(dest, DLLGetData(i)); /* Copying to 'dest' */
			++count;
		}
	}

	return (count);
}

dll_iter_t DLLSplice(dll_iter_t from, dll_iter_t to, dll_iter_t where)
{ 
	dll_iter_t last_node = DLLPrev(to); /* new pointer to 1 before 'to' */

	assert(from && to && where);

	from->prev->next = to;    /* skipping over 'from' and 'to' in place*/
	to->prev = DLLPrev(from);

	from->prev = DLLPrev(where); /* Connecting the element in range - */
	last_node->next = where;     /* 'from' and 'to'  with 'where' location */
	where->prev->next = from;
	where->prev = last_node;

	return (last_node);
}


/*******************************************************************************
                             Helper Functions
*******************************************************************************/

dll_node_t *CreateNode(void *new_data)
{
	dll_node_t *new_node = (dll_node_t *)malloc(sizeof(dll_node_t));
	
	if(NULL == new_node)
	{
		return (NULL);
	}

	new_node->data = new_data;
	new_node->next = NULL;
	new_node->prev = NULL;

	return (new_node);
}

void PrintList(const dll_t *list)
{
	dll_iter_t i = DLLBegin(list);

	printf("\t");

	while(DLLNext(i))
	{
		printf("%d -> ", *(int *)(DLLGetData(i)));
		i = DLLNext(i);
	}

	printf("NULL\n");
}


	