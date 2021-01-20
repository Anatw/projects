/*******************************************************************************
Templates + STL (Point)
Written by Anat Wax, anatwax@gmail.com
Created: 15.6.20
*******************************************************************************/
#include <iostream> /* cout, cin, cerr */
#include <cassert>  // assert()

template <class T>
class Point
{
public:
    Point(T x = 0, T y = 0) : m_x(x), m_y(y){};

    inline const T &GetX() const;
    inline void SetX(const T x);
    inline const T &GetY() const;
    inline void SetY(const T y);

    Point<T> &operator+=(const Point<T> &other);
    Point<T> &operator-=(const Point<T> &other);

private:
    T m_x;
    T m_y;
};

template <class T>
Point<T> operator+(const Point<T> &point1, const Point<T> &point2);
template <class T>
Point<T> operator-(const Point<T> &point1, const Point<T> &point2);

////////////////////////////////////////////////////////////////////////////////
//                           Inline functions:                                //
////////////////////////////////////////////////////////////////////////////////

template <class T>
inline const T &Point<T>::GetX() const
{
    return (this->m_x);
}

template <class T>
inline void Point<T>::SetX(const T x)
{
    this->m_x = x;
}

template <class T>
inline const T &Point<T>::GetY() const
{
    return (this->m_y);
}

template <class T>
inline void Point<T>::SetY(const T y)
{
    this->m_y = y;
}

////////////////////////////////////////////////////////////////////////////////
//                           Operators functions:                             //
////////////////////////////////////////////////////////////////////////////////

template <class T>
Point<T> &Point<T>::operator+=(const Point<T> &other)
{
    this->m_x = this->m_x + other.m_x;
    this->m_y = this->m_y + other.m_y;

    return (*this);
}
template <class T>
Point<T> &Point<T>::operator-=(const Point<T> &other)
{
    this->m_x = this->m_x - other.m_x;
    this->m_y = this->m_y - other.m_y;

    return (*this);
}

template <class T>
Point<T> operator+(const Point<T> &point1, const Point<T> &point2)
{
    Point<T> result;

    result.SetX(point1.GetX() + point2.GetX());
    result.SetY(point1.GetY() + point2.GetY());

    return (result);
}

template <class T>
Point<T> operator-(const Point<T> &point1, const Point<T> &point2)
{
    Point<T> result;

    result.SetX(point1.GetX() - point2.GetX());
    result.SetY(point1.GetY() - point2.GetY());

    return (result);
}
