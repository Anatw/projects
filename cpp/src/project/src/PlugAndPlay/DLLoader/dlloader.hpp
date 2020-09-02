/*******************************************************************************
Plug&Play - Phase 3:
DLLoader class

Written by Anat Wax, anatwax@gmail.com
Created: 30.8.20
Reviewer:
*******************************************************************************/
#ifndef __ILRD_RD8586_DLLOADER_HPP_
#define __ILRD_RD8586_DLLOADER_HPP_

#include <list>
#include <string>
#include <sys/inotify.h>

#include "advanced_observer.hpp"
#include "dirmonitor.hpp"
#include "dispatcher.hpp"
#include "logger.hpp"
#include "shared_object.hpp"

namespace ilrd
{

class DLLoader
{
public:
    explicit DLLoader(std::string plug_in_path);
    ~DLLoader();

private:
    void AddSharedObj(const std::string lib_name);

    // the path to listen to (using the m_dirmonitor member)
    std::string m_plug_in_path;

    // List of libraries the dlloader knows about
    std::list< boost::shared_ptr< SharedObject > > m_libs;

    // Dirmonitor member to monitor changes in thr m_plug_in_path
    DirMonitor m_dirmonitor;

    // callback to load symbols when the dirmonitor incounter a change in the
    // dirctory
    Callback< Dispatcher< std::string > > m_callback;
};

} // namespace ilrd

#endif /* __ILRD_RD8586_DLLOADER_HPP_ */
