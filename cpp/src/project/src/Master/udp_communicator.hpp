#ifndef ILRD_RD8586_UDP_COMMUNICATOR_HPP
#define ILRD_RD8586_UDP_COMMUNICATOR_HPP

#include <iostream>
#include <map>

#include <boost/shared_ptr.hpp>
#include <boost/thread.hpp>
#include <sys/inotify.h>

#include "reactor.hpp"
#include "master_storage_manager.hpp"
#include "minion_info.hpp"
#include "logger.hpp"
#include "master_protocol.hpp"

namespace ilrd
{
class IMasterCommunicator
{
};

class UDPcommunicator : public IMasterCommunicator, private boost::noncopyable
{
public:
    class Broadcaster;
    typedef Broadcaster MinionUDPIdentifier;

    UDPcommunicator(int port, Reactor &reactor, MasterStorageManager &storage_manager);
    ~UDPcommunicator();
private:
        class UDPMinion : public MinionInfo
        {
        public:
            UDPMinion(int fd, int port, const std::string &ip);
            void Send(char* data);
            inline int GetFd();
            inline int GetPort();
            inline std::string GetIp();

        private:
            int m_fd;
            int m_port;
            std::string m_ip;
        };

        class Broadcaster
        {
        public:
            // Init in a new thread, Open a socket for UDP broadcast
            Broadcaster(int port);
            inline int GetFd();
            ~Broadcaster();
        private:
            int m_fd;
            int m_port;
            bool m_is_on;
            boost::thread m_sending_thread;

            // send the bradcasatmessage every 1 second 
            void SendBroadCast();
            // void CheckMinionsStatus();

        };

    void CreateMinion(int fd);
    void STDIN_Stop(int fd);
    
    int m_port;
    Reactor &m_reactor;
    MasterStorageManager &m_storage_manager;
    std::map<std::string, boost::shared_ptr<UDPMinion> > m_udp_minions;
    MinionUDPIdentifier m_minionUDPidentifier;
};
} // namespace ilrd

inline int UDPcommunicator::UDPMinion::GetFd()
{
    return m_fd;
}

inline int UDPcommunicator::MinionUDPIdentifier::GetFd()
{
    return m_fd;
}

inline int UDPcommunicator::UDPMinion::GetPort()
{
    return m_port;
}

inline std::string UDPcommunicator::UDPMinion::GetIp()
{
    return m_ip;
}

#endif //ILRD_RD8586_UDP_COMMUNICATOR_HPP