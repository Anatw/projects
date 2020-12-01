/*******************************************************************************
Given n dices each with m faces, numbered from 1 to m, find the number of ways to get a given sum X. X is the summation of values on each face when all the dice are thrown.

Input : faces = 4 throws = 2 sum =4
Output : 3
Ways to reach sum equal to 4 in 2 throws can be { (1, 3), (2, 2), (3, 1) }
Input : faces = 6 throws = 3 sum = 12
Output : 25
Version: 1
** whats the complexity ?
static int NoofWays(int face, int throwsVal, int sum)

Authour: Anat Wax, anatwax@gmail.com
Datecreation: 29.10.2020

NOT FINISHED!!!
I'm thinking about changing direction - and solve it recursovely (makes more sense because it feels like the number of throuws sould be equall to the number of inner loop in an iterative solution)
*******************************************************************************/
#include <iostream> // cout
#include <limits> // interger min + max values
#include <vector>

static int NoOfWays(const int face, const int num_throws, const int sum)
{
    int index = 1;
    int inner_index = 1;
    int throw_index = 0;
    int temp_value = 0;
    int ways_counter = 0;
    std::vector<int> array;
    int current_sum = 0;
    int temp_sum = 0;
    int throw_counter = 0;

    if (num_throws == 1)
    {
        if (sum <= face)
        {
            return 1;
        }
        else
        {
            return 0;
        }
        
    }

    for (index = 1; index <= face; ++index)
    {
        current_sum = index;

        for (throw_counter = 1; throw_counter < num_throws; ++throw_counter)
        {
            temp_sum = current_sum;

            for (inner_index = 1;
                 inner_index <= face && current_sum < sum;
                 ++inner_index)
            {
                current_sum = temp_sum;

                current_sum += inner_index;
            }
        }

        if (current_sum == sum)
        {
            ++ways_counter;
        }
    }
    //
    for (index = 1, throw_counter = 1;
         index <= face && throw_counter < num_throws;
         ++index, ++throw_counter)
    {
        current_sum = index;

        for (inner_index = 1;
            inner_index <= face && current_sum < sum;
            ++inner_index)
        {
            temp_sum = current_sum;

            current_sum = temp_sum;

            current_sum += inner_index;
        }

        if (current_sum == sum)
        {
            ++ways_counter;
        }
    }

    return ways_counter;
}

void Test1()
{
    int faces = 4;
    int throws = 2;
    int sum = 4;

    std::cout << "output should be 3. Is = " << NoOfWays(faces, throws, sum)  << std::endl;
}

void Test2()
{
    int faces = 6;
    int throws = 3;
    int sum = 12;

    std::cout << "output should be 25. Is = " << NoOfWays(faces, throws, sum)  << std::endl;
}

int main()
{
    Test1();
    Test2();

    return 0;
}