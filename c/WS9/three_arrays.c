/*******************************************************************************
This function recieves three arrays. the function prints the letters that 
appear in both the first 2 arrays, but does not appear in the third arrray.
		  
Written by Anat Wax on February 20, 2020. Reviewer: Noffar Gil
*******************************************************************************/

#include <stdio.h> /* printf() */
#include <stdlib.h> /* */
#include <string.h> /* strlen(), strcat() */

#define LUTSIZE (123)/* ascii: 'A' = 65, 'Z' = 90, 'a' = 97, 'z' = 122 : 122-65=*/
#define LUTSHIFT (65)  /* ascii: 'A' = 65 */

enum cell_status
{
	EMPTY,
	STRING1,
	STRING2,
};

void PrintIdentical(char* string1, char* string2, char* string3);

int main()
{
	char *string1 = "abgslkjc";
	char *string2 = "cfsfddkja";
	char *string3 = "fbcwekoc";
	
	PrintIdentical(string1, string2, string3);
	 
	return (0);
}

void PrintIdentical(char* string1, char* string2, char* string3)
{
	int s1_length = (int)(strlen(string1));
	int s2_length = (int)(strlen(string2));
	int s3_length = (int)(strlen(string3));
	int temp_array[LUTSIZE] = {0};
	int index = 0;
	
	/* initizlise the entire array as EMPTY */
	for(index = 0; index < LUTSIZE; ++index)
	{
		temp_array[index] = EMPTY;
	}
	
	/* sign every existing letter with 1 */
	for(index = 0; index < s1_length; ++index)
	{
		temp_array[(int)string1[index]] = STRING1;
	}
	
	/* sign every letter that exist in string1 & string2 with 2 */
	for(index = 0; index < s2_length; ++index)
	{
		if(STRING1 == temp_array[(int)string2[index]])
		{
			temp_array[(int)string2[index]] = STRING2;
		}
	}
	
	/* if a cell is signed as 2 and also exist in string3 - turn in EMPTY */
	for(index = 0; index < s3_length; ++index)
	{
		if(EMPTY != temp_array[(int)string3[index]])
		{
			temp_array[(int)string3[index]] = EMPTY;
		}
	}
	
	for(index = 0; index < LUTSIZE; ++index)
	{
		if(STRING2 == temp_array[index])
		{
			printf("%c\n", (char)index);
		}
	}
}	

/*	
	char *string4 = strcat(string1, string2);
	int s4_length = (int)strlen(string4);
	int index = 0;
	
	
	while(index = 0; index < s4_length; ++index)
	{
		if(string4[index] >= 'a' && string4[index] <= 'z')
		{
			
		}
	}
*/
