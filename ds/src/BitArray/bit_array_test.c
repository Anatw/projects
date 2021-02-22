/*******************************************************************************
					  	 Written by Anat Wax
						  February 24, 2020
						Reviewer: Amir Paz
*******************************************************************************/

#include <stdio.h> /* printf() */

#include "bit_array.h"

int main()
{
	long array = 1234567;
	char string[65];
	
	BitArrayToString(array, string);
	printf("%s\n\n", string);
	
	printf("SetAll\n");
	array = BitArraySetAll();
	printf("%s\n\n", BitArrayToString(array, string));
	
	printf("ResetAll\n");
	array = BitArrayResetAll();
	printf("%s\n\n", BitArrayToString(array, string));
	
	printf("SetOn\n");
	array = BitArraySetOn(array, 5);
	printf("%s\n\n", BitArrayToString(array, string));
	
	printf("SetOff\n");
	array = BitArraySetOff(array, 5);
	printf("%s\n\n", BitArrayToString(array, string));
	
	printf("SetBit\n");
	array = BitArraySetBit(array, 5, 1);
	printf("%s\n\n", BitArrayToString(array, string));
	
	printf("SetOn\n");
	array = BitArraySetOn(array, 3);
	printf("%s\n\n", BitArrayToString(array, string));
	
	printf("FlipBit\n");
	array = BitArrayFlipBit(array, 6);
	printf("%s\n\n", BitArrayToString(array, string));
	
	printf("GetVal\n");
	printf("%d\n\n", BitArrayGetVal(array, 4));
	
	printf("SetOn\n");
	array = BitArraySetOn(array, 6);
	printf("%s\n\n", BitArrayToString(array, string));
	
	printf("CountOn\n");
	printf("%d\n\n", BitArrayCountOn(array));
	
	printf("CountOnLUT\n");
	printf("%d\n\n", BitArrayCountOnLUT(array));
	
	printf("CountOff\n");
	printf("%d\n\n", BitArrayCountOff(array));
	
	printf("RotL\n");
	array = BitArrayRotL(array, 10);
	printf("%s\n\n", BitArrayToString(array, string));
	
	printf("RotR\n");
	array = BitArrayRotR(array, 20);
	printf("%s\n\n", BitArrayToString(array, string));
	
	return (0);
}
