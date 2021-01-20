/*******************************************************************************
bit array (design pattern)
Written by Anat Wax, anatwax@gmail.com
Created: 6.7.20
*******************************************************************************/
#ifndef ILRD_RD8586_BIT_ARRAY_HPP
#define ILRD_RD8586_BIT_ARRAY_HPP

#include <algorithm> // for_each()
#include <climits>   // CHAR_BIT
#include <iostream>  // cout, cin, cerr
#include <numeric>   // accumulate()
#include <stddef.h>  // size_t
#include <string.h>  // strcmp()

using namespace std;

typedef unsigned char BYTE;
#define ON (1)
#define FULL_BYTE (255)
#define BIT_CHAR(bit) ((bit) / CHAR_BIT)

const unsigned char full_byte = 255;

void ShiftRightOp(unsigned char* bit_array, size_t bits_num, size_t shift);
void ShiftLeftOp(unsigned char* bit_array, size_t bits_num, size_t shift);
static inline void ZeroUnusedBits(unsigned char* bit_array_end,
                                  size_t bits_num);

////////////////////////////////////////////////////////////////////////////////
//                       BitProxy class & functions:                          //
////////////////////////////////////////////////////////////////////////////////

class BitProxy
{
public:
    BitProxy(unsigned char& byte, BYTE index);
    BitProxy& operator=(const BitProxy& rhs);
    BitProxy& operator=(bool val);
    operator bool() const;
    bool operator!() const;

private:
    BYTE& m_byte;
    unsigned char m_index;
};

BitProxy::BitProxy(unsigned char& byte, BYTE index)
    : m_byte(byte), m_index(index % 8)
{
}

////////////////////////////////////////////////////////////////////////////////

BitProxy& BitProxy::operator=(const BitProxy& rhs)
{
    return (*this = (bool)rhs);
}

////////////////////////////////////////////////////////////////////////////////

BitProxy& BitProxy::operator=(bool val)
{
    char mask = 1;
    mask <<= (m_index % CHAR_BIT);

    if (val)
    {
        m_byte |= mask;
    }
    else
    {
        m_byte &= ~(mask);
    }

    return (*this);
}

////////////////////////////////////////////////////////////////////////////////

BitProxy::operator bool() const
{
    return (m_byte & (1ul << m_index));
}

////////////////////////////////////////////////////////////////////////////////

bool BitProxy::operator!() const
{
    return (!(m_byte & (1ul << m_index)));
}

////////////////////////////////////////////////////////////////////////////////
//                               Functors:                                    //
////////////////////////////////////////////////////////////////////////////////

class ShiftRight
{
public:
    ShiftRight(size_t shmnt) : m_shmntR(shmnt), m_shmntL(CHAR_BIT - shmnt)
    {
    }
    unsigned char operator()(unsigned char b1, unsigned char b2);

private:
    size_t m_shmntR;
    size_t m_shmntL;
};

unsigned char ShiftRight::operator()(unsigned char b1, unsigned char b2)
{
    return ((b2 >> m_shmntR) | (b1 << m_shmntL));
}

////////////////////////////////////////////////////////////////////////////////

class ShiftLeft
{
public:
    ShiftLeft(size_t shmnt)
        : m_shmntR(CHAR_BIT - shmnt), m_shmntL(shmnt), m_prev(0)
    {
    }

    unsigned char operator()(unsigned char b1);

private:
    size_t m_shmntR;
    size_t m_shmntL;
    unsigned char m_prev;
};

unsigned char ShiftLeft::operator()(unsigned char b1)
{
    unsigned char res = (b1 << m_shmntL) | (m_prev >> m_shmntR);

    m_prev = b1;

    return (res);
}

////////////////////////////////////////////////////////////////////////////////

class NumBitsInByte
{
public:
    int operator()(int sum, unsigned char byte) const
    {
        unsigned char lut[] = {
            0, 1, 1, 2, 1, 2, 2, 3, 1, 2, 2, 3, 2, 3, 3, 4, 1, 2, 2, 3, 2, 3,
            3, 4, 2, 3, 3, 4, 3, 4, 4, 5, 1, 2, 2, 3, 2, 3, 3, 4, 2, 3, 3, 4,
            3, 4, 4, 5, 2, 3, 3, 4, 3, 4, 4, 5, 3, 4, 4, 5, 4, 5, 5, 6, 1, 2,
            2, 3, 2, 3, 3, 4, 2, 3, 3, 4, 3, 4, 4, 5, 2, 3, 3, 4, 3, 4, 4, 5,
            3, 4, 4, 5, 4, 5, 5, 6, 2, 3, 3, 4, 3, 4, 4, 5, 3, 4, 4, 5, 4, 5,
            5, 6, 3, 4, 4, 5, 4, 5, 5, 6, 4, 5, 5, 6, 5, 6, 6, 7, 1, 2, 2, 3,
            2, 3, 3, 4, 2, 3, 3, 4, 3, 4, 4, 5, 2, 3, 3, 4, 3, 4, 4, 5, 3, 4,
            4, 5, 4, 5, 5, 6, 2, 3, 3, 4, 3, 4, 4, 5, 3, 4, 4, 5, 4, 5, 5, 6,
            3, 4, 4, 5, 4, 5, 5, 6, 4, 5, 5, 6, 5, 6, 6, 7, 2, 3, 3, 4, 3, 4,
            4, 5, 3, 4, 4, 5, 4, 5, 5, 6, 3, 4, 4, 5, 4, 5, 5, 6, 4, 5, 5, 6,
            5, 6, 6, 7, 3, 4, 4, 5, 4, 5, 5, 6, 4, 5, 5, 6, 5, 6, 6, 7, 4, 5,
            5, 6, 5, 6, 6, 7, 5, 6, 6, 7, 6, 7, 7, 8,
        };
        return (sum + lut[byte]);
    }
};

