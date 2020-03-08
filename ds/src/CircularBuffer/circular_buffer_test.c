/*******************************************************************************
					  	 Written by Anat Wax
						    March 5-8, 2020
						Reviewer: Amir Saraf
*******************************************************************************/
#include <stdlib.h> /* size_t */
#include <stdio.h> /* printf() */
#include <string.h> /* strlen() */

#include "circular_buffer.h"

#define CAPACITY (50)

int main()
{
	circularbuffer_t *new_buffer = CBCreate(CAPACITY);
	/*circularbuffer_t *new_buffer = CBCreate_offset(CAPACITY);*/
	char *string = "please enter this";
	char get_info[20];
	size_t test = 0; 
	int index = 0;
	
	CBWrite(new_buffer, string, strlen(string));
	printf("the current size of the buffer is: %ld\n", CBSize(new_buffer));
	printf("free space at the moment: %ld\n", CBFreeSpace(new_buffer));
	CBRead(new_buffer, get_info, 6);
	
	while (index < 6)
	{
		printf("read[%d]: %c\n", index, get_info[index]);
		++index;
	}
	
	test = CBRead(new_buffer, get_info, 6);
	printf("read size: %ld\n", test);
		
	printf("is the buffer empty? %s\n", (CBIsEmpty(new_buffer) ? "no" : "yes"));
	
	CBDestroy(new_buffer);
	
	return (0);
}
