#include <stdio.h>
#include <string.h>

/***************************************************************************
this function deletes white spaces ("tab" and "spaces") from the beggining
and end of the strind, and deletes duplicte whilte spaces within the string
(replacs sewuences of multiple whitespaces with the first whitespace in the
sequense.
***************************************************************************/

void RmSpaces(char *str);

int main()
{
	char str[] = " this is  a check	";
	printf("%s\n", str);
	RmSpaces(str);
	printf("after Rm\n");
	printf("%s\n", str);
	return 0;
}


void RmSpaces(char *str)
{
	char *read = str;
	char *write = str;
		
	if(*str == ' ' || *str == '\t')
	{
		read++;
	}
	
	while(*read)
	{
		if(!(*read == ' ' || *read == '\t'))
		{
			*write = *read;
			read++;
			write++;
		}
		else
		{
			*write = ' ';
			++write;
			++read;
			read = read + strspn(read, " \t");
		}
	}
	if(*(write - 1) == ' ')
	{
		*(write -1) = '\0';
	}
	else
	{
	*write = '\0';
	}
}
