/*******************************************************************************
Storage class (part of project Minion)
Written by Anat Wax, anatwax@gmail.com
Created: 4.8.20
Reviewer: Shumuel Sinder
*******************************************************************************/
#ifndef ILRD_RD8586_STORAGE_HPP
#define ILRD_RD8586_STORAGE_HPP

#include <assert.h>
#include <boost/noncopyable.hpp>
#include <fstream>
#include <iostream> // cout, cin, cerr

#include "logger.hpp"

namespace ilrd
{
template < size_t BLOCK_SIZE >
class Storage : private boost::noncopyable
{
public:
    // Possible return status: 0 == SUCCESS, 1 == FAILED TO OPEN, 2 ==
    // FAILED TO WRITE, 3 == FAILED TO READ, 4 == OUT OF RANGE
    explicit Storage(size_t num_of_blocks);
    // Write Function
    // Receives: index where to write data, pointer to source.
    // Returns: status of operation
    void Write(size_t index, const void* src);
    // Read Function
    // Receives: index from where to read, pointer to store read data .
    // Returns: status of operation
    void Read(size_t index, void* dest) const;

    // GetCapacity Function
    // Receives: nothing.
    // Return: size_t number of blocks
    size_t GetCapacity() const
    {
        return m_blocks_capacity;
    }

private:
    size_t m_blocks_capacity;

    const char* m_storage_file;
};

////////////////////////////////////////////////////////////////////////////////
//                           Functions implementations: //
////////////////////////////////////////////////////////////////////////////////

template < size_t BLOCK_SIZE >
Storage< BLOCK_SIZE >::Storage(size_t num_blocks)
    : m_blocks_capacity(num_blocks), m_storage_file("storage_file.txt")
{
    std::fstream storage_file;
    storage_file.open("storage_file.txt");
    storage_file.close();

    LOG_INFO("inside Storage(): opened a storage file - 'storage_file.txt'");
}

////////////////////////////////////////////////////////////////////////////////

template < size_t BLOCK_SIZE >
void Storage< BLOCK_SIZE >::Read(size_t index, void* dest) const
{
    assert(index <= m_blocks_capacity);

    std::fstream storage_file;
    storage_file.open("storage_file.txt");
    storage_file.seekg((index * BLOCK_SIZE), std::fstream::beg);
    storage_file.read(static_cast< char* >(dest), BLOCK_SIZE);

    LOG_INFO(__FILE__ + std::string("::Read(): reading from index" + index));

    storage_file.close();
}

////////////////////////////////////////////////////////////////////////////////

template < size_t BLOCK_SIZE >
void Storage< BLOCK_SIZE >::Write(size_t index, const void* src)
{
    std::cout << "index:\n\n" << index << std::endl;
    assert(index <= m_blocks_capacity);

    std::fstream storage_file;
    storage_file.open("storage_file.txt");
    storage_file.seekp((index * BLOCK_SIZE), std::fstream::beg);
    storage_file.write(static_cast< const char* >(src), BLOCK_SIZE);

    LOG_INFO(__FILE__ + std::string("::Write(): reading from index" + index));

    storage_file.close();
}

} // namespace ilrd

#endif // ILRD_RD8586_STORAGE_HPP
