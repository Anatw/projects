/*************************************************************************
the hash table is an array of dll_t members
**************************************************************************/
#include <stddef.h> /* offsetof(), size_t */
#include <stdlib.h> /* malloc(), calloc(), free(), size_t, abs() */
#include <assert.h> /* assert() */

#include "hash_table.h"
#include "doubly_linked_list.h"

#define FREE(x) ((free(x), (x = NULL)))

struct hash_table
{
    size_t(*hash_func)(const void *data);
    int(*cmp_func)(const void *data1, const void *data2);
    dll_t **table;
    size_t table_size;
};

/************************* functions: ************************/

hash_t *HashCreate(int (*cmp_func)(const void *data1, const void *data2),
                   size_t (*hash_func)(const void *data),
                   size_t table_size)
{
    hash_t *table_manager = (hash_t *)malloc(sizeof(hash_t));
    size_t i = 0;
    assert (table_size > 0);

    if (NULL == table_manager)
    {
        return (NULL);
    }

    for (i = 0; i < (table_size - 1); ++i)
    {
        table_manager->table[i] = DLLCreate();
        if (NULL ==  table_manager->table[i])
        {
            FREE(table_manager);
            return (NULL);
        }
    }

    table_manager->hash_func = hash_func;
    table_manager->cmp_func = cmp_func;
    table_manager->table_size = table_size;

    return (table_manager);
}

void HashDestroy(hash_t *table)
{
    size_t i = 0;
    assert(table);
    
    for (i = 0; i < table->table_size; ++i)
    {
        DLLDestroy(table->table[i]);
    }

    FREE(table);
}

int HashInsert(hash_t *table, void *data)
{
    size_t key = table->hash_func(data);
    iter_t new_node = NULL;

    new_node = DLLPushBack(table->table[key], data);

    if (NULL == new_node)
    {
        return (1);
    }

    return (0);
}

void HashRemove(hash_t *table, const void *data)
{
    size_t key = 0;
    iter_t iterator = NULL;
    assert(table);

    key = table->hash_func(data);
    iterator = DLLBegin(table->table[key]);

    /* rotate through the dll list and find the given data: */
    while (!DLLIsEmpty(table->table[key]))
    {
        while (0 != table->cmp_func(DLLGetData(iterator), data))
        {
            iterator = DLLNext(iterator);
        }
    }
    
    if (0 == table->cmp_func(DLLGetData(iterator), data))
    {
        DLLRemove(iterator);
    }
}

void *HashFind(const hash_t *table, const void *data)
{
    size_t key = 0;
    iter_t iterator = NULL;
    assert(table);

    key = table->hash_func(data);
    iterator = DLLBegin(table->table[key]);

    while (!DLLIsEmpty(table->table[key]))
    {
        while (0 != table->cmp_func(DLLGetData(iterator), data))
        {
            iterator = DLLNext(iterator);
        }
    }
    
    if (0 == table->cmp_func(DLLGetData(iterator), data))
    {
        return (iterator);
    }
    else
    {
        return (NULL);
    }
}

int HashIsEmpty(const hash_t *table)
{
    assert(table);

    return (0 == HashSize(table) ? 1 : 0);
}
int HashForEach(hash_t *table,
                int (*op_func)(void *data, const void *param),
                const void *param)
{
    size_t i = 0;
    iter_t iterator = 0;
    int status = 0;

    iterator = DLLBegin(table->table[i]);

    for (i = 0; i < table->table_size; ++i, iterator = DLLNext(iterator))
    {
        status = DLLForEach(DLLBegin(table->table[i]), DLLEnd(table->table[i]),
                            op_func, param);
    }

	return (status);
}

size_t HashSize(const hash_t *table)
{
    size_t i = 0;
    iter_t iterator = 0;
    size_t counter = 0;

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

/*
    DLLFind(DLLBegin(table->table[i]), DLLEnd(table->table[i]),
                     data, table->cmp_func(data, DLLGetData(iterator)));
*/