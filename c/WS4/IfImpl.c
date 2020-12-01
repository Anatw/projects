/************************************************************************
only when the letters 'A' and 'T' are pressed - print a massage to the
terminal.
this is an implementation using a if statement.

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
		if(c == 'A')
		{
			printf("A pressed\n");
		}
		else if (c == 84)
		{
			printf("T pressed\n");
		}
	}
	
	system("stty icanon echo");
	return 0;
}
