/*******************************************************************************
					  	 Written by Anat Wax
						    March 5-8, 2020
						Reviewer: Amir Saraf
*******************************************************************************/
#ifndef CIRCULAR_BUFFER_H
#define CIRCULAR_BUFFER_H

#include <unistd.h> /* ssize_t */

typedef struct cb circularbuffer_t;

/* purpose: Create an new circular buffer array 							  */
/* return value: circularbuffer_t = a new variable in the struct of cb 		  */
/* capacity - the requested size for the buffer 							  */
/* Complexity: O(1) 														  */
circularbuffer_t *CBCreate(size_t capacity);

/* purpose: implementation with offsetof() 									  */
/* return value: circularbuffer_t = a variable in the struct of cb  		  */
/* capacity - the requested size fotr thr buffer 							  */
/* Complexity: O(1) 														  */
circularbuffer_t *CBCreate_offset(size_t capacity);

/* purpose: Delete (free) the array 										  */
/* return value: -  														  */
/* cb - pointer to the circular buffer 										  */
/* Complexity: O(1) 														  */
void CBDestroy(circularbuffer_t *cb);

/* purpose: return the number of read cells 								  */
/* return value: the  number of cells that were written. 					  */
/* ssize_t - can move from (-65536) to 65535 								  */
/* cb - pointer to the circular buffer 										  */
/* buf - the buffer to which the read data should be written 				  */
/* count - the number of elements (cells) you'de like to read 				  */
/* Complexity: O(1) 														  */
ssize_t CBRead(circularbuffer_t *cb, void *buf, size_t count);

/* purpose: buf - pointer to the data you'de like to enter					  */
/* count - the number of cells you are entering to (in case of string this 	  */
/* will be strlen(string) 													  */
/* return value: the amount of cells that were written 						  */
/* cb - pointer to the circular buffer 										  */
/* buf - pointer to the string containing the information to be added to the  */
/* buffer 																	  */
/* count - the number of elements (cells) you'de like to write to 			  */
/* Complexity: O(n) 													      */
ssize_t CBWrite(circularbuffer_t *cb, const void *buf, size_t count);

/* purpose: check the amount of free space in the buffer (number of cells 	  */
/* that are available for writing 											  */
/* return value: the number of free cells (writtable space) 				  */
/* cb - pointer to the circular buffer 										  */
/* Complexity: O(n) 														  */
size_t CBFreeSpace(circularbuffer_t *cb);

/* purpose: check the size of the buffer (meaning the cells that contain data)*/
/* return value: the number of occupied cells in the buffer 				  */
/* cb - pointer to the circular buffer 										  */
/* Complexity: O(1) 														  */
size_t CBSize(circularbuffer_t *cb);

/* purpose: check if the buffer is empty 									  */
/* return value: 1 if empty, 0 if full 										  */
/* cb - pointer to the circular buffer 										  */
/* Complexity: O(1) 														  */
int CBIsEmpty(circularbuffer_t *cb);

#endif /* CIRCULAR_BUFFER_H */
