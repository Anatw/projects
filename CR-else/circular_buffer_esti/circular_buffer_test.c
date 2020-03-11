/******************************************************************************
* File: circular_buffer_test.c
* Auther: Esti Binder
* Reviewed by: 
* Description: test file of operation functions on Queue
*******************************************************************************/

#include "circular_buffer.h"
#include <stdio.h> /*printf*/

#define CAPACITY 10

int main()
{
	char *buf1 = "esti";
	char buf2[5] = {0};
	
	circular_buffer_t *cb = CBCreate(CAPACITY);	
	
	printf("CBIsEmpty %d\n\n", CBIsEmpty(cb));	
	
	printf("CBWrite %lu\n", CBWrite(cb, buf1, 4));
	
	printf("CBFreeSpace %lu\n", CBFreeSpace(cb));
	
	printf("CBSize %lu\n", CBSize(cb));
	
	printf("CBIsEmpty %d\n\n", CBIsEmpty(cb));
	
	printf("CBRead %lu\n", CBRead(cb, buf2, 2));
	
	printf("%c %c\n", buf2[0], buf2[1]);
	
	printf("CBFreeSpace %lu\n", CBFreeSpace(cb));
	
	printf("CBSize %lu\n", CBSize(cb));
	
	printf("CBIsEmpty %d\n\n", CBIsEmpty(cb));	
	
	printf("CBRead %lu\n", CBRead(cb, buf2, 2));
	
	printf("%c %c\n", buf2[0], buf2[1]);
	
	printf("CBFreeSpace %lu\n", CBFreeSpace(cb));
	
	printf("CBSize %lu\n", CBSize(cb));
	
	printf("CBIsEmpty %d\n\n", CBIsEmpty(cb));	
	
	printf("CBRead %lu\n", CBRead(cb, buf2, 2));
	
	CBDestroy(cb);
	
	return (0);
}
