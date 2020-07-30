/*******************************************************************************
Singleton (design pattern)

Written by Anat Wax, anatwax@gmail.com
Created: 29.7.20
Reviewer:
*******************************************************************************/
#include <cstring>  // strlen()
#include <fstream>  // ofstream
#include <iostream> // cout, cin, cerr
#include <mutex>

#include "singleton.hpp"

using namespace std;
using namespace ilrd;

/*
create Logger class that writes to a file.
call it from different threads and during different timelines (on thread
creation, global variable initialization, main, etc) obviously you can create
any class you want or use an existing std class. but it is always fun to be
creative with your tests
*/

class Logger
{
public:
    ~Logger();
    void Log(const char* massage);

private:
    Logger(string log_file);
    ofstream m_stream;
    mutex m_mutex;
};

Logger::Logger(string log_file) : m_stream(log_file, ofstream::out)
{
    m_stream.open(log_file);
}

Logger::~Logger()
{
    m_stream.close();
}

void Logger::Log(const char* massage)
{
    m_stream.write(massage, strlen(massage));
}

int main()
{
    Logger* log = Singleton< Logger >::GetInstance();

    return (0);
}
