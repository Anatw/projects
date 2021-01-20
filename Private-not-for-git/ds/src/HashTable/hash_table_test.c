/*******************************************************************************
the hash table is an array of dll_t variables.

					  		 Written by Anat Wax
						   23-25 of April, 2020
							Reviewer: Esti Binder
*******************************************************************************/
#include <stdio.h>  /* printf(), size_t */
#include <assert.h> /* assert() */
#include <string.h> /* size_t, atoi() */
#include <stdlib.h> /* malloc(), free(), abs() */

#include "hash_table.h"
#include "doubly_linked_list.h"

#define SIZE (102305)
#define BASIC_SIZE (7)
#define HASH (5381)
#define K_HASH (33)
#define FREE(x) ((free(x), (x = NULL)))
#define UNUSED(x) (void)(x)
#define WORD_SIZE (30)

int HashCmpFunc(const void *first, const void *second);
static size_t HashFunc(const void *data);
void LinuxDictionaryTests();
void BasicTests();
int HashPrintWord(void *data, void *param);
size_t HashKeyBasicTests(const void *data);


int main()
{
    BasicTests();
    LinuxDictionaryTests();

    return (0);
}

/******************************************************************************/

int HashCmpFunc(const void *first, const void *second)
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

/******************************************************************************/

static size_t HashFunc(const void *data)
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
    key = key % SIZE;

    return (key);
}

/******************************************************************************/

size_t HashKeyBasicTests(const void *data)
{
    size_t key = 0;
    
    assert(data);

    key = *(size_t *)data;
    key = key % BASIC_SIZE;

    return (key);
}

/******************************************************************************/

int HashPrintWord(void *data, void *param)
{  
    UNUSED(param);
    printf("%s\n", data);

    return (0);
}

/******************************************************************************/

void BasicTests()
{
    char *data1 = "a string";
    char *data2 = "stringi string";
    char *character = "wohoo";
    hash_t *hash_table = HashCreate(HashCmpFunc, HashKeyBasicTests, BASIC_SIZE);

    printf("table is%s empty\n", (HashIsEmpty(hash_table) ? "" : " not"));
    printf("the size of the hash table is %ld nodes.\n", HashSize(hash_table));
    HashInsert(hash_table, data1);
    HashInsert(hash_table, data2);
    printf("the size of the has table is %ld nodes.\n", HashSize(hash_table));
    printf("_table table is%s empty\n", (HashIsEmpty(hash_table) ? "" : " not"));

    printf("the _table load is %f\n", HashLoad(hash_table));
    printf("the _table standard deviation is %f\n", HashSD(hash_table));

    printf("HashForEach:\n");
    HashForEach(hash_table, HashPrintWord, character);

    printf("HashRemove:\n");
    HashRemove(hash_table, data1);

    printf("the size of the has table is %ld nodes.\n", HashSize(hash_table));

    printf("%c\n", *(char *)(HashFind(hash_table, data2)));
    printf("HashDestroy:\n");
    HashDestroy(hash_table);
    printf("Basic tests ended!\n\n");
}

/******************************************************************************/

void LinuxDictionaryTests()
{
    hash_t *new_hash = HashCreate(HashCmpFunc, HashFunc, SIZE);
	char **dictionary = (char **)malloc(sizeof(char *) * SIZE);
	FILE *fp = fopen("/usr/share/dict/american-english", "r");
    int i = 0;
    char words[WORD_SIZE] = {0};
    int check = 0;
    int length = 0;
	
	for (i = 0; i < SIZE; ++i)
	{
		fscanf(fp, "%s", words);
		length = strlen(words);
		dictionary[i] = (char *)malloc(sizeof(char) * (length + 1));
		strcpy(dictionary[i], words);
	}
	
	fclose(fp);
	
	for (i = 0; i < SIZE; ++i)
	{
		HashInsert(new_hash, dictionary[i]);
	}


	printf("After putting the dictionary, the hash table is NOT empty (0): ");
	printf("%d\n", HashIsEmpty(new_hash));
	printf("And it's size is (%d): %ld\n\n", SIZE, HashSize(new_hash));
	
	printf("The Hash Load is: %f\n", HashLoad(new_hash));
	printf("And the SD is: %f\n", HashSD(new_hash));

	printf("\n\nPress Enter to continue\n");
	fgets(words, 2, stdin);
	system("clear");
	
	while (0 == check)
	{
		printf("\n\n\t\t\tEnter a word to look for, or 'QUIT' to exit\n");
		printf("\t\t\t\t\t\n");
		scanf("%s", words);
		system("clear");
		if (0 == strcmp(words, "QUIT"))
		{
			check = 1;
		}
		else if (NULL == HashFind(new_hash, words))
		{
			printf("\n\n\t\t\t%s\n\n", words);
			printf("\t\t\tWord Not Found\n");
		}
		else
		{
			printf("\n\n\t\t\t%s\n\n", words);
			printf("\t\t\tWord Found\n");
		}	
	}
    
    for (i = 0; i < SIZE; ++i)
	{
		free(dictionary[i]);
	}
	
	free(dictionary);
	dictionary = NULL;

	HashDestroy(new_hash);
}