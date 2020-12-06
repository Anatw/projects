/*******************************************************************************
Comment and un-comment the defines to send the array into the different sorting functions.

                     Multy threaded counting sort
                          Written by Anat Wax
                          May 18th-19th, 2020
                         Reviewer: Haim Sa'adia
                                  &
                    Shuffle and sort dictionary file
                          Written by Anat Wax
                            May 19th, 2020
                        Reviewer: Ivanna Fleisher

DICTIONARY_COPIES (10); TOTAL_SIZE (1023050):


DICTIONARY_COPIES (5); TOTAL_SIZE (511525):
Total time 1 thread: 446693.000000
Total time 3 thread: 446751.000000
Total time 4 thread: 446672.000000
*******************************************************************************/
#include <stdio.h> /* printf(), size_t */
#include <string.h> /* strlen() */
#include <pthread.h> /* pthread_t, pthread_create()  */
#include <stdatomic.h> /* atomic_int */
#include <unistd.h> /* ssize_t */
#include <time.h> /* time() */

#include "sorts.h"
#include "utility.h"

/**** Exercises: ****/
/*#define DNDBUG*/
/* #define MERGE_TESTING - Currently not working good enough - need more work */
#define SHUFFLE_AND_SORT_THREADS
/*#define MULTY_THREADED_COUNTING_SORT*/

/**** Shuffle and sort threads - different sorting algorithm: ****/
/*#define COUNTING_SORT*/
/*#define BUBBLE_SORT*/    /* Too slow to run on my machine */
/*#define SELECTION_SORT*/ /* Too slow to run on my machine */
/*#define INSERTION_SORT*/ /* Too slow to run on my machine */
/*#define RADIX_SORT*/
/*#define MERGE_SORT*/
/*#define Q_SORT*/ /* Takes some time to run, patience... */

static void ReadDictionary(int *dictionary);
static void *SortData(void *param);
void *CountMe(void *index);

#define SIZE (102305)
#define WORD (30)
#define NUM_THREADS (2)
#define DICTIONARY_COPIES (5)
#define TOTAL_SIZE (511525)

size_t total_size = SIZE * DICTIONARY_COPIES;
pthread_t thread[NUM_THREADS] = {0};
/* big_data - one big array to hold all the data: */
int big_data[TOTAL_SIZE] = {0};
atomic_int t_num = 0;

typedef struct information
{
    size_t begin;
    size_t middle;
    size_t end;
    int size;
}info_t;

