#ifndef ILRD_RD8586_UDP_COMMUNICATOR_HPP
#define ILRD_RD8586_UDP_COMMUNICATOR_HPP

#include <iostream>
#include <map>

#include <boost/shared_ptr.hpp>
#include <boost/thread.hpp>
#include <boost/core/noncopyable.hpp>
#include <sys/inotify.h>

#include "reactor.hpp"
#include "reactor_listener.hpp"
#include "advanced_observer.hpp"
#include "master_storage_manager.hpp"
#include "minion_info.hpp"
#include "logger.hpp"
#include "master_protocol.hpp"
#include "scheduler.hpp" // set a fd that will wake up in a given time

namespace ilrd
{
class IMasterCommunicator
{
};

class UDPcommunicator : public IMasterCommunicator, private boost::noncopyable
{
public:
    UDPcommunicator(int port, Reactor &reactor, MasterStorageManager &storage_manager);
    ~UDPcommunicator();

private:
        // UDPMinion class will be a representation of a minion that it connected to the master. All these Minions will be added to the m_udp_minions
        class UDPMinion : public MinionInfo
        {
        public:
            UDPMinion(int fd, int port, const std::string &ip);
            void Send(char* data); // send read/write requests to minion
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
            Broadcaster(int port, Scheduler &scheduler);
            inline int GetFd();
            inline UID GetUID();
            ~Broadcaster();
        private:
            int m_fd;
            int m_port;
            bool m_is_on;
            UID m_master_uid;
            Scheduler &m_scheduler;

            // Send the bradcasatmessage every 1 second 
            void SendBroadCast(int irrelevant);
        };
        
        typedef Broadcaster MinionUDPIdentifier;

    // This function will be called when the fd of the broadcast will be on. This function will check if the replying Minion is in the map. If it exists in the map - it will set it's status to "active". If it is not in the map - it will create a UDPMinion and will add it to the map.
    // Than, another function should be called, and will transfer to the storage manager a list of all the Minions that are in the map but their status is set to "not working". This will happen every 5 seconds (using the scheduler).
    void OnMinionReply(int fd);
    void STDIN_Stop(int fd);
    void StartMasterReactor();
    void CheckMinionsStatus(int irrelevant);
    
    int m_fd ; // This is a general read/write fd for receieving responses from Minions. In addition, every minion will have it's own fd for direct communication
    int m_port; // for read/write responses from minions. This port should't be binded to reactor
    Reactor &m_reactor;
    Scheduler m_scheduler;
    MasterStorageManager &m_storage_manager;
    // This map contain the Minion's IP as the key, and the UDPMinion as the value:
    std::map< std::string, boost::shared_ptr< UDPMinion > > m_udp_minions;
    Broadcaster m_master_broadcaster;
    boost::thread m_reactor_thread;
};
} // namespace ilrd

using namespace ilrd;

inline int UDPcommunicator::MinionUDPIdentifier::GetFd()
{
    return m_fd;
}

int UDPcommunicator::UDPMinion::GetFd()
{
    return m_fd;
}

int UDPcommunicator::UDPMinion::GetPort()
{
    return m_port;
}

std::string UDPcommunicator::UDPMinion::GetIp()
{
    return m_ip;
}

UID UDPcommunicator::Broadcaster::GetUID()
{
    return m_master_uid;
}

#endif //ILRD_RD8586_UDP_COMMUNICATOR_HPP