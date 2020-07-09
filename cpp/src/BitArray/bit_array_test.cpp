

#include <iostream>  // cout, cin, cerr
#include <algorithm> // for_each()

#include "bit_array.hpp"

using namespace std;

int main()
{
    BitArray<8> bit;
    BitArray<8> another_bit;
    //   cout << sizeof(bit) << endl;

    cout << "comparing a bit and another bit: " << (bit == another_bit) << endl;
    bit.SetAll();
    another_bit.SetAll();
    /* cout << bit.Get(0) << endl;
    cout << bit.Get(1) << endl;*/
    cout << "After SetAll() " << endl;
    cout << bit.ToString() << endl;

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

    cout << "to string: \n"
         << bit.ToString() << endl;

    bit.Flip(7);

    cout << "Get: \n"
         << bit.Get(7) << endl;

    bit.FlipAll();
    cout << "to string: \n"
         << bit.ToString() << endl;

    cout << "Counting on bits: \n"
         << bit.CountBitsOn() << endl;

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

    return (0);
}
