/******************************************************************************

Array of Elements

Editor: Haim Saadia
Date: Feb 2020
Reviewer: Anat Wax

*******************************************************************************/


#include "Functions.h"


Elements array[ARRAY_LENGTH] = 
{
    { "First", 1, 1.5 },
    { "Second", 2, 2.5 },
    { "Third", 3, 3.5 }
};

int main()
{
    /* Print array */
    PrintArray(array);
    
    /* Add to array */
    AddToArray(array);
    
    /* Print array again */
    PrintArray(array);
    
    return (0);
}
