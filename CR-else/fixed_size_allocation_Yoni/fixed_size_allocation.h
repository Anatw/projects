/*******************************************************************************
* file name: fixed_size_allocation.h	     	               				   *
* last update: 2020-03-22 Yoni Naor											   *
* reviewer:	Anat Wax     									    	   		   *
*******************************************************************************/
#ifndef FIXED_SIZE_ALLOCATION__H
#define FIXED_SIZE_ALLOCATION__H

/* managing struct for the fsa */
typedef struct fixed_size_allocation fsa_t;

/* returns the size of memory sould be allocated for managing a memory pool with
   with a specific num of blocks with a speific size
*  recive: num_blocks- number of blocks wished to be allocated, block_size- size
           of each block
*  O(1) */
size_t FSASuggestSize(size_t num_blocks, size_t block_size);

/* creats a managing struct for the a memory pool that was allocated
*  returns: a pointer to the managing sruct;
*  recive: memory- pointer to the memory pool, seg_size- the size of the pool in
		   bytes, block_size- size of each block wished to be allocated 
*  O(1) */
fsa_t *FSAInit(void *memory, size_t seg_size, size_t block_size);

/* returns a pointer to an allocated block for the user to use if no free blocks
   available returns NULL
*  recive: fsa_pool- pointer to the managment sturct of the memory pool
*  O(1) */
void *FSAAlloc(fsa_t *fsa_pool);

/* frees a block that was allocated from the pool
*  recive: block_ptr- pointer to the blockto be freed
*  O(1) */
void FSAFree(void *block_ptr);
/* returns num of free blocks
*  recive: fsa_pool- pointer to the managment sturct of the memory pool
*  O(n) */
size_t FSACountFree(const fsa_t *fsa_pool);

#endif /* FIXED_SIZE_ALLOCATION__H */
