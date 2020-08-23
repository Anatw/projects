/*******************************************************************************
Logger (will be used inside the Minion).

Written by Anat Wax, anatwax@gmail.com
Created: 17.8.20
Reviewer: Haim Sa'adia
*******************************************************************************/
#ifndef __ILRD_RD8586_LOGGER_HPP__
#define __ILRD_RD8586_LOGGER_HPP__

#include <boost/chrono.hpp>
#include <boost/thread.hpp>
#include <fstream>
#include <iostream>
#include <string>

#include "priority_queue.hpp"
#include "singleton.hpp"
#include "waitable_queue.hpp"

namespace ilrd
{

#define MSG_SIZE (512)

class Logger
{
public:
    enum LogLevel
    {
        ERROR = 0,
        WARNING = 1,
        INFO = 2,
        DEBUG = 3
    };

    // construct the message and push into the queue:
    void PushMessage(LogLevel log_level, std::string msg);

private:
    struct Message
    {
        Message()
        {
        }
        Message(LogLevel llevel,
                std::string message); // constructor computes time here

        inline bool operator>(const Message& other_) const
        {
            return (m_timepoint > other_.m_timepoint);
        }

        LogLevel m_error;
        std::string m_string;
        boost::chrono::system_clock::time_point m_timepoint;
    };

private:
    friend class Singleton< Logger >;
    Logger(); //: m_filename(getenv("LOGGERNAME"))  // check creating is fine
    ~Logger();
    // thread which will take care of it
    // print the message in the logfile with log level and timepoint:
    void PrintMessageIntoLogfile();

    WaitableQueue< PriorityQueue< Message, std::vector< Message >,
                                  std::greater< Message > >,
                   Message >
        m_wqueue;
    char* m_filename;
    std::fstream m_pFile;
    boost::thread m_log_thread;
};

#define LOG_ERROR(msg)                                                         \
    (Singleton< Logger >::GetInstance()->PushMessage(Logger::ERROR, (msg)))
#define LOG_WARNING(msg)                                                       \
    (Singleton< Logger >::GetInstance()->PushMessage(Logger::WARNING, (msg)))
#define LOG_INFO(msg)                                                          \
    (Singleton< Logger >::GetInstance()->PushMessage(Logger::INFO, (msg)))
#define LOG_DEBUG(msg)                                                         \
    (Singleton< Logger >::GetInstance()->PushMessage(Logger::DEBUG, (msg)))

} // namespace ilrd

#endif /* __ILRD_RD8586_LOGGER_HPP__ */
