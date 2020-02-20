#include <stdio.h>


#define ENDIAN() { \
	unsigned long ul = 1;\
	if (1 == *((unsigned char *)&ul))\
	{\
	puts("Little endian");\
	}\
	else\
	{\
	puts("Big endian");\
	}\
}

int main(void)
{
	ENDIAN();
	
	return 0;
}
