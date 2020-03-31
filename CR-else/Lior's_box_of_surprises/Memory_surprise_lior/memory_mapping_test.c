/****************************************************************************
* File Name: memory_mapping_test.c											*
* Writer: Lior Cohen														*
* Date: 22/03/2020														    *
* Purpose: The tester for the memory mapping assignment 					*
* Code reviewer: Yaacov Evenchik											*
*****************************************************************************/

#include <stdio.h>	/* printf() */
#include <unistd.h> /* sleep()	*/
#include <stdlib.h> /* system() */

#include "memory_mapping.h"

int several_times = 5;

int main()
{
	const size_t size = 10;
	size_t index = 0;
	int seconds = 1;
	int i = 0;
	char *welcome = "Hello and welcome to this amazing and unforgettable program";
	char *welcome2 = "Which does a lot of stuff, yet does absolutely nothing at all";
	char *good_luck = "So lets start, shall we? ";
	char *warning = "WHAT EVER YOU DO DON'T CLOSE THE PROGRAM!";
	
	system("clear");
	
	sleep(seconds);
	printf("%s\n", welcome);
	printf("%s\n\n", welcome2);
	
	sleep(2);
	printf("%s\n\n", warning);
	
	seconds = 4;
	sleep(seconds);
	printf("%s\n", good_luck);
	
	GoodLuck();
	
	seconds = 2;
	sleep(seconds);
	
	printf("So, first, lets get the boring stuff out of the way:\n");
	printf("Now we have bla bla bla bla bla static function and bla,\n");
	printf("bla bla bla global function bla bla bla.\n");
	printf("bla variable, bla bla global bla bla static, bla bla const,\n\n");
	printf("I hope everything is understood until here... if not.. well,\n");
	printf("bla bla bla...\n\n");
	
	sleep(8);
	printf("OK, here we go:\n");
	seconds = 1;
	sleep(seconds);
	system("clear");
	sleep(2);
	printf("3...\n");
	sleep(seconds);
	printf("2...\n");
	sleep(seconds);
	printf("1...\n\n");
	sleep(seconds);
	
	for (i = 0; i < several_times; ++i)
	{
		printf("This should be (%ld): %d\n", size - (i * 2), Foo(size, index));
		index += 2;
	}
	
	seconds = 3;
	sleep(seconds);
	system("clear");
	printf("Aaaaaaaaaaaaaaaaaaaaaaaaaaaaand...\n\n");
	sleep(seconds);
	printf("We're done!!!!\n");
	printf("Wasn't that just amazing???\n\n");
	sleep(seconds);
	printf("I hope you'll be able to sleep tonight after seeing that\n");
	printf("I really do!!\n");
	sleep(seconds);
	printf("Well that was it... (don't close the program yet)\n");
	sleep(3);
	system("clear");
	printf("I was\n\n\n\n\n\n");
	
	Bar(1);
	
	printf("Bye bye\n");
	sleep(seconds);
	system("clear");
	
	return (0);
}
