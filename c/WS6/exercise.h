/*****************************************************************************
Different bitwise functions.

Written by Anat Wax anatwax@gmail.com
February 2020
*****************************************************************************/
#ifndef EXERCISE_H
#define EXERCISE_H

long Pow2(unsigned int x, unsigned int y);

int IsPower2a(unsigned int n);

int IsPower2b(unsigned int n);

int AddOne(int a);

void CountSet3Bits(unsigned int *array, int arraySize, unsigned
 int *result);
 
unsigned int ReverseBitsA(unsigned int x);
 
unsigned int ReverseBitsB(unsigned int x);

int BothBits2And6(unsigned char character);

int OrBits2And6(unsigned char character);

int SawpBits3And5(unsigned char character);

unsigned int DivisbleBy16(unsigned int number);

void Swap(int *x, int *y);

int CountBitsOn(int number);

int CountBitsNoLoop(int number);

int FloatInBits(float number);

int BitReturn(int number, int index);

#endif /* EXERCISE_H */