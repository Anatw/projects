/*****************************************************************************
This is the main-test c file. There are two more files: exercise.h (header
file), exercise.c (the functions's code).

Written by Anat Wax on February 2020. Reviewed by Lior Cohen.
*****************************************************************************/
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

#include "exercise.h"

int main()
{
	/* variables definitions: */
	/* for Pow2 */
	unsigned int x = 4;
	unsigned int y = 6;
	long result1 = Pow2 (x, y);
	
	/* for ispower2 */
	unsigned int n = 8;
	int result2a = ispower2a(n);
	int result2b = ispower2b(n);
	/* int result2b = ispower2b(n); */
	
	/* for addOne */
	int a = 0;
	int result3 = addOne(a);
	
	/* for countSet3Bits */
	unsigned int array[] = {3, 6, 7, 21, 1600, 2};
	int arraySize = sizeof(array) / sizeof(array[0]);
	unsigned int *result4 = (unsigned int *)
		malloc(arraySize * (sizeof(unsigned int)));
	int index = 0;
	
	/* for bothBits2And6 */
	unsigned char character = 'c'; /* 99 in ascii */
	
	/* for orBits2And6 */
	unsigned char character2 = 34;
	
	/* for sawpBits3And5 */
	unsigned char character3 = 4;
	
	/* for divisbleBy16 */
	unsigned int number1 = 67;
	
	/* for  swap */
	int b = 7;
	int r = 20;
	int *pB = &b;
	int *pR = &r;
	
	/* for floatInBits */
	int number2 = 55;
		
	/* for floatInBits */
	float number3 = 6.487;
	
	/****************************/
	/* printing results: */
	
	printf("for Pow2: %ld\n", result1);
	
	printf("for ispower2a (with loop): %d\n", result2a);
	printf("for ispower2b (no loop): %d\n", result2b);
	
	printf("for addOne: %d\n", result3);
	
	countSet3Bits(array, arraySize, result4);
	while((size_t)index <= sizeof(result4) /
	 sizeof(result4[0]))
	{
		printf("for countSet3Bits: %d\n",
		 result4[index]);
		 ++index;
	}
	free(result4);
	
	printf("for reverseBitsA: %d\n", reverseBitsA(25));
	/* expcted resaults = 152 */
	
	printf("for bothBits2And6: %d\n", 
	bothBits2And6(character));
	
	printf("for orBits2And6: %d\n",
	 orBits2And6(character2));
	
	printf("for sawpBits3And5: %d\n",
	 sawpBits3And5(character3));
	 
	printf("for divisbleBy16: %d\n", divisbleBy16(number1)); 
	
	swap(pB, pR);
	printf("for swap: pB: %d, pR: %d\n", b, r);
	
	printf("for setBits: %d\n", setBits(character));
	
	printf("for setBitsNoLoop: %d\n", setBitsNoLoop(number2));
	
	printf("for floatInBits:\n");
	floatInBits(number3);
	printf("\n");
	

	return (0);
}
