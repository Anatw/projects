/*******************************************************************************
impl:
1.Given an array of integers, return a new array such that each element at index i of the new
array is the product of all the numbers in the original array except the one at i.
For example, if our input was [1, 2, 3, 4, 5], the expected output would be [120, 60, 40, 30, 24].
If our input was [3, 2, 1], the expected output would be [2, 3, 6].
Follow-up: what if you can't use division?
_______________

Dp and SOLID
2. how many solid principles to you remember ?
Read about the facade dp and explain what solid principle it implements

The Facade design pattern implement the D in solid (dependency inversion) - the abstraction in OOP - the outer
_______________

3. how would u desing a notepad ? What ds would u use?

List of strings - each list entry is a line in the document, written inside a string.


Authour: Anat Wax, anatwax@gmail.com
Datecreation: 8.11.2020
*******************************************************************************/
#include <iostream> // cout
#include <limits> // interger min + max values

size_t ReturnExcI(int array[], size_t length, int index)
{
    size_t sum = 1;
    int zero_counter = 0;

    if (0 == array[index])
    {
        return 0;
    }

    for (size_t i = 0; i < length; ++i)
    {
        if (0 == array[i])
        {
            ++zero_counter;
            ++i;
            if (i == length)
            {
                break;
            }
        }

        sum *= array[i];
    }

    if ((zero_counter % 2) == 1) // There is a odd amount of zeroes
    {
        return 0;
    }

    return (sum / array[index]);
}

size_t NoDiv(int array[], size_t length, int index)
{
    size_t sum = 1;
    int zero_counter = 0;

    if (0 == array[index])
    {
        return 0;
    }

    for (size_t i = 0; i < length; ++i)
    {
        if (i == index)
        {
            ++i;
        }

        if (0 == array[i])
        {
            ++zero_counter;
            ++i;
            if (i == length)
            {
                break;
            }
        }

        sum *= array[i];
    }

    if ((zero_counter % 2) == 1) // There is a odd amount of zeroes
    {
        return 0;
    }

    return sum;
}

void LogResult(size_t result)
{
    std::cout << result << std::endl;
}

void Test1()
{
    int array[] = {1, 2, 3, 4, 5};
    int index = 3;
    size_t length = sizeof(array) / sizeof(array[0]);
    size_t result = ReturnExcI(array, length, index);
    size_t result2 = NoDiv(array, length, index);

    LogResult(result);
    LogResult(result2);
}
void Test2()
{
    int array[] = {0, 2, 3, 4, 5};
    int index = 3;
    size_t length = sizeof(array) / sizeof(array[0]);
    size_t result = ReturnExcI(array, length, index);
    size_t result2 = NoDiv(array, length, index);

    LogResult(result);
    LogResult(result2);

}
void Test3()
{
    int array[] = {1, 2, 3, 0, 5};
    int index = 3;
    size_t length = sizeof(array) / sizeof(array[0]);
    size_t result = ReturnExcI(array, length, index);
    size_t result2 = NoDiv(array, length, index);

    LogResult(result);
    LogResult(result2);

}

void Test4()
{
    int array[] = {1, 0, 3, 4, 0, 5};
    int index = 3;
    size_t length = sizeof(array) / sizeof(array[0]);
    size_t result = ReturnExcI(array, length, index);
    size_t result2 = NoDiv(array, length, index);

    LogResult(result);
    LogResult(result2);

}

void Test5()
{
    int array[] = {1, 2, 3, 4, 5, 0};
    int index = 3;
    size_t length = sizeof(array) / sizeof(array[0]);
    size_t result = ReturnExcI(array, length, index);
    size_t result2 = NoDiv(array, length, index);

    LogResult(result);
    LogResult(result2);

}

int main()
{
    Test1();
    Test2();
    Test3();
    Test4();
    Test5();
    
    return 0;
}