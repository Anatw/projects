#ifndef ILRD_RD8586_MINION_INFO
#define ILRD_RD8586_MINION_INFO

#include <iostream>

namespace ilrd
{
class MinionInfo
{
public:
    MinionInfo() : m_status(true)
    {
        static int counter;
        ++counter;
        m_id = counter;
    }

    virtual ~MinionInfo()
    {}

    void SetStatus(bool status);
    bool GetStatus() const;
    int GetId();

    virtual int GetFd() = 0;
    virtual int GetPort() = 0;
    virtual std::string GetIp() = 0;
    // This function send the data to the Minion
    virtual void Send(char* data) = 0;

private:
    int m_id;
    bool m_status; // 1 = working, 0 = not-working
};

inline void MinionInfo::SetStatus(bool status)
{
    m_status = status;
}

inline bool MinionInfo::GetStatus() const
{
    return m_status;
}

inline int MinionInfo::GetId()
{
    return m_id;
}


} // namespace ilrd

#endif //ILRD_RD8586_MINION_INFO