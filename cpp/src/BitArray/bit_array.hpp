#ifndef ILRD_RD8586_BIT_ARRAY_HPP
#define ILRD_RD8586_BIT_ARRAY_HPP

#include <stddef.h>  // size_t
#include <algorithm> // for_each()
#include <iostream>  // cout, cin, cerr
#include  <numeric> // accumulate()
#include <string.h> //strcmp()

using namespace std;

typedef char BYTE;
#define ON (1)
#define BITS_IN_BYTE (8)
#define FULL_BYTE (255)
#define BIT_CHAR(bit) ((bit) / BITS_IN_BYTE)

class NumBitsInByte
{
public:
	int operator()(int sum, char byte) const 
	{ 
		unsigned char lut[] = { 0, 1, 1, 2, 1, 2, 2, 3, 1, 2, 2, 3, 2, 3, 3, 
        4, 1, 2, 2, 3, 2, 3, 3, 4, 2, 3, 3, 4, 3, 4, 4, 5, 1, 2, 2, 3, 2, 3, 3, 
        4, 2, 3, 3, 4, 3, 4, 4, 5, 2, 3, 3, 4, 3, 4, 4, 5, 3, 4, 4, 5, 4, 5, 5,
        6, 1, 2, 2, 3, 2, 3, 3, 4, 2, 3, 3, 4, 3, 4, 4, 5, 2, 3, 3, 4, 3, 4, 4, 
        5, 3, 4, 4, 5, 4, 5, 5, 6, 2, 3, 3, 4, 3, 4, 4, 5, 3, 4, 4, 5, 4, 5, 5, 
        6, 3, 4, 4, 5, 4, 5, 5, 6, 4, 5, 5, 6, 5, 6, 6, 7, 1, 2, 2, 3, 2, 3, 3, 
        4, 2, 3, 3, 4, 3, 4, 4, 5, 2, 3, 3, 4, 3, 4, 4, 5, 3, 4, 4, 5, 4, 5, 5, 
        6, 2, 3, 3, 4, 3, 4, 4, 5, 3, 4, 4, 5, 4, 5, 5, 6, 3, 4, 4, 5, 4, 5, 5, 
        6, 4, 5, 5, 6, 5, 6, 6, 7, 2, 3, 3, 4, 3, 4, 4, 5, 3, 4, 4, 5, 4, 5, 5, 
        6, 3, 4, 4, 5, 4, 5, 5, 6, 4, 5, 5, 6, 5, 6, 6, 7, 3, 4, 4, 5, 4, 5, 5, 
        6, 4, 5, 5, 6, 5, 6, 6, 7, 4, 5, 5, 6, 5, 6, 6, 7, 5, 6, 6, 7, 6, 7, 7, 
        8, };
        
		return (sum + lut[(int)byte]);
	}
};

// class Setter
// {
// public:
// 	Setter(char filler) : m_fill(filler) {}
// 	char operator()()
// 	{
// 		return(m_fill);
// 	}
// private:
// 	char m_fill;
// };

class MoveRight
{
public:
    MoveRight(int to_move) : move(to_move), buff(0), next_buff(0) {}
    char operator()(char byte)
    {
        cout << next_buff << endl;

        next_buff = byte << (BITS_IN_BYTE - move);

        byte >>= move;
        byte ^= buff;
        buff = next_buff;

        return (byte);
    }

private:
    int move;
    unsigned char buff;
    unsigned char next_buff;
};



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

class FlipByte
{
public:
    char operator()(char byte)
    {
        return (~byte);
    }
};

class BitAnd
{
    public:
    char operator() (char arr, char o)
    {
        return (arr &= o);
    }
};

class BitOr
{
    public:
    char operator() (char arr, char o)
    {
        return (arr |= o);
    }
};

class BitXor
{
    public:
    char operator() (char arr, char o)
    {
        return (arr ^= o);
    }
};


////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////

template <typename T>
class BitProxy
{
public:
    BitProxy(char &byte, BYTE index) : m_byte(byte), m_index(index) {}
    BitProxy &operator=(bool val);
    operator bool() const;
    bool operator!() const;

private:
    char &m_byte;
    BYTE m_index;
};
/*bitarray<100>b;
b[2] = true; */

template <typename T>
BitProxy<T> &BitProxy<T>::operator=(bool val)
{
    char mask = 1;
    mask <<= this->m_index;

    if (val)
    {
        this->m_byte |= mask;
    }
    else
    {
        this->m_byte &= ~mask;
    }
    

    return (*this);
}

template <typename T>
BitProxy<T>::operator bool() const
{
    return ((this->m_byte >> this->m_index) & 1);
}

template <typename T>
bool BitProxy<T>::operator!() const
{
    return ((this->m_byte >> this->m_index) & 0);
}


