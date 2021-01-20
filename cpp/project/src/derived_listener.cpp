/*******************************************************************************
Dynamic library for a derived listener.

Written by Anat Wax, anatwax@gmail.com
Created: August 20
*******************************************************************************/

#include "derived_listener.hpp"

using namespace ilrd;

std::vector< HandleAndMode >
DerievedListener::Listen(const std::vector< HandleAndMode >& handle)
{
    fd_set ReadFDs;
    fd_set WriteFDs;
    fd_set ExceptFDs;

    FD_ZERO(&ReadFDs);
    FD_ZERO(&WriteFDs);
    FD_ZERO(&ExceptFDs);

    // Inserting keys from vector into the lists with regards to correct
    // MODE
    std::vector< HandleAndMode >::const_iterator i;
    for (i = handle.begin(); i != handle.end(); ++i)
    {
        switch (i->first)
        {
        case READ:
            FD_SET(i->second, &ReadFDs);
            break;

        case WRITE:
            FD_SET(i->second, &WriteFDs);
            break;

        case EXCEPTION:
            FD_SET(i->second, &ExceptFDs);
            break;

        default:
            break;
        }
    }

    if (0 > select(FD_SETSIZE, &ReadFDs, &WriteFDs, &ExceptFDs, NULL))
    {
        throw std::domain_error("select failed");
    }

    std::vector< HandleAndMode > return_vector;

    for (int index = 0; index < FD_SETSIZE; ++index)
    {
        if (FD_ISSET(index, &ReadFDs))
        {
            return_vector.push_back(HandleAndMode(READ, index));
        }
        if (FD_ISSET(index, &WriteFDs))
        {
            return_vector.push_back(HandleAndMode(WRITE, index));
        }
        if (FD_ISSET(index, &ExceptFDs))
        {
            return_vector.push_back(HandleAndMode(EXCEPTION, index));
        }
    }

    return (return_vector);
}

DerievedListener::~DerievedListener()
{
}
