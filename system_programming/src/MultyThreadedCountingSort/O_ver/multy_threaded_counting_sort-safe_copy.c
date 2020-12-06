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
#define COPIES (5)
#define NUM_THREADS (2)

size_t total_size = SIZE * COPIES;
pthread_t *thread = NULL;
int *subarray[SIZE] = {0};

struct Sort_helper
{
    int i;
    int *big_data;
} sort_helper;

int main()
{
    int return_value = 0;
    /* Creating one big array to hold all the data */
    sort_helper->big_data = (int *)calloc( total_size, sizeof(int));

    ReadDictionary(big_data);
    /* Creating N sub-array and thread: */
    for (sort_helper.i = 0; sort_helper.i < NUM_THREADS; sort_helper.i += 1)
    {
        return_value = pthread_create(&thread[sort_helper.i], NULL, SortData, (void *)sort_helper);
        return_value = pthread_join(thread[sort_helper.i], NULL);

        if (0 != return_value)
        {
            printf("ERROR in joining new thread!\n");
        }
        if (0 != return_value)
        {
            printf("ERROR in creating new thread!\n");
        }
    }
    
    free(big_data);
	big_data = NULL;

    return (0);
}

void ReadDictionary(int *big_data)
{
	FILE *fp = fopen("/usr/share/dict/american-english", "r");
    size_t i = 0;
    size_t j = 0;
    char words[WORD] = {0};
    int length = 0;
    static size_t counter = 0;

    while (counter < total_size)
    {
        for (i = 0; i < SIZE; ++i)
        {
            for (; j < total_size; ++j)
            {
                fscanf(fp, "%s", words);
                length = strlen(words);
                big_data[j] = length;
                ++counter;
            }
        }
    }
 
    fclose(fp);
}

void *SortData(void *data)
{
    int new_thread_num = sort_helper.i + 1;
    sort_helper thread_info = (sort_helper)data;

    size_t begin = ((total_size / NUM_THREADS) * (new_thread_num - 1)) + 1;
    size_t end = (total_size / NUM_THREADS) * new_thread_num;
    size_t j = 0;
    size_t i = 0;

    if (end < total_size &&
        end > (total_size / NUM_THREADS) * (NUM_THREADS - 1))
    {
        end = total_size;
    }

    for (j = begin, i = 0; j <= end; ++j, ++i)
    {
        subarray[i] = sort_helper->big_data[j];
    }

    CountingSort(&thread[*(int *)thread_number], (total_size / NUM_THREADS));
}
