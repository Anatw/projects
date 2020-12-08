/************************************************************************
only when the letters 'A' and 'T' are pressed - print a massage to the
terminal.
this is an implementation using LUT.

written by Anat Wax, February 2020. reviewer: Amir Saraf
*************************************************************************/

#include <stdlib.h>
#include <stdio.h>

void APressed();
void TPressed();
void DoNothing();

/* this is an array of pointers called p_Char */
void (*p_Char[256]) (); 

int main()
{
	unsigned int c = 0;
	int index = 0;
	for(index = 0; index < 256; ++index)
	{
		p_Char[index] = DoNothing;
	}
	p_Char[65] = APressed;
	p_Char[84] = TPressed;
				
	system("stty -icanon -echo");	
	
	while((c = getchar()) != 27)
	{		
		(*p_Char[c])();
	}
	
	system("stty icanon echo");
	return 0;
}

		
void APressed()
{
	printf("A pressed\n");
}

void TPressed()
{
	printf("T pressed\n");
}

void DoNothing()
{
	;
}

