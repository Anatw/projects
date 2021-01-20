#ifndef BITARRAY_H
#define BITARRAY_H

/* the type of the array based on the word-size of the architecture */
typedef size_t bitarray_t;

/* recieves bit array and turns on index, returns bit array */
bitarray_t SetOn(bitarray_t arr, int index);

/* recieves bit array and turns off index, returns bit array */
bitarray_t SetOff(bitarray_t arr, int index);

/* recieves bit array and turns on all the elements, returns bit array */
bitarray_t SetAll();

/* recieves bit array and turns off all the elements, returns bit array */
bitarray_t ResetAll();

/* recieves bit array and sets index to value, returns bit array */
bitarray_t SetBit(bitarray_t arr, int index, int value);

/* recieves bit array and index, returns the value of index */
int GetVal(bitarray_t arr, int index);

/* recieves bit array and index, flips the value in index and returns *
 * bit array 														  */
bitarray_t Flip(bitarray_t arr, int index);

/* recieves bit array, rotate it n times right, returns bit array */
bitarray_t RotR(bitarray_t arr, int n);

/* recieves bit array, rotate it n times left, returns bit array */
bitarray_t RotL(bitarray_t arr, int n);

/* recieves bit array, reverse its content, returns bit array */
bitarray_t Mirror(bitarray_t arr);

/* recieves bit array, returns the amount of on elements */
size_t CountOn(bitarray_t arr);

/* recieves bit array, returns the amount of off elements */
size_t CountOff(bitarray_t arr);

/* recieves bit array and char string dest (at least wordsize * CHAR_BIT + 10) *
 * make a string of the bit array content and returns its elements */
char *ToString(bitarray_t arr, char *dest);

#endif /* BITARRAY_H */
