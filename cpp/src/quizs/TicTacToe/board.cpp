/*******************************************************************************
Title & Description: Master Storage Manager - part of the Master in the 
final project.
This part is in charge of all the documentation and maintenance of the 
mapping between the offsets of the memory and the Minion responsible to 
operate

Authour: Anat Wax, anatwax@gmail.com
Reviewer: 
Datecreation: 20.09.2020
Version: 1
*******************************************************************************/
#include <iostream> // cout
#include <limits> // interger min + max values
#include <cstring> // memset()

#include "board.hpp"

using namespace ilrd;

Board::Board(int size) : m_size(size), m_game_status(1), m_X(1, 1), m_O(0, 0)
{
    // The addition of () at the end will set all chars to '0'
    m_board_set = new Player[size * size];
}

Board::~Board()
{
    delete[] m_board_set;
}

char Board::CheckGameStatus(int location)
{
    int counter = 0; // Counting the currently sent location
    int loc = location - 1;
    int i = 0;
    bool current_shape = m_board_set[loc].GetShape();

    while (counter < m_size)
    {
        // If location is in one of the corners:
        if (loc == 0 ||
            loc == m_size - 1 ||
            loc == (m_size * m_size) - 1 ||
            loc == (m_size * m_size) - m_size)
        {

        }
        // If location if in the middle of the board:
        else if (loc == (m_size * m_size) / 2)
        {

        }
        // If location if in the middle of a raw:
        else
        {
            // Check raw:
            for (i = (i - (loc % m_size));
                    i <= (loc + (loc % m_size));
                    ++i)
            {
                if (current_shape == m_board_set[i].GetShape())
                {
                    ++counter;
                }
            }

            // Check Column:
            for (i = loc % m_size; i < (m_size * m_size); i += m_size)
            {
                if (current_shape == m_board_set[i].GetShape())
                {
                    ++counter;
                }
            }
        }
    }

    if (counter == m_size)
    {
        std::cout << "Player " << (current_shape == 1 ? "X" : "O") << "is the winner!" << std::endl;
    }
    else
    {
        std::cout << "Tie! press 'a' to start the game over" << std::endl;
    }
    
}

void Board::PlaceToken(bool p_color, int location)
{
    int loc = location - 1;
    Player player(p_color, true);

    // check if location is valid and available (meaning empty)
    if ((location >= 1 && location <= 9) ||
         0 != m_board_set[location].GetShape())
    {
        std::cout << "location is invalid" << std::endl;
        std::cin >> location;
    }
    // If token is placed - check if player is a winner - check the close squars - if you finc an identical shape - keep checking in that direction. if not, check the resp of the close squares
    m_board_set[loc] = player;

    m_game_status = CheckGameStatus(loc);
}