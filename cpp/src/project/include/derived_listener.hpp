/*******************************************************************************
Dynamic library for a derived listener.

Written by Anat Wax, anatwax@gmail.com
Created: August 20
*******************************************************************************/

#include <vector>

#include "reactor.hpp"

#ifndef __ILRD_RD8586_DERIVED_LISTENER_HPP_
#define __ILRD_RD8586_DERIVED_LISTENER_HPP__

namespace ilrd
{

class DerievedListener : public IListener
{
public:
    typedef std::pair< MODE, Handle > HandleAndMode;

    std::vector< HandleAndMode >
    Listen(const std::vector< HandleAndMode >& handle);

    ~DerievedListener();
};

} // namespace ilrd

#endif /* __ILRD_RD8586_DERIVED_LISTENER_HPP__ */
