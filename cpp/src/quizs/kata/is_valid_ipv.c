/* submitted 8.11.20 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* Return 1 is addr is a valid IP address, return 0 otherwise */
int is_valid_ip(const char *addr)
{
    int array[4] = {0};
    int i = 0;
    int j = 0;
    int counter = 0;
    char temp_str[3] = {0};
  
    for (i = 0; addr[i] != '\0'; ++i)
    {
        if (addr[i] == '.')
        {
            j = 0;
            ++i;
            array[counter] = atoi(temp_str);

            /* If the number is not 0, but the first digit on is IS zero - not valid: */
            if (array[counter] != 0 && '0' == temp_str[0]) /** 0 should be indicated as a char and not as a number **/
            {
                return 0;
            }
            else if (array[counter] < 10)
            {
                if (array[0] == 0)
                {
                    return 0;
                }
            }
            
            if (array[counter] > 255 || array[counter] < 0)
            {
                return 0;
            }

            memset(temp_str, 0, sizeof(temp_str)); /** temp_str must be set to zero in every round so that if the number in the nest slost is smaller than the number of the current slot - they won't interfier */
            ++counter;
        }
        
        if (addr[i] < '0' || addr[i] > '9')
        {
            return 0;
        }

        temp_str[j++] = addr[i];
    }
  
    if (counter != 3)
    {
        return 0;
    }
  
    return 1;
}

void test(const char *str)
{
    printf("%s : %d\n", str, is_valid_ip(str));
}

int main()
{
   /* const char *str = "123.123.123.123";
    const char *str1 = "12.255.56.1";
    const char *str2 = "12.34.56.1";
    const char *str3 = "12.34.56.-1";
    const char *str4 = "123.045.067.089";*/
    const char *str5 = "4.167.95.116";
   /* test(str);
    test(str1);
    test(str2);
    test(str3);
    test(str4);*/
    test(str5);

    return 0;
}



/* Return 1 is addr is a valid IP address, return 0 otherwise 
int is_valid_ip(const char * addr)
{
    char *array[4] = {0};
    int i = 0;
    int j = 0;
    int counter = 0;
    int num = 0;

    for (i = 0; i < 4; ++i)
    {
        array[i] = (char *)calloc(3, sizeof(char));
    }
  
    for (i = 0; addr[i] != '\0'; ++i)
    {
        if (addr[i] == '.')
        {
            ++j;
            ++i;
            ++counter;
        }
        
        array[j][i] = addr[i];
    }
  
    if (counter != 3)
    {
        return 0;
    }
    
    i = 0;
    for (j = 0; j < 4; ++j)
    {
        num = atoi(array[j]);
        if (num > 255 || num < 0)
        {
            return 0;
        }
        else if (array[j][0] == 0)
        {
            return 0;
        }
        else if (num < 10)
        {
            if (array[j][1] == 0)
            {
                return 0;
            }
        }
    }
  
      for (i = 0; i < 4; ++i)
    {
        free(array[i]);
        array[i] = NULL;
    }
  
    return 1;

}

*/