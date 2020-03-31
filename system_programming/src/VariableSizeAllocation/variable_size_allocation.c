/*******************************************************************************
* Note: Due to efficiency reasons, there are no user protection in the
functions, and all the validations are the responsibility of the user.

					  	 Written by Anat Wax
						    March 23-25, 2020
						Reviewer: Ben-David Zikri
*******************************************************************************/
#include <sys/types.h> /* size_t, ssize_t */
#include <stdlib.h> /* NULL */
#include <assert.h> /* assert() */

#include "variable_size_allocation.h"

/* the biggest number ssize_t can hold, minus 1: */
#define LASTBLOCK (4611686018427387902)
/* ment to validate that the block is a header: */
#define ISHEADER (533422123455553342)
#define SWITCHMODE (-1)
#define WORD (sizeof(void *))

struct block_header
{
	ssize_t block_size; /* positive value = free; negetive value = not free */
	#ifndef ND
	long valid; /* ment to validate that we point to a header and not data */
	#endif
};

/******************************** functions: **********************************/

block_t *VSAInit(void *memory, size_t seg_size)
{
	vsa_t *vsa_pool = NULL;
	block_t *last_block = NULL;
	char *byte_p = NULL;
	
	/* set the block size to word size so that the inner blocks 
	 * will be alligned: */
	size_t new_seg = seg_size - (seg_size % WORD); 
	
	assert(memory);
	
	vsa_pool = (vsa_t *)memory;
	/* size - begin and end blocks: */
	vsa_pool->block_size = new_seg - (sizeof(vsa_t) * 2);
	
	byte_p = (char *)vsa_pool;
	byte_p += vsa_pool->block_size + sizeof(vsa_t); 
	last_block = (block_t *)byte_p;
	last_block->block_size = LASTBLOCK;
	
	#ifndef NDEBUG
	last_block->valid = ISHEADER;
	vsa_pool->valid = ISHEADER;
	#endif /*NDEBUG */

	return (vsa_pool);
}

/******************************************************************************/

void *VSAAlloc(vsa_t *vsa_pool, size_t size_needed)
{
	char *byte_p = NULL;
	block_t *block_p = NULL;
	block_t *new_block = NULL;
	size_t temp_block_size = 0;
	size_needed = (((size_needed - 1) / WORD) + 1) * WORD;
	
	assert(vsa_pool);
	
	/* move all pointer to the beginning of the memory pool: */
	byte_p = (char *)vsa_pool;
	block_p = vsa_pool;
	new_block = vsa_pool;
	
	/* if there is no block big enoughh for size_needed */
	if (VSALargestBlockAvailable(vsa_pool) < (size_t)size_needed)
	{
		return (NULL);
	}

	while (LASTBLOCK != block_p->block_size)
	{
		/* block is free but not enough for size_needed */
		while (0 < block_p->block_size &&
			   size_needed > (block_p->block_size + temp_block_size) && 
			   LASTBLOCK != block_p->block_size)
		{
			byte_p += block_p->block_size + sizeof(block_t);
			new_block = (block_t *)byte_p;
			
			if (0 < new_block->block_size)
			{
				block_p->block_size += new_block->block_size + sizeof(block_t);
			}
			else
			{
				byte_p = (char *)block_p;
			
				break;
			}
		}
		
		/* block is bigger than size_needed - split block */
		if (block_p->block_size > (ssize_t)(size_needed + sizeof(block_t)))
		{
			byte_p += size_needed + sizeof(block_t);
			new_block = (block_t *)byte_p;
			
			/* create a new header inside the block */
			new_block->block_size = labs(block_p->block_size) - size_needed -
									sizeof(block_t);
			#ifndef ND				
			new_block->valid = ISHEADER;
			#endif /* ND */
			
			block_p->block_size = size_needed * SWITCHMODE;
			
			return (block_p + 1); /* the block right after the header */
		}
		/* the block is in the exact size or bigger than for size_needed: */
		else if ((ssize_t)size_needed <= block_p->block_size)
		{
			block_p->block_size *= SWITCHMODE;
			#ifndef ND
			block_p->valid = ISHEADER;
			#endif /* ND */
			
			return (block_p + 1);
		}
		
		byte_p += labs(block_p->block_size) + sizeof(block_t);
		block_p = (block_t *)byte_p;
	}
	
	return (NULL);
}

/******************************************************************************/

size_t VSALargestBlockAvailable(vsa_t *pool)
{
	char *byte_p = NULL;
	block_t *block_p = NULL;
	ssize_t max = 0; /* this variable will store the biggest block size */
	ssize_t current_max = 0;
	
	assert(pool);
	
	byte_p = (char *)pool;
	block_p = (block_t *)byte_p;
	
	while (block_p->block_size != (ssize_t)LASTBLOCK)
	{
			if (0 <= block_p->block_size)
			{
				current_max = block_p->block_size;
				
				/* move to next block */
				byte_p += block_p->block_size + sizeof(block_t);
				block_p = (block_t *)byte_p;
				
				/* if the next block is free as well - enter it's size to	*/
				/* max_p and move to the next block							*/
				while (0 <= block_p->block_size &&
					   block_p->block_size != (ssize_t)LASTBLOCK)
				{
					current_max += block_p->block_size + sizeof(block_t);
					
					byte_p += block_p->block_size + sizeof(block_t);
					block_p = (block_t *)byte_p;
				}
			
				/* current block size is bigger than max_p */
				if (current_max > max)
				{
					max = current_max;
				}
			}
			else
			{
				byte_p += labs(block_p->block_size) + sizeof(block_t);
				block_p = (block_t *)byte_p;
			}
	}
	
	return (max);
}

/******************************************************************************/

void VSAFree(void *block_ptr)
{
	block_t *free_block = NULL;
	
	assert(block_ptr);
	
	free_block = ((block_t *)block_ptr) - 1;
	free_block->block_size = labs(free_block->block_size);
}
