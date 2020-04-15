/****************************************************************************
* File Name: recursion.h													*
* Writer: Lior Cohen														*
* Date: 06/04/2020														    *
* Purpose: The header file for the recursion assignment						*
* Code reviewer: Anat Wax													*
*****************************************************************************/

#ifndef RECURSION_H
#define RECURSION_H

#include <stdio.h>	/* size_t	*/

typedef struct list_node Node;

typedef struct stack stack_t;


/******************************************************************************/

/*
 * FibonacciR: Recursive Fibonacci, returns the number at the given index
 * Return: The number at the given index
 * Receive: int - The index to find
 * Time Complexity: O(n)
 */
int FibonacciR(int element_index);

/*
 * FibonacciI: Iteration Fibonacci, returns the number at the given index
 * Return: The number at the given index
 * Receive: int - The index to find
 * Time Complexity: O(n)
 */
int FibonacciI(int element_index);

/*
 * Flip List: Flips a singly linked list from start to end
 * Return: Pointer to the new beggining of the list
 * Receive: Node * - Pointer to the the node to start fliping from
 * Time Complexity: O(n)
 */
Node *FlipList(Node *node);


/************************** Sorting Unsorted Stack ***************************/

/*
 * Stack Sort: Sorting the stack one element at a time (Recursive)
 * Recieve: stack_t * - Pointer to the stack
 * Time Complexity: O(n)
 */
void StackSort(stack_t *stack);

/*
 * Stack Push: Putting the the element back into the stack
 * Recieve:
 * - stack_t * - Pointer to the stack
 * - int - The number to put back in the stack
 * Time Complexity: O(n)
 */
void StackInsert(stack_t *stack, int num);

/************************* Implment String Functions **************************/

/*
 * Strlen: Finds the length of a given string (Recursive)
 * Return: The size of the string
 * Receive: const char * - Pointer to the string
 * Time Complexity: O(n)
 */
size_t Strlen(const char *str);

/*
 * Strcmp: Compares between two given strings (Recursive)
 * Return:
 * - 0 If they are the same
 * - Positive if str1 is larger than str2
 * - Negative if str1 is smaller than str2
 * Receive:
 * - const char * - Pointer to the first string
 * - const char * - Pointer to the second string
 * Time Complexity: O(n)
 */
int Strcmp(const char *str1, const char *str2);

/*
 * Strcpy: Copies a string into another buffer (Recursive)
 * Return: Pointer to the beggining of the copied string
 * Receive:
 * - char * - Pointer to the destenation string to copy into
 * - const char * - Pointer to the source string to copy from
 * Time Complexity: O(n)
 */
char *Strcpy(char *dest, const char *src);

/*
 * Strcat: Appends one string to the end of another string
 * Return: Pointer to the beggining of the whole new string
 * Receive:
 * - char * - Pointer to the destenation, to append to it's end
 * - const char * - Pointer to the source, to copy from
 * Time Complexity: O(n)
 */
char *Strcat(char *dest, const char *src);

/*
 * Strstr: Finds the place where one string is found in the other one
 * Return: Pointer to the first place the whole string was found
 * Receive:
 * - const char * - Pointer to string to look inside it
 * - const char * - Pointer to string to look for
 * Time Complexity: O(n)
 */
char *Strstr(const char *haystack, const char *needle);





#endif /* RECURSION_H */


