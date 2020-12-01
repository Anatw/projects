/*******************************************************************************
					  	 Written by Anat Wax
						  March 3, 2020
						Reviewer: Yehuda Levavi
*******************************************************************************/
#include <stddef.h> /* size_t */

#ifndef SLINGLY_LINKED_LIST_H
#define SLINGLY_LINKED_LIST_H

typedef struct SLL SLL_t;
typedef struct sll_node *iter_t;

/* Functionality: create a the last element of the list 					*/
/* Complexity: O(1)															*/
SLL_t *SLLCreate();

/* Functionality: free all the memory thet was allocated in the program 	*/
/* 'list' - the list you ean to delete 										*/
/* Complexity: O(n) 														*/
void SLLDestroy(SLL_t *list);

/* Functionality: insert a new node before the head. It returns status		*/
/* if failes returns the last element 										*/
/* 'where' - where would you like to insert the new member 					*/
/* 'vod *data' - pointer to the data you wan to assign to the new member 	*/
/* Complexity: O(1) 														*/
iter_t SLLInsert(iter_t where, void *data);

/* Functionality: this function remove the member you point at. After 		*/
/* remove the iterator is invalid 											*/
/* 'who' - the member you want to remove (delete) 							*/
/* Complexity: O(1) 														*/
iter_t SLLRemove(iter_t who);

/* Functionality: function that count the number of mmbers in the list 		*/
/* 'list' - the list who's members you'de like to count 					*/
/* Complexity: O(n) 														*/
size_t SLLCount(const SLL_t *list);

/* Functionality: check if a list is empty 									*/
/* 'list' - the list who's members you'de like to check. 					*/
/* Complexity: O(1) 														*/
int SLLIsEmpty(const SLL_t *list);

/* Functionality: return the data in the requested iterator				    */
/* return value: the function will return (1) if empty and (0) if not empty */
/* 'node' - the requested iterator to retrieve data from 					*/
/* Complexity: O(1) 														*/
void *SLLGetData(const iter_t node);

/* Functionality: set changes the data in a specific node				    */
/* 'node' - the requested iterator to set data inside					    */
/* 'data' - the data you'de like to assign								    */
/* Complexity: O(1) 														*/
void SLLSetData(const iter_t iterator, const void *data);

/* Functionality: move the iterator to the next node					    */
/* Complexity: O(1) 														*/
/* */iter_t SLLNext(const iter_t);

/* Functionality: returns an iterator to te head of the list. Iif empty		*/
/* returns the last element  												*/
/* Complexity: O(1) 														*/
/* */iter_t SLLBegin(const SLL_t *list);

/* Functionality: returns an iterator to te end of the list 				*/
/* Complexity: O(1) 														*/
/* */iter_t SLLEnd(const SLL_t *list);

/* Functionality: check if two iterators point at the same node			    */
/* 'iter1' - the first iterator to compare to 'iter2' 						*/
/* 'iter2' - the second iterator to compare to 'iter1' 						*/
/* Complexity: O(1) */
int SLLIsSameIter(const iter_t iter1, const iter_t iter2);

/* return the next iterator in the list 									*/
/* 'member' - you want to retrieve the pointer to the member after 			*/
/* the requested member 													*/
/* Complexity: O(1) 														*/
iter_t SLLNext(const iter_t member);

/* Functionality: check if any node contains the searched data * pointer to a */
/* function																	  */
/* 'from' - the member from which you'd like to search 						  */
/* 'to' - the member until which you'de like to search 						  */
/* 'data' - the data you are searching for 									  */
/* '*match_func' - pointer to a function that received two void pointer to    */
/* any data 																  */
/* Complexity: O(n) 														  */
iter_t SLLFind(const iter_t from, const iter_t to, const void *data,
			   int (*match_func)(const void *, const void *));

/* Functionality: receieves a function (action_func()) and assign it to all   */
/* the members of the list	-	returns 0 is successed and 1 if failed		  */
/* 'from' - the member from which you'd like to commit the action 			  */
/* 'to' - the member until which you'de like to commit the action 			  */
/* '*param' - the parameter you senf to the action_func 					  */
/* '*action_func' - a pointer to the function who's action you'd			  */
/* like to conduct on the 'from'-'to' members								  */
/* Complexity: O(n) 														  */
int SLLForEach(iter_t from, iter_t to, void *param, int
			   (*action_func)(void *param, void *data));

/******************************************************************************/

/* Functionality: appent the 'src' list right after the '*dest' list 		*/
/* '*dest' - the list which will be start the new list 						*/
/* '*src' - the appended list (after '*dest') 								*/
/* Complexity: O(1) 														*/
void SLLAppend(SLL_t *dest, SLL_t *src);

void PrintList(iter_t head);

iter_t FlipRec(iter_t node);

iter_t FlipIter(iter_t current);

#endif /* SLINGLY_LINKED_LIST_H */
