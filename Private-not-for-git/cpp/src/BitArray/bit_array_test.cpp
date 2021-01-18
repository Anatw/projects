/*******************************************************************************
bit array (design pattern)
Written by Anat Wax, anatwax@gmail.com
Created: 6.7.20
Reviewer: Daria Korotkova
*******************************************************************************/
#include <algorithm> // for_each()
#include <iostream>  // cout, cin, cerr

#include "bit_array.hpp"

using namespace std;

int main()
{
    BitArray< 16 > bit;
    BitArray< 16 > another_bit;
    //   cout << sizeof(bit) << endl;

    cout << "comparing a bit and another bit: " << (bit == another_bit) << endl;
    bit.SetAll();
    another_bit.SetAll();
    /* cout << bit.Get(0) << endl;
    cout << bit.Get(1) << endl;*/
    cout << "After SetAll() " << endl;
    cout << bit.ToString() << endl;

    try
    {
        bit.Set(1, 0);
        bit.Set(3, 0);
        bit.Set(5, 0);
        bit.Set(7, 0);
        cout << "bit " << endl;
        cout << bit.ToString() << endl;

        cout << "another_bit " << endl;
        cout << another_bit.ToString() << endl;
        cout << endl;

        bit ^= another_bit;

        cout << "bit ^= another_bit: " << bit.ToString() << endl;
        // bit <<= 4;
        //     cout << "bit <<= 4: " << bit.ToString() << endl;

        cout << "After zig-zag setting " << endl;
        cout << bit.ToString() << endl;

        cout << "After FlipAll() " << endl;
        cout << bit.ToString() << endl;

        cout << "to string: \n" << bit.ToString() << endl;

        bit.Flip(7);

        cout << "Get: \n" << bit.Get(7) << endl;

        bit.FlipAll();
        cout << "to string: \n" << bit.ToString() << endl;

        cout << "Counting on bits: \n" << bit.CountBitsOn() << endl;

        cout << "bit " << endl;
        cout << bit.ToString() << endl;

        for (int i = 0; i < 8; ++i)
        {
            cout << "bit[] = ";
            cout << bit[i] << endl;
        }

        cout << "bit[3] - before changing = ";
        cout << bit[3] << endl;
        bit[3] = 1;
        cout << "bit[3] - after changing= ";
        cout << bit[3] << endl;

        cout << "\n\ntesting right shift:\n before: " << endl;
        cout << bit.ToString() << endl;

        bit >>= 3;
        cout << "Shifting 3 to the right (bit >>= 3): " << endl;
        cout << bit.ToString() << endl;

        cout << "Shifting 7 to the left (bit <<= 7): " << endl;
        bit <<= 7;
        cout << bit.ToString() << endl;
    }
    catch (const out_of_range& oor)
    {
        cerr << "Out of range: " << oor.what() << endl;
    }
    return (0);
}
