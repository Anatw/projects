/******************************************************************************

Array of Elements

Editor: Haim Saadia
Date: Feb 2020
Reviewer: Anat Wax

*******************************************************************************/

#define ARRAY_LENGTH (3)
#define STRING_LENGTH (20)

#pragma pack(1)

/******************************************************************************/

typedef struct
{
    char string[STRING_LENGTH];
    int natural;
    float floatie;
} Elements;

/******************************************************************************/

/* Go over each type in the struct and print it */
void PrintStructElement(Elements);

/* Go over each cell in the array and send for printing */
void PrintArray(Elements *);

/* Get number from the user */
int GetAddition();

/* Add the given number to the types */
void AddToStructElement(Elements *, int);

/* Go over each cell in the array and send for adding */
void AddToArray(Elements *);
