/*******************************************************************************
* Note: Due to efficiency reasons, there are no user protection in the
functions, and all the validations are the responsibility of the user.

Written by Anat Wax, anatwax@gmail.com
March 23-25, 2020
*******************************************************************************/
#include <stdio.h> /* printf() */
#include <sys/types.h> /* ssize_t, size_t */
#include <stdlib.h> /* malloc(), free() */
#include <assert.h> /* assert() */

#include "variable_size_allocation.h"

#define POOLSIZE (200)


int main()
{
	char *new_block = NULL;
	char *new_block2 = NULL;
	void *memory_pool = (void *)malloc(POOLSIZE);
	
	VSAInit(memory_pool, POOLSIZE);
	
	printf("the biggest block availabe is %ld bytes\n", 
			VSALargestBlockAvailable(memory_pool));

	new_block = VSAAlloc(memory_pool, 32);
	
	printf("the biggest block availabe is %ld bytes\n", 
			VSALargestBlockAvailable(memory_pool));
	
	new_block2 = VSAAlloc(memory_pool, 35);

	printf("the biggest block availabe is %ld bytes\n", 
			VSALargestBlockAvailable(memory_pool));
					
	free(memory_pool);
	
	return (0);
}
