/******************************************************************************

Array of Elements

Editor: Haim Saadia
Date: Feb 2020
Reviewer: Anat Wax

*******************************************************************************/

#include <stdio.h>	/* printf(), scanf() */
#include <string.h>	/* sprintf(), strcat() */ 

#include "Functions.h"

/******************************************************************************/

/* Go over each type in the struct and print it */
void PrintStructElement(Elements element)
{
    printf("\n%s\n", element.string);
    printf("%d\n", element.natural);
    printf("%f\n", element.floatie);
}

/* Go over each cell in the array and send for printing */
void PrintArray(Elements *array)
{
    unsigned int i = 0;
    
    for(i = 0; i <= (sizeof(array) / ARRAY_LENGTH); ++i)
    {
        PrintStructElement(array[i]);
    }
}

/******************************************************************************/

/* Get number from the user */
int GetAddition()
{
    int addition;
    
    printf("\nEnter integer: ");
    scanf("%d", &addition);
    
    return (addition);
}

/* Add the given number to the types */
void AddToStructElement(Elements *element, int addition)
{
    char cast_int[10];
    
    sprintf(cast_int, "%d", addition);
    strcat(element->string, cast_int);
    element->natural += addition;
    element->floatie += addition;
}

/* Go over each cell in the array and send for adding */
void AddToArray(Elements *array)
{
    int addition;
	unsigned int i = 0;
    
    addition = GetAddition();
    
    for(i = 0; i <= (sizeof(array) / ARRAY_LENGTH); ++i)
    {
        AddToStructElement(&array[i], addition);
    }
    
}
