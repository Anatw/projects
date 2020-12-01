#include <boost/interprocess/sync/interprocess_semaphore.hpp>
#include <boost/thread/mutex.hpp>

int counter = 0;

// a mutex only for the reading part - to protect the counter, so that only
// one reader can change it in any given time:
boost::mutex mutexR;
// s = starvation: this murtex prevent the writer from beeing starved -
// without it there is greater prefferation for the readers:
boost::mutex mutexS;
boost::interprocess::interprocess_semaphore semaphore_w; // initialized with 1

// I have a counter to check how many reders I have., I want the first and the
// last readers to update the semaphore - when the first reader enters - lock
// the semaphore. when the las reader finished - unlock the semaphore.
void Read()
{
    // checking if a writer is in the middle of writing:
    mutexS.lock();
    mutexS.unlock();

    // The first reader lockes the semphore:
    mutexR.lock();
    if (++counter == 1)
    {
        semaphore_w.wait();
    }
    mutexR.unlock();

    //
    // read...
    //

    // The last reader open the semaphore:
    mutexR.lock();
    if (--counter == 1)
    {
        semaphore_w.post();
    }
    mutexR.unlock();
}

void Write()
{
    // int write_counter = 0;
    mutexS.lock();
    // mutexW.lock();
    // if (++write_counter == 1);
    //{
    semaphore_w.wait();
    //     mutexW.unlock();
    //}
    mutexS.unlock();

    //
    // write...
    //

    // Add a check - are any writers waiting to write? if there are - don't
    // post...
    // mutexW.lock();
    // if (--counter == 0)
    // {
    //    semaphore_w.post();
    // }
    // mutexW.unlock();
    semaphore_w.post();
}

// If a Writer is writing:
// it lockes the semaphore - until it finished all other writer requestes will
// be blocked on the semaphore:
//  * so only one writer is alloued at any given time.
//  * all reader will be blocked on the semaphopre until the writer has
//    finished.
//
// If a Reader is reading:
// it checkes if a writer is trying to read (mutexS) if not - it lockes the
// mutex and add onr to the counter. If it is the dirst reader - it lockes the
// semaphore. if not - it directly go to the read part.
// At the end, the last reader unlock the semaphore and now.
// If a writer wants to write it will lock the writer semaphor (semaphorS) and
// all the readers that will come after that will be blocked on the mutex. When
// the last reader finished - the writer will get it's time and will be able to
// write while all the other readers are blocked. If another writer want's to
// write when a writer is in the middle of weiting -

// Semaphore lock and Mutex unlock is NOT fifo - meaning that it is NOT
// guarenteed that the first thread that was locked on the semaphore/mutex will
// also be the foorst thread to use it when it is unlocked!!
