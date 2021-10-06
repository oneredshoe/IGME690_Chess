#include <SFML/Graphics.hpp>

float squareSize = 50;
sf::RectangleShape board[8][8];

void setUp() {
    bool isBlack = true;
    for (int i = 0; i < 8; i++) {
        for (int j = 0; j < 8; j++) {
            board[i][j] = sf::RectangleShape(sf::Vector2f(squareSize, squareSize));
            
            if(isBlack)board[i][j].setFillColor(sf::Color::Black);
            if(!isBlack)board[i][j].setFillColor(sf::Color::White);

            isBlack = !isBlack;

            board[i][j].setPosition(sf::Vector2f(i * squareSize, j * squareSize));
        }

        isBlack = !isBlack;
    }
}

int main()
{
    sf::RenderWindow window(sf::VideoMode(1000, 1000), "SFML works!");
    bool firstRound = true;

    while (window.isOpen())
    {
        if (firstRound) {
            setUp();
            firstRound = false;
        }
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        for (int i = 0; i < 8; i++) {
            for (int j = 0; j < 8; j++) {
                window.draw(board[i][j]);
            }
        }

        window.display();
    }

    return 0;
}