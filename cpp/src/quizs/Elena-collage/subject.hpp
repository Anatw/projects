/*******************************************************************************

Written by Anat Wax, anatwax@gmail.com
reated: 7.10.20
Reviewer:
*******************************************************************************/

#ifndef __ILRD_RD8586_SUBJECT_HPP_
#define __ILRD_RD8586_SUBJECT_HPP_

#include <boost/noncopyable.hpp> // boost::noncopyable
#include <string>

namespace ilrd
{
class Subject
{
public:
    Subject(const std::string& name); // m_name(name)
    inline std::string GetName() const
    {
        return (m_name);
    }

private:
    std::string m_name;
};
} // namespace ilrd

#endif /* __ILRD_RD8586_SUBJECT_HPP_ */