////////////////////////////////////////////////////////////////////////////////
//                             class BitArray:                                //
////////////////////////////////////////////////////////////////////////////////

template <size_t Size>
class BitArray
{
public:
    BitArray() : m_array(), m_size((((Size - 1) / 8) + 1))
    {
    }

    inline BitArray &SetAll();
   
    BitArray &Set(const size_t pos, const bool val);

    bool Get(size_t pos) const;

    inline BitArray &FlipAll();
    
    BitArray &Flip(size_t pos);

    inline size_t CountBitsOn() const;

    string ToString() const;

    bool operator[](size_t pos) const;
    BitProxy<bool> operator[](size_t pos);

    bool operator==(const BitArray &o_) const;
    bool operator!=(const BitArray &o_) const;

    BitArray &operator&=(const BitArray &o_);
    BitArray &operator|=(const BitArray &o_);
    BitArray &operator^=(const BitArray &o_);
    
    BitArray &operator<<=(size_t shift);
    BitArray &operator>>=(size_t shift);

private:
    char m_array[((Size - 1) / 8) + 1];
    int m_size;

    void ZeroLeftovers();
};


////////////////////////////////////////////////////////////////////////////////
//                           Template functions:                              //
////////////////////////////////////////////////////////////////////////////////


template <size_t Size>
string BitArray<Size>::ToString() const
{
    string str_;

    for_each(this->m_array, this->m_array + this->m_size, BytesToString(str_));

    return (str_);
}


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

template <size_t Size>
BitArray<Size> &BitArray<Size>::Flip(const size_t pos)
{
    char mask = 1;
    mask <<= (pos % BITS_IN_BYTE);
    this->m_array[BIT_CHAR(pos)] ^= mask;

    return (*this);
}

template <size_t Size>
size_t BitArray<Size>::CountBitsOn() const
{
    return (accumulate(this->m_array, this->m_array + this->m_size,
            0, NumBitsInByte()));
}

template <size_t Size>
BitArray<Size> &BitArray<Size>::SetAll()
{
    fill(this->m_array, this->m_array + this->m_size, FULL_BYTE);
    return (*this);
}

template <size_t Size>
BitArray<Size> &BitArray<Size>::FlipAll()
{
    transform(this->m_array, this->m_array + this->m_size,
              this->m_array, FlipByte());
    return (*this);
}

template <size_t Size>
bool BitArray<Size>::operator==(const BitArray &o_) const
{
    return (equal(this->m_array, this->m_array + this->m_size, o_.m_array));
}

template <size_t Size>
bool BitArray<Size>::operator!=(const BitArray &o_) const
{
    return (!equal(this->m_array, this->m_array + this->m_size, o_.m_array));
}
template <size_t Size>
BitArray<Size> &BitArray<Size>::operator&=(const BitArray &o_)
{
    transform(this->m_array, this->m_array + this->m_size, o_.m_array, this->m_array, BitAnd());
    return (*this);
}

template <size_t Size>
BitArray<Size> &BitArray<Size>::operator|=(const BitArray &o_)
{
    transform(this->m_array, this->m_array + this->m_size, o_.m_array, this->m_array, BitOr());
    return (*this);
}

template <size_t Size>
BitArray<Size> &BitArray<Size>::operator^=(const BitArray &o_)
{
    transform(this->m_array, this->m_array + this->m_size, o_.m_array, this->m_array, BitXor());
    return (*this);
}
/*
template <size_t Size>
BitArray<Size> &BitArray<Size>::operator<<=(size_t shift)
{
    if (shift >= this->m_size)
    {
        memset(this->m_array, 0, this->m_size);
    }

    memmove(m_array, m_array + )

    transform(m_array, m_array + m_size, m_arr, MoveRight(n % 8));

	ZeroLeftovers();
    return (*this);
}

template <size_t Size>
BitArray &BitArray<Size>::operator>>=(size_t shift)
{}*/

template <size_t Size>
bool BitArray<Size>::operator[](size_t pos) const
{
    return (this->Get(pos));
}

template <size_t Size>
BitProxy<bool> BitArray<Size>::operator[](size_t pos)
{
    BitProxy<bool> bit_proxy(this->m_array[pos / BITS_IN_BYTE], pos % BITS_IN_BYTE);
	
    return (bit_proxy);
}

template <size_t Size>
void BitArray<Size>::ZeroLeftovers()
{
	 size_t bits = Size % BITS_IN_BYTE;
    if (bits != 0)
    {
        char mask = 0xFF << (BITS_IN_BYTE - bits);


        m_array[(Size - 1) / BITS_IN_BYTE] &= mask;
    }
}

#endif // ILRD_RD8586_BIT_ARRAY_HPP
