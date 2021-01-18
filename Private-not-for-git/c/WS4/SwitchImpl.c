/************************************************************************
only when the letters 'A' and 'T' are pressed - print a massage to the
terminal.
this is an implementation using switch statement.

written by Anat Wax, February 2020. reviewer: Amir Saraf
*************************************************************************/

#include <stdlib.h>
#include <stdio.h>

int main()
{
	char c = 0;
	system("stty -icanon -echo");	
	
	while((c = getchar()) != 27)
	{
		switch(c)
		{
			case 'A':
			{ 
				printf("A pressed\n");
				break;
			}
			case 'T': 
			{
				printf("T pressed\n");
				break;
			}
		}
	}
	
	system("stty icanon echo");
	return (0);
}
