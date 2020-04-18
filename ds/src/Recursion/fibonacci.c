/*******************************************************************************
					  		Written by Anat Wax
						 	April fth-6th, 2020
						   Reviewer: Noffar Gil
*******************************************************************************/
#include <stdio.h> /* printf() */

/* 
 * function to calculate (recursivly)) the Fibonacci number in theindex given.
 * 		   This function can calaulete only indexes equal or larger than 3.
 * Return: int - the Fibonacci number corresponding to the location.
 * 		   (index) entered.
 * Argument: element_index: the index location of the Fibonacci number to seek.
 * Time comlexity: O(2n)
 * Space complexity: O(n)
 */
int FibonacciRecursive(int element_index);

/* 
 * function to calculate the Fibonacci number in the index inserted. 
 * Return: int - the Fibonacci number corresponding to the location.
 * 		   (index) entered.
 * Argument: element_index: the index location of the Fibonacci number to seek.
 * Time comlexity: O(n)
 * Space complexity: O(n)
 */
int FibonacciNonRecursive(int element_index);

/******************************************************************************/

int main ()
{
	int next_fib = 14;
	
	printf("recursive: the next Fibonacci number after %d is: %d\n",
			next_fib, FibonacciRecursive(next_fib));

	printf("non-recursive: the next Fibonacci number after %d is: %d\n",
			next_fib, FibonacciNonRecursive(next_fib));

	return (0);
}

/******************************************************************************/

int FibonacciRecursive(int element_index)
{	
	if (1 >= element_index)
	{
		return (element_index);
	}
		
	return (FibonacciRecursive(element_index - 1) + 
			FibonacciRecursive(element_index - 2));
}

/*******************************************/

int FibonacciNonRecursive(int element_index)
{
	int prev = 1;
	int current = 1;
	int fibonacci_number = 1;
	/* because actual changes in the Fibonaccy */
	/* system starts from index number 2:      */
	int counter = 2;
	
	if (1 >= element_index)
	{
		return (0);
	}
	
	for (; counter < element_index; ++counter)
	{
		fibonacci_number = current + prev;
		
		prev = current;
		current = fibonacci_number;
	}
	return (fibonacci_number);
}
