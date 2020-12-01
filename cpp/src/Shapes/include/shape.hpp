/*******************************************************************************
                                Shapes
                          Written by Anat Wax
                             June 7th-, 2020
                        Reviewer: Laura Bedah
*******************************************************************************/
#ifndef ILRD_RD8586_SHAPES_HPP
#define ILRD_RD8586_SHAPES_HPP

#include <cmath> // M_PI
#include <cstdlib>
#include <sstream>
#include <string>

#include "color.hpp"
#include "glut_utils.h"
#include "point.hpp"

namespace ilrd
{
template < typename T >
std::string to_string(T value)
{
    // create an output string stream
    std::ostringstream os;

    // throw the value into the string stream
    os << value;

    // convert the string stream into a string and return
    return os.str();
}

// Draw() will call drawInternal() to make sure that
// function draw is always called first.
class Shape
{
public:
    Shape();
    Shape(Point point_, double engle_, Color color_);
    ~Shape()
    {
    }

    void Draw() const;

    inline Point GetPosition() const;
    inline void SetPosition(const Point position);

    inline int GetColor() const;
    inline void SetColor(const Color rgb);

    inline double GetAngle() const;
    inline void SetAngle(const double angle_);

    virtual void Rotate_m(const double delta_angle);
    virtual void Revolve_m(const Point& c_point, double angle);
    virtual void Move_m(const Point& vector);

    virtual std::ostream& operator<<(std::ostream& os) const = 0;
    virtual std::istream& operator>>(std::istream& is) = 0;

private:
    virtual void DrawInternal() const
    {
    }

    Point position_m;
    double angle_m;
    Color color_m;
};

inline Point Shape::GetPosition() const
{
    return this->position_m;
}

inline void Shape::SetPosition(const Point position_)
{
    this->position_m = position_;
}

inline int Shape::GetColor() const
{
    return (this->color_m.GetR() * this->color_m.GetG() * this->color_m.GetB());
}

inline void Shape::SetColor(const Color rgb)
{
    this->color_m = rgb;
}

inline double Shape::GetAngle() const
{
    return this->angle_m;
}

inline void Shape::SetAngle(const double angle_)
{
    this->angle_m = angle_;
}
} // namespace ilrd
#endif // ILRD_RD8586_SHAPES_HPP
