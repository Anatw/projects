/*******************************************************************************
                                Shapes
                          Written by Anat Wax
						     June 7th-, 2020
						Reviewer: Laura Bedah
*******************************************************************************/
#ifndef ILRD_RD8586_LINE_HPP
#define ILRD_RD8586_LINE_HPP

#include "shape.hpp"
#include "point.hpp"
#include "color.hpp"
#include "glut_utils.h"

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

#endif //ILRD_RD8586_LINE_HPP
