/****************************************************************************
* File Name: memory_mapping.c												*
* Writer: Lior Cohen														*
* Date: 26/03/2020														    *
* Purpose: The functions for the memory mapping assignment					*
* Code reviewer: 															*
*****************************************************************************/

#include <stdio.h>	/* printf() */
#include <stdlib.h> /* malloc(), free() */
#include <assert.h> /* assert() */
#include <unistd.h> /* sleep()	*/

#include "memory_mapping.h"

static void MyName(int seconds);

static void GoodJob();

/******************************************************************************/

int Foo(size_t size, size_t index)
{
	int *arr = NULL;
	size_t i = 0;
	int to_return = 0;
	size_t counter = size;
	
	arr = (int *)malloc(size);
	
	for (i = 0; i < size; ++i)
	{
		arr[i] = counter;
		--counter;
	}
	
	to_return = arr[index];
	
	free(arr);
	arr = NULL;
	
	return (to_return);
}

/******************************************************************************/

void Bar(int seconds)
{
	MyName(seconds);
	GoodJob();
}



/*
static function V
extern function V
heap variables
const and non const
	local variable
	global variable
	static local variable
	static global variable
string literal
enviroment variables
command line arguments



*/

/******************************************************************************/

static void MyName(int seconds)
{
	sleep(seconds);
	printf("	 *           * * * * *     * * *      * * * *       \n");
	sleep(seconds);
	printf("	 *               *       *       *   *       *    	\n");
	sleep(seconds);
	printf("	 *               *       *       *   *       *      \n");
	sleep(seconds);
	printf("	 *               *       *       *   * * * *     	\n");
	sleep(seconds);
	printf("	 *               *       *       *   *      *   	\n");
	sleep(seconds);
	printf("	 *               *       *       *   *       *   	\n");
	sleep(seconds);
	printf("	 * * * * *   * * * * *     * * *     *        *     \n\n");
	printf("\n\n\n\n");
}

/******************************************************************************/

void GoodLuck()
{
	sleep(2);
	printf("\n");
	printf("  * * * *     * * * *     * * * *    * * * * 	\n");
	printf(" *       *   *       *   *       *   *       *	\n");
	printf(" *           *       *   *       *   *        *	\n");
	printf(" *  * * *    *       *   *       *   *        *	\n");
	printf(" *       *   *       *   *       *   *        *	\n");
	printf(" *       *   *       *   *       *   *       *	\n");
	printf("  * * * *     * * * *     * * * *    * * * *	\n\n");
	
	printf(" *           *       *    * * * *    *     *    \n");
	printf(" *           *       *   *       *   *   *     	\n");
	printf(" *           *       *   *           * *        \n");
	printf(" *           *       *   *           * *     	\n");
	printf(" *           *       *   *           *   *   	\n");
	printf(" *            *     *    *       *   *     *   	\n");
	printf(" * * * * *     *****      * * * *    *       *  \n");
	printf("************************************************\n\n");
}

/******************************************************************************/

static void GoodJob()
{
	sleep(2);
	printf("************************************************\n");
	printf("  * * * *     * * * *     * * * *    * * * * 	\n");
	printf(" *       *   *       *   *       *   *       *	\n");
	printf(" *           *       *   *       *   *        *	\n");
	printf(" *  * * *    *       *   *       *   *        *	\n");
	printf(" *       *   *       *   *       *   *        *	\n");
	printf(" *       *   *       *   *       *   *       *	\n");
	printf("  * * * *     * * * *     * * * *    * * * *	\n\n");
	
	printf("         * * *    * * * *     * * * *     	\n");
	printf("            *    *       *   *       *   	\n");
	printf("            *    *       *   *       *   	\n");
	printf("      *     *    *       *   * * * *     	\n");
	printf("      *     *    *       *   *       *   	\n");
	printf("      *     *    *       *   *       *   	\n");
	printf("       * * *      * * * *     * * * *    	\n\n");
}

