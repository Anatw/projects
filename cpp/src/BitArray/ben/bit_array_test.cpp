/*******************************************************************************
* WS: Bit Array API                                                            *
* Topic: C++                                                                   *
* Date: 5/07/2020                                                              *
* Author: Ben David Zikri                                                      *
* Reviwer:                                                                     *
*******************************************************************************/
#include <iostream>
#include <algorithm>
#include "bit_array.hpp"
#include "bit_array.cpp"

#define NUM 35

using namespace std;

int main()
{	
	BitArray<NUM> bit_arr;
	BitArray<NUM> bit_arr2;
	string str;
	cout << "Size of total bit capacity: " << sizeof(bit_arr) * CHAR_BITS << endl;
	cout << bit_arr.ToString() << endl;

	cout << "bit_arr: Set all bits to 1" << endl;
	bit_arr.SetAll();

	cout << bit_arr.ToString() << endl;
	cout << "Count: " << bit_arr.CountSetBits() << endl;

	cout << "Flip all bits" << endl;
	bit_arr.FlipAll();
	cout << bit_arr.ToString() << endl;

	cout << "Flip bits: 1,3,5,7 bits to 1" << endl;
	bit_arr.Flip(1);
	bit_arr.Flip(5);
	bit_arr.Flip(7);
	bit_arr.Set(3, 1);
	bit_arr.Set(15, 1);

	str = bit_arr.ToString();
	cout << str << endl;

	cout << "Setting bit 4 to 1 using operator[] " << endl;
	bit_arr[4] = 1;
	cout << "Print bit_arr[4]: (without !)" << endl;
	cout << bit_arr[4] << endl;
	cout << "Print bit_arr[4]: (with !)" << endl;
	cout << !bit_arr[4] << endl;

	cout << "bit_arr2: Set all bits to 1" << endl;
	bit_arr2.SetAll();
	cout << bit_arr2.ToString() << endl;
	cout << "bit_arr == bit_arr2 ";
	cout << (bit_arr == bit_arr2) << endl;

	bit_arr |= bit_arr2;
	bit_arr ^= bit_arr2;
	bit_arr &= bit_arr2;

	cout << "bit_arr >>= 19 " << endl;
	bit_arr >>= 19;
	cout << bit_arr.ToString() << endl;
	

	bit_arr.SetAll();
	// bit_arr.Flip(25);
	cout << "originals  : "<< bit_arr.ToString() << endl;
	bit_arr <<= 9;
	cout << "Left shift : " << bit_arr.ToString() << endl;

	bit_arr.SetAll();
	// bit_arr.Flip(15);
	cout << "originals  : "<< bit_arr.ToString() << endl;
	bit_arr >>= 9;
	cout << "Right shift: " << bit_arr.ToString() << endl;

	return (0);
}
