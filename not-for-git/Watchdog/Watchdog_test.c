/*******************************************************************************
Comment the DNDBUG option to deliberately crash the main user process - so that the watchdog can revive it.

                          Watchdog - test file
                          Written by Anat Wax
                       May 10th - May 16th, 2020
                         Reviewer: Haim Sa'adia
*******************************************************************************/
#include <stdio.h> /* printf() */
#include <time.h> /* time, srand() */
#include <unistd.h> /* sleep() */
    
#include "utility.h"
#include "Watchdog.h"

/*#define DNDBUG*/

int CrashMyProccess();

int main(int argc, char *argv[])
{
    #ifndef DNDBUG
    int num = 0;
    #endif
    
    printf("~~ Entering the user main process ~~\n\n");
    
    UNUSED(argc);
    
    #ifndef DNDBUG
    srand(time(0));
    num = (rand() % 100) + 1; /* num is now a number between 1 and 100 */
    #endif

    WatchdogStart(argv[0]);
    sleep(10);
    printf("I'm here (1)\n");
    sleep(10);
    printf("still here(2)\n");
    sleep(10);
    printf("still me! (3)\n");
    sleep(10);
    printf("OK, I'll wait... (4)\n");
    sleep(10);
    printf("YooHoo!! (5)\n");
    sleep(10);

    #ifndef DNDBUG
    if (0 == (num % 3)) /* 25% of crashing */
    {
      printf("\n\nPAY ATTANTION: A.OUT: Intending to crush your main programm!\n\n");
      CrashMyProccess();
    }
    #endif
    
    printf("hello there (6)\n");
    sleep(4);
    printf("ahoi (7)\n");
    sleep(4);
    printf("hey, you, it's still me (8)\n");
    sleep(4);
    printf("closing now... (9)\n");
    printf("~&~&~&~& Lets do this again! &~&~&~&~\n");
    sleep(10);
    printf("I'm here (1)\n");
    sleep(10);
    printf("still here(2)\n");
    sleep(10);
    printf("still me! (3)\n");
    sleep(10);
    printf("OK, I'll wait... (4)\n");
    sleep(10);
    printf("YooHoo!! (5)\n");

    WatchdogStop();
    printf("Closing now!!!!\n");

    return (0);
}
