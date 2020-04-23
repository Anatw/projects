#include <stdio.h>  /* printf(), size_t */
#include <assert.h> /* assert() */
#include <string.h> /* size_t, atoi() */

#include "hash_table.h"
#include "doubly_linked_list.h"

#define SIZE (350000)
#define HASH (5381)
#define K_HASH (33)

/* a struct of a single element that I can send to the ForEach function: */
typedef struct
{
    size_t key;
    char data[35];
} single_element;

int CmpFunc(const void *first, const void *second);
size_t HashFunc(const void *data);
int AddChar(void *param, const void *data);
int StringChange(void *data, const void *param);

int main()
{
    char *data1 = "string";
    char *data2 = "stringi string";
    char *character = "wohoo";
    hash_t *hash_table = HashCreate(CmpFunc, HashFunc, SIZE);

    printf("hash table is%s empty\n", (HashIsEmpty(hash_table) ? "" : " not"));
    printf("the size of the has table is %ld nodes.\n", HashSize(hash_table));
    HashInsert(hash_table, data1);
    HashInsert(hash_table, data2);
    printf("the size of the has table is %ld nodes.\n", HashSize(hash_table));
    printf("hash table is%s empty\n", (HashIsEmpty(hash_table) ? "" : " not"));

    printf("the hash load is %f\n", HashLoad(hash_table));
    printf("the hash standard deviation is %f\n", HashSD(hash_table));

    HashForEach(hash_table, AddChar, character);

    HashRemove(hash_table, data1);

    printf("the size of the has table is %ld nodes.\n", HashSize(hash_table));

    printf("%c\n", *(char *)DLLGetData(HashFind(hash_table, data2)));

    HashDestroy(hash_table);

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

int StringChange(void *data, const void *param)
{
    assert(param);

    strcat(((single_element *)data)->data, param);

    return (0);
}


int AddChar(void *param, const void *data)
{
    strcat((char *)data, param);
	
	return (0);
}
