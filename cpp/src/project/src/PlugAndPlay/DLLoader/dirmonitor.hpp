/*******************************************************************************
Plug&Play - Phase 2:
Dirmonitor class

Written by Anat Wax, anatwax@gmail.com
Created: 30.8.20
Reviewer:
*******************************************************************************/
#ifndef __ILRD_RD8586_DIRMONITOR_HPP_
#define __ILRD_RD8586_DIRMONITOR_HPP_

#include <string>
#include <sys/inotify.h>

#include "advanced_observer.hpp"
#include "dispatcher.hpp"
#include "logger.hpp"

namespace ilrd
{

class DirMonitor
{
public:
    explicit DirMonitor(std::string dir_path);
    ~DirMonitor();

    void Subscribe(Callback< Dispatcher< std::string > >* callback);
    void UnSubscribe(Callback< Dispatcher< std::string > >* callback);
    void StartMonitoring();

private:
    void Monitor();

    std::string m_path;
    Dispatcher< std::string > m_dispatcher;
    bool m_is_running;
};

} // namespace ilrd

#endif /* __ILRD_RD8586_DIRMONITOR_HPP_ */