////////////////////////////////////////////////////////////////////////////////

class BytesToString
{
public:
    BytesToString(const unsigned char* bit_array, size_t bits_num);

    char operator()(char byte);

private:
    const unsigned char* m_bit_array;
    size_t m_bits_num;
};

BytesToString::BytesToString(const unsigned char* bit_array, size_t bits_num)
    : m_bit_array(bit_array), m_bits_num(bits_num)
{
}

inline char BytesToString::operator()(char byte)
{
    (void)byte;

    --m_bits_num;

    // If the bits are outside of the bits number they wont be
    bool val =
        m_bit_array[m_bits_num / CHAR_BIT] & (1ul << (m_bits_num % CHAR_BIT));

    return (val ? '1' : '0');
}

////////////////////////////////////////////////////////////////////////////////

class FlipByte
{
public:
    char operator()(char byte)
    {
        return (~(byte));
    }
};

////////////////////////////////////////////////////////////////////////////////

class AndBit
{
public:
    char operator()(char byte, char o_)
    {
        return (byte &= o_);
    }
};

////////////////////////////////////////////////////////////////////////////////

class OrBit
{
public:
    char operator()(char byte, char o_)
    {
        return (byte |= o_);
    }
};

////////////////////////////////////////////////////////////////////////////////

class XorBit
{
public:
    char operator()(char byte, char o_)
    {
        return (byte ^= o_);
    }
};

////////////////////////////////////////////////////////////////////////////////
//                      BitArray class & functions:                           //
////////////////////////////////////////////////////////////////////////////////

template < size_t Size >
class BitArray
{
public:
    BitArray();

    inline BitArray& SetAll();

    BitArray& Set(const size_t pos, const bool val);

    bool Get(size_t pos) const;

    inline BitArray& FlipAll();

    BitArray& Flip(size_t pos);

    bool operator[](size_t pos) const;
    BitProxy operator[](size_t pos);

    bool operator==(const BitArray& o_) const;
    bool operator!=(const BitArray& o_) const;

    BitArray& operator&=(const BitArray& o_);
    BitArray& operator|=(const BitArray& o_);
    BitArray& operator^=(const BitArray& o_);

    BitArray& operator<<=(size_t shift);
    BitArray& operator>>=(size_t shift);

    string ToString() const;
    size_t CountBitsOn() const;

private:
    unsigned char m_array[((Size - 1) / 8) + 1];
    int m_size;
};

template < size_t Size >
BitArray< Size >::BitArray() : m_array(), m_size((((Size - 1) / 8) + 1))
{
    memset(&m_array, 0, sizeof(m_array));
}

template < size_t Size >
BitArray< Size >& BitArray< Size >::SetAll()
{
    fill(m_array, m_array + m_size, full_byte);
    ZeroUnusedBits(m_array + m_size - 1, Size);
    return (*this);
}

template < size_t Size >
BitArray< Size >& BitArray< Size >::FlipAll()
{
    transform(m_array, m_array + m_size, m_array, FlipByte());
    ZeroUnusedBits(m_array + m_size - 1, Size);
    return (*this);
}

////////////////////////////////////////////////////////////////////////////////

template < size_t Size >
BitArray< Size >& BitArray< Size >::Set(const size_t pos, const bool val)
{
    char mask = 1;
    mask <<= (pos % CHAR_BIT);

    if (val)
    {
        (m_array[BIT_CHAR(pos)] |= mask);
    }
    else
    {
        m_array[BIT_CHAR(pos)] &= ~(mask);
    }

    return (*this);
}

////////////////////////////////////////////////////////////////////////////////

template < size_t Size >
bool BitArray< Size >::Get(size_t pos) const
{
    char mask = 1;
    mask <<= (pos % CHAR_BIT);
    char temp = m_array[BIT_CHAR(pos)];

    return (temp &= mask);
}

////////////////////////////////////////////////////////////////////////////////

template < size_t Size >
BitArray< Size >& BitArray< Size >::Flip(const size_t pos)
{
    char mask = 1;
    mask <<= (pos % CHAR_BIT);
    m_array[BIT_CHAR(pos)] ^= mask;

    return (*this);
}

////////////////////////////////////////////////////////////////////////////////

template < size_t Size >
bool BitArray< Size >::operator[](size_t pos) const
{
    return (this->Get(pos));
}

