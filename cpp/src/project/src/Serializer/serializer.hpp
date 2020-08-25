/*******************************************************************************
Serializer

Written by Anat Wax, anatwax@gmail.com
Created: 20.8.20
Reviewer:
*******************************************************************************/

#ifndef __ILRD_RD8586_SERIALIZER_HPP_
#define __ILRD_RD8586_SERIALIZER_HPP__

#include <boost/noncopyable.hpp> // boost::noncopyable
#include <boost/shared_ptr.hpp>
#include <iostream> // std::cout, std::ostream, std::ios
#include <string.h>

#include "factory.hpp"

namespace ilrd
{

template < class BASE >
class Serializer : boost::noncopyable
{
public:
    template < class DERIVED >
    void Add(); // DERIVED should have default ctor
    void Serialize(const BASE& obj, std::ostream& os) const;
    boost::shared_ptr< BASE > Deserialize(std::istream& is) const;

private:
    template < class DERIVED >
    static BASE* Creator(std::istream& is);
    Factory< std::string, BASE, std::istream& > m_factory;
};

////////////////////////////////////////////////////////////////////////////////
//                       function implementation:                             //
////////////////////////////////////////////////////////////////////////////////

template < class BASE >
template < class DERIVED >
void Serializer< BASE >::Add()
{
    m_factory.Add(typeid(DERIVED).name(), &Creator< DERIVED >);
}

template < class BASE >
void Serializer< BASE >::Serialize(const BASE& obj, std::ostream& os) const
{
    os << typeid(obj).name() << ' ';
    obj << os;
}

template < class BASE >
boost::shared_ptr< BASE >
Serializer< BASE >::Deserialize(std::istream& is) const
{
    std::string key;
    is >> key;

    boost::shared_ptr< BASE > base_ptr(
        Serializer< BASE >::m_factory.Create(key, is));

    return (base_ptr);
}
template < class BASE >
template < class DERIVED >
BASE* Serializer< BASE >::Creator(std::istream& is)
{
    // Creating a blanc object that will be filled with the istream content:
    DERIVED* base = new DERIVED();

    *base >> is;

    return (base);
}

} // namespace ilrd

#endif /* __ILRD_RD8586_SERIALIZER_HPP__ */
