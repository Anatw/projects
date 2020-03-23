/*******************************************************************************
This program is a fixed-size-allocated-memory-manager (memory pool manager).
The user is in charge of all the malloc (including alignment) and free, while
the program manages the memory itself and can answer the need to:
 - Know the next free block available for use.
 - Know the number of free blocks available in the memory pool.
 - When using a block from the memory pool, use FSAAlloc to indicate that this
 block is in use. 
Step one: use the FSASuggestSize to know the size of block you need to allocate.
Step two: use FSAInit to initialize the allocated memory block.
Step Three: You are ready to roll!

					  	 Written by Anat Wax
						    March 19-22, 2020
						Reviewer: Dean Oron
*******************************************************************************/
#ifndef FIXED_SIZE_ALLOCATION_H
#define FIXED_SIZE_ALLOCATION_H

typedef struct fixed_size_allocation fsa_t;

/* 
 * Fixed Size Allocation Suggest Size: suggest size for client allocation
 * Receive: size_t num_blocks - amount of blocks requested
 *          size_t block_size - size in bytes for each block		
 * Return: size_t of the size suggested for allocation		     	  
 * Time Complexity: O(1) 
 */
size_t FSASuggestSize(size_t num_blocks, size_t block_size);

/* 
 * Initializes the memory pool.
 * Receive: memory - pointer to memory allocated by client.
 *          seg_size - value returned by FSASuggestSize.
 *          block size - size in bytes for each block.
 * Return: pointer to fsa_t initialized memory pool.
 * Time Complexity: O(n) 
 */
fsa_t *FSAInit(void *memory, size_t seg_size, size_t block_size);

/*
 * Tag a memory block as allocated.
 * Return: void pointer to the begining of the next free memory block. If there
 * are no more available blocks - returns NULL.
 * Argument: fsa_pool - pointer to the fsa memory pool.
 * Complexity: O(1)
 */
void *FSAAlloc(fsa_t *fsa_pool);

/*
 * Tag a memory block as free.
 * Return: - 
 * Argument: block_ptr - the memory block you wish to free.
 * Complexity: O(1)
 */
void FSAFree(void *block_ptr);

/* 
 * Count the number of free block remaining in the memory pool.
 * Return: the size of free space in bytes.
 * Argument: fsa_pool - the memory block you wish to count free space in.
 * Complexity: O(1) - O(n) (if all blocks are empty)
 */
size_t FSACountFree(const fsa_t *fsa_pool);


#endif /* FIXED_SIZE_ALLOCATION_H */
