/*******************************************************************************
* file name: fixed_size_allocation_test.c     	               				   *
* last update: 2020-03-22 Yoni Naor											   *
* reviewer:	Anat Wax     									    	   		   *
*******************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "fixed_size_allocation.h"

int main()
{
	size_t block1 = 10;
	size_t num_blocks1 = 5;
	size_t size_sug = FSASuggestSize(num_blocks1, block1);
	void *memory = (void *)malloc(size_sug);
	fsa_t *struct_ptr = NULL;

	char string1[] = "aaaaaaaaa";
	char string2[] = "bbbbbbbbb";
	char string3[] = "ccccccccc";
	char string4[] = "ddddddddd";
	char *ptr_1 = NULL;
 	char *ptr_2 = NULL;
	char *ptr_3 = NULL;
	char *ptr_4 = NULL; 
  int count = 0;
	printf("pool size suggested for %lu blocks of size %lu is %lu\n",
 			num_blocks1, block1, size_sug);

	struct_ptr = FSAInit(memory, size_sug, block1); 
	
	printf("free blocks: %lu\n", FSACountFree(struct_ptr));
	ptr_1 = FSAAlloc(struct_ptr);	
	ptr_2 = FSAAlloc(struct_ptr);	
	ptr_3 = FSAAlloc(struct_ptr);	
	ptr_4 = FSAAlloc(struct_ptr);	

	printf("free blocks after allocating 4 blocks: %lu\n", FSACountFree(struct_ptr));
	do
	{
		*(ptr_1 + count) = *(string1 +count);
		++count;	
	}
	while(count < 10);

	printf("%s\n", ptr_1);		

	count = 0;
	do
	{
		*(ptr_2 + count) = *(string2 +count);
		++count;	
	}

	while(count < 10);

	printf("%s\n", ptr_2);		

count = 0;
	do
	{
		*(ptr_3 + count) = *(string3 +count);
		++count;	
	}

	while(count < 10);

	printf("%s\n", ptr_3);		

count = 0;
	do
	{
		*(ptr_4 + count) = *(string4 +count);
		++count;	
	}

	while(count < 10);

	printf("%s\n", ptr_4);		

	FSAFree(ptr_2);
	printf("free blocks after allocating 4 blocks and freeing 1: %lu\n", 				
			FSACountFree(struct_ptr));		
		
	free(memory);


	return (0);
}
