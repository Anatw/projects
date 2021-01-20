/*******************************************************************************
Scope lock WS
Written by Anat Wax, anatwax@gmail.com
Created: 30.6.20
*****
Compilation: g++ ./scope_lock.cpp -pthread
*******************************************************************************/
#include <iostream>  // cout, cin, cerr
#include <pthread.h> /* ptherad_mutex functions andd variables */
#include <mutex>     // Mutex

using namespace std;

#define NUM_INDEXES (100)

int g_nTest = 0;
int g_array[100] = {0};
std::mutex g_mutex;

void *ProducerFunc(void *unused);
void *ConsumerFunc(void *unused);

template <typename T>
class ScopeLock
{
public:
    ScopeLock(T &lock); //ctor

    ~ScopeLock(); //dtor

    // Cctor and assignment operator are private so class is noncopyable.
private:
    ScopeLock(const ScopeLock &other);
    ScopeLock &operator=(const ScopeLock &other);

    T &lock;
};

template <typename T>
ScopeLock<T>::ScopeLock(T &lock) : lock(lock)
{
    cout << "Locking mutex 'lock'" << endl;
    lock.lock();
}

template <typename T>
ScopeLock<T>::~ScopeLock()
{
    cout << "Unlocking mutex 'lock'\n"
         << endl;
    this->lock.unlock();
}

////////////////////////////////////////////////////////////////////////////////
//                                 Main:                                      //
////////////////////////////////////////////////////////////////////////////////

int main()
{
    pthread_t producer;
    pthread_t consumer;
    int counter = 5;

    for (int i = 0; i < counter; ++i)
    {
        if (pthread_create(&producer, NULL, &ProducerFunc, NULL))
        {
            cout << "ERROR in pthread_create (producer)" << endl;
            return (1);
        }

        if (pthread_create(&consumer, NULL, &ConsumerFunc, NULL))
        {
            cout << "ERROR in pthread_create (producer)" << endl;
            return (1);
        }

        pthread_join(producer, NULL);
        pthread_join(consumer, NULL);
    }

    return (0);
}

void *ProducerFunc(void *unused)
{
    cout << "Entered ProducerFunc\n"
         << endl;
    unused = unused;
    ScopeLock<mutex> critical_section(g_mutex);
    for (int i = 0; i < NUM_INDEXES; ++i)
    {
        ++g_array[i];
    }

    cout << endl;

    return (NULL);
}

void *ConsumerFunc(void *unused)
{
    cout << "Entered ConsumerFunc\n"
         << endl;
    unused = unused;
    ScopeLock<mutex> critical_section(g_mutex);
    for (int i = 0; i < NUM_INDEXES; ++i)
    {
        cout << g_array[i] << "->";
    }

    cout << endl;

    return (NULL);
}
