#ifndef DOUBLY_LINKED_LIST_H
#define DOUBLY_LINKED_LIST_H

#include <stddef.h> /* size_t */

/* doubly linked list type*/
typedef struct doubly_linked_list dll_t;

/* iterator type */
typedef struct dll_node *iter_t;

/*  
 *	DLLCreate: Allocates memory for new Doubly linked list- manager struct
 *	Recieve: -   
 *  Return: pointer to a new dll_t struct
 * 	Error: return NULL if can't allocate memory
 *  Time Complexity: O(1)  
 */
dll_t *DLLCreate();

/*  
 *	DLLDestroy: destroy all and free all allocated memory for dll    
 *  Recieve: 1. pointer to dll_t 'list'- manager struct 
 *	Return: - 
 *  Time Complexity: O(n) 
 */
void DLLDestroy(dll_t *list);

/*
 *	DLLBegin: 
 *	Recieve: 1. pointer to dll_t 'list'- manager struct
 *	Return: iterator to the first element of dll, 
 *			if it's empty- undefined behavior! 
 *	Time Complexity: O(1) 
 */
iter_t DLLBegin(const dll_t *list);

/*
 *	DLLEnd:
 *	Recieve: 1. pointer to dll_t 'list'- manager struct
 *	Return: NULL iterator which is not the last element! 
 *			can't use Set/GetData on this iterator 
 *	Time Complexity: O(1) 
 */
iter_t DLLEnd(dll_t *list);

/*	DLLSize: check current size of dll
 *	Recieve: 1. pointer to dll_t 'list'- manager struct
 *	Return: size_t size of dll
 *	Time Complexity: O(N) 
 */
size_t DLLSize(const dll_t *list);

/*	DLLIsEmpty : check if dll is empty
 *	Recieve: 1. pointer to dll_t 'list'- manager struct
 *	Return: 1 if dll 'list' is empty 0 if not  
 *	Time Complexity: O(1) 
 */
int DLLIsEmpty(const dll_t *list);

/*	DLLPopBack: remove the last element of dll 
 *	Recieve: 1. pointer to dll_t 'list'- manager struct
 *	Return: void * which is the data of the element that poped  
 *	Time Complexity: O(1) 
 */
void *DLLPopBack(dll_t *list);

/* 
 *	DLLPushBack: insert element at the end of dll
 *	Recieve:	1. pointer to dll_t 'list'- manager struct
 *				2. void * data to insert to the new element
 *	Return: iter_t that points to the new element from the list
 *	Errors: if can't insert returns iterator at the end of the list
 *	Time Complexity: O(1) 
 */
iter_t DLLPushBack(dll_t *list, void *data);
 
/* 
*	DLLPopFront: removed the first element in list
*	Recieve: 1. dll_t *list which points to dll_t manager struct
*	Return: void * with the data of the element that poped
*	Time Complexity: O(1) 
*/
void *DLLPopFront(dll_t *list);

/* 
*	DLLPushFront: insert element at the head of the dll
*	Recieve: 1. dll_t *list which points to dll_t manager struct
* 		   2. void *data to insert the new element
*	Return: iter_t that points to the new element 
*	Errors: if can't insert, returns iterator at the end of the list
*	Time Complexity: O(1) at failur o(n)
*/
iter_t DLLPushFront(dll_t *list, void *data);

/* 
*	DLLGetData: get data from iterator
*	Recieve: 1. iter_t iter that points at an element from the list
*	Return: void * pointer to the data from iter
*	Time Complexity: O(1) 
*/
void *DLLGetData(const iter_t where);

/* 
*	DLLSetData: set data to iterator
*	Recieve: 1. iter_t iter that points at an element from the list
* 		   2. void *data to set the iterator to
*	Time Complexity: O(1) 
*/
void DLLSetData(iter_t where, void *new_data);

