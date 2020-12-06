/******************************************************************************
File-	Sorting with Threads		
Author -	Noffar Gil								  
Date -	19.05.20									  
Reviewer -	Amir Paz			
******************************************************************************/


#include <stdio.h>	/*printf()*/
#include <string.h> /* strlen strcpy strcmp */
#include <stdlib.h>	/* malloc() free()*/
#include <pthread.h>/*thread_funcs*/
#include <time.h> 	/* clock(), clock_t, time_t, time() */


#define MAX_WORD_SIZE (23)
#define THREAD_NUM (1)
#define DICT_SIZE (102305)
#define NUM_COPIES (12)

/*   #define TWO_THREADS */
/* #define Three_THREADS */ 
/*  #define FOUR_THREADS */
 
char **LoadDictNtimes(char *path, int n);
void PrintArr(void *arr[], size_t size);
int ShuffleOrder(const void *num1, const void *num2);
int CmpStrings(const void *arg1, const void *arg2);
char **Merge2SortedArray(char **arr1, char **arr2, int arr1_size, int arr2_size);
void *SortStrings(void *arg);


int range =  ((DICT_SIZE * NUM_COPIES) / THREAD_NUM);
char **dictionary;

int main()
{   
    char *path = "/usr/share/dict/american-english";
    dictionary = LoadDictNtimes(path, NUM_COPIES);
    size_t size = DICT_SIZE * NUM_COPIES;
    int i = 0;
    
    pthread_t thread[THREAD_NUM];
    int base = 0;

    qsort(dictionary, size, 8, ShuffleOrder);
    
    for (i = 0; i < THREAD_NUM; ++i)
    {   
        pthread_create(&thread[i], NULL, SortStrings, (void *)base);
        base = base + range;
    }

    for (i = 0; i < THREAD_NUM; ++i)
    {
        pthread_join(thread[i], NULL);
    }

#ifdef TWO_THREADS 
    printf("error\n");
    dictionary = Merge2SortedArray(dictionary, dictionary + range, range, range);
#endif

#ifdef THREE_THREADS
    dictionary = Merge2SortedArray(Merge2SortedArray(dictionary, 
    												dictionary + range, 
    												range, 
    												range), 
    								dictionary + (range * 2), 
    								range * 2, 
    								range);
 #endif

#ifdef FOUR_THREADS
   dictionary = Merge2SortedArray(Merge2SortedArray(dictionary, 
    												dictionary + range, 
    												range, 
    												range), 
    								Merge2SortedArray(dictionary + (2 * range), 
    												dictionary + (3 * range), 
    												range, 
    												range), 
    								range * 2, 
    								range * 2);
 #endif

/*     PrintArr((void**)dictionary, DICT_SIZE * NUM_COPIES);
 */
    return (0);
}

char **LoadDictNtimes(char *path, int n)
{
	FILE *dict;
	char **words_arr = NULL;
	char buff[MAX_WORD_SIZE];
	size_t i = 0;
    size_t j = 0;
    int counter = 0;
	
	words_arr = (char **)malloc(sizeof(char *) * (DICT_SIZE * n));
	dict = fopen(path, "r");
	
	if (!dict)
	{
		return (NULL);
	}
    /* Loading the dictionary for the first time */
        for(i = 0; i < DICT_SIZE; ++i)
	    {	
            fscanf(dict, "%s", buff);
	    	words_arr[i] = (char *)malloc(strlen(buff) + 1);
	    	strcpy(words_arr[i], buff);
	    }

    /* create n - 1 copies of dictionary */
        while(counter < n -1)
        {    
            for (j = 0; j < DICT_SIZE; ++j, ++i)
            {
                words_arr[i] = words_arr[j];
            }

            ++counter;
        }

	return (words_arr);
}

void PrintArr(void *arr[], size_t size)
{
    
    for(int i = 0; i < size; ++i)
    {
        printf("%s  ----  %d\n", (char *)arr[i], i);
    } 

    printf("the size is %ld\n", size);
}

/* wrap for qsort pointer to function 
	instead of using strcmp, return rand number at the range of -57 to 57
	to make shuffle order */
int ShuffleOrder(const void *num1, const void *num2)
{
    int flag = 0;
    (void)num1;
    (void)num2;

    flag = (rand() % 114) - 57;

    return (flag);
    
}

/* wrap for qsort pointer to function create an ordered dictionary */
int CmpStrings(const void *arg1, const void *arg2)
{
    const char **str1 = (const char **)arg1;
    const char **str2 = (const char **)arg2;

    return (strcmp(*str1, *str2));
}

void *SortStrings(void *arg)
{
    int base = (int)arg;
#ifndef NDEBUG
    printf("the base is %d\n", base);
    printf("the range is %d\n", range);
#endif /* NDEBUG */
    
    qsort(dictionary + base, range, sizeof(char *), CmpStrings);
}

char **Merge2SortedArray(char **arr1, char **arr2, int arr1_size, int arr2_size)
{
	int i = 0;		/* arr1 loop counter */
	int j = 0;		/* arr2 loop counter */
	int k = 0;		/* merge_array loop counter */
	
	char **merged_array = (char **)malloc(sizeof(char *) *(arr1_size + arr2_size));

	/* merge temp arrays back into arr[].
		while there are elements at the TWO subarrays compare values of first 
		index at the two subarrays and copy the smallest value to arr[] */
        
	while (i < arr1_size && j < arr2_size)
	{
        if(strcmp(arr1[i], arr2[j]) < 0)
		{
			merged_array[k] = arr1[i];
			++i;
		}
		else
		{
			merged_array[k] = arr2[j];
			++j;
		}
		++k;
	}
	
	/* copy the remaining elements of top_arr/ bottom_arr if there are*/
	while (i < arr1_size)
	{
		merged_array[k] = arr1[i];
		++i;
		++k;
	}
	while (j < arr2_size)
	{
		merged_array[k] = arr2[j];
		++j;
		++k;
	}

	return (merged_array);
}
