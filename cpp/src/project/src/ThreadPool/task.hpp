/*******************************************************************************
Comment and un-comment the defines to see both phases (one at a time).

WS name
Templates + STL (Histo)
Written by Anat Wax, anatwax@gmail.com
Created: 15.6.20
Reviewer:
*******************************************************************************/

#ifndef __ILRD_RD8586__HPP_
#define __ILRD_RD8586__HPP__

#include <boost/chrono.hpp>
#include <boost/function.hpp>
#include <boost/thread.hpp>
#include <boost/thread/mutex.hpp>
#include <vector>

#include "priority_queue.hpp"

namespace ilrd
{

class Task
{
public:
    typedef boost::chrono::milliseconds MS;
    typedef boost::chrono::system_clock::time_point TimePoint;
    typedef boost::function< void(int) > ActionFunc;

    Task(const TimePoint& time, ActionFunc action);
    Task(const MS& ms, ActionFunc action);

    inline bool operator<(const Task& other_) const;
    inline bool operator>(const Task& other_) const;
    inline bool operator==(const Task& other_) const;
    inline bool operator!=(const Task& other_) const;

    TimePoint& GetTime() const;
    void SetTime(const TimePoint& time);
    void SetTime(const MS& ms);

private:
    TimePoint m_timepoint;
    ActionFunc m_function;
};

} // namespace ilrd

#endif /* __ILRD_RD8586__HPP__ */
