#include <stdio.h>
#include <string.h>

int IsPalindrome(const char *str);

int main()
{
	const char *palindrom = "!2teret2!";
	printf("%d", (int)IsPalindrome(palindrom));
	
	return 0;
}


int IsPalindrome(const char *str)
{
	int length = strlen(str);
	char *from_end = (char *)str + length - 1;
	
	while (str < from_end)
	{
		if (*str == *from_end)
		{
			--from_end;
			++str;
		}
		else
		{
			return 0; /* string is not palindrome */
		}
	}
	return 1; /* string is palindrome */
}
