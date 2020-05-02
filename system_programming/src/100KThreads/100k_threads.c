/*******************************************************************************
Each exercise is a macro. Comment and un-comment the different macroes to check
each exersize.
Exercises 5 and 6 are in the same macro, Comment and un-comment the pragma macro to see both exercises (5 comment, 6 un-comment).

                             100k threads
                          Written by Anat Wax
						    May 2nd, 2020
					   Reviewer: Ben-David Zikri
*******************************************************************************/
#include <time.h> /* time, size_t, srand() */
#include <unistd.h> /* ssize_t, sleep() */
#include <stdio.h> /* printf(), size_t */
#include <pthread.h> /* pthread_t, pthread_create() */
#include <omp.h> /* openmp */

#include "utility.h"

#define ARRAY_SIZE (100000)
/*#define MAX_SIZE_POSSIBLE (32000)  for 32000: this program took -33 seconds to run */
#define MAX_SIZE_POSSIBLE (15)
/*
MAX_SIZE_POSSIBLE = 1 : this program took 3 seconds to run
MAX_SIZE_POSSIBLE = 2 : this program took 6 seconds to run
MAX_SIZE_POSSIBLE = 3 : this program took 9 seconds to run
MAX_SIZE_POSSIBLE = 4 : this program took 12 seconds to run
MAX_SIZE_POSSIBLE = 5 : this program took 15 seconds to run
MAX_SIZE_POSSIBLE = 6 : this program took 18 seconds to run
MAX_SIZE_POSSIBLE = 7 : this program took 21 seconds to run
MAX_SIZE_POSSIBLE = 8 : this program took 24 seconds to run
MAX_SIZE_POSSIBLE = 9 : this program took 27 seconds to run
MAX_SIZE_POSSIBLE = 10 : this program took 30 seconds to run
MAX_SIZE_POSSIBLE = 11 : this program took 33 seconds to run
MAX_SIZE_POSSIBLE = 12 : this program took 14 seconds to run
MAX_SIZE_POSSIBLE = 13 : this program took 39 seconds to run
MAX_SIZE_POSSIBLE = 14 : this program took 42 seconds to run
MAX_SIZE_POSSIBLE = 15 : this program took 19 seconds to run (after cancelling sleep)
*/
#define GIANT_NUMBER (1000000000)

/*#define EXER1*/
/*#define EXER2*/
/*#define EXER3*/
/*#define EXER4*/
#define EXER5_6


int array[ARRAY_SIZE] = {0};
static int i = 0;
size_t sum_of_devisors = 0;

void *WriteToArray(void *thread);
void *WriteToArrayAndDetachTread(void *thread);
void CreateThread();
void *SumOfDvisors(void *thread_number);

#ifdef EXER1
int main()
{
    pthread_t new_thread = 0;
    time_t time_begin = 0;
    time_t time_end = 0;
    int counter = 0;

    time_begin = time(NULL);
    for (i = 0; i < ARRAY_SIZE; ++i)
    {
        pthread_create(&new_thread, NULL, WriteToArray, NULL);
    }

    sleep(10);
    /*for (i = ARRAY_SIZE - 1; i >= 0; --i)
    {
        printf("i = %d, array[i] = %d\n", i, array[i]);
    }*/

    for (i = 0; i < ARRAY_SIZE; ++i)
    {
        if (array[i] != i)
        {
            ++counter;
        }
    }
    printf("this is the number of failing threads: %d\n", counter);

    time_end = time(NULL);
    printf("\n\nthis program took %ld seconds to run\n",
           (time_end - time_begin));

    return (0);
}

/*
void CreateThread()
{
    pthread_t new_thread = 0;

    pthread_create(&new_thread, NULL, WriteToArray, &new_thread);
}*/
#endif /* EXER1 */

#ifdef EXER2
int main()
{
     pthread_t new_thread[ARRAY_SIZE] = {0};
     time_t time_begin = 0;
     time_t time_end = 0;
     int return_value = 1;
     int i = 0;

    time_begin = time(NULL);

    for (i = 0; i < ARRAY_SIZE; ++i)
    {
        printf("i = %d\n", i);
        while (0 != return_value)
        {
            return_value = pthread_create(&new_thread[i], NULL, WriteToArray, NULL);
        }

        return_value = 1;
    }

    time_end = time(NULL);
    printf("\n\nthis program took %ld seconds to run\n",
           (time_end - time_begin));

    return (0);
}
#endif /* EXER2 */

