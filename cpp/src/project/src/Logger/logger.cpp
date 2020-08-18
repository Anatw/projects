/*******************************************************************************
Logger (will be used inside the Minion

Written by Anat Wax, anatwax@gmail.com
Created: 17.8.20
Reviewer:
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

Logger::Logger() : m_filename(getenv("LOGGERNAME"))
{
    m_log_thread =
        boost::thread(boost::bind(&Logger::PrintMessageIntoLogfile, this));
}

////////////////////////////////////////////////////////////////////////////////

Logger::~Logger()
{
    std::ofstream m_pFile(m_filename);

    m_log_thread.join();

    m_pFile.close();
}

////////////////////////////////////////////////////////////////////////////////

void Logger::PrintMessageIntoLogfile()
{
    std::ofstream m_pFile;

    if (!m_pFile)
    {
        std::cout << "error" << std::endl;
    }

    // m_pFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);
    try
    {
        // m_pFile.open(getenv(m_filename), std::fstream::in | std::fstream::out
        // |
        //  std::fstream::trunc);
        m_pFile.open(m_filename, std::ofstream::app);
    }
    catch (std::ifstream::failure e)
    {
        throw std::runtime_error("Exception opening/reading/closing m_pFile\n");
    }
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

        time_t now = time(0);
        m_pFile << "Type: " << msg.m_error << ". Message: " << msg.m_string
                << ". Date: " << ctime(time(0)) << std::endl;

        m_pFile.flush(); // insert the written data into the log file
        m_pFile.close();
    }
}

////////////////////////////////////////////////////////////////////////////////

Logger::Message::Message(LogLevel llevel, std::string message)
    : m_error(llevel), m_string(message),
      m_timepoint(boost::chrono::system_clock::now())
{
}

////////////////////////////////////////////////////////////////////////////////
//                           Inline functions:                                //
////////////////////////////////////////////////////////////////////////////////
