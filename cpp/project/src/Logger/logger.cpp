/*******************************************************************************
Logger (will be used inside the Minion).

Written by Anat Wax, anatwax@gmail.com
Created: 17.8.20
Reviewer: Haim Sa'adia
*******************************************************************************/
#include <boost/bind.hpp>
#include <boost/thread.hpp>
#include <ctime> // time_t(&time)
#include <fstream>
#include <stdlib.h> // getenv()

#include "logger.hpp"

using namespace ilrd;

void Logger::PushMessage(LogLevel log_level, std::string msg)
{
    Logger::Message message(log_level, msg);
    m_wqueue.Push(message);
}

////////////////////////////////////////////////////////////////////////////////

Logger::Logger()
    : m_log_thread(boost::bind(&Logger::PrintMessageIntoLogfile, this))
{
    char* file_name = getenv("LOGGERNAME");
    if (file_name)
    {
        m_filename = file_name;
    }
    else
    {
        throw std::runtime_error(
            "file name as environment variable was not defined - define it under 'export' in the \".bashrc\" file\n");
    }

    try
    {
        m_pFile.open(m_filename, std::fstream::app);
    }
    catch (const std::ifstream::failure &e)
    {
        char msg_buffer[512] = {0};
        sprintf(msg_buffer, "Exception in opening m_pFile: %s\n", e.what());
        LOG_ERROR(msg_buffer);

        throw std::runtime_error("Exception in opening m_pFile\n");
    }
}

////////////////////////////////////////////////////////////////////////////////

Logger::~Logger()
{
    while (!m_wqueue.Empty())
    {
        ; // spinlock
    }

    m_log_thread.interrupt();

    m_log_thread.join();

    try
    {
        m_pFile.close();
    }
    catch (const std::exception& e)
    {
        LOG_ERROR("inside ~Logger(): failure in close()");
    }
}

////////////////////////////////////////////////////////////////////////////////

void Logger::PrintMessageIntoLogfile()
{
    LOG_INFO("Logger was initialized\n");

    while (true)
    {
        Logger::Message msg;

        m_wqueue.Pop(msg);

        std::time_t t = boost::chrono::system_clock::to_time_t(msg.m_timepoint);

        std::string error_msg;

        switch (msg.m_error)
        {
        case Logger::ERROR:
            error_msg = "ERROR";
            break;
        case Logger::WARNING:
            error_msg = "WARNING";
            break;
        case Logger::INFO:
            error_msg = "INFO";
            break;
        case Logger::DEBUG:
            error_msg = "DEBUG";
            break;
        default:
            break;
        }

        m_pFile << "Type: " << error_msg << ". Message: " << msg.m_string
                << ". Date: " << std::ctime(&t) << std::endl;

        m_pFile.flush(); // insert the written data into the log file
    }
}

////////////////////////////////////////////////////////////////////////////////

Logger::Message::Message(LogLevel llevel, std::string message)
    : m_error(llevel), m_string(message),
      m_timepoint(boost::chrono::system_clock::now())
{
}
