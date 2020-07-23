/*******************************************************************************
Comment and un-comment the defines to see both phases (one at a time).

WS name
Templates + STL (Histo)
Written by Anat Wax, anatwax@gmail.com
Created: 15.6.20
Reviewer:
*******************************************************************************/
#include <boost/bind.hpp>
#include <boost/chrono.hpp>
#include <iostream> // cout, cin, cerr

#include "scheduler.hpp"

using namespace std;
using namespace ilrd;

Scheduler::Scheduler(Reactor& reactor)
    : m_timer(reactor, boost::bind(&Scheduler::ActivateNextTask, this,
                                   _1)) //-1 is a placeholder that will pass on
                                        // what the funtion receieves
{
}

////////////////////////////////////////////////////////////////////////////////

Scheduler::~Scheduler()
{
}

////////////////////////////////////////////////////////////////////////////////
// boost::chrono::time_point_cast<boost::chrono::microseconds>

void Scheduler::ScheduleAction(TimePoint timepoint, ActionFunc function)
{
    Scheduler::Task new_task;
    new_task.m_function = function;
    new_task.m_timepoint = timepoint;

    // boost::chrono::duration_cast<MS>(m_tasks.top().m_timepoint - Now());

    if (!m_tasks.empty())
    {
        // If the new task should begin befor the current first task in the
        // queue - if so - i need to activate timer set
        if (new_task < m_tasks.top())
        {
            // This will return in nano-seconds, and we need to cast it int
            // microseconds.
            MS time = boost::chrono::duration_cast< MS >(new_task.m_timepoint -
                                                         this->Now());
            m_timer.Set(time);
            // timerfd_settime(m_fd, );
        }

        m_tasks.push(new_task);
    }
}

////////////////////////////////////////////////////////////////////////////////

Scheduler::TimePoint Scheduler::Now()
{
    return (boost::chrono::system_clock::now());
}

////////////////////////////////////////////////////////////////////////////////

void Scheduler::ActivateNextTask(int fd)
{
    if (!m_tasks.empty())
    {
        // remove the first task in queue
        Scheduler::Task task_to_execute = m_tasks.top();
        m_tasks.pop();

        // activate the task
        task_to_execute.m_function(fd);

        // activate timer with the next task in line
        MS time = boost::chrono::duration_cast< MS >(m_tasks.top().m_timepoint -
                                                     this->Now());
        m_timer.Set(time);
    }
}

////////////////////////////////////////////////////////////////////////////////
//                           Inline functions:                                //
////////////////////////////////////////////////////////////////////////////////
