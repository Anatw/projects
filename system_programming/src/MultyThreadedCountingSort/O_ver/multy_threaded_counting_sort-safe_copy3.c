/*******************************************************************************
Comment and un-comment the defines to send the array into the different sorting functions.

                     Multy threaded counting sort
                          Written by Anat Wax
                          May 18th-19th, 2020
                         Reviewer: Haim Sa'adia

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

#include "sorts.h"
#include "utility.h"

#define DNDBUG

static void ReadDictionary(int *dictionary);
static void *SortData(void *begin);

#define SIZE (102305)
#define WORD (30)
#define NUM_THREADS (16)
#define DICTIONARY_COPIES (5)
#define TOTAL_SIZE (511525)

size_t total_size = SIZE * DICTIONARY_COPIES;
pthread_t thread[NUM_THREADS] = {0};
/* big_data - one big array to hold all the data: */
int big_data[TOTAL_SIZE] = {0};

int main()
{
    size_t i = 0;
    int new_thread_number = 0;
    clock_t start_t, end_t;
    size_t begin = 0;
    size_t middle = 0;
    size_t end = 2;
	start_t = clock();

    ReadDictionary(big_data);

    /* Creating N threads and sending each one of them to the SortData function, from which they will be sent into counting-sort: */
    for (i = 0; i < NUM_THREADS; ++i)
    {
        begin = (total_size / NUM_THREADS) * (new_thread_number) + 1;

        if (0 != pthread_create(&thread[i], NULL, SortData, &begin[i]))
        {
            printf("ERROR in joining new thread!\n");
        }

        #ifdef DNDBUG
        printf("begin[i] = %ld\n", begin[i]);
        printf("data + (begin[i] / sizeof(int)); = %ld\n", 4 * (begin[i] / sizeof
                (int)) + begin[i] % 4);
        #endif
    }

    for (i = 0; i < NUM_THREADS; ++i)
    {
        if (0 != pthread_join(thread[i], NULL))
        {
            printf("ERROR in creating new thread!\n");
        }
    }

    i = 0;
    while (i < NUM_THREADS)
    {
        new_thread_number = i + 1;
        begin[i] = end - 1;
        end = ((total_size / NUM_THREADS) * new_thread_number) * 2;
        middle = (SIZE / 2);

        if (end < total_size &&
            end > (total_size / NUM_THREADS) * (NUM_THREADS - 1))
        {
            end = total_size;
        }

                    printf("begin[i] = %ld\n", begin[i]);
            printf("end = %ld\n", begin[i]);
        Merge(big_data, begin[i], end, middle);

        i += 2;
    }

    /* Printing the sorted array */
    #ifdef DNDBUG
    for (i = 0; i < total_size ; ++i)
    {
        printf("%d->", big_data[i]);
    }
    #endif

    end_t = clock();
	printf("Total time %d thread: %f\n", NUM_THREADS, (double)(end_t - start_t));
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

static void *SortData(void *begin)
{
    CountingSort((big_data + *(int *)begin), (total_size / NUM_THREADS));

    return (NULL);
}
