#ifndef ILRD_RD8586_BIT_ARRAY_HPP
#define ILRD_RD8586_BIT_ARRAY_HPP

#include <stddef.h>  // size_t
#include <algorithm> // for_each()
#include <iostream>  // cout, cin, cerr
#include <numeric>   // accumulate()
#include <string.h>  //strcmp()
#include <climits>   // CHAR_BIT

using namespace std;

typedef char BYTE;
#define ON (1)
#define BITS_IN_BYTE (8)
#define FULL_BYTE (255)
#define BIT_CHAR(bit) ((bit) / BITS_IN_BYTE)
#define NBYTES(T) (((T - 1) / 8) + 1)


////////////////////////////////////////////////////////////////////////////////

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

////////////////////////////////////////////////////////////////////////////////

class Setter
{
public:
	Setter(char filler) : m_fill(filler) {}
	char operator()(int setter)
	{
        (void)setter;
		return(m_fill);
	}
private:
	char m_fill;
};

////////////////////////////////////////////////////////////////////////////////

class MoveRight
{
public:
    MoveRight(int to_move) : move(to_move), buff(0), next_buff(0) {}
    char operator()(char byte)
    {
        next_buff = byte << (BITS_IN_BYTE - move);

        byte >>= move;
        byte ^= buff;
        buff = next_buff;

        return (byte);
    }

private:
    int move;
    char buff;
    char next_buff;
};


class ShiftRight
{
public:
    ShiftRight(size_t shmnt) : m_shmntR(shmnt), m_shmntL(CHAR_BIT - shmnt) {}
    char operator()(char b1, char b2)
    {
        return ((b2 >> m_shmntR) | (b1 << m_shmntL));
    }

private:
    size_t m_shmntR;
    size_t m_shmntL;
};

void ShiftRightOp(char *bit_array, size_t bits_num, size_t shift)
{
    size_t bit_array_length = ((bits_num - 1) / CHAR_BIT) + 1;
    size_t in_arr_byte_index = shift / CHAR_BIT;
    size_t in_byte_bit_index = shift % CHAR_BIT;

    if (shift >= bits_num) 
    {
        in_arr_byte_index = bit_array_length;
    }

    if (((in_arr_byte_index + 1) < bit_array_length) &&
                                            (0 != in_byte_bit_index)) 
    {
        transform(bit_array + in_arr_byte_index + 1,
                       bit_array + bit_array_length,
                       bit_array + in_arr_byte_index,
                       bit_array + in_arr_byte_index,
                       ShiftRight(in_byte_bit_index));
    }

    bit_array[bit_array_length - 1] >>= in_byte_bit_index;

    if (0 != in_arr_byte_index) 
    {
        copy(bit_array + in_arr_byte_index, bit_array + bit_array_length,
                        bit_array);
    }

    fill(bit_array + (bit_array_length - in_arr_byte_index),
                        bit_array + bit_array_length, 0);
}


class ShiftLeft
{
public:
    ShiftLeft(size_t shmnt) 
        : m_shmntR(CHAR_BIT - shmnt), m_shmntL(shmnt), m_prev(0) {}

    char operator()(char b1)
    {
        unsigned char res = (b1 << m_shmntL) | (m_prev >> m_shmntR);

        m_prev = b1;

        return (res);
    }

private:
    size_t m_shmntR;
    size_t m_shmntL;
    char m_prev;
};

static inline void ZeroUnusedBits(char *bit_array_end, size_t bits_num)
{
    size_t unused_bits = (CHAR_BIT - bits_num) % CHAR_BIT;
    *bit_array_end &= FULL_BYTE >> unused_bits;
}


void ShiftLeftOp(char *bit_array, size_t bits_num, size_t shift)
{
    size_t bit_array_length = ((bits_num - 1) / CHAR_BIT) + 1;
    size_t in_arr_byte_index = shift / CHAR_BIT;
    size_t in_byte_bit_index = shift % CHAR_BIT;

    if (shift >= bits_num) 
    {
        in_arr_byte_index = bit_array_length;
    }

    if (0 != in_arr_byte_index) 
    {
        copy_backward(bit_array,
                      bit_array + (bit_array_length - in_arr_byte_index),
                      bit_array + bit_array_length);
    }

    if (((in_arr_byte_index + 1) < bit_array_length) &&
        (0 != in_byte_bit_index)) 
    {
        transform(bit_array + in_arr_byte_index,
                  bit_array + bit_array_length,
                  bit_array + in_arr_byte_index,
                  ShiftLeft(in_byte_bit_index));
    }

    ZeroUnusedBits(bit_array + bit_array_length - 1, bits_num);

    fill(bit_array, bit_array + in_arr_byte_index, 0);
}



