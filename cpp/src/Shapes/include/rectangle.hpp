/*******************************************************************************
                                Shapes
                          Written by Anat Wax
						     June 7th-, 2020
						Reviewer: Laura Bedah
*******************************************************************************/
#ifndef ILRD_RD8586_RECTANGLE_HPP
#define ILRD_RD8586_RECTANGLE_HPP

#include "shape.hpp"

namespace ilrd
{
    class Rectangle : public Shape
    {
    public:
        Rectangle();
        Rectangle(Point position_, double angle_, Color color_m, int width_, int length_);

        inline void SetLength(int length_)
        {
            this->m_length = length_;
        }

        inline int GetLength() const
        {
            return this->m_length;
        }

        inline void SetWidth(int width_)
        {
            this->m_width = width_;
        }

        inline int GetWidth() const
        {
            return this->m_width;
        }

    private:
        void DrawInternal() const;

        int m_width;
        int m_length;
    };
} // namespace ilrd

#endif //ILRD_RD8586_RECTANGLE_HPP
