#define MAX2(a, b) (((a) > (b)) ? (a) : (b))
#define MAX3(a, b, c) (((a) > (b)) ? (a) : ((c) > (b)) ? (c) : (b))
#define SIZEOF_VAR(var) ((char *)(&var+1)-(char*)(&var))
#define SIZEOF_TYPE(type) ((type *)(1 + ((type *)0)))

#include <stdio.h>


int main() 
{
	int d, e, f;
    
    d = 1;
    e = 66;
    f = 7;
    
    printf("\n%d\n", MAX2(d, e));
    printf("%d\n", MAX3(d, e, f));
    printf("%ld\n", SIZEOF_VAR(d));
    printf("%d\n", SIZEOF_TYPE(int));
    
    return (0);
}
