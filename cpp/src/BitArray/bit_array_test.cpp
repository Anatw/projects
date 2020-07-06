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
    BitArray<8> bit;
    //   cout << sizeof(bit) << endl;

    bit.SetAll();
    /* cout << bit.Get(0) << endl;
    cout << bit.Get(1) << endl;*/
    cout << "After SetAll() " << endl;
    bit.Print();

    bit.Set(1, 0);
    bit.Set(3, 0);
    bit.Set(5, 0);
    bit.Set(7, 0);
    cout << "After zig-zag setting " << endl;
    bit.Print();

    bit.FlipAll();
    cout << "After FlipAll() " << endl;
    bit.Print();

    return (0);
}
////////////////////////////////////////////////////////////////////////////////
//                           Inline functions:                                //
////////////////////////////////////////////////////////////////////////////////
