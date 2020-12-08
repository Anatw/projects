#define _POSIX_C_SOURCE 200809L
#include <stdio.h>
#include <string.h>
#include <strings.h>
#include <stdlib.h>
#include "ws2_string.h"










char *Ws2_Strdup(const char *str)
{
	
	int leng = (strlen(str));
    	/* create string in correct size*/ 
	char *str_returned = (char*) malloc(sizeof(char) * (leng + 1));
	
	while(*str)
	{
	    *str_returned = *str;
	    str_returned++;
	    str++;
	}
    *str_returned = '\0';
	return str_returned - (leng); /*do not froget to free!!!*/
}

int main()
{
	int i = 0;
	int b[10];
	int *p = (int*) malloc(sizeof(int)*3);
	if(p[i] == p[i+1])
	printf("check Strdup\n\n");
	//free(p);
	
	printf("%d", *p);
	//printf("%s\n", Ws2_Strdup(strlen));
	
	printf("%d\n", b[10]);

	//for(p=0; p<=9; p++)
	//{
	//	p[i] = 7;
	//}
	
	return 0;
}
