/*******************************************************************************

phase 1 = max func
phase 3 = prio queue


Written by Anat Wax, anatwax@gmail.com
Created: 16.9.20
Reviewer:
*******************************************************************************/
#include <iostream> // cout, cin, cerr
#include <list>
#include <new>

namespace ilrd
{
template < typename T >
class Queue
{
public:
    Queue(size_t size = 1);
    ~Queue();
    void Enqueue(const T& t);
    const T& Dequeue();
    const T& ReturnMax();

    void PrintQueue();

private:
    void ArrayReallocation();

    T* m_array;
    size_t m_capacity;
    size_t m_size; // this holds both - the next free spot to insert data into,
                   // and the actual amount of data that is in the queue
    std::list< T > m_max;
};

template < typename T >
Queue< T >::Queue(size_t size) : m_capacity(size), m_size(0)
{
    m_array = new T[m_capacity];
}

template < typename T >
Queue< T >::~Queue()
{
    delete[] m_array;
}

template < typename T >
void Queue< T >::ArrayReallocation()
{
    T* temp;

    // Allocating array with double capacity:
    try
    {
        temp = new T[m_capacity * 2];
    }
    catch (const std::bad_alloc&)
    {
        try
        {
            temp = new T[m_capacity * 2];
        }
        catch (const std::exception& e)
        {
            std::cerr << e.what() << '\n';
            throw std::bad_alloc();
        }
    }

    // Copying current data into the new array:
    for (size_t i = 0; i < m_size; ++i)
    {
        temp[i] = m_array[i];
    }

    delete[] m_array;
    m_array = temp;
}

template < typename T >
void Queue< T >::Enqueue(const T& t)
{
    if (m_capacity == m_size)
    {
        ArrayReallocation();

        m_capacity *= 2;
    }

    if (m_size == 0 || t > m_array[m_size])
    {
        m_array[m_size] = t;
        ++m_size;
    }
    else
    {
        T* temp = new T[m_size];
        int i = 0;

        for (; t < m_array[m_size]; ++i)
        {
            temp[i] = m_array[m_size];
            --m_size;
        }

        m_array[m_size++] = t;

        while (i)
        {
            m_array[m_size++] = temp[i--];
        }

        delete[] temp;
    }
}

template < typename T >
const T& Queue< T >::Dequeue()
{
    if (m_size > 0)
    {
        --m_size;
    }
}

template < typename T >
const T& Queue< T >::ReturnMax()
{
    return (m_array[m_size]);
}

template < typename T >
void Queue< T >::PrintQueue()
{
    for (size_t i = 0; i < m_size; ++i)
    {
        std::cout << m_array[i] << ", ";
    }

    std::cout << "\n";
}

} // namespace ilrd

using namespace ilrd;

int main()
{
    Queue< int > queue(5);
    queue.Enqueue(5);
    queue.Enqueue(2);
    queue.Enqueue(7);

    queue.PrintQueue();

    return (0);
}

// namespace ilrd
// {
// template < typename T >
// class Queue
// {
// public:
//     Queue(size_t size = 1);
//     ~Queue();
//     void Enqueue(const T& t);
//     const T& Dequeue();
//     const T& ReturnMax();

// private:
//     void ArrayReallocation();

//     T* m_array;
//     size_t m_capacity;
//     size_t m_size; // this holds both - the next free spot to insert data
//     into,
//                    // and the actual amount of data that is in the queue
//     std::list< T > m_max;
// };

// template < typename T >
// Queue< T >::Queue(size_t size) : m_capacity(size), m_size(0)
// {
//     m_array = new T[m_capacity];
// }

// template < typename T >
// Queue< T >::~Queue()
// {
//     delete[] m_array;
// }PrintQueue

// template < typename T >
// void Queue< T >::ArrayReallocation()
// {
//     try
//     {
//         T* temp = new T[m_capacity * 2];
//     }
//     catch (const std::bad_alloc&)
//     {
//         try
//         {
//             T* temp = new T[m_capacity * 1.5];
//         }
//         catch (const std::exception& e)
//         {
//             std::cerr << e.what() << '\n';
//             throw std::bad_alloc();
//         }
//     }

//     for (size_t i = 0; i < m_size; ++i)
//     {
//         m_max = new T[m_capacity];
//         temp[i] = m_array[i];
//     }

//     delete[] m_array;
//     m_array = temp;
// }

// template < typename T >
// void Queue< T >::Enqueue(const T& t)
// {
//     if (m_capacity == m_size)
//     {
//         ArrayReallocation();

//         m_capacity *= 2;
//     }

//     if (m_max.empty() || m_max.front() < t)
//     {
//         m_max.push_front(t);
//     }

//     m_array[m_size] = t;
//     ++m_size;
// }

// template < typename T >
// const T& Queue< T >::Dequeue()
// {
//     if (m_max.front() == m_array[m_size])
//     {
//         m_max.pop_front();
//     }

//     if (m_size > 0)
//     {
//         --m_size;
//     }
// }

// template < typename T >
// const T& Queue< T >::ReturnMax()
// {
//     return (m_max.front());
// }

// } // namespace ilrd

////////////////////////////////////////////////////////////////////////////////
//                           Inline functions:                                //
////////////////////////////////////////////////////////////////////////////////
