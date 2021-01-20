/*******************************************************************************
These function ara ment to control a long-unit array - every bit can be set on
or off individualy, as well as manipulationg all the bits at the same time.

written by Anat Wax, February 23th 2020. Reviewer: Amir Paz.
*******************************************************************************/

#ifndef BITARRAY_H
#define BITARRAY_H

/* CHAR_BIT = number of bits in a byte (#include <limits.h>) */
#define ARRAY_LENGTH (sizeof(bit_array_t) * CHAR_BIT) 


/* the type of the array based on the word-size of the architecture */
typedef size_t bit_array_t;

/* set a single bit: */
/* set on a specific bit */
bit_array_t BitArraySetOn(bit_array_t array, unsigned int index);

/* set off a specific bit */
bit_array_t BitArraySetOff(bit_array_t array, unsigned int index);

/* set a specific bit on (value = 1) or off (value = 0) as valued */
bit_array_t BitArraySetBit(bit_array_t array, unsigned int index, unsigned int value);

/* print the value in a specific bit */
int BitArrayGetVal(bit_array_t array, unsigned int index);

/* flip the value of a specific bit */
bit_array_t BitArrayFlipBit(bit_array_t array, unsigned int index);

/* set all bits: */
bit_array_t BitArraySetAll();
bit_array_t BitArrayResetAll();
bit_array_t BitArrayRotL(bit_array_t array, unsigned int rot_num);
bit_array_t BitArrayRotR(bit_array_t array, unsigned int rot_num);
bit_array_t BitArrayMirror(bit_array_t array);
int BitArrayCountOn(bit_array_t array);
int BitArrayCountOnLUT(bit_array_t array);
int BitArrayCountOff(bit_array_t array);

/* recieces bit array and a pointer to an array in the size of				*/
/* ((sizeof(bit_array) + 1) * 64), returns its elements status as a string  */
char *BitArrayToString(bit_array_t array, char *dest);

bit_array_t BitArrayReverse(bit_array_t array);

#endif /* BITARRAY_H */
