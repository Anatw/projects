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

        inline void SetLength(int edge_)
        {
            this->m_edge = edge_;
        }

        inline int GetLength() const
        {
            return this->m_edge;
        }

    private:
        void DrawInternal() const;

        int m_edge;
    };
} // namespace ilrd

#endif //ILRD_RD8586_SQUARE_HPP
