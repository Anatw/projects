/*******************************************************************************
Comment and un-comment the defines to see both phases (one at a time).

WS name
Templates + STL (Histo)
Written by Anat Wax, anatwax@gmail.com
Created: 15.6.20
Reviewer: 
*******************************************************************************/
#include <stdio.h> /* printf(), size_t */

#include <string.h> /* size_t, atoi(), memset() */

void RoteteOneLeft(char array[], int length)
{
    int i = 0;

    for (; i < length; ++i)
    {
        array[i] = array[i + 1];
    }
}

void RotateLeft(char array[], int length, int rot)
{
    int i = 0;
    char temp = 0;
    int temp_rot = rot;

    for (i = 0; i < rot; ++i, --temp_rot)
    {
        temp = array[0];
        RoteteOneLeft(array, length);
        array[length - 1] = temp;
    }
}

int main()
{
    char array[] = "dermalogica";
    int length = strlen(array);

    printf("array length - %d\n", length);
    printf("before rotation: %s\n", array);

    RotateLeft(array, length, 3);

    printf("after rotation: %s\n", array);

    return (0);
}