////////////////////////////////////////////////////////////////////////////////

template < size_t Size >
BitProxy BitArray< Size >::operator[](size_t pos)
{
    size_t arrIdx = pos / CHAR_BIT;
    unsigned char bitIdx = pos % CHAR_BIT;

    return (BitProxy(m_array[arrIdx], bitIdx));
}

////////////////////////////////////////////////////////////////////////////////

// Return 1 if equal, 0 if not equal
template < size_t Size >
bool BitArray< Size >::operator==(const BitArray& o_) const
{
    return (equal(m_array, m_array + m_size, o_.m_array));
}

////////////////////////////////////////////////////////////////////////////////

// Return 1 if not equal, 0 if equal
template < size_t Size >
bool BitArray< Size >::operator!=(const BitArray& o_) const
{
    return (!equal(m_array, m_array + m_size, o_.m_array));
}

////////////////////////////////////////////////////////////////////////////////

template < size_t Size >
BitArray< Size >& BitArray< Size >::operator&=(const BitArray& o_)
{
    transform(m_array, m_array + m_size, o_.m_array, m_array, AndBit());
    return (*this);
}

////////////////////////////////////////////////////////////////////////////////

template < size_t Size >
BitArray< Size >& BitArray< Size >::operator|=(const BitArray& o_)
{
    transform(m_array, m_array + m_size, o_.m_array, m_array, OrBit());
    return (*this);
}

////////////////////////////////////////////////////////////////////////////////

template < size_t Size >
BitArray< Size >& BitArray< Size >::operator^=(const BitArray& o_)
{
    transform(m_array, m_array + m_size, o_.m_array, m_array, XorBit());
    return (*this);
}

////////////////////////////////////////////////////////////////////////////////

template < size_t Size >
BitArray< Size >& BitArray< Size >::operator<<=(size_t shift)
{
    ShiftLeftOp(m_array, Size, shift);

    return (*this);
}

////////////////////////////////////////////////////////////////////////////////

template < size_t Size >
BitArray< Size >& BitArray< Size >::operator>>=(size_t shift)
{
    ShiftRightOp(m_array, Size, shift);

    return (*this);
}

////////////////////////////////////////////////////////////////////////////////

template < size_t Size >
inline string BitArray< Size >::ToString() const
{
    string str(Size, 0);
    transform(str.begin(), str.end(), str.begin(),
              BytesToString(m_array, Size));

    return (str);
}

////////////////////////////////////////////////////////////////////////////////

template < size_t Size >
size_t BitArray< Size >::CountBitsOn() const
{
    return (accumulate(m_array, m_array + m_size, 0, NumBitsInByte()));
}

////////////////////////////////////////////////////////////////////////////////
//                             Utility function:                              //
////////////////////////////////////////////////////////////////////////////////

void ShiftRightOp(unsigned char* bit_array, size_t bits_num, size_t shift)
{
    size_t bit_array_length = ((bits_num - 1) / CHAR_BIT) + 1;
    size_t byte_index = shift / CHAR_BIT;
    size_t bit_index = shift % CHAR_BIT;

    if (shift >= bits_num)
    {
        byte_index = bit_array_length;
    }

    if (((byte_index + 1) < bit_array_length) && (0 != bit_index))
    {
        transform(bit_array + byte_index + 1, bit_array + bit_array_length,
                  bit_array + byte_index, bit_array + byte_index,
                  ShiftRight(bit_index));
    }

    bit_array[bit_array_length - 1] >>= bit_index;

    if (0 != byte_index)
    {
        copy(bit_array + byte_index, bit_array + bit_array_length, bit_array);
    }

    fill(bit_array + (bit_array_length - byte_index),
         bit_array + bit_array_length, 0);
}

////////////////////////////////////////////////////////////////////////////////

void ShiftLeftOp(unsigned char* bit_array, size_t bits_num, size_t shift)
{
    size_t bit_array_length = ((bits_num - 1) / CHAR_BIT) + 1;
    size_t byte_index = shift / CHAR_BIT;
    size_t bit_index = shift % CHAR_BIT;

    if (shift >= bits_num)
    {
        byte_index = bit_array_length;
    }

    if (0 != byte_index) // 1 or more bytes should be turned into zeros
    {
        copy_backward(bit_array, bit_array + (bit_array_length - byte_index),
                      bit_array + bit_array_length);
    }

    if (((byte_index + 1) < bit_array_length) && (0 != bit_index))
    {
        transform(bit_array + byte_index, bit_array + bit_array_length,
                  bit_array + byte_index, ShiftLeft(bit_index));
    }

    ZeroUnusedBits(bit_array + bit_array_length - 1, bits_num);

    fill(bit_array, bit_array + byte_index, 0);
}

////////////////////////////////////////////////////////////////////////////////

static inline void ZeroUnusedBits(unsigned char* bit_array_end, size_t bits_num)
{
    size_t unused_bits = (CHAR_BIT - bits_num) % CHAR_BIT;
    *bit_array_end &= full_byte >> unused_bits;
}

#endif // ILRD_RD8586_BIT_ARRAY_HPP
