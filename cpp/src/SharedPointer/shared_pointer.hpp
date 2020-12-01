/*******************************************************************************
Scope lock WS
Written by Anat Wax, anatwax@gmail.com
Created: 1.7.20
Reviewer: Alistair Hudson
*******************************************************************************/
#ifndef ILRD_8586_SHARED_POINTER_HPP_infinty
#define ILRD_8586_SHARED_POINTER_HPP_infinty

#include <iostream>
namespace ILRD_8586_infinty
{
    template <typename T> // int / double/ string/ object
    class SharedPointer
    {
    public:
        template <typename C>
        friend class SharedPointer;

        explicit SharedPointer(T *ptr_ = NULL);
        SharedPointer(SharedPointer<T> &other_);

        ~SharedPointer();
        SharedPointer<T> &operator=(SharedPointer<T> &other);

        T *operator->() const; // can be applied on both const and not const obj

        T &operator*() const;

        inline size_t GetCounter() const
        {
            return (*this->counter);
        }

        template <typename C>
        SharedPointer<T> &operator=(const SharedPointer<C> &other_);

        template <typename C>
        SharedPointer(SharedPointer<C> &other_);

    private:
        // Will count how many point to the same instance:
        size_t *counter;
        T *m_ptr; // Pointer to object/data
        void DecOrDelete();
    }; // namespace ILRD_8586_infinty

    ////////////////////////////////////////////////////////////////////////////
    //                        functions definitions:                          //
    ////////////////////////////////////////////////////////////////////////////

    template <typename T>
    SharedPointer<T>::SharedPointer(T *ptr_) : m_ptr(ptr_)
    {
        this->counter = new size_t;
        *(this->counter) = 1;
    }

    template <typename T>
    SharedPointer<T>::~SharedPointer()
    {
        DecOrDelete();
    }

    template <typename T>
    SharedPointer<T>::SharedPointer(SharedPointer<T> &other_)
    {
        if (this->m_ptr != other_.m_ptr && NULL != other_.m_ptr)
        {
            *(other_.counter) += 1;
            this->m_ptr = other_.m_ptr;
            this->counter = other_.counter;
        }
    }

    template <typename T>
    SharedPointer<T> &SharedPointer<T>::operator=(SharedPointer<T> &other)
    {
        if (this->m_ptr != other.m_ptr)
        {
            this->counter = other.counter;
            this->m_ptr = other.m_ptr;

            --*(this->counter);
            ++*(other.counter);

            if (0 == *(this->counter))
            {
                delete this->m_ptr;
                delete this->counter;
            }
        }

        return (*this);
    }

    template <typename T>
    T *SharedPointer<T>::operator->() const
    {
        return m_ptr;
    }

    template <typename T>
    T &SharedPointer<T>::operator*() const
    {
        return (*(this->m_ptr));
    }

    template <typename T>
    template <class C>
    SharedPointer<T> &SharedPointer<T>::operator=(const SharedPointer<C> &other_)
    {
        if (this->m_ptr != other_.m_ptr)
        {
            DecOrDelete();

            this->counter = other_.counter;
            this->m_ptr = other_.m_ptr;

            ++*(other_.counter);
        }

        return (*this);
    }

    template <typename T>
    template <class C>
    SharedPointer<T>::SharedPointer(SharedPointer<C> &other_)
    {
        if (this->m_ptr != other_.m_ptr && NULL != other_.m_ptr)
        {
            this->m_ptr = other_.m_ptr;
            this->counter = other_.counter;
            ++*(other_.counter);
        }
    }

    template <typename T>
    void SharedPointer<T>::DecOrDelete()
    {
        if (1 == *(this->counter))
        {
            delete this->m_ptr;
            delete this->counter;
        }
        else
        {
            --*(this->counter);
        }
    }

} // namespace ILRD_8586_infinty

#endif // ILRD_8586_SHARED_POINTER_HPP_infinty
