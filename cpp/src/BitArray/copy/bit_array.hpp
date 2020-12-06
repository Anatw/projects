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
#define BITS_IN_BYTE (8)
#define FULL_BYTE (255)
#define BIT_CHAR(bit) ((bit) / BITS_IN_BYTE)

// int SetOn()
// {
//     return (1);
// }

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

class BytesToString
{
public:
    BytesToString(string &str_) : m_str(str_) {}

    void operator()(char byte)
    {
        for (int i = 0; i < BITS_IN_BYTE; ++i)
        {
            m_str += ((byte >> i) & 1) ? '1' : '0';
        }
    }

private:
    string &m_str;
};

template <size_t Size>
class BitArray
{
public:
    BitArray() : m_array(), m_size((((Size - 1) / 8) + 1)) {}

    inline BitArray &SetAll()
    {
        fill(this->m_array, this->m_array + this->m_size, FULL_BYTE);
        //for_each(this->m_array, this->m_array + Size, SetAllOn());

        return (*this);
    }

    BitArray &Set(const size_t pos, const bool val);

    bool Get(size_t pos) const;

    inline BitArray &FlipAll()
    {
        cout << "this->m_array " << Get(0) << endl;
        // for_each(this->m_array, this->m_array + Size, FlipBit);

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

template <size_t Size>
string BitArray<Size>::ToString() const
{
    std::string str_;

    for_each(this->m_array, this->m_array + this->m_size, BytesToString(str_));

    return (str_);
}

/*template <size_t Size>
inline size_t BitArray<Size>::CountBitsOn() const
{
    size_t counter = (this->)
}
*/

// void SetOn(const bool ON)
// {

// }

template <size_t Size>
BitArray<Size> &BitArray<Size>::Set(const size_t pos, const bool val)
{
    char mask = 1;
    mask <<= (pos % BITS_IN_BYTE);

    if (val)
    {
        (this->m_array[BIT_CHAR(pos)] |= mask);
    }
    else
    {
        this->m_array[BIT_CHAR(pos)] &= ~(mask);
    }

    return (*this);
}
template <size_t Size>
bool BitArray<Size>::Get(size_t pos) const
{
    char mask = 1;
    mask <<= (pos % BITS_IN_BYTE);
    char temp = this->m_array[BIT_CHAR(pos)];

    return (temp &= mask);
}
