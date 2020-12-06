/*******************************************************************************

Written by Anat Wax, anatwax@gmail.com
Created: 15.6.20
Reviewer:
*******************************************************************************/
#include <assert.h> /* assert() */
#include <stdio.h>  /* printf(), size_t */
#include <stdlib.h> /* malloc(), free(), abs(), size_t */
#include <string.h> /* size_t, atoi(), memset() */

typedef struct Node
{
    char* data;
    struct SLL* next;
} node_t;

typedef struct SLL
{
    node_t* head;
    node_t* last_node;
} sll_t;

sll_t* SLLInit()
{
    sll_t* list = (sll_t*)malloc(sizeof(sll_t));
    list->head = NULL;
    list->last_node = NULL;

    return (list);
}

node_t* SLLCreateNode(char* data)
{
    node_t* node = (node_t*)malloc(sizeof(node_t);
    node->data = data;
    node->next = NULL;

    return (node);
}

void SLLInsertNode(sll_t* list, char* data)
{
    if (list->head == NULL)
    {
        list->head = SLLCreateNode(data);
        list->last_node = head->next;
    }
    else
    {
        list->last_node->
    }
}

void PushBack()
{
    //
}

/******************************************************************************/

typedef struct Hash
{
    sll_t** array;

    size_t capacity;
    int (*hash_func)(char* key);
} hash_t;

hash_t* HashInit(size_t capacity, int (*hash_func)(char* key))
{
    hash_t* hash = (hash_t*)malloc(sizeof(hash_t));
    if (!hash)
    {
        perror("ERROR in malloc() hashInit()");
        exit(EXIT_FAILURE);
    }

    hash->array = (sll_t**)calloc(capacity, sizeof(sll_t*));
    if (!hash->array)
    {
        free(hash);
        hash = NULL;

        perror("ERROR in hash->array malloc() hashInit()");
        exit(EXIT_FAILURE);
    }

    hash->capacity = capacity;
    hash->hash_func = hash_func;

    return (hash);
}

void HashInsert(hash_t* hash, char* str)
{
    // retrievce key from hash_func and insert into the hash.
    int key = hash->hash_func(str);

    PushBack(hash->array[key], str);
}

char* NewToken(size_t length)
{
    char* token = (char*)malloc(sizeof(char) * length);

    return (token);
}

void DeleteToken(char* token)
{
    free(token);
    token = NULL;
}

hash_t* Tokenise(char* str, size_t length)
{
    size_t token_l = length / 2;
    size_t i = 0;
    size_t j = 0;
    char* token = NewToken(token_l);
    hash_t* hash = HashInit((token_l)*1.3, hash_func);

    while (i < length)
    {
        while (*(str + i) != ';')
        {
            token[j++] = str[i++];
        }

        token[j++] = '\0';
        HashInsert(hash, token);
        ++i;
        j = 0;
    }

    free(token);
    token = NULL;

    return (hash);
}

int main()
{
    char* str = "hey;good;morning";
    size_t length = strlen(str);

    Tokenise(str, length);

    return (0);
}
