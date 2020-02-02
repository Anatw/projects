#include <ws2_string.h>

//strlen
//Variable Length Parameter:  Return the length of the string s.

int strlen(char s[])
{
	int i = 0;
	while (s[i] != '\0')	
	{
	i++
	}
	return i;
}
