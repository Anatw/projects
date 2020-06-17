#include <iostream> /* cout, cin, cerr */
#include <cassert>  // assert()

template <class T>
class Point
{
public:
    Point(T x = 0, T y = 0) : m_x(x), m_y(y){};

    inline T GetX() const;
    inline void SetX(T x);
    inline T GetY() const;
    inline void SetY(T y);

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
inline T Point<T>::GetX() const
{
    return (this->m_x);
}

template <class T>
inline void Point<T>::SetX(T x)
{
    this->m_x = x;
}

template <class T>
inline T Point<T>::GetY() const
{
    return (this->m_y);
}

template <class T>
inline void Point<T>::SetY(T y)
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

    result.SetX(point1.GetX() + point2.GetX());
    result.SetY(point1.GetY() + point2.GetY());

    return (result);
}

////////////////////////////////////////////////////////////////////////////////
//                                   Main:                                   //
////////////////////////////////////////////////////////////////////////////////

void CheckInt()
{
    Point<int> first(10, 5);
    Point<int> second(6, 15);

    Point<int> third = first + second;
    assert(third.GetX() == 16);
    assert(third.GetY() == 20);

    first += second;
    assert(first.GetX() == 16);
    assert(first.GetY() == 20);

    third -= first;
    assert(third.GetX() == 0);
    assert(third.GetY() == 0);
}

void CheckDouble()
{
    Point<double> first(10.5, 5.5);
    Point<double> second(6.5, 15.5);

    Point<double> third = first + second;
    assert(third.GetX() == 17);
    assert(third.GetY() == 21);

    first += second;
    assert(first.GetX() == 17);
    assert(first.GetY() == 21);

    third -= first;
    assert(third.GetX() == 0);
    assert(third.GetY() == 0);
}

void CheckChar()
{
    Point<unsigned char> first('a', 'b');  // (97, 98)
    Point<unsigned char> second('c', 'd'); // (99, 100)

    Point<unsigned char> third = first + second;
    assert(third.GetX() == 196);
    assert(third.GetY() == 198);

    first += second;
    assert(first.GetX() == 196);
    assert(first.GetY() == 198);

    third -= first;
    assert(third.GetX() == 0);
    assert(third.GetY() == 0);
}

void CheckFloat()
{
    Point<float> first(10.5, 5.5);
    Point<float> second(6.5, 15.5);

    Point<float> third = first + second;
    assert(third.GetX() == 17);
    assert(third.GetY() == 21);

    first += second;
    assert(first.GetX() == 17);
    assert(first.GetY() == 21);

    third -= first;
    assert(third.GetX() == 0);
    assert(third.GetY() == 0);
}

int main()
{
    CheckInt();
    CheckDouble();
    CheckChar();

    return (0);
}
