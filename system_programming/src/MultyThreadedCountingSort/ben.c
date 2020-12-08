/*******************************************************************************
*                                                                              *
*                      Shuffle and Sort Multi-Threaded                         *
*                           System Programming                                 *
*                               20/05/2020                                     *
*                        Author: Ben David Zikri                               *
*                          Reviwer: Kobi Rappaport                             *
*                                                                              *
*******************************************************************************/
#include <stdio.h> /* printf(), fopen(), fclose(), fscanf() */
#include <stdlib.h> /* malloc(), free(), qsort(), rand() */
#include <string.h> /* strcmp() */
#include <time.h> /* clock_gettime(), time(), timespec */
#include <pthread.h>/* pthread_t, pthread_create(), pthread_join() */

#define FREE(p) (free(p), (p) = NULL)
#define DICT_SIZE (102305)
#define NUM_THREADS (4)

char **LoadDict();
int Shuffle(const void *data1, const void *data2);
int CompareStr(const void *data1, const void *data2);
void *ThreadFunction(void *arg);
int Merge(int start, int mid, int end);

char **dictionary;

int main()
{
	int i = 0;
	pthread_t threads[NUM_THREADS];
	struct timespec start, finish;
 	double elapsed = 0;

	dictionary = LoadDict();
	qsort(dictionary, DICT_SIZE, sizeof(char *), Shuffle);
  
  	clock_gettime(CLOCK_MONOTONIC, &start);  

	for (i = 0; i < NUM_THREADS; ++i)
	{
		pthread_create(&threads[i], NULL, ThreadFunction, (void *)i);
	}

	for (i = 0; i < NUM_THREADS; ++i)
	{
		pthread_join(threads[i], NULL);
	}

	elapsed = (finish.tv_sec - start.tv_sec);
  	elapsed += (finish.tv_nsec - start.tv_nsec) / 1000000000.0;
	printf("Sorting took: %f seconds\n", elapsed);
 	
	if(NUM_THREADS == 1)
	{
		Merge(0, (DICT_SIZE / 2) - 1, DICT_SIZE - 1);
	}
	else if(NUM_THREADS == 4)
	{
		Merge(0, (2 * (DICT_SIZE / NUM_THREADS)) - 1, (DICT_SIZE / 2) - 1); 
		Merge(2 * (DICT_SIZE / NUM_THREADS),  (3 * (DICT_SIZE / NUM_THREADS)) -1, DICT_SIZE - 1); 
		Merge(0, (2 * (DICT_SIZE / NUM_THREADS)) -1, DICT_SIZE - 1);
	}
	
	return (0);
}

void *ThreadFunction(void *arg)
{
	int i_arg = (int)arg;
	int start = i_arg * (DICT_SIZE / NUM_THREADS);
	int end = start + (DICT_SIZE / NUM_THREADS);
	
	if (i_arg == NUM_THREADS - 1)
	{
		end += DICT_SIZE % NUM_THREADS;
	}

	qsort(dictionary + start, end - start, sizeof(char *), CompareStr);

	return (NULL);
}

char **LoadDict()
{
	FILE *fp = NULL;
   	size_t i = 0;
   	size_t j = 0;
    char **dictionary = (char **)malloc(sizeof(char *) * DICT_SIZE);
    
    if(!dictionary)
    {
    	return (NULL);
    }
	
   	for (i = 0; i < DICT_SIZE; ++i)
   	{
    	dictionary[i] = (char *)malloc(sizeof(char) * 30);

    	if(!dictionary[i])
    	{
    		for (; j < i; ++j)
    		{
    			FREE(dictionary[j]);
    		}

    		FREE(dictionary);
    		return NULL;
    	}
   	}

	fp = fopen ("/usr/share/dict/american-english", "r");
   
  	for (i = 0; i < DICT_SIZE; ++i)
  	{
		fscanf(fp, "%s\n", dictionary[i]);
  	}

   	fclose(fp);

	return (dictionary);
}

int Shuffle(const void *data1, const void *data2)
{
	(void)(data1);
	(void)(data2);
    
	if (rand() % 100 > 50)
	{
        return (0);
	}
    else
    {
	    return (1);
	}
}

int CompareStr(const void *data1, const void *data2)
{
    return (strcmp(*(char **)data1, *(char **)data2));
}

int Merge(int start, int mid, int end)
{
	int i = start, j = mid + 1, k = start;
	char **b = (char **)malloc((end + 1) * sizeof(char *));
	
	while(i <= mid && j <= end)
	{
		if(strcmp(dictionary[i], dictionary[j]) < 0)
		{
			b[k++] = dictionary[i++];
		}

		else
		{
			b[k++] = dictionary[j++];
		}
	}

	while(i <= mid) 							
	{
		b[k++] = dictionary[i++];
	}

	while(j <= end)
	{
		b[k++] = dictionary[j++];
	}

	for(i = start; i <= end; ++i) 
	{	
		dictionary[i] = b[i];
	}
	FREE(b); 

	return (0);
}