/*******************************************************************************
These function ara ment to control a long-unit array - every bit can be set on
or off individualy, as well as manipulationg all the bits at the same time.

written by Anat Wax, February 23ed 2020.
*******************************************************************************/

#include <stdlib.h>

/* manager function - send 
void BitArray(long *array, int index, int value);

/* set a single bit: */
void SetOn(long *array, int index);
void SetOff(long *array, int index);
void SetBit(long *array, int index, int value);
void GetVal(long *array, int index);
void FlipBit(long *array, int index);

/* set all bits: */
void SetAll(long *array);
void ResetAll(long *array);
void RotL(long *array);
void Mirror(long *array);
void CountOn(long *array);
void CountOff(long *array);
void ToString(long *array);


