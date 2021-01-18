/*******************************************************************************
Given an array of integers, return a new array such that each element at index i
of the new array is the product of all the numbers in the original array except
the one at i.

For example, if our input was [1, 2, 3, 4, 5], the expected output would be
[120, 60, 40, 30, 24].
If our input was [3, 2, 1], the expected output would be [2, 3, 6].

Follow-up: what if you can't use division?

Written by Anat Wax, anatwax@gmail.com
December 31, 2020
*******************************************************************************/
#include <iostream>
#include <vector>

std::vector<size_t> ProductOfOtherElements(std::vector<int> &list)
{
    size_t sum = 1;
    int zero_counter = 0;
    size_t i = 0;
    int index_of_zero = -1;
    std::vector<size_t> result;

    for (i = 0; i < list.size(); ++i)
    {
        if (0 == list[i])
        {
            if (1 == zero_counter) // this is the second zero - all elements should be zero.
            {
                for (i = 0; i < list.size(); ++i)
                {
                    result.push_back(0);
                }

                return result;
            }
            else
            {
                ++zero_counter;
                index_of_zero = i;
            }   
        }
        else
        {
            sum *= list[i];
        }
    }

    if (0 == zero_counter)
    {
        for (i = 0; i < list.size(); ++i)
        {
            result.push_back(sum / list[i]);
        }
    }
    else
    {
        for (i = 0; i < list.size(); ++i)
        {
            result.push_back(0);
        }

        result[index_of_zero] = sum;
    }
    

    return result;
}


int main()
{
    /*
    std::vector<int> num_list;
    num_list.push_back(120);
    num_list.push_back(60);
    num_list.push_back(40);
    num_list.push_back(30);
    num_list.push_back(24);
    */
   std::vector<int> num_list;
    num_list.push_back(1);
    num_list.push_back(2);
    num_list.push_back(0);
    num_list.push_back(4);
    num_list.push_back(5);

    std::vector<size_t> result = ProductOfOtherElements(num_list);

    for (size_t i = 0; i < result.size(); ++i)
    {
        std::cout << result[i] << std::endl;
    }

    return (0);
}
