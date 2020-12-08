#include <sys/types.h>
#include <stdlib.h> /* NULL */
#include <assert.h>
#include <stdio.h>

#include "variable_size_allocation.h"

#define LASTBLOCK (4611686018427387902) /* the biggest number ssize_t can hold */
#define ISHEADER (5334221234555533422)
#define SWITCHMODE (-1)
#define WORD (sizeof(void *))

struct block_header
{
	ssize_t block_size; /* positive value = free; negetive value = not free */
#ifndef ND
	long valid; /* ment to validate that we point to a header and not data */
#endif
};

block_t *VSAInit(void *memory, size_t seg_size)
{
	vsa_t *vsa_pool = NULL;
	block_t *last_block = NULL;
	char *byte_p = NULL;

	/* set the block size to word size: */
	size_t new_seg = seg_size - (seg_size % WORD);

	assert(memory);

	vsa_pool = (vsa_t *)memory;
	/* size - begin and end blocks */
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
			   size_needed > (block_p->block_size + temp_block_size))
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
			new_block->block_size = block_p->block_size - size_needed -
									sizeof(block_t);
#ifndef ND
			new_block->valid = ISHEADER;
#endif /* ND */

			block_p->block_size = size_needed * SWITCHMODE;

			return (block_p + 1); /* the block right after the header */
		}
		/* the block is in the exact size for size_needed: */
		else if ((ssize_t)size_needed <= block_p->block_size)
		{
			block_p->block_size *= SWITCHMODE;

			return (block_p + 1);
		}

		byte_p += labs(block_p->block_size) + sizeof(block_t);
		block_p = (block_t *)byte_p;
	}

	return (NULL);
}

size_t VSALargestBlockAvailable(vsa_t *pool)
{
	char *byte_p = NULL;
	block_t *block_p = NULL;
	ssize_t max_p = 0; /* this variable will store the biggest block size */

	assert(pool);

	byte_p = (char *)pool;
	block_p = (block_t *)byte_p;

	while (block_p->block_size != (ssize_t)LASTBLOCK)
	{
		/* current block size is bigger than max_p */
		if (block_p->block_size >= max_p)
		{
			max_p = block_p->block_size;
		}

		byte_p += labs(block_p->block_size) + sizeof(block_t);
		block_p = (block_t *)byte_p;

#ifndef ND
		assert(block_p->valid == ISHEADER);
#endif /* ND */
	}

	return (max_p);
}

void VSAFree(void *block_ptr)
{
	block_t *free_block = ((block_t *)block_ptr) - 1;
	free_block->block_size = labs(free_block->block_size);
}
