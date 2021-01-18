////////////////////////////////////////////////////////////////////////////////
// File Name: dir_monitor.cpp                                                 //
// Author: Lior Cohen                                                         //
// Date 30/08/2020                                                            //
// Purpose: functions file for the dir_monitor class                          //
// Code Reviewer: Kobi Rappaport                                              //
////////////////////////////////////////////////////////////////////////////////

#include <dlfcn.h>
#include <sys/inotify.h>
#include <boost/thread.hpp>

#include "dir_monitor.hpp"
//#include "logger.hpp"

#define EVENT_SIZE  ( sizeof (struct inotify_event) )
#define EVENT_BUF_LEN     ( 1024 * ( EVENT_SIZE + 16 ) )

using namespace ilrd;

DirMonitor::DirMonitor(std::string dir_path) : m_path(dir_path), m_run(true)
{}

void DirMonitor::Subscribe(Callback<Dispatcher<std::string> > *callback)
{
    m_dispatcher.Subscribe(callback);
}

void DirMonitor::UnSubscribe(Callback<Dispatcher<std::string> > *callback)
{
    m_dispatcher.Unsubscribe(callback);
}

void DirMonitor::Running()
{
    int fd = inotify_init();

    if (0 > fd)
    {
        //LOG_ERROR("Failed to inotify in dir_monitor.cpp");
        std::cout << "Failed to inotify in dir_monitor.cpp" << std::endl;
    }

    int wd = inotify_add_watch(fd, m_path.c_str(), IN_OPEN | IN_MODIFY | IN_CLOSE);

    if (0 > wd)
    {
        //LOG_ERROR("Failed to inotify_add_watch in dir_monitor.cpp");
        std::cout << "Failed to inotify_add_watch in dir_monitor.cpp" << std::endl;
    }

    char buffer[EVENT_BUF_LEN];
    int length = read(fd, buffer, EVENT_BUF_LEN);

    if (0 > length)
    {
        //LOG_ERROR("Failed to read in dir_monitor.cpp");
        std::cout << "Failed to read in dir_monitor.cpp" << std::endl;
    }

    while (m_run)
    {
        struct inotify_event *event = (struct inotify_event*) &buffer;

        if (event->mask & IN_OPEN)
        {
            std::cout << "OPEN" << std::endl;
            m_dispatcher.Notify(&event->name);
        }
        else if (event->mask & IN_MODIFY)
        {
            std::cout << "MODIFIED" << std::endl;
            m_dispatcher.Notify(&event->name);
        }
        else if (event->mask & IN_CLOSE)
        {
            std::cout << "CLOSED" << std::endl;
            m_dispatcher.Notify(&event->name);
        }
    }

    inotify_rm_watch(fd, wd);

    close(fd);
}

void DirMonitor::StartMonitoring()
{
    boost::thread thread{Running};

    
}
