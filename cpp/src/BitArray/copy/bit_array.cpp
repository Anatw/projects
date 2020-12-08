#include <iostream>  // cout, cin, cerr
#include <algorithm> // for_each()

#include "bit_array.hpp"

template <size_t Size>
BitArray<Size> &BitArray<Size>::Set(const size_t pos, const bool val)
{
    char mask = 1;

    mask <<= pos;
    if (this->m_array[pos] != val)
    {
        this->m_array[pos] = val;
    }

    return (*this);
}
