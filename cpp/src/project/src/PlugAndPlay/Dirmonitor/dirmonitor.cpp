/*******************************************************************************
Plug&Play - Phase 2:
Dirmonitor class

Written by Anat Wax, anatwax@gmail.com
Created: 30.8.20
Reviewer:
*******************************************************************************/
#include <boost/filesystem.hpp>
#include <boost/thread.hpp>

#include "dirmonitor.hpp"
#include "logger.hpp"

#define MAX_EVENTS 1024 /*Max. number of events to process at one go*/
#define LEN_NAME                                                               \
    16 /*Assuming that the length of the filename won't exceed 16 bytes*/
#define EVENT_SIZE (sizeof(struct inotify_event)) /*size of one event*/
#define BUF_LEN                                                                \
    (MAX_EVENTS *                                                              \
     (EVENT_SIZE + LEN_NAME)) /*buffer to store the data of events */

using namespace ilrd;

DirMonitor::DirMonitor(std::string dir_path)
    : m_path(dir_path), m_is_running(false)
{
    LOG_DEBUG(__FILE__ + std::string("::DirMonitor()"));
}

DirMonitor::~DirMonitor()
{
    // m_thread.join() - so that the thread will be able to free the memory (fd
    // and so)
    m_is_running = false;
}

void DirMonitor::Subscribe(Callback< Dispatcher< std::string > >* callback)
{
    m_dispatcher.Subscribe(callback);
}

void DirMonitor::UnSubscribe(Callback< Dispatcher< std::string > >* callback)
{
    m_dispatcher.Unsubscribe(callback);
}

// If any change accures in the folder dlmonitor is monitoring, a notification
// will be sent to the DLLoader:
void DirMonitor::Monitor()
{
    m_is_running = true;
    LOG_DEBUG(__FILE__ + std::string("::Monitor() - started"));

    char log_msg[MSG_SIZE] = {0};
    char buffer[BUF_LEN] = {0};

    // Inotify is a Linux kernel feature that provides an event-driven
    // framework for applications to monitor changes in the filesystem:
    int fd = inotify_init();
    if (0 > fd)
    {
        sprintf(log_msg,
                "%s: inside StartMonitoring()->Monitor(): error in "
                "inotify_init() method",
                __FILE__);
        LOG_ERROR(log_msg);
    }

    // Set the file desciptor to watch a directory:
    int wd = inotify_add_watch(fd, m_path.c_str(),
                               IN_CREATE /*| IN_CLOSE_WRITE | IN_DELETE*/);

    if (-1 == wd)
    {
        LOG_ERROR(__FILE__ +
                  std::string("::StartMonitoring()->Monitor(): error in "
                              "inotify_add_watch() method"));
    }
    else
    {
        LOG_INFO(
            __FILE__ +
            std::string("::StartMonitoring()->Monitor(): started watching"));
    }

    while (m_is_running)
    {
        int i = 0;
        int length = read(fd, buffer, BUF_LEN);

        if (length < 0)
        {
            LOG_ERROR(__FILE__ +
                      std::string("::StartMonitoring()->Monitor(): error in "
                                  "read() method"));

            throw std::runtime_error("inside DirMonitor thread, Monitoring() - "
                                     "ERROOR in inotify read())");
        }

        while (i < length)
        {
            struct inotify_event* event = (struct inotify_event*)&buffer[i];
            if (event->len)
            {
                if (event->mask & IN_CREATE)
                {
                    LOG_INFO(__FILE__ +
                             std::string("::StartMonitoring()->Monitor(): "
                                         "inside IN_CREATE, the file ") +
                             event->name + std::string(" was created"));
                    m_dispatcher.Notify(event->name);
                }

                /*
                // check if an existing file was changed:
                if (event->mask & IN_CLOSE_WRITE)
                  {
                      sprintf(
                          log_msg,
                          "%s: inside StartMonitoring()->Monitor(): "
                          "inside IN_MODIFY, the file %s was modified with WD
                  %d",
                          __FILE__, event->name, event->wd);
                      LOG_INFO(log_msg);
                      m_dispatcher.Notify(&event->name[0]);
                  }

                // Check if an existing file was deleted
                  if (event->mask & IN_DELETE)
                  {
                      sprintf(
                          log_msg,
                          "%s: inside StartMonitoring()->Monitor(): "
                          "inside IN_DELETE, the file %s was deleted with WD
                  %d",
                          __FILE__, event->name, event->wd);
                      LOG_INFO(log_msg);
                      m_dispatcher.Notify(&event->name[0]);
                  }*/

                i += sizeof(struct inotify_event) + event->len;
            }
        }
    }

    /* Clean up*/
    inotify_rm_watch(fd, wd);
    close(fd);
}

void DirMonitor::StartMonitoring()
{
    // If there any files existing in the library before starting the Monitor -
    // all and activate them
    boost::filesystem::directory_iterator end_iter;
    for (boost::filesystem::directory_iterator iter(m_path.c_str());
         iter != end_iter; ++iter)
    {
        m_dispatcher.Notify(iter->path().filename().c_str());
    }

    boost::thread monitoring(boost::bind(&DirMonitor::Monitor, this));
}
