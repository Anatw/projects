#include <stdio.h>

int IsDivisableIntoEqualSubsets(unsigned int* array, size_t size)
{
    size_t i = 0;
    unsigned int result = 0, sum = 0;

    for (i = 0; i < size; ++i)
    {
        sum += array[i];
    }

    for (i = 0; i < size; ++i)
    {
        if (result + array[i] <= sum / 2)
        {
            result += array[i];
        }
    }

    return (result == sum / 2);
}

int Test1()
{
    unsigned int array[] = {3, 1, 1, 2, 2, 1};
    size_t size = sizeof(array) / sizeof(array[0]);

    printf("%d\n", IsDivisableIntoEqualSubsets(array, size));
    return (IsDivisableIntoEqualSubsets(array, size));
}

int Test2()
{
    unsigned int array[] = {1, 2, 3, 4, 5, 5, 4, 3, 2, 1};
    size_t size = sizeof(array) / sizeof(array[0]);

    printf("%d\n", IsDivisableIntoEqualSubsets(array, size));
    return (IsDivisableIntoEqualSubsets(array, size));
}

int Test3()
{
    unsigned int array[] = {1, 2};
    size_t size = sizeof(array) / sizeof(array[0]);

    printf("%d\n", IsDivisableIntoEqualSubsets(array, size));
    return (IsDivisableIntoEqualSubsets(array, size));
}

int main()
{
    Test1();
    Test2();
    Test3();

    return (0);
}
