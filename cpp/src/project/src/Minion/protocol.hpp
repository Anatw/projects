/*******************************************************************************
protocol (Minion)
Written by Anat Wax, anatwax@gmail.com
Created: 5.8.20
Reviewer:
*******************************************************************************/
#ifndef __ILRD_RD8586_MINION_PROTOCOL_HPP__
#define __ILRD_RD8586_MINION_PROTOCOL_HPP__

#include <stdint.h> /* unint_64_t */
#include <stdlib.h> /*  size_t */

namespace ilrd
{

const size_t MAX_BLOCK_SIZE = 4096;

struct Request
{
    inline size_t RequestSize()
    {
        return sizeof(*this);
    }

    char m_mode;
    uint64_t m_uid;
    uint64_t m_index;
    char m_data[1];
};

struct Response
{
    inline size_t ResponseSize()
    {
        return sizeof(*this);
    }

    char m_mode;
    char m_status;
    uint64_t m_uid;
    char m_data[1];
};

} // namespace ilrd

#endif // __ILRD_RD8586_MINION_PROTOCOL_HPP__
