#ifndef ILRD_RD8586_BOARD_HPP
#define ILRD_RD8586_BOARD_HPP

#include <SFML/Graphics.hpp>

#include "player.hpp"

namespace ilrd
{
class Board
{
public:
    Board(int size);
    ~Board();
    inline char GameStatus();
    void PlaceToken(bool p_color, int location);

private:
    inline char CheckLocation(int location);
    char CheckGameStatus(int location);

    int m_size;
    // game_Status:
    // 0 - no game ation;
    // 1 - game on ; 
    // 2 - tie ;
    // 3 - X wins ;
    // 4 - O wins.
    char m_game_status;
    // Location:
    // 1 = X;
    // 2 = O;
    Player *m_board_set;


    Player m_X;
    Player m_O;
};

inline char Board::GameStatus()
{
    return m_game_status;
}

inline char Board::CheckLocation(int location)
{
    return (m_board_set[location + 1].GetShape());
}

}

#endif // ILRD_RD8586_BOARD_HPP

