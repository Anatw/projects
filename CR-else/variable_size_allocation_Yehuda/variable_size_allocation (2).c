/*******************************************************************************
 * File: variable_size_allocation.c - operation funcs					 	   *
 * Author: Yehuda Levavi                                                       *
 * Reviewed by: Anat Wax				                                   	   *
 * Date: 24.3.2020                                                             *
 * Note: Due to efficiency reasons, there are no user protection in the 	   *
 * functions, and all the validations are the responsibility of the user.      *
 ******************************************************************************/

#include <unistd.h> /* ssize_t, size_t */
#include <stdlib.h> /* labs */
#include <assert.h> /* assert */

#include "variable_size_allocation.h"

#define LAST_BLOCK (0xDEADBEAF)	 /* value of last block size */
#define CHECK_BLOCK (0xCAFED00D) /* block_t check value */
#define WORD_SIZE (sizeof(size_t))

/* block header struct, with check member for debugging */
typedef struct block_header
{
	ssize_t block_size;

#ifndef NDEBUG
	size_t check; /* to check if equal to CHECK_BLOCK */
#endif			  /* NDEBUG */

} block_t;

/* utility functions:  */
static void *GetBlockData(block_t *block);

static block_t *GetNextBlock(block_t *block);

static int IsLastBlock(block_t *block);

static int IsBlockFree(block_t *block);

static block_t *GetBlockHeader(void *data);

/* main functions: */

vsa_t *VSAInit(void *memory, ssize_t seg_size)
{
	vsa_t *new_vsa = NULL;
	block_t *tail_block = NULL;
	char *byte_p = NULL;

	assert(memory);
	assert(seg_size > (ssize_t)sizeof(vsa_t));

	/* reduce segment size to word alignment */
	seg_size = (seg_size / WORD_SIZE) * WORD_SIZE;

	new_vsa = (vsa_t *)memory;
	byte_p = ((char *)memory) + (seg_size - sizeof(block_t));
	tail_block = (block_t *)byte_p;

	new_vsa->block_size = seg_size - sizeof(vsa_t) - sizeof(block_t);
	tail_block->block_size = LAST_BLOCK;

#ifndef NDEBUG
	new_vsa->check = CHECK_BLOCK;
	tail_block->check = CHECK_BLOCK;
#endif /* NDEBUG */

	return (new_vsa);
}

void *VSAAlloc(vsa_t *vsa_pool, ssize_t block_size)
{
	block_t *current_block = NULL;
	block_t *next_block = NULL;
	block_t *base_block = NULL;
	size_t potential_size = 0;
	char *byte_p = NULL;

	assert(vsa_pool);
	assert(block_size >= 0);

	/* add word-size padding */
	block_size = (((block_size - 1) / WORD_SIZE) + 1) * WORD_SIZE;

	current_block = vsa_pool;

	/* find the first free block sequence fits block_size */
	while (!IsLastBlock(current_block))
	{
		potential_size = current_block->block_size;
		base_block = current_block;

		/* check if the free sequence is large enough */
		while (!IsLastBlock(current_block) &&
			   IsBlockFree(current_block))
		{
			/* if potential size is bigger enough for block_size, 	  *
			 * and there is enough space a new block header at end 	  */
			if (potential_size > block_size + sizeof(block_t))
			{
				base_block->block_size = -1 * block_size;

				byte_p = (char *)base_block + sizeof(block_t) + block_size;
				next_block = (block_t *)byte_p;
				next_block->block_size = potential_size - block_size -
										 sizeof(block_t);
#ifndef NDEBUG
				next_block->check = CHECK_BLOCK;
#endif /* NDEBUG */

				return (GetBlockData(base_block));
			}
			/* if potential size is bigger enough for block_size, but there *
			 * is not enough space for new block header for next block      */
			else if (potential_size >= (size_t)block_size)
			{
				base_block->block_size = potential_size * -1;

				return (GetBlockData(base_block));
			}

			current_block = GetNextBlock(current_block);

			potential_size += sizeof(block_t) + current_block->block_size;
		}

		if (IsLastBlock(current_block))
		{
			break;
		}

		potential_size = 0;
		current_block = GetNextBlock(current_block);
	}

	return (NULL);
}

void VSAFree(void *block_ptr)
{
	block_t *block_to_free = NULL;

	assert(block_ptr);

	block_to_free = GetBlockHeader(block_ptr);

	/* make block_size positive indicates it is free */
	block_to_free->block_size = labs(block_to_free->block_size);
}

size_t VSALargestBlockAvailable(vsa_t *vsa_pool)
{
	size_t largest_sequence = 0;
	size_t current_largest = 0;
	block_t *current_block = (block_t *)vsa_pool;

	assert(vsa_pool);

	/* scan the whole pool for free sequences */
	while (!IsLastBlock(current_block))
	{
		/* for each first free block scan its sequence */
		if (IsBlockFree(current_block))
		{
			current_largest = current_block->block_size;
			current_block = GetNextBlock(current_block);

			/* scan the free sequence and count free bytes */
			while (IsBlockFree(current_block) && !IsLastBlock(current_block))
			{
				current_largest += current_block->block_size + sizeof(block_t);
				current_block = GetNextBlock(current_block);
			}

			/* update largest_sequence if needed */
			if (largest_sequence < current_largest)
			{
				largest_sequence = current_largest;
			}
		}
		else
		{
			current_block = GetNextBlock(current_block);
		}
	}

	return (largest_sequence);
}

/* utility functions: */

static void *GetBlockData(block_t *block)
{
	assert(block);
	assert(block->block_size != LAST_BLOCK);
#ifndef NDEBUG
	assert(block->check == CHECK_BLOCK);
#endif /* NDEBUG */

	++block;
	return ((void *)(block));
}

static block_t *GetNextBlock(block_t *block)
{
	char *byte_p = NULL;
	size_t abs_size = 0;

	assert(block);
	assert(block->block_size != LAST_BLOCK);
#ifndef NDEBUG
	assert(block->check == CHECK_BLOCK);
#endif /* NDEBUG */

	/* make it positive if negative */
	abs_size = labs(block->block_size);

	byte_p = ((char *)block) + sizeof(block_t) + abs_size;

	return ((block_t *)byte_p);
}

static int IsLastBlock(block_t *block)
{
	assert(block);
#ifndef NDEBUG
	assert(block->check == CHECK_BLOCK);
#endif /* NDEBUG */

	return (block->block_size == LAST_BLOCK);
}

static int IsBlockFree(block_t *block)
{
	assert(block);
#ifndef NDEBUG
	assert(block->check == CHECK_BLOCK);
#endif /* NDEBUG */

	return (block->block_size >= 0);
}

static block_t *GetBlockHeader(void *data)
{
	assert(data);

#ifndef NDEBUG
	assert((((block_t *)data) - 1)->check == CHECK_BLOCK);
#endif /* NDEBUG */

	return (((block_t *)data) - 1);
}