////////////////////////////////////////////////////////////////////////////////

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

////////////////////////////////////////////////////////////////////////////////

class MirrorByte
{
public:
    char operator()(char byte)
    {
        //  byte: 10111110
        //        10110000
        //        00001011
        //                          10111110
        //                          00001111
        //                          00001110
        //                          11100000
        //  00001011 | 11100000 = 11101011    
        // 0xF0 = 11110000, 0x0F = 00001111
        // swap first half of byte with second half:
        byte = (byte & 0xF0) >> 4 | (byte & 0x0F) << 4; 
        
        
        //  byte: 11101011  
        //        11001000
        //        00110010
        //                    byte: 00110010
        //                          00110011    
        //                          00110010
        //                          11001000
        // 00110010 | 11001000 = 11111010
        // 0xCC = 11001100, 0x33 = 00110011
        byte = (byte & 0xCC) >> 2 | (byte & 0x33) << 2;

        //  byte: 11111010
        //        10101010
        //        01010101
        //                    byte: 01010101
        //                          01010101
        //                          01010101
        //                          10101010
        // 01010101 | 10101010 = 11111111
        // 0xAA = 10101010, 0xAA = 01010101
        byte = (byte & 0xAA) >> 1 | (byte & 0x55) << 1;

        return byte;
    }
};

////////////////////////////////////////////////////////////////////////////////

class FlipByte
{ 
public:
    char operator()(char byte)
    {
        return (~byte);
    }
};

////////////////////////////////////////////////////////////////////////////////

class BitAnd
{
public:
    char operator()(char arr, char o)
    {
        return (arr &= o);
    }
};

////////////////////////////////////////////////////////////////////////////////

class BitOr
{
public:
    char operator()(char arr, char o)
    {
        return (arr |= o);
    }
};

////////////////////////////////////////////////////////////////////////////////

class BitXor
{
public:
    char operator()(char arr, char o)
    {
        return (arr ^= o);
    }
};

////////////////////////////////////////////////////////////////////////////////
//                  BitProxy class and template functions:                    //
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

////////////////////////////////////////////////////////////////////////////////

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

////////////////////////////////////////////////////////////////////////////////

template <typename T>
BitProxy<T>::operator bool() const
{
    return ((this->m_byte >> this->m_index) & 1);
}

////////////////////////////////////////////////////////////////////////////////

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

    bool Get(const size_t pos) const;

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
    void ReverseBits();
    void Shifter(size_t shift);
    void CheckBoundries(size_t position);
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

////////////////////////////////////////////////////////////////////////////////

