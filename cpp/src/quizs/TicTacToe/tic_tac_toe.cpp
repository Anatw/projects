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
#include <SFML/Graphics.hpp>

#include "board.hpp"
#include "player.hpp"

using namespace  ilrd;

#define X (1)
#define O (0)

bool NextTurn(bool player)
{
    // Returns the opposite of the current player:
    return (!player);
}

int main()
{
    int size = 0;
    std::cout << "To start the game enter amout of desired size (squares in a raw)" << std::endl;
    std::cin >> size;

    if (size < 3)
    {
        size = 3;
    }

    Board board(size);

    while (0 != board.GameStatus())
    {
        int location = -1;
        std::cout << "Player X, enter a location" << std::endl;
        std::cin >> location;
        bool player = X; // X will start

        board.PlaceToken(player, location);
        player = NextTurn(player);


        sf::RenderWindow window(sf::VideoMode(400, 400), "Tic Tac Toe");
        sf::RectangleShape shape;
        shape.setSize(sf::Vector2f(100, 100));
        shape.setFillColor(sf::Color::Green);
        shape.setOutlineColor(sf::Color::Black);

        while (window.isOpen())
        {
            sf::Event event;
            while (window.pollEvent(event))
            {
                if (event.type == sf::Event::Closed)
                    window.close();
            }

            window.clear();
            window.draw(shape);
            window.display();
        }
    }

    return 0;
}