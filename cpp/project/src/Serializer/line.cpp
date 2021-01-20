/*******************************************************************************
                                Shapes
                          Written by Anat Wax
                             June 7th-, 2020
                        Reviewer: Laura Bedah
*******************************************************************************/
#include "line.hpp"

using namespace ilrd;

std::ostream& Line::operator<<(std::ostream& os)
{
    std::string line_str;
    line_str.append(to_string(m_length));

    return (os << line_str);
}

std::istream& Line::operator>>(std::istream& is)
{
    std::string line_str;
    is >> line_str;

    int inner_line = std::atoi(line_str.c_str());

    this->SetLength(inner_line);

    return (is);
}

Line::Line(Point position_, double angle_, Color color_, int length_)
    : Shape(position_, angle_, color_), m_length(length_)
{
}

void Line::DrawInternal() const
{
    int half = m_length / 2;
    Point pos = this->GetPosition(); // x, y
    // Transfering the engle to radian (' * M_PI / 180 '):
    double angle = this->GetAngle() * M_PI / 180;

    double start_x = (pos.GetX() - half);
    double start_y = pos.GetY();
    Point start_pos(start_x, start_y);

    double end_x = pos.GetX() + half;
    double end_y = pos.GetY();
    Point end_pos(end_x, end_y);

    start_pos.Revolve(pos, angle);
    end_pos.Revolve(pos, angle);

    DrawPolygon(this->GetColor(), 2, (int)start_pos.GetX(),
                (int)start_pos.GetY(), (int)end_pos.GetX(),
                (int)end_pos.GetY());
}
