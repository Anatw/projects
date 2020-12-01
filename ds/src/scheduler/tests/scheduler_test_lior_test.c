/****************************************************************************
* File Name: scheduler_test.c												*
* Writer: Lior Cohen														*
* Date: 17/03/2020														    *
* Purpose: The tester for the scheduler project								*
*****************************************************************************/


/*****************************************************************************

				*		*     *****		*******     *****
				*		*    *     *	*		   *	 *
				*		*	 *			*		   *	 *
				*		*	  *****		******	   ******
				*		*	  	   *	*		   *	 *
				 *	   *	 *	   *	*		   *	  *
				  *****		  *****		*******	   *      *
	
  *****		   *		*		*   * * * * *   * * *    ******	    *	  *
 *	   *  	  * *		*		*		*		  *		*	   *	**    *
 *			 *	 *		*		*		*		  *		*      *	* *   *
 *			*	  *		*		*		*		  *		*	   *	*  *  *   
 *		   * * * * *	*		*		*		  *		*	   *	*   * *
 *     *  *	   		*	 *	   *		*		  *		*	   *	*    **
  *****  *	   		 *	  *****			*		* * *	 ******		*     *
 
 *****************************************************************************/
 
#include <stdio.h>	/* printf() */
#include <string.h>	/* strlen() */
#include <stdlib.h>	/* srand()	*/
#include <unistd.h>	/* sleep()	*/

#include "scheduler.h"

#define NAMES (13)

/**************************** Test Functions *********************************/
/*
 * Our Names: Prints all of our names by alphabetical order. Param will decide
 *			  how many names to print and the next time the function is being
 			  called it will start from the last point
 * Return: 0 for success, 1 for failure - 1 will stop the running
 * Receive: Pointer to a parameter (should be number between 1 and 13)
 */
int OurNames(void *param);

/*
 * Fibonachi: Prints the Fibonachi numbers until parameter
 * Return: 0 for success, 1 for failure - 1 will stop the running
 * Receive: Pointer to parameter (should be positive int, equal or less than 50)
 */
int Fibonacci(void *param);

/*
 * Revere Num: Prints the reversed digits of a given parameter
 * Return: 0 for succes, 1 for failure - 1 will stop the running
 * Receive: Pointer to parameter (should be an int, between -10000 and 10000)
 */
int ReverseNum(void *param);

/*
 * Prints Minus Nums: Prints the numbers from -1 to the parameter
 * Return: 0 for success, 1 for failure - 1 will stop the running
 * Receive: Pointer to parameter (should be a negative int, down to -100)
 */
int PrintMinusNums(void *param);

/* Prime Numbers: Prints the prime numbers until the parameter
 * Return: 0 for printed, 1 for not printed - 1 will stop the running
 * Receive: Pointer to parameter (should be a positive int, up to 1000)
 */
int PrimeNumbers(void *param);

/*
 * ABC: Prints one letter of the abc, in the right order, every time the
 		function is being called
 * Return: 0 for success, 1 for failure - 1 will stop the running
 * Receive: Pointer to parameter which is the numeric place of the letter to
 *			start printing from, should be between 1 and 26
 */
int ABC(void *param);

/*
 * Small And Big: Turns small letters to big ones and vise versa
 * Return: 0 for success, 2 for remove - 2 will remove the task from the
 *		   scheduler
 * Receive: Pointer to parameter
 */
int SmallAndBig(void *param);

/*
 * Almost Always Right: Generates 10 diffrent random numbers, will stop if the
 *						one of the random numbers equals the param
 * Return: 0 if it worked, 1 if stoped - 1 will stop the running
 * Receive: Pointer to param (should be between 0 and 2000)
 */
int AlmostAlwaysRight(void *param);

/******************************************************************************/
/******************************************************************************/

