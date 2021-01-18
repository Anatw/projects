/*******************************************************************************


Authour: Anat Wax, anatwax@gmail.com
Datecreation: 23.11.2020
Version: 1
*******************************************************************************/
#include <iostream> // cout
#include <limits> // interger min + max values

size_t KnapSack(const int w, int wt[], int val[], int n)
{
    int i = 0;
    int j = 0;
    size_t temp_sum = 0;
    size_t sum = 0;
    int weight = 0;

    for (i = 0; i < n; ++i)
    {
        weight = wt[i];
        temp_sum = (wt[i] * val[i]);

        for (j = i + 1; j < n; ++j)
        {
            if (w >= (weight + wt[j]))
            {
                weight += wt[j];
                temp_sum += (wt[j] * val[j]);
            }           
        }

        if (temp_sum > sum)
        {
            sum = temp_sum;
        }

        weight = 0;
        temp_sum = 0;
    }

    return sum;
}

void Test1()
{
    int val[] = {60, 100, 120, 300};
    int wt[] = {10, 20, 30, 50};
    int w = 70;
    int n = sizeof(val) / sizeof(val[0]);

    std::cout << KnapSack(w, wt, val, n) << std::endl;
}

int main()
{
    Test1();

    return 0;
}