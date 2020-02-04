#include <stdio.h>
#include "ws2_string.h"
#include <assert.h>
#include <stdlib.h>


int main()
{
	char s[] = "Hello 2 u world!";
	const char s1[] = "WORld!";
	const char s2[] = "woRldz!";
	//printf("%u", Strlen(s));

	printf("%d", Strcasecmp(s1, s2));
	printf("\n");

	return 0;
}



/*
int main()
{
	assert(Strlen("anat")==4);
	
	return 0;
}
*/
