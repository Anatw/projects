/*******************************************************************************
					  	 Written by Anat Wax
						  February 18, 2020
						Reviewer: Lusy Volkov
*******************************************************************************/

#ifndef MAIN_FUNCS_H
#define MAIN_FUNCS_H

/* so we can know which data type the element contain - this    */
/* is the first field in the union (named elementValue)		    */
typedef enum {INTEGER, FLOAT, STRING} elementType;

/* the ectual value that is inside the elemen  - this is    	*/
/* the second field in the union (named elementValue) 			*/
typedef union
{
	int integer_num;
	float float_num;
	char *string;		/* pointer to the beggining of the string */
} elementValue;

/* the struct is the biggest */
typedef struct Element
{
	elementType element_type;
	elementValue element_value; /* the union */
} element;


void PrintArray(element *array, int arraySize);

void AddToArray(element *array, int arraySize, int intFromUser);

void FreeMemory(element *member, int arraySize);

#endif