int main()
{
	Uid_t task1 = UIDGetBadUID();
	Uid_t task2 = UIDGetBadUID();
	Uid_t task3 = UIDGetBadUID();
	Uid_t task4 = UIDGetBadUID();
	Uid_t task5 = UIDGetBadUID();
	Uid_t task6 = UIDGetBadUID();
	Uid_t task7 = UIDGetBadUID();
	Uid_t task8 = UIDGetBadUID();
	
	int status = 0;
	int param1 = 7;
	int param2 = -4321;
	int param3 = -23;
	int param4 = 237;
	char param5[] = "Are We Not Pure? “No, Sir!” Panama’s Moody Noriega Brags.\
 “It Is Garbage!” Irony Dooms A Man—a Prisoner Up To New Era";
	int param6 = 15000;
	
	
	
	
	/* Create the schedule */
	scheduler_t *main_scheduler = SchedulerCreate();

	printf("\n After creation the scheduler is empty (0): ");
	printf("%d\n\n", SchedulerIsEmpty(main_scheduler));
	
	/* Inserting 8 diffrent tasks inside it */
	task1 = SchedulerInsertTask(5, OurNames, &param1);
	task2 = SchedulerInsertTask(0, Fibonacci, &param1);
	task3 = SchedulerInsertTask(0, ReverseNum, &param2);
	task4 = SchedulerInsertTask(0, PrintMinusNums, &param3);
	task5 = SchedulerInsertTask(0, PrimeNumbers, &param4);
	task6 = SchedulerInsertTask(1, ABC, &param1);
	task7 = SchedulerInsertTask(3, SmallAndBig, &param5);
	task8 = SchedulerInsertTask(0, AlmostAlwaysRight, &param6);

	printf("After adding 8 new tasks the scheduler is NOT empty (1): ");
	printf("%d\n\n", SchedulerIsEmpty(main_scheduler);
	
	printf("The size of the scheduler is (8): ");
	printf("%ld\n\n", SchedulerSize(main_scheduler));
	
	/* Running the scheduler: will remove task 6 after 2 runs,	*/
	/* and will stop after 4 runs								*/
	status = SchedulerRun(main_scheduler);
	
	/* Removing 2 tasks out of the scheduler */
	SchedulerRemoveTask(main_scheduler, task2);
	SchedulerRemoveTask(main_scheduler, task3);

	printf("After removing total of 3 tasks, the size is (5): ");
	printf("%ld\n\n", SchedulerSize(main_scheduler));
	
	/* Running again: Will stop after 4 runs */
	status = SchedulerRun(main_scheduler);
	
	/* Cleaning the scheduler */
	SchedulerClear(main_scheduler);
	printf("After clean the scheduler is empty (0): ");
	printf("%d\n\n", SchedulerIsEmpty(main_scheduler));
	
	SchedulerDestroy(main_scheduler);
	
	return (0);
}

/******************************************************************************/
/******************************************************************************/

int OurNames(void *param)
{
	int par = *(int *)param;
	static int from = 0;
	static int counter = 0;
	char name[13][20] = {"Amir Paz", "Amir Saraf", "Anat Wax",
						 "Ben David Zikri", "Dean Oron", "Esti Binder",
						 "Haim Saadia", "Lior Cohen", "Lusy Volkov",
						 "Noffar Gil", "Yaacov Evenchik", "Yehuda Levavi",
						 "Yoni Naor"};

	if (0 >= par || 14 <= par)
	{
		return (SchedulerStop(main_scheduler));
	}
	
	if (4 == counter)
	{
		return (SchedulerStop(main_scheduler));
	}
	
	while (0 != par)
	{
		printf("%s, ", name[from]);
		++from;
		--par;
		if (NAMES == from)
		{
			from = 0;
		}
		
	}
	printf("\n\n");
	counter += 1;
	
	return (0);
}

/******************************************************************************/

int Fibonacci(void *param)
{
	int par = *(int *)param;
	int a = 0;
	int b = 1;
	int temp = 0;
	
	if (0 >= par || 50 < par)
	{
		return (SchedulerStop(main_scheduler));
	}	
	
	if (1 == par)
	{
		printf("1\n");
	}
	else if (2 == par)
	{
		printf("1\n");
	}
	else
	{
		while (0 != par)
		{
			printf("%d, ", temp);
			temp = a;
			a = b;
			b = a + b;
			--par;
		}
	}
	printf("\n\n");	
	
	return (0);
}

/******************************************************************************/

int ReverseNum(void *param)
{
	int par = *(int *)param;
	int result = 0;
	
	if (-10000 > par || 10000 < par)
	{
		return (SchedulerStop(main_scheduler));
	}
	
	while (0 != par)
	{
		result = (result * 10) + (par % 10);
		par /= 10;
	}
	printf("%d\n\n", result);
	
	return (0);
}

/******************************************************************************/

int PrintMinusNums(void *param)
{
	int par = *(int *)param;
	int i = 0;
	
	if (0 < par || -100 > par)
	{
		return (SchedulerStop(main_scheduler));
	}
	
	for (i = 0; i > par; --i)
	{
		printf("%d, ", i);
	}
	printf("%d\n\n", i);
	
	return (0);
}

/******************************************************************************/

int PrimeNumbers(void *param)
{
	int start = 0;
	int par = *(int *)param;
	int i = 0;
	int flag = 0;;
	
	if (0 > par || 1000 < par)
	{
		return (SchedulerStop(main_scheduler));
	}
    
    while (start < par)
    {
        flag = 0;

        for (i = 2; i <= start / 2; ++i)
        {
            if (start % i == 0)
            {
                flag = 1;
                break;
            }
        }

        if (flag == 0)
            printf("%d ", start);
        ++start;
    }
    printf("\n\n");
    
	return (0);
}

/******************************************************************************/

int ABC(void *param)
{
	int par = *(int *)param;
	static int letter = 64;
	static int count = 0;
	
	if (0 >= par || 26 < par)
	{
		return (SchedulerStop(main_scheduler));
	}
	
	if (0 == count)
	{
		++count;
		letter += par;
	}
	
	printf("%c\n", letter);
	++letter;
	
	if (91 == letter)
	{
		letter = 64;
	}
	
	return (0);
}

/******************************************************************************/

int SmallAndBig(void *param)
{
	char *par = (char *)param;
	int length = strlen((char *)param);
	static int count = 0;

	if (2 == count)
	{
		return (2);
	}

	while (*par)
	{
		if ('A' <= *par && 'Z' >= *par)
		{
			*par += 32;
		}
		else if ('a' <= *par && 'z' >= *par)
		{
			*par -= 32;
		}

		++par;
	}
	par -= length;
	printf("%s\n", par);
	count += 1;
	
	return (0);
}

/******************************************************************************/

int AlmostAlwaysRight(void *param)
{
	int par = *(int *)param;
	int i = 0;
	int random = 0;
	
	srand(time(0)); 
  
	for (i = 0; i < 10; ++i)
	{
		random = rand() % 2000;
		printf("%d ", random);
		if (par == random)
		{
			printf("Stoped cause random number equal 1!!!\n");
			return (SchedulerStop(main_scheduler));
		}
	}
	printf("\n\n");
	
	return (0);
}























