/*******************************************************************************
 * File: variable_size_allocation.h - 	header file				 		       *
 * Author: Yehuda Levavi                                                       *
 * Reviewed by: Anat Wax				                                   	   *
 * Date: 24.3.2020                                                             *
 * Note: Due to efficiency reasons, there are no user protection in the 	   *
 * functions, and all the validations are the responsibility of the user.      *
 ******************************************************************************/

#ifndef VARIABLE_SIZE_ALLOCATION_H
#define VARIABLE_SIZE_ALLOCATION_H

#include <unistd.h> /* ssize_t, size */

/* variable size allocation type */
typedef struct block_header vsa_t;

/* 
* Variable Size Allocation Initialize: initialize memory pool
* Receive: void *memory - pointer to memory segment allocated by client
*          size_t seg_size - size of memory segment, at least 20 bytes
* Return: pointer to vsa_t initialized memory pool
* Time Complexity: O(1) 
*/
vsa_t *VSAInit(void *memory, ssize_t seg_size);

/* 
* Variable Size Allocation Allocate: allocate memory block
* Receive: vsa_t *vsa_pool - an initialized memory pool to allocate memory from
*          size_t block_size - size of memory block requested
* Return: pointer void data of the user. NULL if can't allocate enaugh space
* Time Complexity: O(n) 
*/
void *VSAAlloc(vsa_t *vsa_pool, ssize_t block_size);

/* 
* Variable Size Allocation Free: free memory block
* Receive: void *block_ptr - pointer to the data block requested to be free
* Time Complexity: O(1)
*/
void VSAFree(void *block_ptr);

/* 
* Variable Size Allocation Largest Block Available: get size of largest free 
*                                                   block
* Receive: fsa_t *fsa_pool - an initialized memory pool
* Return: size_t with the size of the largest free block
* Time Complexity: O(n) 
*/
size_t VSALargestBlockAvailable(vsa_t *vsa_pool);

#endif /* VARIABLE_SIZE_ALLOCATION_H */