int main()
{
    int i = 0;
    info_t data[NUM_THREADS] = {0};
    #ifdef MERGE_TESTING
    ssize_t j = 0;
    ssize_t begin = 0;
    ssize_t middle = 0;
    ssize_t end = -1;
    int counter = 0;
    static int temp_t_num = 0;
    #endif /* MERGE_TESTING */
    
    struct timespec start = {0};
    struct timespec finish = {0};
	double running_time = 0;

    ReadDictionary(big_data);
    clock_gettime(CLOCK_MONOTONIC, &start);
    /* Creating N threads and sending each one of them to the SortData function, from which they will be sent into counting-sort: */
    #ifndef MULTY_THREADED_COUNTING_SORT
    for (i = 0; i < NUM_THREADS; ++i)
    {
        data[i].begin = (total_size / NUM_THREADS) * (i + 1);
        if (0 == i)
        {
             data[i].begin = 0;
        }
        if (0 != pthread_create(&thread[i], NULL, SortData, (void *)i))
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
#endif /* MULTY_THREADED_COUNTING_SORT */


#ifndef SHUFFLE_AND_SORT_THREADS
    for (i = 0; i < NUM_THREADS; ++i)
    {
        if (0 != pthread_create(&thread[i], NULL, CheckDifferentSorts, &i))
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
    #endif /* SHUFFLE_AND_SORT_THREADS */
    
    /* Merging the entire big_data array: */
    #ifdef SHUFFLE_AND_SORT_THREADS
    CountingSort(big_data, total_size);
    #endif /* SHUFFLE_AND_SORT_THREADS */

    #ifdef COUNTING_SORT
    CountingSort(big_data, total_size);
    #endif /* COUNTING_SORT */
    
    #ifdef BUBBLE_SORT
    BubbleSort(big_data, total_size);
    #endif /* BUBBLE_SORT */

    #ifdef SELECTION_SORT
    SelectionSort(big_data, total_size);
    #endif /* SELECTION_SORT */

    #ifdef INSERTION_SORT
    InsertionSort(big_data, total_size);
    #endif /* INSERTION_SORT */

    #ifdef RADIX_SORT
    RadixSort(big_data, total_size);
    #endif /* RADIX_SORT */

    #ifdef MERGE_SORT
    MergeSort(big_data, total_size);
    #endif /* MERGE_SORT */

    #ifdef Q_SORT
    Qsort(big_data, total_size, total_size, QsortCompare, NULL);
    #endif /* Q_SORT */


    #ifdef MERGE_TESTING
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

            if ((size_t)end < total_size &&
                (size_t)end > (total_size / NUM_THREADS) * (NUM_THREADS - 1))
            {
                end = total_size;
            }
        
        Merge(big_data, begin, middle, end);
        printf(" \ninside merge - temp_t_num = %d\n\n", temp_t_num
        );
        printf(" inside merge - begin = %ld\n", begin);
        printf(" inside merge - middle = %ld\n", middle);
        printf(" inside merge - end = %ld\n", end);
        }
        
        end = -1;
        temp_t_num *= 2;
    }
    #endif /* MERGE_TESTING */

    /* Printing the sorted array */
    #ifdef DNDBUG
    for (i = 0; (size_t)
    i < total_size ; ++i)
    {
        printf("%d->", big_data[i]);
    }
    #endif

    running_time = (start.tv_sec - finish.tv_sec);

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
    for (; (size_t)j < total_size; ++j)
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
    size_t begin = (total_size / NUM_THREADS) * ((int)index);
    printf("SortData: begin = %ld\n\n", begin);

    CountingSort((big_data + begin), (total_size / NUM_THREADS));

    ++t_num;

    return (NULL);
}

void *CheckDifferentSorts(void *unused)
{
    static atomic_int t_num = 0;

    #ifdef COUNTING_SORT
    CountingSort((big_data + *(int *)begin_indicator.begin[begin_indicator.thread_number]), (total_size / NUM_THREADS));
    #endif /* COUNTING_SORT */

    #ifdef BUBBLE_SORT
    BubbleSort((big_data + *(int *)begin_indicator.begin[begin_indicator.thread_number]), (total_size / NUM_THREADS));
    #endif /* BUBBLE_SORT */

    #ifdef SELECTION_SORT
    SelectionSort((big_data + *(int *)begin_indicator.begin[begin_indicator.thread_number]), (total_size / NUM_THREADS));
    #endif /* SELECTION_SORT */

    #ifdef INSERTION_SOR
    InsertionSort((big_data + *(int *)begin_indicator.begin[begin_indicator.thread_number]), (total_size / NUM_THREADS));
    #endif /* INSERTION_SORT */

    #ifdef RADIX_SORT
    RadixSort((big_data + *(int *)begin_indicator.begin[begin_indicator.thread_number]), (total_size / NUM_THREADS));
    #endif /* RADIX_SORT */

    #ifdef MERGE_SORT
    if (MergeSort((big_data + *(int *)begin_indicator.begin[begin_indicator.thread_number]), (total_size / NUM_THREADS)))
    {
        printf("ERROR in merge sort\n");
    }
    #endif /* MERGE_SORT */

    #ifdef Q_SORT
    Qsort((big_data + *(int *)begin_indicator.begin[begin_indicator.thread_number]), (total_size / NUM_THREADS),
          (total_size / NUM_THREADS), QsortCompare, NULL);
    #endif /* Q_SORT */

    UNUSED(unused);
    ++t_num;
    
    return (NULL);
}

void *CountMe(void *index)
{
    printf("index = %ls\n", (int *)index);

    return (NULL);
}