/* 
*	DLLInsert: inserts an element to the list
*	Recieve: 1. iter_t iter that points at an element to insert before it
*		   2. void *data to insert to the new element
*	Return: iter_t that points to the new element from the dll
*	Errors: if can't insert returns iterator at the end of the dll
*	Time Complexity: O(1) at failure o(n)
*/
iter_t DLLInsert(iter_t where, void *data);

/* 
*	DLLRemove: removes an element from the dll
*	Recieve: 1. iter_t iter that points at an element to remove
*	Return: iter_t that points at the next iterator from the dll
*	Time Complexity: O(1) 
*/
iter_t DLLRemove(iter_t where);

/* 
*	DLLNext:
*	Recieve: 1. iter_t iter that points at an element from the dll
*	Return: the next iterator from the list
*	Time Complexity: O(1) 
*/
iter_t DLLNext(const iter_t iter);

/* 
* 	DLLPrev:
* 	Recieve: 1. iter_t iter that points at an element from the dll
* 	Return: the previous iterator from the dll
* 	Time Complexity: O(1) 
*/
iter_t DLLPrev(const iter_t iter);

/* 
* 	DLLIsSameIter: check if iter1 and iter2 are the same
* 	Recieve: 1. 2 iter_t iter1 and iter2 to check if they are the same
* 	Return: 1 if the iterators are the same, 0 if not
* 	Time Complexity: O(1) 
*/
int DLLIsSameIter(iter_t iter1, iter_t iter2);

/* 
*	DLLFind: find an element with 'data' recieve  in the the range 
*			'from'(include) 'to'(not include) 
*			at the dll at defult the range is 'from' the begining 'to' the end.
*	Recieve:1. iter_t 'from' that sets the start point of the function
*			2. iter_t 'to' that sets the end point of the function
*			3. match_func function that recieves two pointers to void, compares
*		      their content, and if they are equal return 1, if not returns 0;
*			4. const void *data to find in the dll
* 	Return: iter_t that points to an element if found, 
*			if not found return iterator to the end
* 	Time Complexity: O(n) 
*/
iter_t DLLFind(const iter_t from, const iter_t to, 
				int (*match_func)(const void *data1, void *data2), void *data);

/* 
*	DLLForEach: commit an action element at sll in the range 'from'(include) 'to'
*			(not include) at the dll at defult the range is 'from' the begining 
*			'to' the end.
*	Recieve:1. iter_t from that sets the start point of the function
*			2. iter_t to	that sets the end point of the function
*			3. action_func function that recieves pointer to void data and 
*		      pointer to void param, and commits an action on the data with the 
*		      param. it returns 0 for success and any other number if else
*			4. void *param for the use of action_func
* Return: 0 if completed successfuly, the number that returned from action_func
* 		  if the loop stopped by it
* Time Complexity: O(n) 
*/
int DLLForEach(const iter_t from, const iter_t to, 
				int (*act_func)(void *operand1, void *operand2), 
			    void *param);

/* 
*	DLLSplice: inserts a slice from one list into another one.
*	Recieve:1. iter_t from that sets the start point of the crop
*			2. iter_t to that sets the end point of the crop
*			3. iter_t where to insert the slice before it in a second list
*	Return: the last iterator that copy
*	Time Complexity: O(n) 
*/
iter_t DLLSplice(iter_t from, iter_t to, iter_t where);
 
/* 
*	DLLMultiFind: find elements that match and add them to a new list
*	Recieve:1. const iter_t from to start search from
* 		   2. const iter_t to to end the search at
*		   3. const void *data to match with
*		   4. match_func function that recieves two pointers to void, compares
*		      their content, and if they are equal return 1, if not returns 0.
*		   5. dll_t *dest to insert the matched elements into.
*	Return: 
*	Time Complexity: O(n) 
*/
size_t DLLMultiFind(const iter_t from, const iter_t to, void *data, 
				int (*match_func)(const void *data1, void *data2), dll_t *dest);

#endif /* DOUBLY_LINKED_LIST_H */

