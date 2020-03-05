/******************************************************************************/
/* 					Worksheet 12 - Singly Linked LIst Implementation		  */
/*					Description - Test File				  				 	  */
/*					Autor - Dean Oron									 	  */
/*					Date - 03.03.20									     	  */
/*					Reviewer - 	Anat Wax						         	  */
/*					Open Lab 86											  	  */
/******************************************************************************/
#include"singly_linked_list.h"
#include <stdio.h>
#include<stdlib.h>

int IsTheSame(void *data1, void *data2);
void AddInt(void *data, void *param);
void PrintInt(void *);

int (*match_func)(void *data1, void *data2) = IsTheSame;
void (*act_func)(void *data, void *param) = AddInt;
void (*Print)(void *) = PrintInt;

int main()
{
	int x1 = 1;
	int x2 = 2;
	int x3 = 3;
	int x4 = 4;
	int x5 = 5;
	int param = 1;
	int set = 10;
	int *ptr1 = &x1;
	int *ptr2 = &x2;
	int *ptr3 = &x3;
	int *ptr4 = &x4;
	int *ptr5 = &x5;
	int *param_p = &param;
	int *ptr_set = &set;
	
	
/******************************SLLCreate***************************************/
	
	sll_t *sll = SLLCreate();
	
	iter_t i;
	printf("the list address is %lu\n", (size_t)sll);
/******************************SLLBegin****************************************/	
	
	i = SLLBegin(sll);

/******************************SLLIsEmpty**************************************/
	
	printf("is empty return %d\n", SLLIsEmpty(sll));
	
/******************************SLLInsert&SLLNext*******************************/	
	i = SLLInsert(i, ptr1);
	i = SLLNext(i);
	i = SLLInsert(i, ptr2);
	i = SLLNext(i);
	i = SLLInsert(i, ptr3);
	i = SLLNext(i);
	i = SLLInsert(i, ptr4);
	i = SLLNext(i);
	i = SLLInsert(i, ptr5);
	
/******************************SLLGetData**************************************/
		
	for(i = SLLBegin(sll); i != SLLEnd(sll); i = SLLNext(i))
	{
		Print(SLLGetData(i));
	}		
	
	i = SLLBegin(sll);

/******************************SLLCount****************************************/
	printf("the size is %lu\n", SLLCount(sll));

/**********************************SLLEnd**************************************/	
	i = SLLEnd(sll);
	printf("the last element is the list address %lu\n", (size_t)SLLGetData(i));
	
/******************************SLLFind*****************************************/
	
	i = SLLFind(SLLBegin(sll), SLLEnd(sll), ptr3, IsTheSame);
	printf("the data of current iterator is %d\n", *((int*)(SLLGetData(i))));
	
/******************************SLLSetData**************************************/	

	i = SLLBegin(sll);
		
	SLLSetData(i, ptr_set);
	printf("after set the first iterator to %d\n", *ptr_set); 
	for(i = SLLBegin(sll); !(SLLIsSameIter(i, SLLEnd(sll))); i = SLLNext(i))
	{
		Print(SLLGetData(i));
	}

/******************************SLLForEach**************************************/
	
	printf("after addition of 1 from begin to end :\n");
	SLLForEach(SLLBegin(sll), SLLEnd(sll), AddInt, param_p);

	for(i = SLLBegin(sll); !(SLLIsSameIter(i, SLLEnd(sll))); i = SLLNext(i))
	{
		Print(SLLGetData(i));
	}
	
	SLLDestroy(sll);
return (0);

}

int IsTheSame(void *data1, void *data2)
{
	return((*(int *)data1 == *(int *)data2) ? 1 : 0);
}

void AddInt(void *data, void *param)
{
	*(int*)data += *(int*)param; 
}

void PrintInt(void *data)
{
	printf("%d\n", *(int*)data);
}