void *WriteToArray(void *thread)
{
    UNUSED(thread);
    array[i] = i;

    /*printf("i = %d, array[i] = %d\n", i, array[i]);*/

    return (NULL);
}


#ifdef EXER3
int main()
{
     pthread_t new_thread = 0;
     time_t time_begin = 0;
     time_t time_end = 0;
     int pcreate_return = 1;
     
     int i = 0;

    time_begin = time(NULL);

    for (i = 0; i < ARRAY_SIZE; ++i)
    {
        printf("i = %d\n", i);
        while (0 != pcreate_return)
        {
            pcreate_return = pthread_create(&new_thread, NULL, WriteToArrayAndDetachTread, NULL);
        }
    }

    time_end = time(NULL);
    printf("\n\nthis program took %d seconds to run\n",
           (time_end - time_begin));

    return (0);
}

void *WriteToArrayAndDetachTread(void *thread)
{
    UNUSED(thread);
    int pdetach_return = 1;
    /* pthread_self is a function that returns the id of the current thread */
    pdetach_return = pthread_detach(pthread_self());

    if (0 != pdetach_return)
    {
        printf("ERROR in joining new thread!\n");
       }

    array[i] = i;
    
    return (NULL);
}
/* this function will mark the thread identified as 'thread_id' as detach.
When the detached thread retminted, its resources are automatically released back to the system.
return: 0 in case of success, the error number in case of an error.

int pthread_detach(pthread_t thread_id)
{

} */

#endif /* EXER3 */

#ifdef EXER4
int main()
{
    pthread_t new_thread[MAX_SIZE_POSSIBLE] = {0};
    time_t time_begin = 0;
    time_t time_end = 0;
    int return_value = 1;

    time_begin = time(NULL);

    for (i = 0; i < MAX_SIZE_POSSIBLE; ++i)
    {
        return_value = pthread_create(&new_thread[i], NULL, SumOfDvisors, &i);
        return_value = pthread_join(new_thread[i], NULL);

        if (0 != return_value)
        {
            printf("ERROR in joining new thread!\n");
        }
        if (0 != return_value)
        { 
            printf("ERROR in creating new thread!\n");
        }
    }

    time_end = time(NULL);
    printf("\n\nthis program took %ld seconds to run\n", (time_end - time_begin));

    printf("sum of devisors for 1000000000 is %ld\n", sum_of_devisors);

    return (0);
}

void *SumOfDvisors(void *thread_number)
{
    int new_thread_num = *(int *)thread_number + 1;
    int begin = ((GIANT_NUMBER / MAX_SIZE_POSSIBLE) * (new_thread_num - 1)) + 1;
    int end = (GIANT_NUMBER / MAX_SIZE_POSSIBLE) * new_thread_num;
    int j = 0;

    /*
    This is part is ment for the final round: in case that the giant number can't be devided into a whole number when devided by number-of-threads,  the variable "end" needs to specificly be told to be equal to the giant number.
    */
    if (end < GIANT_NUMBER &&
        end > (GIANT_NUMBER / MAX_SIZE_POSSIBLE) * (MAX_SIZE_POSSIBLE - 1))
    {
        end = GIANT_NUMBER;
    }

    printf("end = %d\n", end);

    pthread_detach(pthread_self());

    for (j = begin; j <= end; ++j)
    {
        if (0 == GIANT_NUMBER % j)
        {
            sum_of_devisors += j;
        }
    }

    return (NULL);
}

#endif /* EXER4 */


#ifdef EXER5_6
int main()
{
    size_t sum_of_devisors = 0;
    size_t i = 1;
    time_t time_begin = 0;
    time_t time_end = 0;

    time_begin = time(NULL);
    
    /*#pragma omp parallel*/
    
    for (i = 1; i <= GIANT_NUMBER; ++i)
    {
        if (0 == GIANT_NUMBER % i)
        {
            sum_of_devisors += i;
        }
    }

    printf("Sum of devisors for %d is %ld\n", GIANT_NUMBER, sum_of_devisors);

    time_end = time(NULL);
    printf("\n\nThis program took %ld seconds to run\n",
           (time_end - time_begin));

    return (0);
}

/*
from terminal:
sum of devisors for 1000000000 is 2497558338


this program took 66 seconds to run



#2
Sum of devisors for 1000000000 is 2497558338


This program took 38 seconds to run


#3 - EXER6: with openmp:
Sum of devisors for 1000000000 is 2497558338


This program took 34 seconds to run
*/
#endif /* EXER5_6 */