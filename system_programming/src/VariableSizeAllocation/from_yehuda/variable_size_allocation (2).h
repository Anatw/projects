#ifndef VARIABLE_SIZE_ALLOCATION_H
#define VARIABLE_SIZE_ALLOCATION_H

#include <stddef.h> /* size_t, ssize_t */

typedef struct block_header vsa_t;
typedef struct block_header block_t;

/*
 * Arguments:
 			 * Pointer to begining of memory segment allocated by the user
 			 * Total memory segment size in bytes
 			 * 
 * Return: A pointer to the first user data block
 * Complexity:
 */
block_t *VSAInit(void *memory, size_t seg_size);

/*
 * Arguments: Allocate a new freed block for the user
 			 * A pointer to the begining of memory segment vsa_pool
 			 * The size of block to be allocated 'block_size'
 			 * 
 * Return: A pointer to the user data block
 * Complexity: O(n)
 */

void *VSAAlloc(vsa_t *vsa_pool, size_t size_needed);

/*
 * Arguments: Free the block pointed by 'block_ptr' within memory segment
 			 * A pointer to the required block to be freed
 * Return: void
 * Time complexity O(1)
 */
void VSAFree(void *block_ptr);
size_t VSALargestBlockAvailable(vsa_t *pool);

#endif /* VSA */
