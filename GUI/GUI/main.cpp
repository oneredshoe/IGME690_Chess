#include <SFML/Graphics.hpp>
#include "Board.h"


int main()
{
    sf::RenderWindow window(sf::VideoMode(50*8, 50*8), "Chess");
    bool firstRound = true;
    Board board(window);

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        board.Draw();
        window.display();
    }

    return 0;
}