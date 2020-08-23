/*******************************************************************************
                                Shapes
                          Written by Anat Wax
                             June 7th-, 2020
                        Reviewer: Laura Bedah
*******************************************************************************/
#ifndef ILRD_RD8586_RECTANGLE_HPP
#define ILRD_RD8586_RECTANGLE_HPP

#include "color.hpp"
#include "point.hpp"
#include "shape.hpp"

namespace ilrd
{
class Rectangle : public Shape
{
public:
    Rectangle();
    Rectangle(Point position_, double angle_, Color color_m, int width_,
              int length_);

    void SetLength(int length_);
    int GetLength() const;
    void SetWidth(int width_);
    int GetWidth() const;

    std::ostream& operator<<(std::ostream& os);
    std::ostream& operator>>(std::istream& is);

private:
    void DrawInternal() const;

    int m_width;
    int m_length;
};

// Inline functions:
inline void Rectangle::SetLength(int length_)
{
    this->m_length = length_;
}

inline int Rectangle::GetLength() const
{
    return this->m_length;
}

inline void Rectangle::SetWidth(int width_)
{
    this->m_width = width_;
}

inline int Rectangle::GetWidth() const
{
    return this->m_width;
}
} // namespace ilrd

#endif // ILRD_RD8586_RECTANGLE_HPP
