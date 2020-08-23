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

template < class DERIVED >
template < class BASE >
void Serializer< DERIVED >::Add()
{
}

template < class BASE >
void Serializer< BASE >::Serialize(const BASE& obj, std::ostream& os) const
{
}

template < class BASE >
boost::shared_ptr< BASE >
Serializer< BASE >::Deserialize(std::istream& is) const
{
}

template < class DERIVED >
template < class BASE >
BASE* Serializer< DERIVED >::Creator(std::istream& is)
{
}

} // namespace ilrd

#endif /* __ILRD_RD8586_SERIALIZER_HPP__ */
