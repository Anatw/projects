/*******************************************************************************
                                Shapes
                          Written by Anat Wax
                             June 7th-, 2020
                        Reviewer: Laura Bedah
*******************************************************************************/
#ifndef ILRD_RD8586_LINE_HPP
#define ILRD_RD8586_LINE_HPP

#include "color.hpp"
#include "glut_utils.h"
#include "point.hpp"
#include "shape.hpp"

namespace ilrd
{
class Line : public Shape
{
public:
    Line() : m_length(100)
    {
    }

    Line(Point position_, double angle_, Color color_, int length_);
    int GetLength() const;
    inline void SetLength(const int length_)
    {
        m_length = length_;
    }

    std::ostream& operator<<(std::ostream& os) const;
    std::istream& operator>>(std::istream& is);

private:
    void DrawInternal() const;

    int m_length;
};

// Inline functions:
inline int Line::GetLength() const
{
    return this->m_length;
}

} // namespace ilrd

#endif // ILRD_RD8586_LINE_HPP
