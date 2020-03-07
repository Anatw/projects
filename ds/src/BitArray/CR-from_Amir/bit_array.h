/*******************************************************************************
These function ara ment to control a long-unit array - every bit can be set on
or off individualy, as well as manipulationg all the bits at the same time.

Written by Anat Wax, February 23th 2020. Reviewer: Amir Paz.
*******************************************************************************/

#ifndef BITARRAY_H
#define BITARRAY_H

/* CHAR_BIT = number of bits in a byte (#include <limits.h>) */
#define ARRAY_LENGTH (sizeof(bit_array_t) * CHAR_BIT) 


/* the type of the array based on the word-size of the architecture */
typedef size_t bit_array_t;

/* set a single bit: */
/* set on a specific bit */
bit_array_t SetOn(bit_array_t array, unsigned int index);

/* set off a specific bit */
bit_array_t SetOff(bit_array_t array, unsigned int index);

/* set a specific bit on (value = 1) or off (value = 0) as valued */
bit_array_t SetBit(bit_array_t array, unsigned int index, unsigned int value);

/* print the value in a specific bit */
int GetVal(bit_array_t array, unsigned int index);

/* flip the value of a specific bit */
bit_array_t FlipBit(bit_array_t array, unsigned int index);

/* set all bits: */                           
bit_array_t SetAll();                       /*חסר הסבר על כל הפונק' מה  כל פונקציה עושה ומה מחזירה במקרה שנכשלה*/
bit_array_t ResetAll();
bit_array_t RotL(bit_array_t array, unsigned int rot_num);
bit_array_t RotR(bit_array_t array, unsigned int rot_num);
bit_array_t Mirror(bit_array_t array);
int CountOn(bit_array_t array);
int CountOnLUT(bit_array_t array);
int CountOff(bit_array_t array);

/* recieces bit array and a pointer to an array in the size of				*/
/* ((sizeof(bit_array) + 1) * 64), returns its elements status as a string  */
char *ToString(bit_array_t array, char *dest);

bit_array_t Reverse(bit_array_t array);    /*חסר הסבר על כל הפונק' מה  כל פונקציה עושה ומה מחזירה במקרה שנכשלה*/

#endif /* BITARRAY_H */
