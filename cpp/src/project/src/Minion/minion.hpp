/*******************************************************************************
Minion class
Written by Anat Wax, anatwax@gmail.com
Created: 9.8.20
Reviewer: Daria Korotkova
*******************************************************************************/
#ifndef __ILRD_RD8586_MINION_HPP__
#define __ILRD_RD8586_MINION_HPP__

#include <boost/noncopyable.hpp> // boost::noncopyable

#include "master_communicator.hpp"
#include "protocol.hpp"
#include "reactor.hpp"
#include "storage.hpp"

namespace ilrd
{
class Minion : private boost::noncopyable
{
public:
    explicit Minion(int port, size_t num_of_blocks, int master_port);
    ~Minion();

    void Run();

private:
    // OnRequest
    // Receives: Request structure.
    // Returns: nothing
    void OnRequest(const Request& request);

    Reactor m_reactor;
    MasterCommunicator m_communicator;
    Storage< MAX_BLOCK_SIZE > m_storage;
};

} // namespace ilrd

#endif /* __ILRD_RD8586_Minion_HPP__ */
