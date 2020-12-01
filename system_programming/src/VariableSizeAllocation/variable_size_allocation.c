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

typedef struct block_header block_t;

struct block_header
{
	ssize_t block_size; /* positive value = free; negative value = occupied */
	#ifndef _NDEBUG
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
	/* size minus begin (vas_t) and end (block_t) blocks (both are the same size): */
	vsa_pool->block_size = new_seg - (sizeof(vsa_t) * 2);
	
	/* insetring a hearer indicating it is the ladt block right at the end of the pool: */
	byte_p = (char *)vsa_pool;
	byte_p += vsa_pool->block_size + sizeof(vsa_t); 
	last_block = (block_t *)byte_p;
	last_block->block_size = LASTBLOCK;
	
	#ifndef _NDEBUG
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
	/* setting size_needed to start in a word-allignment orientation (I'm using "size_needed - 1" and than adding back that one for the case that size_needed is devidable by WORD - in which case the resault will be zero - wring...): */
	size_needed = (((size_needed - 1) / WORD) + 1) * WORD;
	
	assert(vsa_pool);
	
	/* move all pointer to the beginning of the memory pool - the managing struct, the vsa_t, is also indicating as the first header - an actual block header: */
	byte_p = (char *)vsa_pool;
	block_p = vsa_pool;
	new_block = vsa_pool;

	while (LASTBLOCK != block_p->block_size)
	{
		/* while block is free but not enough for 'size_needed' - unite free
		 adjacent blocks. This block keep uniting free adjacent blocks even
		 if the size matches the size_needed, until it discovers an occupied
		 block. It can be easely changed by adding at the end of the block an
		 if statement to check if the block_size is big enough for
		 size_needed, and if so - break. */
		while (0 < block_p->block_size &&
			   (ssize_t)size_needed > (block_p->block_size) && 
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
			#ifndef _NDEBUG				
			new_block->valid = ISHEADER;
			#endif /* _NDEBUG */
			
			block_p->block_size = size_needed * SWITCHMODE;
			
			return (block_p + 1); /* the block right after the header */
		}
		/* the bloc_size equals size_needed: */
		else if ((ssize_t)size_needed == block_p->block_size)
		{
			block_p->block_size *= SWITCHMODE;
			#ifndef _NDEBUG
			block_p->valid = ISHEADER;
			#endif /* _NDEBUG */
			
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
