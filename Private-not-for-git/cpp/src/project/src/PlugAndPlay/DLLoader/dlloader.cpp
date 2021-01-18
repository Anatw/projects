/*******************************************************************************
Plug&Play - Phase 3:
DLLoader class

Written by Anat Wax, anatwax@gmail.com
Created: 30.8.20
Reviewer:
*******************************************************************************/
#include <boost/bind.hpp>
#include <boost/smart_ptr/make_shared.hpp>
#include <new>

#include "dlloader.hpp"
#include "logger.hpp"

using namespace ilrd;

DLLoader::DLLoader(std::string plug_in_path)
    : m_plug_in_path(plug_in_path), m_dirmonitor(plug_in_path),
      m_callback(boost::bind(&ilrd::DLLoader::AddSharedObj, this, _1))
{
    m_dirmonitor.Subscribe(&m_callback);
    m_dirmonitor.StartMonitoring();
}

DLLoader::~DLLoader()
{
    // while (!m_libs.empty())
    // {
    //     // delete m_libs.front();
    //     m_libs.pop_front();
    // }

    LOG_DEBUG(__FILE__ + std::string(": ~DLLoader()"));
}

void DLLoader::AddSharedObj(const std::string lib_name)
{
    LOG_INFO(__FILE__ +
             std::string(": inside AddSharedObj(): a new SharedObject was "
                         "added to the list: ") +
             lib_name);

    // SharedObject* so = new SharedObject(lib_name);
    try
    {
        m_libs.push_back(boost::make_shared< SharedObject >(
            m_plug_in_path + std::string("/") + lib_name));
        // m_libs.push_front(so);
    }
    catch (const std::exception& e)
    {
        LOG_ERROR(__FILE__ +
                  std::string("::AddSharedObj() - error in push_front() for ") +
                  lib_name);

        throw std::runtime_error(e.what());
    }
}
