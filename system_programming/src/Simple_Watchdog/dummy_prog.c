#include <stdio.h> /* printf() */
#include <unistd.h>    /* getpid() */

int main()
{
    printf("I am  a dummy prog, ");
    printf("I am a child!, my pid is %d\n", getpid());

    return (0);
}