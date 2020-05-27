#define _POSIX_C_SOURCE 200112L  /* timespec */
#include <stdio.h>      /*  printf          */
#include <stdlib.h>
#include <sys/time.h>   /*timeofday*/
#include <string.h>     /*  strlen, stcmp   */
#include <pthread.h>    /*  create thread   */

static void Vocabulary(void);
static void *SortCountPart(void *param);
static void PrintBuff(int * buff, size_t counter);
static void MultiplyBuff(int *buff, size_t counter);

typedef struct information
{
    int *start_read;
    int *count_arr;
    int amount_of_work;
    size_t min ;

}info_t;

static void LOG(const char * msg)
{
    fputs(msg,stderr);
}
float timedifference_msec(struct timeval t0, struct timeval t1)
{
    return (t1.tv_sec - t0.tv_sec) * 1000.0f + (t1.tv_usec - t0.tv_usec) / 1000.0f;
}

/******************************************************************************/
#define RETURN_BAD(is_good, status, msg)\
if((is_good)){LOG(msg);}
/******************************************************************************
                                    * MAIN *
******************************************************************************/ 
int main ()
{
    Vocabulary();
    return 0;
}
/******************************************************************************/
#define N_THREADS (6)
#define SIZE_W (25)
#define NUM_DICTIONARY (1)

void Vocabulary(void)
{
    /******FOR TIME*************/
    struct timespec start = {0};
    struct timespec stop = {0};
    double time_result = 0;
    struct timeval t0;
    struct timeval t1;
    float elapsed;

    FILE * fp;
    /**FOR THREAD WORK ************/
    pthread_t jobs[N_THREADS] = {0};
    info_t data[N_THREADS] = {0};
    size_t work_for_thread = 0;
    size_t amount_of_work = 0;
    size_t remainder = 0;
    
    size_t answer = 0;
    size_t min = SIZE_W;
    size_t max = 0;
    
    size_t i = 0;  
    size_t j = 0;

    int *arr_lenght = NULL;
    char buffer[SIZE_W] = {0}; 
    int **count_arr = malloc(sizeof(int *)* N_THREADS);

    /* open dictionary */
    fp = fopen("/usr/share/dict/words","r");
    if (NULL == fp)
    {
        printf("FAIL OPEN\n");
    }
    /* calculate amount of words in dictionary */
    while (NULL != fgets(buffer,SIZE_W,fp))
    {
        ++amount_of_work;
    }

    printf("COUNTER %ld\n", amount_of_work);

    fseek(fp, 0, SEEK_SET);
    /* create the big buffer */
    arr_lenght = calloc(sizeof(int) *NUM_DICTIONARY,amount_of_work);

    /* set all lengths in buff */
  
    for (i = 0; fgets(buffer,SIZE_W,fp) != NULL; ++i)
    {
       arr_lenght[i] = strlen(buffer);
       if(min >arr_lenght[i])
       {
           min = arr_lenght[i];
       }
       if(max < arr_lenght[i])
       {
           max = arr_lenght[i];
       }
    }

    for(i = 0; i < N_THREADS; i++)
    {
        count_arr[i]=  malloc(sizeof(int )* (max- min +1));
    }

    MultiplyBuff(arr_lenght,amount_of_work);
    /* divide the work */
    amount_of_work *= NUM_DICTIONARY;
    work_for_thread = amount_of_work/N_THREADS;
    remainder = amount_of_work - work_for_thread*N_THREADS;
    
    clock_gettime(CLOCK_REALTIME, &start);
    gettimeofday(&t0, 0);
    for ( i = 0; i < N_THREADS-1; ++i)
    {
        data[i].start_read = arr_lenght + i *work_for_thread;
        data[i].amount_of_work = work_for_thread;
        data[i].count_arr = count_arr[i];
        data[i].min = min;

        RETURN_BAD((0 != pthread_create(&jobs[i], NULL, SortCountPart,&data[i])),
                                 1, "FAIL  pthread_create \n")
    }
    data[i].start_read = arr_lenght + i *work_for_thread;
    data[i].amount_of_work = work_for_thread + remainder;
    data[i].count_arr = count_arr[i];
    data[i].min = min;
        
    RETURN_BAD((0 != pthread_create(&jobs[i], NULL, SortCountPart,&data[i])),
                                               1, "FAIL  pthread_create \n")
    for ( i = 0; i < N_THREADS; ++i)
    {
        size_t num = 0;
        RETURN_BAD(0 != pthread_join(jobs[i],(void** )&num),1, "FAIL  pthread_join \n")
      /*   answer += num; */
    }

 	for (i = 1; i < N_THREADS; ++i)
	{
		for(j = 0; j <= max; ++j)
		{
			count_arr[0][j] += count_arr[i][j];
		}
	}

    /*MERG RESULT PAR OF THE COUNTING SORT*/
     for (i = 0; i < max - min + 1; i++)
    {
        while(count_arr[0][i] > 0)
        {
            arr_lenght[j] = i + min;
            count_arr[0][i]--;
            j++;
        }
    }
    gettimeofday(&t1, 0);
    clock_gettime( CLOCK_REALTIME, &stop);

     PrintBuff(arr_lenght, amount_of_work); 
    printf("ANSWER %d\n", answer);
    time_result = (stop.tv_sec - start.tv_sec) * 1e9;
    time_result =(time_result +(stop.tv_nsec - start.tv_nsec))* 1e-9;

    printf("Time :%f \n",time_result);
    elapsed = timedifference_msec(t0, t1);
    printf("Code executed in %f milliseconds.\n", elapsed);

    fclose(fp);
    free(arr_lenght);
    free(count_arr);
}

static void PrintBuff(int * buff, size_t counter)
{
    size_t i = 0;
    for (i = 0; i < counter; i++)
    {
        printf("%d->",buff[i] );
    }
}

static void MultiplyBuff(int *buff, size_t counter)
{
    size_t i = 0;

    for (i = 1; i < NUM_DICTIONARY; i++)
    {
        memcpy(buff + counter * i, buff,  counter);
    }  
}

/*********************************TREAD * WORK*********************************/
static void *SortCountPart(void *param)
{
    info_t * data = param;
    size_t i = 0;
    size_t counter = 0;
    for ( i = 0; i < data->amount_of_work; i++)
    {
        data->count_arr[data->start_read[i] - data->min] +=1;
    }

  /*   for(i = 0; i < data->amount_of_work; ++i)
    {
        counter += data->start_read[i];
    } */

    return (void *)counter;
}
/******************************************************************************/




