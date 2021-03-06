///////////////////////////////////////////////////////////////////////BS"S**///
//	Title:		Master Storage Manager
//	Authour:	
//	Reviewer:	 
//	Version:	05.09.2020.0
///////////////////////////////////////////////////////////////////////////////

#include <iostream>

#include "minion_info.hpp"
#include "master_storage_manager.hpp"

using namespace ilrd;


class DerivedMinionInfo: public MinionInfo
{
public:

    DerivedMinionInfo(int fd, const std::string& ip, int port)
        : m_fd(fd), m_ip(ip), m_port(port)
    {}
    
    void Send(char *data)
    {
        SendToOffset(data);
    }

    void SendToOffset(char* data) 
    {
        (void)data;
        std::cout << "sending message to ID: " << this->GetId() << 
            " IP: " << this->GetIp() << std::endl;
    }

    int GetFd()
    {
        return m_fd;
    }

    int GetPort()
    {
        return m_port;
    }

    std::string GetIp()
    {
        return m_ip;
    }

private:
    int m_fd;
    std::string m_ip;
    int m_port;
};

int main()
{
    MasterStorageManager masterstoragemanager(4, 10);

    boost::shared_ptr<MinionInfo> minioninfo1(new DerivedMinionInfo(1, "192.0.0.1", 8080));
    boost::shared_ptr<MinionInfo> minioninfo2(new DerivedMinionInfo(2, "192.0.0.2", 8080));
    boost::shared_ptr<MinionInfo> minioninfo3(new DerivedMinionInfo(3, "192.0.0.3", 8080));
    boost::shared_ptr<MinionInfo> minioninfo4(new DerivedMinionInfo(4, "192.0.0.4", 8080));

    masterstoragemanager.RegisterNewMinion(minioninfo1);
    masterstoragemanager.RegisterNewMinion(minioninfo2);
    masterstoragemanager.RegisterNewMinion(minioninfo3);
    masterstoragemanager.RegisterNewMinion(minioninfo4);

    

    std::cout << "write test\n";
    masterstoragemanager.Write(0, (char*)"test writing");
    masterstoragemanager.Write(1, (char*)"test writing");
    masterstoragemanager.Write(2, (char*)"test writing");
    masterstoragemanager.Write(3, (char*)"test writing");
    masterstoragemanager.Write(4, (char*)"test writing");


std::cout << "read test\n";
    std::cout << "readind offset 0:\n";
    masterstoragemanager.Read(0);
    std::cout << "readind offset 1:\n";
    masterstoragemanager.Read(1);
    std::cout << "readind offset 2:\n";
    masterstoragemanager.Read(2);
    std::cout << "readind offset 3:\n";
    masterstoragemanager.Read(3);
    std::cout << "readind offset 4:\n";
    masterstoragemanager.Read(4);
    
    return 0;
}
