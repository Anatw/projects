/******************************************************************************/
/* 					Worksheet 12 - Singly Linked LIst Implementation		  */
/*					Description -  SLinked List DS - Creation, Manipulation,  */							  
/*								   and Destruction	  				 	      */
/*					Autor    -     Dean Oron								  */
/*					Date     - 	   03.03.20									  */
/*					Reviewer - 	   Anat Wax						         	  */
/*					Open Lab 86											  	  */
/******************************************************************************/
#ifndef S_LINKED_LIST
#define S_LINKED_LIST

#include<stddef.h>

typedef struct list sll_t;
typedef struct sll_node *iter_t;

/* Return new list struct, create the last element of the list*/
sll_t *SLLCreate();

/* free all alocated memory that was allocated during the program */
void SLLDestroy(sll_t *list);

/* function that insert new element with data in it to the location 
   iteratior is pointing to if failed return the last element*/
iter_t SLLInsert(iter_t where, void *data);

/* remove the element which iterator is pointing to fDestroyrom list 
   iterator to the forword element*/
iter_t SLLRemove(iter_t who);

/* count how many elements within the list */
/* complexity of o(n) */
size_t SLLCount(const sll_t *list);

/* check whether the list is empty or not */
int SLLIsEmpty(const sll_t *list);

/* funciton recieve an iterator and return the address of data of element 
   which itarator is pointing to*/
void *SLLGetData(const iter_t iterator);

/* Set the data within a certain element which iterator is pointing to*/
void SLLSetData(iter_t iterator, void *data);

/* a function that moves the iterator to the next element within a list */
iter_t SLLNext(const iter_t iterator);

/* function that return iterator fot the first element of a certain list
   if empty return iterator to the last element */
iter_t SLLBegin(const sll_t *list);

/*function thatr get a specific list and return the iterator to the last
  element of the list*/
iter_t SLLEnd(const sll_t * list);

/* a function that check if two iterators are identical
   return 1 for true and 0 if false */
int SLLIsSameIter(const iter_t iter1, const iter_t iter2);

/* A function to find a specific data within the list within the range of 
   from - to and use the match_func to declare found/didn't find match
   between data1 and data2. return the iterator of finding/itertor *to* if didnt
   find*/
iter_t SLLFind(const iter_t from, const iter_t to, void *data, int (*match_func)(void *data1, void *data2));

/* Execute the act_func operation with the parameter *param*  for each 
   element within the range of iterators *from* - *to* return 0 for success
   and 1 for failure */
int SLLForEach(const iter_t from, const iter_t to, void (*act_func)(void *data, void *param), void *param);

#endif

