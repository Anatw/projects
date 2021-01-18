#ifndef ILRD_RD8586_PLAYER_HPP
#define ILRD_RD8586_PLAYER_HPP

namespace ilrd
{
class Player
{
public:
    Player(); // Default constructor for empty squares
    Player(bool color, bool turn);
    inline bool GetShape()
    {
        return m_color;
    }

private:
    char m_color; // 0 = empty, 1 = X, 2 = O
    bool m_is_turn;

};

class PlayerX : public Player
{
public:
    PlayerX();

private:

};

class PlayerO : public Player
{
public:
    PlayerO();

private:

};

}

#endif // ILRD_RD8586_PLAYER_HPP
