#include <stdio.h>

#include "BitWiseOperations.h"

int main()
{	
	int a = 10;
	int b = 10;
	int c = 263.3;
	
	int res = Pow2(a,b);
	printf( "res1 %d", res);
	
	printf( "is 100 power of 2? %d\n", IsPowOfTwo(100));
	printf( "is 64 power of 2? %d\n", IsPowOfTwo(64)); 
	
	printf( "is 100 power of 2? %d\n\n", IsPowOfTwoWithLoop(100));
	printf( "is 64 power of 2? %d\n", IsPowOfTwoWithLoop(64)); 
	
	printf( "add 1 to 64- %d\n", AddOneToInt(64));					
	printf( "add 1 to 0- %d\n", AddOneToInt(0));
	
	
	/*printsIntsWithExactlyThreeBitsOn*/
	
	printf( "biton 11- %d\n", CountSetBits(11));
	printf( "biton 105- %d\n", CountSetBits(105));
	printf( "biton 11- %d\n", CountSetBitsNoLoop(11));
	printf( "biton 105- %d\n", CountSetBitsNoLoop(105));
	
	printf( "mirror 199- %d\n", ByteMirrorLoop(199));
	printf( "mirror 105- %d\n", ByteMirrorNoLoop(105));
	
	printf( "68 is 2 and 6 are on?- %d\n", IsTwoAndSixBitsAreOn(68));
	printf( "68 is 2 or 6 are on?- %d\n", IsTwoOrSixBitsAreOn(64));
				
	printf( "105 is 2 and 6 are on?- %d\n", IsTwoAndSixBitsAreOn(105));
	printf( "68 is 2 or 6 are on?- %d\n", IsTwoOrSixBitsAreOn(105));
	
	printf( "swap 3 and 5 bits of 8- %d\n", SwapBetweenThirdAndFifthBit(8));
	
	printf( "closet num to 35 divi by 16- %d\n", ClosetNumDivisibleBy16(35));
	
	
	printf( "is 35 divi by 16- %d\n", IsDivisibleBy16(35));
	printf( "is 35 divi by 64- %d\n", IsDivisibleBy16(64));
	
	printf ( "before %d, %d\n", a, b);
	SwapWithBitwise(&a, &b);
	printf ( "after %d, %d\n", a, b);
	
	PrintFloatBits(c);
	printf( "263.3 in binary- %d\n", c );
	
	return (0);
}

