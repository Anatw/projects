/*******************************************************************************
Multy threaded counting sort

Written by Anat Wax, anatwax@gmail.com
May 18th-19th, 2020

DICTIONARY_COPIES (10); TOTAL_SIZE (1023050):
Total time 1 thread: 204503.000000
Total time 2 thread: 218649.000000
Total time 3 thread: 244477.000000
Total time 4 thread: 195008.000000
Total time 5 thread: 170992.000000  BEST
Total time 8 thread: 219889.000000
Total time 10 thread: 227948.000000
Total time 12 thread: 179124.000000
Total time 16 thread: 166595.000000
Total time 20 thread: 214613.000000

DICTIONARY_COPIES (5); TOTAL_SIZE (511525):
Total time 1 thread: 88493.000000
Total time 2 thread: 94432.000000
Total time 4 thread: 65478.000000  BEST
Total time 5 thread: 97862.000000
Total time 8 thread: 94821.000000
Total time 12 thread: 89527.000000
Total time 16 thread: 113547.000000
*******************************************************************************/
#include <stdio.h> /* printf(), size_t */
#include <string.h> /* strlen() */
#include <pthread.h> /* pthread_t, pthread_create()  */
#include <stdatomic.h> /* atomic_int */
#include <unistd.h> /* ssize_t */
#include <time.h> /* time() */

#include "sorts.h"
#include "utility.h"

#define DNDBUG


static void ReadDictionary(int *dictionary);
static void *SortData(void *begin);

#define SIZE (100)
#define WORD (30)
#define NUM_THREADS (4)
#define DICTIONARY_COPIES (1)
#define TOTAL_SIZE (511525)

int total_size = SIZE * DICTIONARY_COPIES;
pthread_t thread[NUM_THREADS] = {0};
/* big_data - one big array to hold all the data: */
int big_data[TOTAL_SIZE] = {0};

int main()
{
    ssize_t i = 0;
    ssize_t j = 0;
    int new_thread_number = 0;
    clock_t start_t, end_t;
    ssize_t begin = 0;
    ssize_t middle = 0;
    ssize_t end = -1;
    int counter = 0;
    static int temp_t_num = 0;
    
    struct timespec start, finish;
	double running_time = 0;

    ReadDictionary(big_data);
    clock_gettime(CLOCK_MONOTONIC, &start);
    /* Creating N threads and sending each one of them to the SortData function, from which they will be sent into counting-sort: */
    for (i = 0; i < NUM_THREADS; ++i)
    {
        if (0 != pthread_create(&thread[i], NULL, SortData, &i))
        {
            printf("ERROR in creating new thread!\n");
        }
    }

    for (i = 0; i < NUM_THREADS; ++i)
    {
        if (0 != pthread_join(thread[i], NULL))
        {
            printf("ERROR in joining new thread!\n");
        }
    }


    #ifndef MERGE_TESTING
    temp_t_num = (NUM_THREADS / (NUM_THREADS / 2));
    counter = (NUM_THREADS / (NUM_THREADS / 2));
    /* Merging the entire big_data array */
    for (j = 1; j <= (NUM_THREADS / 2); ++j, --counter)
    {
        printf("j = %ld\n\n", j);
        for (i = 0; i < counter; ++i)
        {
            begin = end + 1;
            end = (total_size / (temp_t_num)) * (i + 1);
            middle = begin + ((end - begin) / 2);

            if (end < total_size &&
                end > (total_size / NUM_THREADS) * (NUM_THREADS - 1))
            {
                end = total_size;
            }
        
        Merge(big_data, begin, middle, end);
        printf(" \ninside merge - temp_t_num = %d\n\n", temp_t_num
        );
        printf(" inside merge - begin = %d\n", begin);
        printf(" inside merge - middle = %d\n", middle);
        printf(" inside merge - end = %d\n", end);
        }
        
        end = -1;
        temp_t_num *= 2;
    }
    #endif /* MERGE_TESTING */

    /* Printing the sorted array */
    #ifdef DNDBUG
    for (i = 0; i < total_size ; ++i)
    {
        printf("%d->", big_data[i]);
    }
    #endif

    running_time = (finish.tv_sec - start.tv_sec);

	printf("Total time %d thread: %f\n", NUM_THREADS, running_time);
    return (0);
}

static void ReadDictionary(int *big_data)
{
	FILE *fp = fopen("/usr/share/dict/american-english", "r");
    size_t j = 0;
    char words[WORD] = {0};
    int length = 0;

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

static void *SortData(void *index)
{
    static atomic_int t_num = 0;
    size_t begin = 0;

    begin = (total_size / NUM_THREADS) * t_num + 1;
    if (index = 0)
    {
        begin = 0;
    }

    CountingSort((big_data + begin), (total_size / NUM_THREADS));

    ++t_num;

    return (NULL);
}
