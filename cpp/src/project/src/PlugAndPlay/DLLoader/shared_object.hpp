/*******************************************************************************
Plug&Play - Phase 1:
SharedObject class

Written by Anat Wax, anatwax@gmail.com
Created: 27.8.20
Reviewer:
*******************************************************************************/

#ifndef __ILRD_RD8586_SHARED_OBJECT_HPP_
#define __ILRD_RD8586_SHARED_OBJECT_HPP_

#include <dlfcn.h> // dlopen(), dlclose(), dlsym()
#include <string>

#include "logger.hpp"

namespace ilrd
{

class SharedObject
{
public:
    explicit SharedObject(const std::string& library_path);

    virtual ~SharedObject();

    template < typename T >
    T* LoadSymbol(std::string symbol);

private:
    std::string m_path;
    void* m_handle;
};

template < typename T >
T* SharedObject::LoadSymbol(std::string symbol)
{
    T* func = (T*)dlsym(m_handle, symbol.c_str());
    if (NULL !=
        dlerror()) // consider changings whats inside the brackets to '!func'
    {
        dlclose(m_handle);

        char log_msg[MSG_SIZE] = {0};

        sprintf(log_msg, "%s: inside LoadSymbol(): error in dlsym() method",
                __FILE__);
        LOG_ERROR(log_msg);

        throw std::runtime_error(
            "ERROR: requested symbol was not found in the Shared Object\n");
    }

    return (func);
}

} // namespace ilrd

#endif /* __ILRD_RD8586_SHARED_OBJECT_HPP_ */
