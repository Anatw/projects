#ifndef ILRD_RD8586_SQUARE_HPP
#define ILRD_RD8586_SQUARE_HPP

#include "shape.hpp"
#include "point.hpp"
#include "color.hpp"

namespace ilrd
{
    class Square : public Shape
    {
    public:
        Square() : m_edge(100)
        {
        }

        Square(Point position_, double angle_, Color color_, int edge_);

        void SetLength(int edge_);
        int GetLength() const;

    private:
        void DrawInternal() const;

        int m_edge;
    };

    // Inline functions:
    inline void Square::SetLength(int edge_)
    {
        this->m_edge = edge_;
    }

    inline int Square::GetLength() const
    {
        return this->m_edge;
    }
} // namespace ilrd

#endif //ILRD_RD8586_SQUARE_HPP
