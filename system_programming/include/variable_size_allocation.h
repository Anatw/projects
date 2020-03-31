/*******************************************************************************
This program is a variable-size-allocated-memory-manager (memory pool manager).
The client is in charge of all the malloc (including alignment), free and all 
validations, while the program manages the memory itself and can answer the 
need to:
 - Know the amount of memory in the largest free block available for use.
 - When using a block from the memory pool, use VSAAlloc to indicate that this
 block is in use.
 - When freeing a block from the memory pool, use VSAFree to indicate that this
 block is now free for use.
After allocation use VSAInit to initialize the allocated memory block.

					  	 Written by Anat Wax
						    March 23-25, 2020
						Reviewer: Ben-David Zikri
*******************************************************************************/
#ifndef VARIABLE_SIZE_ALLOCATION_H
#define VARIABLE_SIZE_ALLOCATION_H

#include <stddef.h> /* size_t, ssize_t */

typedef struct block_header vsa_t;
typedef struct block_header block_t;

/*
 * Initializes the memory pool.
 * Arguments: memory - pointer to begining of memory segment allocated by
 					   the user
 *			  seg_size - total memory segment size in bytes
 * Return: A pointer to the first user data block
 * Complexity: O(1)
 */
block_t *VSAInit(void *memory, size_t seg_size);

/*
 * Tag a memory block as allocated.
 * Arguments: vsa_pool - pointer to the begining of memory segment vsa_pool
 *			  size_needed - the size of block to be allocated 'block_size'
 * Return: A pointer to the user data block
 * Complexity: O(n)
 */
void *VSAAlloc(vsa_t *vsa_pool, size_t size_needed);

/*
 * Free the block pointed by 'block_ptr' within memory segment
 * Arguments: block_ptr - pointer to the required block to be freed.
 * Return: -
 * Complexity O(1)
 */
void VSAFree(void *block_ptr);

/*
 * Find the size of the biggest memory block available for use. If two
 * or more subsequent memory blocks are free, the functions sum all
 * blocks as one big block free and avaiable for use.
 * Arguments: pool - pointer to the begining of memory segment vsa_pool.
 * Returns the size of the biggest free block availale for use.
 * Complexity O(n)
 */
size_t VSALargestBlockAvailable(vsa_t *pool);

#endif /* VSA */
