/*******************************************************************************
Given an array of integers, return a new array such that each element at
index i of the new array is the product of all the numbers in the original
array except the one at i.
For example, if our input was [1, 2, 3, 4, 5], the expected output would
be [120, 60, 40, 30, 24]. If our input was [3, 2, 1], the expected output
would be [2, 3, 6].

there’s naive approach o(n^2) and a better approach o(n)
start with the first, continue to the second
(what if you can't use division?)

Written by Anat Wax, anatwax@gmail.com
Created: 1.12.20
*******************************************************************************/
#include <iostream> // cout, cin, cerr
#include <stack>

namespace ilrd
{
/*
psaudo:
- iterate the array and areate a number the represent the duplication oon all
elements in array.
If zero is encouter as data - count it add don't doublt it. if only one zero is
in the array - return zero for every request other for index other than the one
containing the zero - and only for that specific one - return the general sum.
if two zeroes are encountered as data - count it and break the loop - return
zero for every request
*/

int General


}
