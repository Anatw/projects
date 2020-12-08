/*******************************************************************************
                                Shapes
                          Written by Anat Wax
                             June 7th-, 2020
                        Reviewer: Laura Bedah
*******************************************************************************/
#ifndef ILRD_RD8586_CIRCLE_HPP
#define ILRD_RD8586_CIRCLE_HPP

#include "color.hpp"
#include "glut_utils.h"
#include "point.hpp"
#include "shape.hpp"

namespace ilrd
{

class Circle : public Shape
{
public:
    Circle() : m_radius(100)
    {
    }

    Circle(Point position_, double angle_, Color color_, int radius_);
    void SetRadius(int radius_);
    int GetRadius() const;

    std::ostream& operator<<(std::ostream& os) const;
    std::istream& operator>>(std::istream& is);

private:
    void DrawInternal() const;

    int m_radius;
};

// inline functions:
inline void Circle::SetRadius(int radius_)
{
    this->m_radius = radius_;
}

inline int Circle::GetRadius() const
{
    return this->m_radius;
}

} // namespace ilrd
#endif // ILRD_RD8586_CIRCLE_HPP
