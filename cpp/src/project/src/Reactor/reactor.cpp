/*******************************************************************************
Reactor (design pattern)
Written by Anat Wax, anatwax@gmail.com
Created: 7.7.20
Reviewer: Dean Oron
*******************************************************************************/
#include <boost/function.hpp>
#include <cstdio> // perror
#include <iostream>
#include <map>
#include <queue>
#include <utility> // pair
#include <vector>

#include "advanced_observer.hpp"
#include "advanced_subject.hpp"
#include "reactor.hpp"

using namespace std;

#define ORIGINAL_VERSION

template < typename T >
class RetrieveMapKey
{
    T operator()(T key_and_func) const
    {
        return key_and_func.first;
    }
};

Reactor::~Reactor()
{
    // for_each(m_EventHandlers.begin(), m_EventHandlers.end(),
    // DeleteOnDestruction);
    map< HandleAndMode, SimpleSrc< int >* >::iterator i;

    for (i = this->m_EventHandlers.begin(); i != this->m_EventHandlers.end();
         ++i)
    {
        delete i->second;
    }
}

void Reactor::Add(HandleAndMode handle_and_mode,
                  Callback< SimpleSrc< int > >* callback)
{
    SimpleSrc< int >* source = new SimpleSrc< int >;
    source->Subscribe(callback);
    this->m_EventHandlers.insert(make_pair(handle_and_mode, source));
}

// void Reactor::DeleteOnDestruction()
// {
//     delete m_EventHandlers[index].
// }

void Reactor::Remove(HandleAndMode handle_and_mode)
{
    this->m_EventHandlers.erase(handle_and_mode);
}

// infinite loop that: call listen (after retrieving all the keys from the map),
// recieve from it the resources that were beeing call, and than go to the map
// and activate the relative functions.

void Reactor::Run()
{
    this->to_stop = 0; // Making sure it is on when run is called

    while (!this->to_stop && !this->m_EventHandlers.empty())
    {
        // Creating an iterator for map, iterating through the map and
        // inserting all HandleAndMode elements into the active_keys vector:
        map< HandleAndMode, SimpleSrc< int >* >::iterator i;
        vector< HandleAndMode > inserted_keys;
        vector< HandleAndMode > active_keys;

        for (i = this->m_EventHandlers.begin();
             i != this->m_EventHandlers.end(); ++i)
        {
            inserted_keys.push_back(i->first);
        }
#ifndef NDBUG
        cout << "key retrieved into active keys vector" << endl;
#endif // NDBUG

        // Calling listen() with the available keys, and recieving the active
        // keys:
        active_keys = this->m_Listener->Listen(inserted_keys);

        // for (size_t index = 0;
        //      index < active_keys.size() && !this->to_stop;
        //      ++index)
        // {
        //     // Activate the function from map
        //     this->m_EventHandlers[active_keys[index]].Notify(active_keys[index].second);
        // }

        vector< HandleAndMode >::iterator iter;

        for (iter = active_keys.begin(); iter != active_keys.end(); ++iter)
        {
            m_EventHandlers[*iter]->Notify((*iter).second);
        }
    }
}

// Stop() can be called only from the handler/run if there is nothing to listen
// to (if the map is empty)
void Reactor::Stop()
{
    this->to_stop = 1;
}
