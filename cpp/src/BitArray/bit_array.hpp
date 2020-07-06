/*******************************************************************************
bit array header
Written by Anat Wax, anatwax@gmail.com
Created: 5.7.20
Reviewer: Daria Kortokova
*******************************************************************************/

#include <stddef.h>  // size_t
#include <algorithm> // for_each()
#include <iostream>  // cout, cin, cerr

using namespace std;

typedef char BYTE;
#define ON (1)

int SetOn()
{
    return (1);
}

void printx2(int a)
{
    cout << a << " " << endl;
}

class BitProxy
{
public:
    BitProxy(char &byte, BYTE index);
    BitProxy &operator=(bool val);
    operator bool() const;
    bool operator!() const;

private:
    char &byte;
    BYTE index;
};
/*bitarray<100>b;
b[2] = true; */

class Printush
{
public:
    Printush(int bit) : m_bit(bit) {}
    int operator()(int number) const
    {
        number = number;
        cout << this->m_bit << " " << endl;
        return (0);
    }

private:
    int m_bit;
};

class SetBit
{
public:
    SetBit(char *bit) : m_bit(bit) {}
    void operator()(char *number) const
    {
        number = number;
    }

private:
    char *m_bit;
};

struct FlipBit
{
};

template <size_t Size>
class BitArray
{
public:
    BitArray() : m_array(), m_size((((Size - 1) / 8) + 1))
    {
    }

    inline void Print()
    {
        for_each(this->m_array, this->m_array + Size, printx2);
        //for_each(this->m_array, this->m_array + Size, Printush(0));// this print the value in brackets... need to fix
    }

    inline BitArray &SetAll()
    {
        //fill(this->m_array, this->m_array + Size, 1);
        for_each(this->m_array, this->m_array + Size, SetBit(this->m_array));

        return (*this);
    }

    inline BitArray &Set(size_t pos, bool val)
    {
        if (this->m_array[pos] != val)
        {
            this->m_array[pos] = val;
        }

        return (*this);
    }

    inline bool Get(size_t pos) const
    {
        return (m_array[pos]);
    }

    inline BitArray &FlipAll()
    {
        cout << "this->m_array " << Get(0) << endl;
        // for_each(this->m_array, this->m_array + Size, FlipBit);
        // {bool mask = 1;
        //     // mask <<= pos;

        return (*this);
    }
    inline BitArray &Flip(size_t pos)
    {
    }
    inline size_t CountBitsOn() const;
    // {
    //     //size_t counter = (this->);
    // }
    string ToString() const;

    bool operator[](size_t pos) const;
    BitProxy operator[](size_t pos);
    bool &operator==(const BitArray &o_) const;
    bool &operator!=(const BitArray &o_) const;
    BitArray &operator&=(const BitArray &o_);
    BitArray &operator|=(const BitArray &o_);
    BitArray &operator^=(const BitArray &o_);
    BitArray &operator<<=(size_t shift);
    BitArray &operator>>=(size_t shift);

private:
    char m_array[((Size - 1) / 8) + 1];
    int m_size;
};

/*template <size_t Size>
BitArray<Size>::BitArray &SetAll()
{
}

template <size_t Size>
inline size_t BitArray<Size>::CountBitsOn() const
{
    size_t counter = (this->)
}
*/

// void SetOn(const bool ON)
// {

// }
