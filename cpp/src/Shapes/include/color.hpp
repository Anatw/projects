/*******************************************************************************
                                Shapes
                          Written by Anat Wax
						     June 7th-, 2020
						Reviewer: Laura Bedah
*******************************************************************************/
#ifndef ILRD_RD8586_COLOR_POINT
#define ILRD_RD8586_COLOR_POINT

//#include "shape.hpp"
// #include "point.hpp"
// #include "glut_utils.h"

namespace ilrd
{
    class Color
    {
    public:
        Color() : m_r(50), m_g(50), m_b(50) // COLOR_WHITE
        {
        }

        Color(unsigned int r_, unsigned int g_, unsigned int b_);
        //~Color() = default;
        //Color(const Color&) = default;
        //Color& operator=(const Color&) = default;

        inline unsigned int GetR() const;
        inline void SetR(unsigned int value);

        inline unsigned int GetG() const;
        inline void SetG(unsigned int value);

        inline unsigned int GetB() const;
        inline void SetB(unsigned int value);

    private:
        unsigned int m_r;
        unsigned int m_g;
        unsigned int m_b;
    };

    inline unsigned int Color::GetR() const
    {
        return this->m_r;
    }

    inline void Color::SetR(unsigned int value)
    {
        this->m_r = value;
    }

    inline unsigned int Color::GetG() const
    {
        return this->m_g;
    }

    inline void Color::SetG(unsigned int value)
    {
        this->m_g = value;
    }

    inline unsigned int Color::GetB() const
    {
        return this->m_b;
    }

    inline void Color::SetB(unsigned int value)
    {
        this->m_b = value;
    }
} // namespace ilrd
#endif // ILRD_RD8586_COLOR_POINT
