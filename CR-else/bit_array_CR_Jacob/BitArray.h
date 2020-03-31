/****************************************************************
*          		   Ya'acov Evenchik 24.2.2020                   *
* 				  declaration of Bit Array funcs		 	    *
*                       				              			*
****************************************************************/
#ifndef bitarray_h
#define bitarray_h


typedef size_t ds_t; /* ds_t = data sturct */

/* turn ds_t to string receives ds_t and */
/* string buffer - (sizeof(ds_t * CHAR_BIT + 1)) */
char *ToString(ds_t a, char *str);

/* turn on specific bit receives ds_t and location (int n) */
ds_t SetOn(ds_t a, unsigned int n);

/* turn off specific bit receives ds_t and location (int n)*/
ds_t SetOff(ds_t a, unsigned int n);

/* set on all bits receives ds_t */
ds_t SetAll();

/* set bit on or off receives ds_t , location (int n) and 0/1 (int off_on*/
ds_t SetBit(ds_t a, unsigned int n, unsigned int off_on);

/* set off all bits. receives current ds_t */
size_t ResetAll();

/* return bit on or off receives ds_tand location (int n) */
size_t GetVal(ds_t a, unsigned int n);

/* flip bit on or off receives ds_t and location (int n) */
ds_t FlipBit(ds_t a, unsigned int n);

/* rotate ds_t right receives ds_t and times of rotation (int t) */
ds_t RotR(ds_t a, unsigned int t);

/* rotate ds_t left receives ds_t and times of rotation (int t) */
ds_t RotL(ds_t a, unsigned int t);

/* mirror the bits in ds_t receives ds_t */
ds_t Mirror(ds_t a);

/* count set bits receives ds_t */
size_t CountOn(ds_t a);

/*count non set bits receives ds_t */
size_t CountOff(ds_t a);

#endif

