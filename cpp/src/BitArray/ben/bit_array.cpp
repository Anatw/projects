/*******************************************************************************
* WS: Bit Array API                                                            *
* Topic: C++                                                                   *
* Date: 5/07/2020                                                              *
* Author: Ben David Zikri                                                      *
* Reviwer:                                                                     *
*******************************************************************************/
#include<string.h>
#include "bit_array.hpp"

static unsigned char lut[] = { 0, 1, 1, 2, 1, 2, 2, 3, 1, 2, 2, 3, 2, 3, 3, 4,
       1, 2, 2, 3, 2, 3, 3, 4, 2, 3, 3, 4, 3, 4, 4, 5, 1, 2, 2, 3, 2, 3, 3, 4,
       2, 3, 3, 4, 3, 4, 4, 5, 2, 3, 3, 4, 3, 4, 4, 5, 3, 4, 4, 5, 4, 5, 5, 6,
       1, 2, 2, 3, 2, 3, 3, 4, 2, 3, 3, 4, 3, 4, 4, 5, 2, 3, 3, 4, 3, 4, 4, 5,
       3, 4, 4, 5, 4, 5, 5, 6, 2, 3, 3, 4, 3, 4, 4, 5, 3, 4, 4, 5, 4, 5, 5, 6,
       3, 4, 4, 5, 4, 5, 5, 6, 4, 5, 5, 6, 5, 6, 6, 7, 1, 2, 2, 3, 2, 3, 3, 4, 
       2, 3, 3, 4, 3, 4, 4, 5, 2, 3, 3, 4, 3, 4, 4, 5, 3, 4, 4, 5, 4, 5, 5, 6,
       2, 3, 3, 4, 3, 4, 4, 5, 3, 4, 4, 5, 4, 5, 5, 6, 3, 4, 4, 5, 4, 5, 5, 6,
       4, 5, 5, 6, 5, 6, 6, 7, 2, 3, 3, 4, 3, 4, 4, 5, 3, 4, 4, 5, 4, 5, 5, 6,
       3, 4, 4, 5, 4, 5, 5, 6, 4, 5, 5, 6, 5, 6, 6, 7, 3, 4, 4, 5, 4, 5, 5, 6, 
	   4, 5, 5, 6, 5, 6, 6, 7, 4, 5, 5, 6, 5, 6, 6, 7, 5, 6, 6, 7, 6, 7, 7, 8 };

class BinaryToString
{
public:
	BinaryToString(std::string& string) : m_str(string) {}

	void operator()(uint8_t byte) 
	{
		uint8_t msb = 1 << CHAR_BITS - 1;

        for (int i = 0; i < CHAR_BITS; ++i, byte <<= 1)
        {
            m_str += ((byte & msb) >> CHAR_BITS - 1) + '0';
        }

		m_str += ' ';
	}

private:
	std::string& m_str;
};

