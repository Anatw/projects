#include <stdlib.h>
#include <stdio.h>
#include <string.h>

int *AddingStringToNum(char *num1,char *num2);
int main ()
{
    char *num1 = "222";   
    char *num2 = "111";		
							
	int *result = AddingStringToNum(num1, num2);
	int i;
	int len = strlen(num1);

	
	for(i = 0; i < len; i++)
	{
        printf ("%d", result[i]);   
	}
 printf ("\n");
  return 0;
}


int *AddingStringToNum(char *num1,char *num2)
{
	int longer = 0;
	int shorter = 0;
	int tmp_int = 0;
	char *p_big = '\0';
	char *p_small = '\0';
	int i = 0;
	int *result = '\0';	
	int *remember = '\0';
	
	
	if(strlen(num1) > strlen(num2))
	{
		longer = strlen(num1);
		shorter = strlen(num2);		
		p_big = num1 + longer - 1;
		p_small = num2 + shorter - 1;
	}
	
	else
	{
		longer = strlen(num2);
		shorter = strlen(num1);		
		p_big = num2 + longer - 1;
		p_small = num1 + shorter - 1;
	}

	result = (int *)calloc(longer,sizeof(int) + 1);
	remember = result;
	result += (longer);

	for(i = shorter; i > 0; i--)
	{
		tmp_int = ((*p_big - 48) + (*p_small - 48));

		if(tmp_int > 9)
        {
            *result += tmp_int % 10;
            *(result - 1) += tmp_int / 10;
        }
        
        else
        {
            *result += tmp_int;
		}
		
		p_big--;
		p_small--;
		result--;
	}

	for(i = 1; i <= (longer-shorter) + 1; i++)
    {
		*(result) += ((*p_big) - 48);
		p_big--; 
		result--;
	}

	result = remember + 1;


	return result;
}