template <size_t Size>
BitArray<Size> &BitArray<Size>::Set(const size_t pos, const bool val)
{
    CheckBoundries(pos);

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

////////////////////////////////////////////////////////////////////////////////

template <size_t Size>
bool BitArray<Size>::Get(const size_t pos) const
{
    if (pos >= Size)
	{
		cout << endl;
    	throw out_of_range("BitArray: index is out of range");
	}

    char mask = 1;
    mask <<= (pos % BITS_IN_BYTE);
    char temp = this->m_array[BIT_CHAR(pos)];

    return (temp &= mask);
}

////////////////////////////////////////////////////////////////////////////////

template <size_t Size>
BitArray<Size> &BitArray<Size>::Flip(const size_t pos)
{
    CheckBoundries(pos);

    char mask = 1;
    mask <<= (pos % BITS_IN_BYTE);
    this->m_array[BIT_CHAR(pos)] ^= mask;

    return (*this);
}

////////////////////////////////////////////////////////////////////////////////

template <size_t Size>
size_t BitArray<Size>::CountBitsOn() const
{
    return (accumulate(this->m_array, this->m_array + this->m_size,
                       0, NumBitsInByte()));
}

////////////////////////////////////////////////////////////////////////////////

template <size_t Size>
BitArray<Size> &BitArray<Size>::SetAll()
{
    fill(this->m_array, this->m_array + this->m_size, FULL_BYTE);
    return (*this);
}

////////////////////////////////////////////////////////////////////////////////

template <size_t Size>
BitArray<Size> &BitArray<Size>::FlipAll()
{
    transform(this->m_array, this->m_array + this->m_size,
              this->m_array, FlipByte());
    return (*this);
}

////////////////////////////////////////////////////////////////////////////////

template <size_t Size>
bool BitArray<Size>::operator==(const BitArray &o_) const
{
    return (equal(this->m_array, this->m_array + this->m_size, o_.m_array));
}

////////////////////////////////////////////////////////////////////////////////

template <size_t Size>
bool BitArray<Size>::operator!=(const BitArray &o_) const
{
    return (!equal(this->m_array, this->m_array + this->m_size, o_.m_array));
}

////////////////////////////////////////////////////////////////////////////////

template <size_t Size>
BitArray<Size> &BitArray<Size>::operator&=(const BitArray &o_)
{
    transform(this->m_array, this->m_array + this->m_size, o_.m_array, this->m_array, BitAnd());
    return (*this);
}

////////////////////////////////////////////////////////////////////////////////

template <size_t Size>
BitArray<Size> &BitArray<Size>::operator|=(const BitArray &o_)
{
    transform(this->m_array, this->m_array + this->m_size, o_.m_array, this->m_array, BitOr());
    return (*this);
}

////////////////////////////////////////////////////////////////////////////////

template <size_t Size>
BitArray<Size> &BitArray<Size>::operator^=(const BitArray &o_)
{
    transform(this->m_array, this->m_array + this->m_size, o_.m_array, this->m_array, BitXor());
    return (*this);
}

////////////////////////////////////////////////////////////////////////////////

template <size_t Size>
BitArray<Size> &BitArray<Size>::operator<<=(size_t shift)
{
    // ShiftRightOp(m_array, Size, shift);
    ShiftLeftOp(m_array, Size, shift);

    return (*this);
}

////////////////////////////////////////////////////////////////////////////////

template <size_t Size>
BitArray<Size> &BitArray<Size>::operator>>=(size_t shift)
{
    // ShiftLeftOp(m_array, Size, shift);
    ShiftRightOp(m_array, Size, shift);

    return (*this);
}

////////////////////////////////////////////////////////////////////////////////

template <size_t Size>
bool BitArray<Size>::operator[](size_t pos) const
{
    CheckBoundries(pos);

    return (this->Get(pos));
}

////////////////////////////////////////////////////////////////////////////////

template <size_t Size>
BitProxy<bool> BitArray<Size>::operator[](size_t pos)
{
    CheckBoundries(pos);
    
    BitProxy<bool> bit_proxy(this->m_array[pos / BITS_IN_BYTE], pos % BITS_IN_BYTE);

    return (bit_proxy);
}

////////////////////////////////////////////////////////////////////////////////

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

////////////////////////////////////////////////////////////////////////////////

template <size_t Size>
void BitArray<Size>::ReverseBits()
{
    reverse(m_array, m_array + m_size);
    transform(m_array, m_array + m_size, m_array, MirrorByte());
}

////////////////////////////////////////////////////////////////////////////////

// template <size_t Size>
// void BitArray<Size>::Shifter(size_t shift)
// {
//     if (shift >= Size)
//     {
//         transform(m_array, m_array + m_size, m_array, Setter(0));
//         return;
//     }

//     memmove(m_array + shift / BITS_IN_BYTE,
//             m_array,
//             m_size + 1 - shift / BITS_IN_BYTE);

//     memset(m_array, 0, shift / BITS_IN_BYTE);
    
//     transform(m_array + shift / BITS_IN_BYTE,
//               m_array + m_size,
//               m_array + shift / BITS_IN_BYTE,
//               MoveRight(shift % BITS_IN_BYTE));
// }

////////////////////////////////////////////////////////////////////////////////

template <size_t Size>
void BitArray<Size>::CheckBoundries(size_t position)
{
	if (position >= Size)
	{
		cout << endl;
    	throw out_of_range("BitArray: index is out of range");
	}
}

#endif // ILRD_RD8586_BIT_ARRAY_HPP
