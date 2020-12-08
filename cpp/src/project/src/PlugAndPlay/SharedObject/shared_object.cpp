/*******************************************************************************
Plug&Play - Phase 1:
SharedObject class

Written by Anat Wax, anatwax@gmail.com
Created: 27.8.20
Reviewer:
*******************************************************************************/

#include "shared_object.hpp"

using namespace ilrd;

SharedObject::SharedObject(const std::string& library_path)
    : m_path(library_path)
{
    if (NULL == (m_handle = dlopen(m_path.c_str(), RTLD_LAZY)))
    {
        char log_msg[MSG_SIZE] = {0};
        sprintf(log_msg, "%s: inside LoadSymbol(): error in dlopen() method",
                __FILE__);
        LOG_ERROR(log_msg);
    }
}

SharedObject::~SharedObject()
{
    // dlclose(m_handle);
}
