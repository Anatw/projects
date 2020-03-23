/*******************************************************************************
* file name: fixed_size_allocation.c	     	               				   *
* last update: 2020-03-22 Yoni Naor											   *
* reviewer:	Anat Wax     									    	   		   *
*******************************************************************************/
#include <stddef.h> /* size_t */
#include <assert.h> /* assert */

#include "fixed_size_allocation.h"

#define WORD (sizeof(size_t)) /* size of WORD */

struct fixed_size_allocation /* managing sruct for a memory pool */
{
      size_t block_size;
      size_t num_blocks;
      size_t next_free;
};

typedef struct block_header
{
        size_t next_free;   /* Offset (in bytes) from the start of the FSA. */
} block_t;

size_t FSASuggestSize(size_t num_blocks, size_t block_size)
{
	size_t suggested_size = 0;

	block_size = ((block_size - 1) / WORD + 1) * WORD;
 	suggested_size = num_blocks*(block_size + sizeof(block_t)) + sizeof(fsa_t);

	return (suggested_size);		
}

fsa_t *FSAInit(void *memory, size_t seg_size, size_t block_size)
{
	fsa_t *memory_pool = NULL;
	block_t *block_ptr = NULL;	
	char * byte_ptr = NULL;
	unsigned int i = 0;
	size_t offset = sizeof(fsa_t);	
	size_t block_offset = 0; 
	
	assert(memory);
	memory_pool = (fsa_t *)memory;

	block_size = ((block_size - 1) / WORD + 1) * WORD;

	block_offset = block_size + sizeof(block_t);	/* size of b_header + block */

	memory_pool->block_size = block_size;

	memory_pool->num_blocks = (seg_size - sizeof(fsa_t)) / (block_offset);

	memory_pool->next_free = offset;
	
	for(i = 0; i < memory_pool->num_blocks; ++i)
	{
		offset = memory_pool->next_free + i * (block_offset);  
		byte_ptr = (char *)memory_pool + offset;
		block_ptr = (block_t *)byte_ptr;
		
		block_ptr->next_free = offset + block_offset;	
	}	
		block_ptr->next_free = 0;
			
	return (memory_pool);			
}

void *FSAAlloc(fsa_t *fsa_pool)
{
	char *ptr_byte = NULL;
	block_t *ptr_block = NULL;
	
	assert(fsa_pool);	

	if(fsa_pool->next_free == 0)	
	{
		return NULL;
	}

	ptr_byte = (char *)fsa_pool + fsa_pool->next_free; 
	ptr_block = (block_t *)ptr_byte;

	ptr_block->next_free = ptr_block->next_free + fsa_pool->next_free;
	fsa_pool->next_free = ptr_block->next_free - fsa_pool->next_free;
	ptr_block->next_free = ptr_block->next_free - fsa_pool->next_free;

	return ((void *)(ptr_block + 1));
}

void FSAFree(void *block_ptr)
{
	block_t *block = (block_t *)block_ptr - 1;
	fsa_t *fsa_p =(fsa_t *)((char*)block - block->next_free);
	
	assert(block_ptr);
	
	fsa_p->next_free ^= block->next_free;
	block->next_free ^= fsa_p->next_free;
	fsa_p->next_free ^= block->next_free;
}

size_t FSACountFree(const fsa_t *fsa_pool)
{
	char *byte_ptr = NULL;
	block_t *block_ptr = NULL;
	size_t count = 0;
	
	if(0 == fsa_pool->next_free)
	{
		return count;
	}

	byte_ptr = (char *)fsa_pool + fsa_pool->next_free;	
	block_ptr = (block_t *)byte_ptr;	
	++count;
	while(block_ptr->next_free != 0)
	{
		++count;
		byte_ptr = (char *)fsa_pool + block_ptr->next_free;	
		block_ptr = (block_t *)byte_ptr;
	}	
					
	return (count);	
}

