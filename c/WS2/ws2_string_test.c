#include <stdio.h>
#include "ws2_string.h"
#include <assert.h>
#include <stdlib.h>
#include <string.h>


int main()
{
	char s[] = "Hello 2 u world!";
	
	char *new_string = Strdup(s);
	
	printf("%ld", Strlen(s));
	printf("\n");
	
	printf("%s\n", new_string);
	
	free(new_string);

	printf("\n");
	return 0;
}



/*
int main()
{
	assert(Strlen("anat")==4);
	
	return 0;
}



const char s1[] = "WORld!";
	const char s2[] = "woRldz!";



//printf("mine: %d\n", Strcasecmp(s1, s2));
	//printf("%d\n", strcasecmp(s1, s2));




*/







