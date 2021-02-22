/*******************************************************************************
					  		Written by Anat Wax
						 	April fth-6th, 2020
						   Reviewer: Noffar Gil
*******************************************************************************/

#ifndef RECURSION_H
#define RECURSION_H

typedef struct sll_node Node;

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


/*
 * Flip List: Flips a singly linked list from start to end.
 * Return: Pointer to the new beggining of the list.
 * Receive: node - Pointer to the the node to start fliping from.
 * Time Complexity: O(n)
 * Space complexity: O(n)
 */
Node *FlipList(Node *node);

#endif  /* RECURSION_H */