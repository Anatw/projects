/*******************************************************************************
Comment and un-comment the defines to see both phases (one at a time).

                            Simple Watchdog
                          Written by Anat Wax
                            May th, 2020
                          Reviewer: 
*******************************************************************************/
    #include <stddef.h> /* offsetof(), size_t */
    #include <stdlib.h> /* malloc(), free(), abs(), size_t */
    #include <assert.h> /* assert() */
    #include <time.h> /* time, size_t, srand() */
    #include <unistd.h> /* ssize_t, sleep(), execvp(), fork() */
    #include <stdio.h> /* printf(), size_t */
    #include <string.h> /* size_t, atoi() */
    #include <sys/types.h> /* pid_t */
    #include <sys/wait.h> /* wait() */
    #include <signal.h>    /* sig_atomic_t, kill() */
    #include <pthread.h> /* pthread_t, pthread_create(), ptherad_mutex_t, pthread_mutex_init(), pthread_mutex_unlock() */

    #include <semaphore.h> /* sem_init(), se,_destroy(), sem_wait(), sem_post(), sem_trywait(), sem_getvalue() */
    #include <fcntl.h>           /* For O_* constants */
    #include <stdatomic.h> /* atomic_int */


#include "utility.h"
#include "Watchdog.h"

int main(int argc, char *argv[])
{
    int i = 50;
    printf("This is the main process\n");
    printf("creating a watchdog\n");
    UNUSED(argc);

    WatchdogStart(argv[0]);
    for (i = 50; i > 0; --i)
    {
      printf("*************************** i = %d ******************\n", i);
      sleep(5);
      /*printf("I'm here (1)\n");
      sleep(4);
      printf("still here(2)\n");
      sleep(4);
      printf("still me! (3)\n");
      sleep(4);
      printf("OK, I'll wait... (3)\n");
      sleep(10);
      printf("YooHoo!! (4)\n");
      sleep(4);
      printf("hello there (5)\n");
      sleep(4);
      printf("ahoi (6)\n");
      sleep(4);
      printf("hey, you, it's still me (7)\n");
      sleep(4);
      printf("closing now... (8)\n");*/

      if (i == 40)
      {
        WatchdogStop();
      }
    }
    

    /* watchdog stop */

    return (0);
}