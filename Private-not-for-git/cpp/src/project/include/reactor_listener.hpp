/*******************************************************************************
Title & Description: Master Storage Manager - part of the Master in the 
final project.
This part is in charge of all the documentation and maintenance of the 
mapping between the offsets of the memory and the Minion responsible to 
operate

Authour: Anat Wax, anatwax@gmail.com
Reviewer: 
Datecreation: 20.09.2020
Version: 1
*******************************************************************************/
#include <iostream> // cout
#include <limits> // interger min + max values
#include <vector>

#include "reactor.hpp"
#include "logger.hpp"

using namespace ilrd;

class ReactorListener : public IListener
{
public:
std::vector< HandleAndMode > Listen(const std::vector< HandleAndMode >& handle)
    {
        fd_set ReadFDs;
        fd_set WriteFDs;
        fd_set ExceptFDs;

        FD_ZERO(&ReadFDs);
        FD_ZERO(&WriteFDs);
        FD_ZERO(&ExceptFDs);

        // Inserting keys from vector into the lists with regards to correct
        // MODE
        std::vector< HandleAndMode >::const_iterator iterator = handle.begin();
        std::vector< HandleAndMode >::const_iterator end = handle.end();
        for (; iterator != end; ++iterator)
        {
            switch (iterator->first)
            {
            case READ:
                FD_SET(iterator->second, &ReadFDs);
                break;

            case WRITE:
                FD_SET(iterator->second, &WriteFDs);
                break;

            case EXCEPTION:
                FD_SET(iterator->second, &ExceptFDs);
                break;

            default:
                break;
            }
        }

        if (0 > select(FD_SETSIZE, &ReadFDs, &WriteFDs, &ExceptFDs, NULL))
        {
            throw std::domain_error("select failed");
            LOG_ERROR(__FILE__ + std::string("::Listen() - select() failed."));
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
};
