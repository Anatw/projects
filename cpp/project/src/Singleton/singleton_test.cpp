/*******************************************************************************
Singleton (design pattern)

Written by Anat Wax, anatwax@gmail.com
Created: 29.7.20
Reviewer: Lior Cohen
*******************************************************************************/
#include <boost/thread/mutex.hpp>
#include <cstring>   // strlen()
#include <fstream>   // ofstream
#include <iostream>  // cout, cin, cerr
#include <pthread.h> // pthread_create()

#include "singleton.hpp"

using namespace std;
using namespace ilrd;

#define COUNTER ('0')

class Logger
{
public:
    Logger();
    ~Logger();
    void Open(const char* log_file);
    void Log(const char* massage);

private:
    ofstream m_stream;
    boost::mutex m_mutex;
};

Logger::Logger()
{
    std::cout << "inside ctor of Logger class" << std::endl;
}

void Logger::Open(const char* log_file)
{
    if (!m_stream.is_open())
    {
        m_stream.open(log_file, std::ios_base::app);
    }
}

Logger::~Logger()
{
    m_stream.close();
}

void Logger::Log(const char* massage)
{
    // m_stream.write(massage, strlen(massage));
    m_mutex.lock();
    m_stream << massage << endl;
    m_mutex.unlock();
}

void* PrintNumToLog(void* number)
{
    Logger* log = Singleton< Logger >::GetInstance();
    static char num = COUNTER;
    char* p_num = &num;

    log->Open("log_file");

    log->Log("inside PrintNumToLog, number = ");
    log->Log(p_num);
    ++num;

    return (number);
}

void ThreadCreate()
{
    Logger* log = Singleton< Logger >::GetInstance();

    log->Open("log_file");

    log->Log("inside ThreadCreate");

    pthread_t thread = 0;

    if (pthread_create(&thread, NULL, &PrintNumToLog, NULL))
    {
        throw runtime_error("Error in pthread_create\n");
    }

    pthread_join(thread, NULL);
}

int main()
{
    Logger* log = Singleton< Logger >::GetInstance();

    Logger* second_log = Singleton< Logger >::GetInstance();

    log->Open("log_file");

    log->Log("hello new log");

    ThreadCreate();
    ThreadCreate();

    second_log->Log("\nhello from second_log\n");

    ThreadCreate();
    ThreadCreate();

    second_log->Log("\n\nEnd of main\n\n");

    return (0);
}
