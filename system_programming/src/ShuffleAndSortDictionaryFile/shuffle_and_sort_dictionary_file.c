/*******************************************************************************
Comment and un-comment the defines to see all phases (one at a time).

                   Shuffle and sort dictionary file
                          Written by Anat Wax
                            May 19th, 2020
                        Reviewer: Ivanna Fleisher


DICTIONARY_COPIES (2); TOTAL_SIZE (204610):
RADIX_SORT:
Total time 1 thread:  64685.000000
Total time 2 thread:  62187.000000
Total time 4 thread:  57945.000000   BEST 
Total time 8 thread:  64465.000000
Total time 12 thread: 88455.000000

MERGE_SORT:
Total time 1 thread:  190741.000000
Total time 2 thread:  129772.000000
Total time 4 thread:  123278.000000   BEST 
Total time 8 thread:  127298.000000
Total time 12 thread: 124420.000000
*Total time 12 thread: 116653.000000

Q_SORT:
Total time 1 thread:  18694855.000000
*Total time 1 thread: 31027410.000000
Total time 2 thread:  14690227.000000
Total time 4 thread:  12596452.000000   BEST 
*Total time 4 thread: 17610090.000000
Total time 8 thread:  13086875.000000
Total time 12 thread: 19360527.000000
*******************************************************************************/
#include <time.h> /* time, size_t, srand() */
#include <stdio.h> /* printf(), size_t */
#include <pthread.h> /* pthread_t, pthread_create() */
#include <string.h> /* strlen() */

#include "sorts.h"
#include "utility.h"

/*#define DNDBUG*/

/*#define COUNTING_SORT*/
/*#define BUBBLE_SORT*/    /* Too slow to run on my machine */
/*#define SELECTION_SORT*/ /* Too slow to run on my machine */
/*#define INSERTION_SORT*/ /* Too slow to run on my machine */
/*#define RADIX_SORT*/
/*#define MERGE_SORT*/
#define Q_SORT /* Takes some time to run, patience... */
    
static void ReadDictionary(int *dictionary);
static void *SortData(void *begin);
static void Shuffle(int *array, size_t num_elements);
#ifdef Q_SORT
static int QsortCompare(const void *first, const void *second, void *arg);
#endif /* Q_SORT */

#define SIZE (102305)
#define WORD (30)
#define NUM_THREADS (1)
#define DICTIONARY_COPIES (2)
#define TOTAL_SIZE (204610)

size_t total_size = SIZE * DICTIONARY_COPIES;
pthread_t thread[NUM_THREADS] = {0};
/* big_data - one big array to hold all the data: */
int big_data[TOTAL_SIZE] = {0};

int main()
{
    size_t i = 0;
    size_t begin = 0;
    int new_thread_number = 0;
    clock_t start_t, end_t;
		
	start_t = clock();

    /* Entering number repersenting word length of the dictionary inside the \ 
    big_data array */
    ReadDictionary(big_data);
    /* Shuffling the data inside big_data array: */
    Shuffle(big_data, TOTAL_SIZE);

    /* Creating N threads and sending each one of them to the SortData \
    function, from which they will be sent into the different sorting funcs: */
    for (i = 0; i < NUM_THREADS; ++i)
    {
        {
            new_thread_number = i + 1;

            begin = ((total_size / NUM_THREADS) * (new_thread_number - 1)) + 1;

            if (0 != pthread_create(&thread[i], NULL, SortData, &begin))
            {
                printf("ERROR in joining new thread!\n");
            }

            #ifdef DNDBUG
            printf("begin = %ld\n", begin);
            printf("data + (begin / sizeof(int)); = %ld\n", 4 * (begin / sizeof(int)) + begin % 4);
            #endif
        }
    }

    for (i = 0; i < NUM_THREADS; ++i)
    {
        if (0 != pthread_join(thread[i], NULL))
            {
                printf("ERROR in creating new thread!\n");
            }
    }

    /* Merging the entire big_data array: */
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

/* Fisher–Yates shuffle Algorithm: */
static void Shuffle(int *array, size_t num_elements)
{
    int i = 0;
    int j = 0;

    /* Use a different seed value so that we don't get same 
    result each time we run this program */
    srand (time(NULL));
  
    /* Start from the last element and swap one by one. We don't 
    need to run for the first element that's why i > 0 */
    for (i = num_elements - 1; i > 0; --i) 
    { 
        /* Pick a random index from 0 to i */
        j = rand() % (i + 1); 
  
        /* Swap arr[i] with the element at random index */
        Swap(&array[i], &array[j]); 
    } 
}

static void *SortData(void *begin)
{
    #ifdef COUNTING_SORT
    CountingSort((big_data + *(int *)begin), (total_size / NUM_THREADS));
    #endif /* COUNTING_SORT */

    #ifdef BUBBLE_SORT
    BubbleSort((big_data + *(int *)begin), (total_size / NUM_THREADS));
    #endif /* BUBBLE_SORT */

    #ifdef SELECTION_SORT
    SelectionSort((big_data + *(int *)begin), (total_size / NUM_THREADS));
    #endif /* SELECTION_SORT */

    #ifdef INSERTION_SOR
    InsertionSort((big_data + *(int *)begin), (total_size / NUM_THREADS));
    #endif /* INSERTION_SORT */

    #ifdef RADIX_SORT
    RadixSort((big_data + *(int *)begin), (total_size / NUM_THREADS));
    #endif /* RADIX_SORT */

    #ifdef MERGE_SORT
    if (MergeSort((big_data + *(int *)begin), (total_size / NUM_THREADS)))
    {
        printf("ERROR in merge sort\n");
    }
    #endif /* MERGE_SORT */

    #ifdef Q_SORT
    Qsort((big_data + *(int *)begin), (total_size / NUM_THREADS),
          (total_size / NUM_THREADS), QsortCompare, NULL);
    #endif /* Q_SORT */

    return (NULL);
}

#ifdef Q_SORT
static int QsortCompare(const void *first, const void *second, void *arg)
{
    UNUSED(arg);

    return (*(int *)first - *(int *)second);
}
#endif /* Q_SORT */
