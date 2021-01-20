#include <stdlib.h> /* size_t */
#include "assert.h"
#include <stdio.h> /* temp - just for writing -  should be deleted!! */

#include "fixed_size_allocation.h"
#define WORD (sizeof(void *))

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


size_t FSASuggestSize(size_t num_blocks, size_t block_size)
{
	size_t size_needed = sizeof(fsa_t) + (num_blocks * sizeof(block_t)
    					 + (num_blocks * block_size));
    if (WORD < block_size)
    {
    	size_needed += (num_blocks * (block_size % WORD));
    }
    else
    {
    	size_needed += (num_blocks * (WORD - block_size));
    }

    return (size_needed);
}

fsa_t *FSAInit(void *memory, size_t seg_size, size_t block_size)
{
	fsa_t *memory_pool = (fsa_t *)memory;
	size_t block_counter = 0; /* count the blocks */
	int modulus = (block_size > WORD ? block_size % WORD : (WORD - block_size));
	size_t bytes_counter = sizeof(fsa_t) + sizeof(block_t) + block_size + modulus;
	block_t *b_header = (block_t *)memory_pool;
	block = (block_t
	int i = 2;
	
	memory_pool->block_size = block_size;
	memory_pool->next_free = sizeof(fsa_t);
	b_header->next_free = sizeof(fsa_t) + sizeof(block_t) + ;
	printf("the first free block is in: %ld\n", b_header->next_free);
	
	for (; bytes_counter != seg_size; ++block_counter)
	{
		bytes_counter += sizeof(block_t);
		b_header->next_free += block_size + sizeof(block_t);
		bytes_counter += block_size + modulus;
		bytes_counter += ;
		printf("the %d next free block is in: %ld\n", i, b_header->next_free);
		++i;
	}
	
	b_header->next_free = (size_t)NULL;
	printf("the last free block is in: %ld\n", b_header->next_free);
	memory_pool->num_blocks = block_counter;
	
	return (memory_pool);
}


void *FSAAlloc(fsa_t *fsa_pool)
{
	assert(fsa_pool);
	
	return ((void *)fsa_pool->next_free);
}

void FSAFree(void *block_ptr)
{
	size_t temp = 0;
	size_t block_size = 0;
	block_t header = 0;
	
	/* i need to get to the fsa manager and than swap bwtween its next and
	 * the block_ptr next */
	header = block_ptr - sizeof(block_t);
	block_ptr - sizeof(block_t) = block_ptr->next_free; /* signing the block as free */
	block_size = block_ptr->next_free - &*block_ptr;
	&*block_ptr - 
	temp = fsa_pool->next_free;
	fsa_pool->next_free = block_ptr->next_free;
	block_ptr->next_free = temp;
}
/*
size_t FSACountFree(const fsa_t *fsa_pool)
{
	size_t temp = 0;
	size_t counter = 0;
	
	temp = fsa_pool->next_free;
	temp = 
}*/
