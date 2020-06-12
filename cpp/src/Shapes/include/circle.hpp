/*******************************************************************************
                                Shapes
                          Written by Anat Wax
						     June 7th-, 2020
						Reviewer: Laura Bedah
*******************************************************************************/
#ifndef ILRD_RD8586_CIRCLE_HPP
#define ILRD_RD8586_CIRCLE_HPP

#include "shape.hpp"
#include "point.hpp"
#include "color.hpp"
#include "glut_utils.h"

namespace ilrd
{

    class Circle : public Shape
    {
    public:
        Circle() : m_radius(100)
        {
        }

        Circle(Point position_, double angle_, Color color_, int radius_);

        inline void SetRadius(int radius_)
        {
            this->m_radius = radius_;
        }

        inline int GetRadius() const
        {
            return this->m_radius;
        }

    private:
        void DrawInternal() const;

        int m_radius;
    };

} // namespace ilrd
#endif //ILRD_RD8586_CIRCLE_HPP
