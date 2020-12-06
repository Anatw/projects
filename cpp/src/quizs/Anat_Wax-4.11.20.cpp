/*******************************************************************************
Farmer John has built a new long barn, with N stalls.
Given an array of integers A of size N where each element of the array represents the location of the stall, and an integer B which represent the number of cows.
His cows don’t like this barn layout and become aggressive towards each other once put into a stall.
To prevent the cows from hurting each other, John wants to assign the cows to the stalls, such that the minimum distance between any two of them is as large as possible. What is the largest minimum distance?

Authour: Anat Wax, anatwax@gmail.com
Datecreation: 4.11.2020
Version: 1
*******************************************************************************/
#include <iostream> // cout
#include <limits> // interger min + max values

int MinimunDistance(int num_stalls, int cows)
{
    if (cows >= num_stalls)
    {
        return 0;
    }
    
    int i = 0;
    int j = 0;
    int current_cows = cows;
    // int *stalls = (int *)calloc(num_stalls, sizeof(int));
    int *stalls = new int(num_stalls);
    int min_distance = num_stalls - 1;
    int temp_min = num_stalls;

    int dis_from_beg = 0;
    int temp_dis_beg = 0;
    int dis_from_end = 0;
    int temp_dis_end = 0;

    stalls[0] = 1;
    stalls[num_stalls - 1] = 1;
    current_cows -= 2;
    int begin = 0;
    int end = 0;

    // Place all cows in available stalls by order:
    for (i = 1; i < num_stalls && current_cows > 0; ++i, -- current_cows)
    {
        stalls[i] = 1;
    }

    // Check if cows can be moved to better locations:
    for (i = 1; i < (num_stalls - 1); ++i)
    {
        // If you found a cow - check the distance from closest cows:
        if (1 == stalls[i])
        {
            j = i - 1;
            while (1 != stalls[j])// until you reach a cow
            {
                --j;
            }
            begin = j;

            j = i + 1;
            while (1 != stalls[j])
            {
                ++j;
            }
            end = j;

            dis_from_beg = i - begin;
            dis_from_end = end - i;
            j = i;

            // Find the first free stall and check if distance is better - if yes - move cow:
            while (0 != stalls[j])
            {
                ++j;
            }

            temp_dis_beg = j - begin;
            temp_dis_end = end - j;

            if ((dis_from_end - dis_from_beg) > (temp_dis_end - temp_dis_beg))
            {
                stalls[i] = 0;
                stalls[j] = 1;
                dis_from_beg = temp_dis_beg;
                dis_from_end = temp_dis_end;

                if (dis_from_beg < 0)
                {
                    dis_from_beg = 1;
                }
                if (dis_from_end < 0)
                {
                    dis_from_end = 1;
                }
            }
        }
        
        temp_min = (dis_from_beg < dis_from_end ? dis_from_beg : dis_from_end);

        if ((temp_min > 0) && (min_distance > temp_min))
        {
            min_distance = temp_min;
        }
        
        if ((i + 1) == j) // If cow was moved 
        {
            ++i;
        }
    }

    return min_distance;
}

int main()
{
    int num_stalls = 5;
    int cows = 3;

    std::cout << "min distance is " << MinimunDistance(num_stalls, cows) << std::endl;

    return 0;
}