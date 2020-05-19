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
    #include <string.h> /* size_t, atoi(), memset() */
    #include <sys/types.h> /* pid_t */
    #include <sys/wait.h> /* wait() */
    #include <signal.h>    /* sig_atomic_t, kill() */
#include <pthread.h> /* pthread_t, pthread_create(), ptherad_mutex_t, pthread_mutex_init(), pthread_mutex_unlock() */
    #include <semaphore.h> /* sem_init(), sem_destroy(), sem_wait(), sem_post(), sem_trywait(), sem_getvalue() */
    #include <fcntl.h>           /* For O_* constants */
    #include <stdatomic.h> /* atomic_int */

#include "sorts.h"
#include "utility.h"

void ReadDictionary(int *dictionary);
void *SortData(void *thread_struct);

#define SIZE (102305)
#define WORD (30)
#define NUM_THREADS (2)
#define DICTIONARY_COPIES (5)

size_t total_size = SIZE * DICTIONARY_COPIES;
pthread_t thread[NUM_THREADS] = {0};

struct Sort_helper
{
    int *small_data;
    int thread_number;
};

int main()
{
    /* Creating an array of structs */
    struct Sort_helper sort_helper[NUM_THREADS];
    /*sort_helper = malloc(sizeof(sort_helper) * NUM_THREADS);*/
    /* big_data - one big array to hold all the data: */
    int *big_data = (int *)calloc( total_size, sizeof(int));
    int i = 0;
    size_t begin = 0;
    size_t end = 0;
    int new_thread_number = 0;

    ReadDictionary(big_data);
    /* Creating N sub-array and thread and send each one of them to the SortData function, from which they will be sent into counting-sort: */
    for (i = 0; i < NUM_THREADS; ++i)
    {
        /*for (sort_helper[n].thread_number = 0;
             sort_helper[n].thread_number < NUM_THREADS;
             sort_helper[n].thread_number += 1)*/
        {
            new_thread_number = i + 1;
            sort_helper[i].thread_number = i;

            begin = ((total_size / NUM_THREADS) * (new_thread_number - 1)) + 1;
            end = (total_size / NUM_THREADS) * new_thread_number;

            if (end < total_size &&
                end > (total_size / NUM_THREADS) * (NUM_THREADS - 1))
            {
                end = total_size;
            }

            sort_helper[i].small_data = (int *)malloc (sizeof(int) * (total_size / NUM_THREADS));
            sort_helper[i].small_data = big_data + ((begin / sizeof(int)) + begin % sizeof(int));

            if (0 != pthread_create(&thread[i], NULL, SortData, &sort_helper[i]))
            {
                printf("ERROR in joining new thread!\n");
            }
            printf("begin = %ld\n", begin);
            printf("end = %ld\n", end);
            printf("data + (begin / sizeof(int)); = %ld\n", 4 * (begin / sizeof(int)) + begin % 4);
            
            if (0 != pthread_join(thread[i], NULL))
            {
                printf("ERROR in creating new thread!\n");
            }
             printf("I'm here2\n");
        }
    }
    
    /*for (i = 0; i < NUM_THREADS; ++i)
    {
        FREE(sort_helper[i].small_data);
    }*/

    FREE(big_data);

    return (0);
}

void ReadDictionary(int *big_data)
{
	FILE *fp = fopen("/usr/share/dict/american-english", "r");
    int j = 0;
    char words[WORD] = {0};
    int length = 0;
    static size_t counter = 0;

    /* Index inside big data: */
    for (; j < total_size; ++j)
    {
        fscanf(fp, "%s", words);
        length = strlen(words);
        big_data[j] = length;
        
        /* Return index inside dictionary to the beggining of the file */
        if (fgetc(fp) == EOF)
        {
            fseek(fp, 0, SEEK_SET);
        }
    }
 
    fclose(fp);
}

void *SortData(void *inner_sort_helper)
{
    struct Sort_helper *sort_helper = (struct Sort_helper *)inner_sort_helper;
   /* int new_thread_num = sort_helper[sort_helper.therad_number] + 1;*/

    CountingSort(sort_helper[sort_helper->thread_number].small_data,
                 (total_size / NUM_THREADS));
    
    printf("0 = %d\n", *(sort_helper[sort_helper->thread_number].small_data + 5000));

    return (NULL);
}
