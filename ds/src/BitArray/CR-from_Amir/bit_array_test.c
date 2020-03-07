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
	
	ToString(array, string);
	printf("%s\n\n", string);
	
	printf("SetAll\n");
	array = SetAll();
	printf("%s\n\n", ToString(array, string));
	
	printf("ResetAll\n");
	array = ResetAll();
	printf("%s\n\n", ToString(array, string));
	
	printf("SetOn\n");
	array = SetOn(array, 5);
	printf("%s\n\n", ToString(array, string));
	
	printf("SetOff\n");
	array = SetOff(array, 5);
	printf("%s\n\n", ToString(array, string));
	
	printf("SetBit\n");
	array = SetBit(array, 5, 1);
	printf("%s\n\n", ToString(array, string));
	
	printf("SetOn\n");
	array = SetOn(array, 3);
	printf("%s\n\n", ToString(array, string));
	
	printf("FlipBit\n");
	array = FlipBit(array, 6);
	printf("%s\n\n", ToString(array, string));
	
	printf("GetVal\n");
	printf("%d\n\n", GetVal(array, 4));
	
	printf("SetOn\n");
	array = SetOn(array, 6);
	printf("%s\n\n", ToString(array, string));
	
	printf("CountOn\n");
	printf("%d\n\n", CountOn(array));
	
	printf("CountOnLUT\n");
	printf("%d\n\n", CountOnLUT(array));
	
	printf("CountOff\n");
	printf("%d\n\n", CountOff(array));
	
	printf("RotL\n");
	array = RotL(array, 10);
	printf("%s\n\n", ToString(array, string));
	
	printf("RotR\n");
	array = RotR(array, 20);
	printf("%s\n\n", ToString(array, string));
	
	return (0);
}
