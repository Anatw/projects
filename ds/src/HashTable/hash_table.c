/*******************************************************************************
the hash table is an array of dll_t variables.

					  		 Written by Anat Wax
						   23-25 of April, 2020
							Reviewer: Esti Binder
*******************************************************************************/
#include <stddef.h> /* offsetof(), size_t */
#include <stdlib.h> /* malloc(), calloc(), free(), size_t, abs() */
#include <assert.h> /* assert() */
#include <math.h>   /* pow(), sqrt() */

#include "hash_table.h"
#include "doubly_linked_list.h"

#define FREE(x) (if (NULL != p); (free(x), (x = NULL)))

struct hash_table
{
    size_t (*hash_func)(const void *data);
    int (*cmp_func)(const void *data1, const void *data2);
    dll_t **table;
    size_t table_size;
};

/******************************* functions: ***********************************/

hash_t *HashCreate(int (*cmp_func)(const void *data1, const void *data2),
                   size_t (*hash_func)(const void *data),
                   size_t table_size)
{
    hash_t *table_manager = (hash_t *)malloc(sizeof(hash_t));
    size_t i = 0;
    size_t j = 0;
    assert(table_size > 0);

    if (NULL == table_manager)
    {
        return (NULL);
    }

    table_manager->table = (dll_t **)malloc((sizeof(dll_t *)) * table_size);
    if (NULL == table_manager->table)
    {
        FREE(table_manager);
        
        return (NULL);
    }
    /* creating dll listst insode all array cells */
    for (i = 0; i < table_size; ++i)
    {
        table_manager->table[i] = DLLCreate();
        if (NULL == table_manager->table[i])
        {
            for (j = 0; j < i; ++j)
            {
                DLLDestroy(table_manager->table[j]);
            }
			
            FREE(table_manager);
            
            return (NULL);
        }
    }

    table_manager->hash_func = hash_func;
    table_manager->cmp_func = cmp_func;
    table_manager->table_size = table_size;

    return (table_manager);
}

/******************************************************************************/

void HashDestroy(hash_t *table)
{
    size_t i = 0;
    assert(table);

    for (i = 0; i < table->table_size; ++i)
    {
        DLLDestroy(table->table[i]);
    }

    FREE(table->table);
    FREE(table);
}

/******************************************************************************/

int HashInsert(hash_t *table, void *data)
{
    size_t key = 0;
    iter_t new_node = NULL;

    assert(table);

    key = table->hash_func(data);
    new_node = DLLPushBack(table->table[key], data);

    if (DLLIsSameIter(new_node, DLLEnd(table->table[key])))
    {
        return (1);
    }

    return (0);
}

/******************************************************************************/

void HashRemove(hash_t *table, const void *data)
{
    size_t key = 0;
    iter_t iterator = NULL;
    assert(table);

    key = table->hash_func(data);
    iterator = DLLBegin(table->table[key]);

    /* rotate through the dll list and find the given data: */
    for (;
         !DLLIsSameIter(iterator, DLLEnd(table->table[key]));
         iterator = DLLNext(iterator))
    {
        if (0 == table->cmp_func(DLLGetData(iterator), data))
        {
            DLLRemove(iterator);

            break;
        }
    }
}

/******************************************************************************/

void *HashFind(const hash_t *table, const void *data)
{
    size_t key = 0;
    iter_t iterator = NULL;
    assert(table);

    key = table->hash_func(data);
    iterator = DLLBegin(table->table[key]);

    for (;
         !DLLIsSameIter(iterator, DLLEnd(table->table[key]));
         iterator = DLLNext(iterator))
    {
        if (0 == table->cmp_func(DLLGetData(iterator), data))
        {
            if (DLLEnd(table->table[key]) != DLLPushFront(table->table[key],
                                                          (void *)data))
            {
                DLLRemove(iterator);
                return ((void *)data);
            }
            /* If there was a problem with DLLPushFront - return 
               the data in the last valid node of the current dll: */
            return (DLLGetData(DLLPrev(DLLEnd(table->table[key]))));
        }
    }

    return (NULL);
}

/******************************************************************************/

int HashIsEmpty(const hash_t *table)
{
    assert(table);

    return (0 == HashSize(table) ? 1 : 0);
}

/******************************************************************************/

int HashForEach(hash_t *table,
                int (*op_func)(void *data, void *param),
                const void *param)
{
    size_t i = 0;
    int status = 0;

    assert(table);

    for (i = 0; i < table->table_size; ++i)
    {
        status = DLLForEach(DLLBegin(table->table[i]), DLLEnd(table->table[i]),
                            op_func, param);
        
        if (0 != status)
        {
            break;
        }
    }

    return (status);
}

/******************************************************************************/

size_t HashSize(const hash_t *table)
{
    size_t i = 0;
    iter_t iterator = 0;
    size_t counter = 0;

    assert(table);

    for (i = 0; i < table->table_size; ++i)
    {
        iterator = DLLBegin(table->table[i]);

        while (NULL != DLLGetData(iterator))
        {
            iterator = DLLNext(iterator);
            ++counter;
        }
    }

    return (counter);
}

/******************************************************************************/

double HashLoad(hash_t *table)
{
    assert(table);

    return ((double)HashSize(table) / (double)table->table_size);
}

/******************************************************************************/
/*
 * Steps to calculate standard deviation:
 * 1. calculate the Mean of nodes for the whole table.
 * 2. In every dll list, subtract the Mean from the size of the list and
 *    power the resolt [(n - Mean)^2].
 * 3. Work out the Mean of THOSE numbers...
 */
double HashSD(hash_t *hash)
{
	size_t key = 0;
	double average = 0;
	double total_pow_sum = 0;
	size_t list_size = 0;

	assert(hash);

	average = HashLoad(hash);

	for (key = 0; key < hash->table_size; ++key)
	{
		list_size = DLLSize(hash->table[key]);
		total_pow_sum += pow(list_size - average, 2);
	}

	total_pow_sum /= hash->table_size;

	return (sqrt(total_pow_sum));
}
