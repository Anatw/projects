struct vsa
{
	
	size_t capacity;
	size_t next_free;
	size_t free_space;
}; /* vsa_t */

typedef struct block_header
{
    size_t block_size;   /* Offset (in bytes) from the start of the FSA. */
    vsa_t *vsa_pool;
} block_t;

fsa_t *VSAInit(void *memory, size_t seg_size);
void *VSAAlloc(vsa_t *vsa_pool size_t block_size);
void VSAFree(void *block_ptr);
size_t VSACountFree(vsa_t *vsa_pool);

#ifndef VARIABLE_SIZE_ALLOCATION_H
#define VARIABLE_SIZE_ALLOCATION_H

#define LAST_BLOCK 9999999999999999/* To be complete */

#include <stddef.h>

typedef struct block_header /* move to function definitin file */
{
	ssize_t block_size; /* negetive value means not free and vice versa */

#ifndef ND
	long valid; /* should hold a specific value to validate proper position */
#endif

}block_t;

/*
/*
 * Arguments:
 			 * Pointer to begining of memory segment allocated by the user
 			 * Total memory segment size in bytes
 			 * 
 * Return: A pointer to the first user data block
 * 
*/
block_t *VSAInit(void *memory, size_t seg_size);


/*
 * Arguments: Allocate a new freed block for the user
 			 * A pointer to the begining of memory segment vsa_pool
 			 * The size of block to be allocated 'block_size'
 			 * 
 * Return: A pointer to the user data block
 * Time complexity O(n)
*/

void *VSAAlloc(VSA_t *vsa_pool, size_t block_size);

/*
 * Arguments: Free the block pointed by 'block_ptr' within memory segment
 			 * A pointer to the required block to be freed
 * Return: void
 * Time complexity O(1)
*/
void VSAFree(void *block_ptr);

/*
 * Arguments:
 			 * 
 			 * 
 			 * 
 * Return: The size of the largest block available within memory segment
 * 
*/

size_t VSALargestBlockAvailable(vsa_t *pool);

#endif /* VARIABLE_SIZE_ALLOCATION_H */
