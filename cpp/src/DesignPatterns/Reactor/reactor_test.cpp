/*******************************************************************************
Reactor (design pattern)
Written by Anat Wax, anatwax@gmail.com
Created: 7.7.20
Reviewer: Dean Oron
*******************************************************************************/
#include <iostream>
#include <vector>
#include <queue>
#include <map>
#include <boost/function.hpp>
#include <utility>
#include <sys/select.h> /* select */
#include <cstdio>       // perror

#include "reactor.hpp"

using namespace std;

class DerievedListener : public IListener
{
public:
    vector<HandleAndMode> Listen(const vector<HandleAndMode> &handle)
    {
        fd_set ReadFDs;
        fd_set WriteFDs;
        fd_set ExceptFDs;

        FD_ZERO(&ReadFDs);
        FD_ZERO(&WriteFDs);
        FD_ZERO(&ExceptFDs);

        // Inserting keys from vector into the lists with regards to correct MODE
        vector<HandleAndMode>::const_iterator i;
        for (i = handle.begin(); i != handle.end(); ++i)
        {
            switch (i->first)
            {
            case READ:
                FD_SET(i->second, &ReadFDs);
                break;

            case WRITE:
                FD_SET(i->second, &WriteFDs);
                break;

            case EXCEPTION:
                FD_SET(i->second, &ExceptFDs);
                break;

            default:
                break;
            }
        }

        if (0 > select(FD_SETSIZE, &ReadFDs, &WriteFDs, &ExceptFDs, NULL))
        {
            throw domain_error("select failed");
        }

        vector<HandleAndMode> return_vector;

        for (int index = 0; index < FD_SETSIZE; ++index)
        {
            if (FD_ISSET(index, &ReadFDs))
            {
                return_vector.push_back(HandleAndMode(READ, index));
            }
            if (FD_ISSET(index, &WriteFDs))
            {
                return_vector.push_back(HandleAndMode(WRITE, index));
            }
            if (FD_ISSET(index, &ExceptFDs))
            {
                return_vector.push_back(HandleAndMode(EXCEPTION, index));
            }
        }

        return (return_vector);
    }

    ~DerievedListener()
    {
    }
};

void FuncW(int d)
{
    d = d;
    static int i = 0;
    cout << "FuncW executed: " << i << endl;
    ++i;
}

class StdinHandler
{
public:
    StdinHandler(Reactor &reactor) : m_reactor(reactor) {}
    void operator()(int i)
    {
        (void)i;
        string input;
        getline(cin, input);

        if (input == "ping")
        {
            cout << "-> pong to stdin!" << endl;
        }
        else if (input == "exit")
        {
            m_reactor.Stop();
        }

        fflush(stdin);
    }

private:
    Reactor &m_reactor;
};

int main()
{
    // DerievedListener listener;
    Reactor reactor(new DerievedListener);

    reactor.Add(HandleAndMode(READ, 0), StdinHandler(reactor));
    reactor.Run();

    // StdinHandler test(reactor);

    // HandleAndMode stdin_w = HandleAndMode(WRITE, 0);

    // reactor.Add(first, FuncW);
    // reactor.Add(HandleAndMode(READ, 0), FuncW);
    // reactor.Add(HandleAndMode(EXCEPTION, 0), FuncW);

    // reactor.Remove(first);

    // reactor.Run();

    return 0;
}
