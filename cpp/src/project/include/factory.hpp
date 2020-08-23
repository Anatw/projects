/*******************************************************************************
Factory (design pattern)
Written by Anat Wax, anatwax@gmail.com
Created: 2.8.20
Reviewer: Shmuel Sinder
*******************************************************************************/
#ifndef ILRD_RD8586_FACTORY_HPP
#define ILRD_RD8586_FACTORY_HPP

#include <boost/core/noncopyable.hpp>
#include <iostream>
#include <map>

namespace ilrd
{
// Factory can be created as a singleton ,Shapes can be used for test
template < class KEY, class BASE, class PARAMS,
           class BUILDER = BASE* (*)(PARAMS) >
class Factory : private boost::noncopyable
{
public:
    // Add Function
    // Exceptions: throws runtime_error if function is NULL;
    // Throws run-time exception if key already exist
    // BUILDER accepts functions which follows this declaration BASE* (*)
    // (PARAMS)

    void Add(KEY key, BUILDER creation_func);

    // Create Function
    // Receives: key - key to the specific function to be created.
    //           build_params - params that are needed for a creation function.
    // Exceptions: throws runtime_error if creation fails or key doesn't exist.

    BASE* Create(KEY key, PARAMS build_params) const;

private:
    std::map< KEY, BUILDER > m_factory_creation;
};

template < class KEY, class BASE, class PARAMS, class BUILDER >
void Factory< KEY, BASE, PARAMS, BUILDER >::Add(KEY key, BUILDER creation_func)
{
    if (NULL == creation_func)
    {
        throw std::runtime_error("creation_func in smepty");
    }
    if (m_factory_creation.find(key) != m_factory_creation.end())
    {
        throw std::runtime_error("Key already exist!");
    }

    m_factory_creation[key] = creation_func;
}

template < class KEY, class BASE, class PARAMS, class BUILDER >
BASE* Factory< KEY, BASE, PARAMS, BUILDER >::Create(KEY key,
                                                    PARAMS build_params) const
{
    BASE* return_val = NULL;
    typename std::map< KEY, BUILDER >::const_iterator iter;
    iter = m_factory_creation.find(key);
    if (m_factory_creation.end() == iter)
    {
        throw std::runtime_error("key is not inside the map!");
    }
    else
    {
        return_val = iter->second(build_params);
    }

    return (return_val);
}

} // namespace ilrd

#endif // ILRD_RD8586_FACTORY_HPP
