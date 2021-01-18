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

#include "player.hpp"

using namespace ilrd;

Player::Player() : m_color(0), m_is_turn(false)
{

}

Player::Player(bool color, bool turn) : m_color(color), m_is_turn(turn)
{

}

PlayerX::PlayerX() : Player(1, false)
{
    
}

PlayerO::PlayerO() : Player(2, true)
{

}

