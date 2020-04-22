#include <stdio.h> /* printf(), size_t */
#include <assert.h> /* assert() */
#include <string.h> /* size_t, atoi() */

#include "hash_table.h"

#define SIZE (350000)
#define HASH (5381)
#define K_HASH (33)

int CmpFunc(const void *first, const void *second);
size_t HashFunc(const void *data);


int main()
{
    hash_t *hash_table = HashCreate(CmpFunc, HashFunc, SIZE);



return (0);
}


int CmpFunc(const void *first, const void *second)
{
	if (*(int *)first > *(int *)second)
	{
		return (1);
	}
	else if (*(int *)first < *(int *)second)
	{
		return (-1);
	}
	else
	{
		return (0);
	}
}

size_t HashFunc(const void *data)
{
    const char *new_data = NULL;
    int size = 0;
    int character = 0;
    size_t key = 0;
    int i = 0;
    assert(data);
    
    new_data = (const char *)data;
    character = *new_data;
    size = strlen(data);

    for (i = 0; i < size; ++i, ++new_data)
    {
        key = ((HASH << 5) + HASH) + character;
    }

    return (key);
}