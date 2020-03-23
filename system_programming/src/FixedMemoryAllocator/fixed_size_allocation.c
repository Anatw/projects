/*******************************************************************************
					  	 Written by Anat Wax
						    March 19-22, 2020
						Reviewer: Dean Oron
*******************************************************************************/
#include <stdlib.h> /* size_t */
#include "assert.h" /* assert() */
#include <stdio.h> /* temp - just for writing -  should be deleted!! */

#include "fixed_size_allocation.h"
#define WORD (sizeof(void *))

void SwapValues(size_t *value1, size_t *value2);

struct fixed_size_allocation
{
    size_t block_size;
    size_t num_blocks;
    size_t next_free;
}; /* fsa_t */

typedef struct block_header
{
    size_t next_free;   /* Offset (in bytes) from the start of the FSA. */
} block_t;

/******************************************************************************/

size_t FSASuggestSize(size_t num_blocks, size_t block_size)
{
	size_t size_needed = sizeof(fsa_t) + (num_blocks * sizeof(block_t) +
    					 ((((block_size - 1) / WORD) + 1) * WORD * num_blocks));
  
    return (size_needed);
}

/******************************************************************************/

fsa_t *FSAInit(void *memory, size_t seg_size, size_t block_size)
{
	fsa_t *memory_pool = (fsa_t *)memory;
	block_t *b_header = NULL;
	size_t block_counter = 0;
	size_t bytes_counter = sizeof(fsa_t);
	char *byte_p = NULL;
	int i = 1; /* helping variable for printf - just for writing phase */
	
	assert(memory);
	
	memory_pool->block_size = ((((block_size - 1 ) / WORD) + 1) * WORD) + 
							  sizeof(block_t);
	memory_pool->next_free = sizeof(fsa_t);
	
	printf("size f block size: %ld\n", memory_pool->block_size);
	
	for (bytes_counter = memory_pool->next_free ;
		 bytes_counter < seg_size;
		 ++block_counter, bytes_counter += memory_pool->block_size)
	{
		byte_p = (char *)memory_pool;
		byte_p += bytes_counter;
		b_header = (block_t *)byte_p;
		b_header->next_free = bytes_counter + memory_pool->block_size;
		
		printf("the next free block (%d) is in: %ld\n", i, b_header->next_free);
		++i;
	}
	
	b_header->next_free = (size_t)NULL;
	memory_pool->num_blocks = block_counter;
	
	printf("the last free block is now: %ld\n", b_header->next_free);
	
	return (memory_pool);
}

/******************************************************************************/

void *FSAAlloc(fsa_t *fsa_pool)
{
	block_t *free_block = NULL;
	char *p_byte = NULL;
	
	assert(fsa_pool);
	
	if(size_t(NULL) == fsa_pool->next_free)
	{
		return NULL;
	}

	p_byte = (char *)fsa_pool;
	p_byte += fsa_pool->next_free;
	free_block = (block_t *)p_byte;
	
	SwapValues(&fsa_pool->next_free, &free_block->next_free);
	
	return (p_byte + sizeof(block_t));
}

/******************************************************************************/

/* Move to the fsa manager (the header is pointing ti itself, hence we have the
 * distance to the fsa) and than swap bwtween its next and the block_ptr next */
void FSAFree(void *block_ptr)
{
	block_t *block_to_free = (block_t *)block_ptr - sizeof(block_t);
	fsa_t *memory_pool = NULL;
	char *p_byte = (char *)block_to_free;
	
	p_byte -= block_to_free->next_free;
	memory_pool = (fsa_t *)p_byte;
	
	SwapValues(&memory_pool->next_free, &block_to_free->next_free);
}

/******************************************************************************/

/* run through the "next->free" until it point to 0, and count as it goes. */
size_t FSACountFree(const fsa_t *fsa_pool)
{
	size_t counter = 0;
	size_t offset = 0;
	block_t *next_block = NULL;
	char *p_byte = (char *)fsa_pool;
	
	offset = fsa_pool->next_free;
	p_byte += fsa_pool->next_free;
	next_block = (block_t *)p_byte;

	while ((size_t)NULL != offset)
	{
		++counter;
		
		p_byte = (char *)fsa_pool;
		p_byte += offset;
		next_block = (block_t *)p_byte;
		offset = next_block->next_free;
	}

	return (counter);
}

/******************************************************************************/

/* helping function - for use in FSAAlloc and FSAFree */
void SwapValues(size_t *value1, size_t *value2)
{
	*value1 += *value2;
	*value2 = *value1 - *value2;
	*value1 -= *value2;
}
