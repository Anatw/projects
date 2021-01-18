/*THIS FILE WAS CHANGED BY ANAT ON FABRUARY 6TH */
/*int Ws2_Strlen(const char *str);

int Ws2_Strcmp(const char *str1, const char *str2);

char *Ws2_Strcpy(char *destination, const char *source);

char *Ws2_Strncpy(char *destination, const char *source, size_t n);

int Ws2_Strcasecmp(const char *str1, const char *str2);

const char *Ws2_Strchr(const char *str, int c);

char *Ws2_Strdup(const char *str);

char *Ws2_Strcat(char *dest, const char *src);

char *Ws2_Strncat(char *dest, const char *src, size_t n);

char *Ws2_Strstr(const char *str1, const char *str2);

size_t Ws2_Strspn(const char *str1, const char *str2);

char *Ws2_Strtok(char *str, const char *delim);*/

#define _POSIX_C_SOURCE 200809L
#include <stdio.h>
#include <string.h>
#include <strings.h>
#include <stdlib.h>
#include "ws2_string.h"

int main()
{
	/* check strlen */
	char strleng[] = "abcdefg  9+hijk";
	char cmp1[] = "wow this gis";
	char cmp2[] = "wow this iss";
	char cpydes[100] = "hello this ";
	char cpysrc[] = "is crazyyyyy"; 
	int test = 'k';
	char cpydes1[100] = "hello this ";
	char cpysrc1[] = "is crazyyyyy"; 
	char haystack[] = "hello world";
	char needle[] = "wo";
	char haystack1[] = "hello world";
	char needle1[] = "wz";
	char haystack2[] = "hello world";
	char needle2[] = "wd";
	char c_strtok[] = "wow-this-is-amazing-shit-indeed";
	char *dupfree;
	char *token;

	printf("check Strlen\n\n");
	
	printf("%d\n", Ws2_Strlen(strleng));
	printf("%ld\n\n", strlen(strleng));
	
	printf("check Strcmp\n\n");
	
	printf("%d\n",Ws2_Strcmp(cmp1, cmp2));
	printf("%d\n\n",strcmp(cmp1, cmp2));
	
	printf("check Strcpy\n\n");
	
	printf("%s\n",Ws2_Strcpy(cpydes, cpysrc));
	printf("%s\n\n",strcpy(cpydes, cpysrc));
	
	printf("check Strncpy\n\n");
	
	printf("%s\n",Ws2_Strncpy(cpydes, cpysrc, 3));
	printf("%s\n\n",strncpy(cpydes, cpysrc, 3));
	
	printf("check Strcasecmp\n\n");
	
	printf("%d\n",Ws2_Strcasecmp(cmp1, cmp2));
	printf("%d\n\n",strcasecmp(cmp1, cmp2));
	
	printf("check Strchr\n\n");
	
	printf("%s\n", Ws2_Strchr(strleng, test));
	printf("%s\n\n", strchr(strleng, test));
	
	printf("check Strdup\n\n");
	
	dupfree = Ws2_Strdup(strleng);
	
	/*printf("%s\n", Ws2_Strdup(strleng));*/
	printf("%s\n\n", strdup(strleng));
	
	free(dupfree);
	printf("check Strcat\n\n");
	
	printf("%s\n", Ws2_Strcat(cpydes1, cpysrc1));
	printf("%s\n\n", strcat(cpydes1, cpysrc1));
	
	printf("check Strstr\n\n");
	
	printf("%s\n", Ws2_Strstr(haystack, needle));
	printf("%s\n\n", strstr(haystack, needle));
	
	printf("check Strspn\n\n");
	
	printf("%lu\n", Ws2_Strspn(haystack1, needle1));
	printf("%lu\n\n", strspn(needle2, haystack2));
	
	printf("check Strtok\n\n");
	
	
		token = Ws2_Strtok(c_strtok, "-");
		
		while (token != NULL)
		{
			printf("%s\n", token);
			token = Ws2_Strtok(NULL, "-");
		}
		
	return 0;
	}
	
  
    
	
	

