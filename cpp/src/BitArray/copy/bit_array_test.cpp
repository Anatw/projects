/*******************************************************************************
bit array test
Written by Anat Wax, anatwax@gmail.com
Created: 5.7.20
Reviewer: Daria Kortokova
*******************************************************************************/
#include <iostream>  // cout, cin, cerr
#include <algorithm> // for_each()

#include "bit_array.hpp"

using namespace std;

int main()
{
    BitArray<64> bit;
    //   cout << sizeof(bit) << endl;

    bit.SetAll();
    /* cout << bit.Get(0) << endl;
    cout << bit.Get(1) << endl;*/
    cout << "After SetAll() " << endl;
    cout << bit.ToString() << endl;

    bit.Set(1, 0);
    bit.Set(3, 0);
    bit.Set(5, 0);
    bit.Set(30, 0);
    cout << "After zig-zag setting " << endl;
    cout << bit.ToString() << endl;

    bit.FlipAll();
    cout << "After FlipAll() " << endl;
    cout << bit.ToString() << endl;

    cout << "to string: \n"
         << bit.ToString() << endl;

    cout << "Get: \n"
         << bit.Get(30) << endl;

    return (0);
}
////////////////////////////////////////////////////////////////////////////////
//                           Inline functions:                                //
////////////////////////////////////////////////////////////////////////////////
