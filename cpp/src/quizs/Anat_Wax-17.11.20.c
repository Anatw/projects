/*******************************************************************************
Implementation:
Write a program that prints the numbers from 1 to 100 and for multiples of ‘3’
print “Fizz” instead of the number and for the multiples of ‘5’ print “Buzz”.

Design a TIC TAC TOE game 
* what are the classes and main methods ? How will u represent the game ? 
** how will u share and pass data between 2 players ? 
*** what is the minimal amount of data needed to be used to represent the game / games moves ? (im trying to ask how many states do u have) 


Authour: Anat Wax, anatwax@gmail.com
Datecreation: 17.11.2020
Version: 1
*******************************************************************************/
#include <stdio.h> /* printf */

// If the number is both - a multiplication of 3 and 5, the function will print both.
void FizzBuzz()
{
    for (int i = 1; i <= 100; ++i)
    {
        char print_num = 1;
        if ((i % 3) == 0)
        {
            printf("Fizz ");
            print_num = 0;
        }
        
        if ((i % 5) == 0)
        {
            printf("Buzz ");            
            print_num = 0;

        }
        
        if (print_num)
        {
            printf("%d ", i);
        }
    }
}

int main()
{
    FizzBuzz();
    
    return 0;
}

/*



*/