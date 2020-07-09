/*******************************************************************************
* WS: Bit Array API                                                            *
* Topic: C++                                                                   *
* Date: 5/07/2020                                                              *
* Author: Ben David Zikri                                                      *
* Reviwer:                                                                     *
*******************************************************************************/
#ifndef BIT_ARRAY_H
#define BIT_ARRAY_H

#include <algorithm>
#include <iostream>
#include <stddef.h>
#include <numeric>
#include <string>

#define CHAR_BITS (8)
#define NBYTES(T) (((T - 1) / CHAR_BITS) + 1)

class BitProxy
{
public:
	BitProxy(uint8_t &bit_arr, uint8_t pos) : m_bit_arr(bit_arr), m_pos(pos) {}
	BitProxy& operator=(bool value)
	{
		uint8_t mask = 1 << m_pos;
		m_bit_arr = (m_bit_arr & ~mask) | ((value << m_pos) & mask);

		return (*this);
	}

	operator bool() const
	{
		return ((m_bit_arr >> m_pos) & 1);
	}

private:
	uint8_t &m_bit_arr;
	uint8_t m_pos;
};

template <uint64_t SIZE>
class BitArray
{
public:
	BitArray() : m_arr() {}
	void SetAll();
	inline void Set(uint64_t pos, bool value);
	inline bool Get(uint64_t pos) const;
	void FlipAll();
	void Flip(uint64_t pos);

	uint64_t CountSetBits() const;

	std::string ToString() const;
	bool operator[](uint64_t pos) const;
	
	BitProxy operator[](uint64_t pos)
	{
		BitProxy bp(m_arr[pos / CHAR_BITS], pos % CHAR_BITS);
		return (bp);
	}

	bool operator==(const BitArray &other) const;
	bool operator!=(const BitArray &other) const;

	BitArray& operator|=(const BitArray &other);
	BitArray& operator&=(const BitArray &other);
	BitArray& operator^=(const BitArray &other);
	BitArray& operator>>=(uint64_t n);
	BitArray& operator<<=(uint64_t n);

private:
	void CheckBounds(uint64_t pos);
	void ZeroLeftovers();
	uint8_t m_arr[NBYTES(SIZE)];
};

#endif // BIT_ARRAY_H