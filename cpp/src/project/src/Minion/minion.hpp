/*******************************************************************************
Minion class
Written by Anat Wax, anatwax@gmail.com
Created: 9.8.20
Reviewer:
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
    typedef u_int32_t ip_t;

    explicit Minion(int port, size_t num_of_blocks, int master_port);
    ~Minion();

    void Run();

    void Write(const void* buffer, size_t bufffer_size, ip_t client_addr,
               int port);
    void Read(void* buffer, size_t bufffer_size, ip_t client_addr, int port);

private:
    // OnRequest
    // Receives: Request structure.
    // Returns: nothing
    void OnRequest(const Request& request);

    Reactor m_reactor;
    MasterCommunicator m_communicator;
    Storage< MAX_BLOCK_SIZE > m_storage;
};

void Minion::OnRequest(const Request& request)
{
    std::cout << "Entring func()\n";
    std::cout << request.m_mode << std::endl;
    std::cout << request.m_index << std::endl;
    std::cout << request.m_uid << std::endl;
    std::cout << request.m_data << std::endl;

    size_t msg_size = MAX_BLOCK_SIZE + Request().RequestSize();

    Response* response = (Response*)operator new(msg_size);
    memset(response, 0, msg_size);

    response->m_mode = '0';
    response->m_status = 'A';
    response->m_uid = 456789;
    const char* msg = "hello back";
    memcpy(response->m_data, msg, strlen(msg));

    m_communicator.Reply(*response);
    delete response;

    // reactor.Stop();
}

} // namespace ilrd

#endif /* __ILRD_RD8586_Minion_HPP__ */
