/*******************************************************************************
These function ara ment to control a long-unit array - every bit can be set on
or off individualy, as well as manipulationg all the bits at the same time.

written by Anat Wax, February 23ed 2020.
*******************************************************************************/
#ifndef BITARRAY_H
#define BITARRAY_H

/* the type of the array based on the word-size of the architecture */
typedef size_t bit_array_t;

/* manager function - send */
bit_array_t BitArray(bit_array_t *array, int index, int value);

/* set a single bit: */
bit_array_t SetOn(bit_array_t array, int index);
bit_array_t SetOff(bit_array_t array, int index);
bit_array_t SetBit(bit_array_t array, int index, int value);
bit_array_t GetVal(bit_array_t array, int index);
bit_array_t FlipBit(bit_array_t array, int index);

/* set all bits: */
bit_array_t SetAll();
bit_array_t ResetAll();
bit_array_t RotL(bit_array_t array, int rot_num);
bit_array_t Mirror(bit_array_t array);
size_t CountOn(bit_array_t array);
size_t CountOff(bit_array_t array);

/* recieces bit array and a opointer to an array in the size of				*/
/* ((sizeof(bit_array) + 1) * 64), returns its elements status as a string  */
char *ToString(bit_array_t array, char *dest);

#endif /* BITARRAY_H */
