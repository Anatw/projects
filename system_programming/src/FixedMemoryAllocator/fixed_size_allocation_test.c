/*******************************************************************************
					  	 Written by Anat Wax
						    March 19-22, 2020
						Reviewer: Dean Oron
*******************************************************************************/
#include <stdlib.h> /* size_t */

#include <stdio.h> /* printf() */
#include <assert.h> /* assert() */

#include "fixed_size_allocation.h"

#define NUM_BLOCKS (6)
#define BLOCK_SIZE (20)
#define FRNL(where) ((free(where)), (where = NULL))

int main()
{
	size_t size_needed = 0;
	fsa_t *mem_pool = 0;
	void *memory = NULL;
	int *data = NULL;
	int array[20] = {1, 2, 3, 4, 5};
	int index = 0;
	
	printf("Creating a new memory block with %d blocks.\n", NUM_BLOCKS);
	printf("The size of each block is %d bytes:\n", BLOCK_SIZE);
	size_needed = FSASuggestSize(NUM_BLOCKS, BLOCK_SIZE);
	printf("%ld\n", size_needed);
	
	memory = malloc(size_needed);
	
	if (NULL == memory)
	{
		printf("allocation problem!!");
		return (1);
	}
	
	printf("alocated at %p\n", memory);
	mem_pool = FSAInit(memory, size_needed, BLOCK_SIZE);
	printf("number of free blocks is %ld\n", FSACountFree(mem_pool));
	
	data = FSAAlloc(mem_pool);
	data = array;
	
	while (index  < (int)(BLOCK_SIZE / sizeof(array[0])))
	{
		printf("%d\n", *(data + index));
		++index;
	}
	
	printf("number of free blocks is %ld\n", FSACountFree(mem_pool));
	/* should give segmentation fault:
	FSAFree(data);
	
	while (index  < 20)
	{
		printf("%d\n", *(data + index));
		++index;
	}
	*/
	
	FRNL(mem_pool);
		
	return (0);
}