class MoveRight
{
public:
    MoveRight(int to_move) : move(to_move), buff(0), next_buff(0) {}
    uint8_t operator()(uint8_t byte)
    {
        next_buff = byte << (CHAR_BITS - move);

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

class MirrorByte
{
public:
    uint8_t operator()(uint8_t byte)
    {
        byte = (byte & 0xF0) >> 4 | (byte & 0x0F) << 4;
        byte = (byte & 0xCC) >> 2 | (byte & 0x33) << 2;
        byte = (byte & 0xAA) >> 1 | (byte & 0x55) << 1;
        return byte;
    }
};

class Setter
{
public:
	Setter(uint8_t filler) : m_fill(filler) {}
	uint8_t operator()(uint8_t byte) { return(m_fill); }
private:
	uint8_t m_fill;
};

// 1: |=, 2: ^=, 3: &= 
class OPFunctor
{
public:
	OPFunctor(const uint8_t *arr, int op) : m_arr(arr), m_idx(0), m_op(op) {}
	uint8_t operator()(uint8_t byte) 
	{ 
		switch (m_op)
		{
		case 1:
			byte |= m_arr[m_idx];
			break;
		case 2:
			byte ^= m_arr[m_idx];
			break;
		case 3:
			byte &= m_arr[m_idx];
			break;
		}

		m_idx++;
		return(byte);
	}
private:
	const uint8_t *m_arr;
	uint64_t m_idx;
	int m_op;
};

class NumBitsInByte
{
public:
	int operator()(int sum , uint8_t byte) const 
	{
		return (sum + lut[byte]);
	}
};

class FlipByte
{
public:
	uint8_t operator()(uint8_t byte) { return(~byte); }
};

template <uint64_t SIZE>
inline bool BitArray<SIZE>::Get(uint64_t pos) const
{
	CheckBounds(pos);
	
	int n = pos % CHAR_BITS;
	return ((m_arr[pos / CHAR_BITS] >> n) & 1);
}

template <uint64_t SIZE>
void BitArray<SIZE>::SetAll()
{
    std::fill(m_arr, m_arr + NBYTES(SIZE), 0xFF);

	ZeroLeftovers();
}

template <uint64_t SIZE>
inline void BitArray<SIZE>::Set(uint64_t pos, bool value)
{
	CheckBounds(pos);

	m_arr[pos / CHAR_BITS] ^= (-value ^ m_arr[pos / CHAR_BITS]) & (1UL << pos % CHAR_BITS);
}

template <uint64_t SIZE>
void BitArray<SIZE>::Flip(uint64_t pos)
{
	CheckBounds(pos);
	
	m_arr[pos / CHAR_BITS] ^= (1 << (CHAR_BITS - 1 - ((pos) % CHAR_BITS)));
}

template <uint64_t SIZE>
void BitArray<SIZE>::FlipAll()
{
	std::transform(m_arr, m_arr + NBYTES(SIZE), m_arr, FlipByte());

   	ZeroLeftovers();
}

template <uint64_t SIZE>
uint64_t BitArray<SIZE>::CountSetBits() const
{
	return (std::accumulate(m_arr, m_arr + NBYTES(SIZE), 0, NumBitsInByte()));
}

template <uint64_t SIZE>
inline bool BitArray<SIZE>::operator [](uint64_t pos) const
{
	return (this->Get(pos));
}

template <uint64_t SIZE>
bool BitArray<SIZE>::operator ==(const BitArray& other) const
{
	return (std::equal(m_arr, m_arr + NBYTES(SIZE), other.m_arr));
}

template <uint64_t SIZE>
bool BitArray<SIZE>::operator !=(const BitArray& other) const
{
	return (!std::equal(m_arr, m_arr + NBYTES(SIZE), other.m_arr));
}

template <uint64_t SIZE>
BitArray<SIZE>& BitArray<SIZE>::operator |=(const BitArray &other)
{
	std::transform(m_arr, m_arr + NBYTES(SIZE), m_arr, OPFunctor(other.m_arr,1));
	
	return (*this);
}

template <uint64_t SIZE>
BitArray<SIZE>& BitArray<SIZE>::operator ^=(const BitArray &other)
{
	std::transform(m_arr, m_arr + NBYTES(SIZE), m_arr, OPFunctor(other.m_arr,2));
	
	return (*this);
}

template <uint64_t SIZE>
BitArray<SIZE>& BitArray<SIZE>::operator &=(const BitArray &other)
{
	std::transform(m_arr, m_arr + NBYTES(SIZE), m_arr, OPFunctor(other.m_arr,3));
	
	return (*this);
}

template <uint64_t SIZE>
BitArray<SIZE> &BitArray<SIZE>::operator>>=(uint64_t n)
{
	Shifter(n);
    ZeroLeftovers();

    return (*this);
}

template <uint64_t SIZE>
BitArray<SIZE> &BitArray<SIZE>::operator<<=(uint64_t n)
{
	ReverseBits();
	Shifter(n);
	ReverseBits();

    return (*this);
}

template <uint64_t SIZE>
std::string BitArray<SIZE>::ToString() const
{
	std::string str;
	std::for_each(m_arr, m_arr + NBYTES(SIZE), BinaryToString(str));
	str.resize(SIZE + NBYTES(SIZE)-1);
	
	return (str);
}

template <uint64_t SIZE>
void BitArray<SIZE>::CheckBounds(uint64_t pos)
{
	if(pos >= SIZE)
	{
		std::cout << std::endl;
    	throw std::out_of_range("BitArray: index is out of range");
	}
}

template <uint64_t SIZE>
void BitArray<SIZE>::ZeroLeftovers()
{
	 uint64_t bits = SIZE % CHAR_BITS;
    if (bits != 0)
    {
        uint8_t mask = 0xFF << (CHAR_BITS - bits);

        m_arr[(SIZE-1)/CHAR_BITS] &= mask;
    }
}

template <uint64_t SIZE>
void BitArray<SIZE>::Shifter(uint64_t n)
{
	if (n >= SIZE)
	{
		std::transform(m_arr, m_arr + NBYTES(SIZE), m_arr, Setter(0));
		return;
	}
	
	memmove(m_arr + n / 8, m_arr, NBYTES(SIZE) + 1 - n / 8);
	memset(m_arr, 0, n / 8);
	std::transform(m_arr + n / 8, m_arr + NBYTES(SIZE), m_arr + n / 8, MoveRight(n % 8));
}

template <uint64_t SIZE>
void BitArray<SIZE>::ReverseBits()
{
	std::reverse(m_arr, m_arr + NBYTES(SIZE));
    std::transform(m_arr, m_arr + NBYTES(SIZE), m_arr, MirrorByte());
}