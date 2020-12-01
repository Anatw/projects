/******************************************************************************
							File: BitWiseOperations.h
      				    header of BitWiseOperations.c File
						contain declarations of functions				
							Written by: Noffar Gil
							   Review by:Anat Wax
							   
								Date: 16.02.2020

*******************************************************************************/


#ifndef BITWIZEOPERATIONS_H
#define BITWIZEOPERATIONS_H

/* return result of x*(2^y) */
long Pow2(unsigned int x, unsigned int y);

int IsPowOfTwo(unsigned int n);

int IsPowOfTwoWithLoop(unsigned int n);

/* flip all bits after the rightmost 0 bit. and flip the rightmost 0 bit*/
int AddOneToInt(int num);

void printsIntsWithExactlyThreeBitsOn (unsigned int arr[], unsigned int len);

/* loop through all bits of num, if a bit is set increment the counter */
unsigned int CountSetBits(unsigned int num);

unsigned int CountSetBitsNoLoop(unsigned int num);

int SawpTwoBits(unsigned int x, int first, int second);

unsigned int ByteMirrorLoop(unsigned char num);

unsigned int ByteMirrorNoLoop(unsigned int num);

unsigned int IsTwoAndSixBitsAreOn(unsigned char ch);

unsigned int IsTwoOrSixBitsAreOn(unsigned char ch);

unsigned char SwapBetweenThirdAndFifthBit(unsigned char ch);

unsigned int ClosetNumDivisibleBy16(unsigned int num);

int IsDivisibleBy16(unsigned int num);

void SwapWithBitwise(int *pa, int *pb);

void PrintFloatBits(float num);

#endif

