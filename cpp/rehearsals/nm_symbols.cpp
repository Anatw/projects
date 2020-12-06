/*******************************************************************************
Title & Description: Master Storage Manager - part of the Master in the 
final project.
This part is in charge of all the documentation and maintenance of the 
mapping between the offsets of the memory and the Minion responsible to 
operate

Authour: Anat Wax, anatwax@gmail.com
Reviewer: 
Datecreation: 20.09.2020
Version: 1
*******************************************************************************/
#include <iostream> // cout
#include <limits> // interger min + max values
#include <string.h>

int zzzzzzzzzzzz = 3;
int zzzzzzzzzzz_un;

void LOGGING_FUNC(char *str)
{
    char *INSIDE_FUNCTION_STRING = str;
    int STRING_LENGTH_INSIDE_FUNC = strlen(INSIDE_FUNCTION_STRING);
    std::cout << INSIDE_FUNCTION_STRING << std::endl;
}

int main()
{
    double ssssssssssssssssssss = 5;
    char *ststststststststst = "this is a string literal";

    LOGGING_FUNC(ststststststststst);

    return 0;
}