#ifndef BOARD_H
#define BOARD_H

#include <SFML/Graphics.hpp>


class Board {
public:
    sf::RectangleShape m_board[8][8];
    Board(sf::RenderWindow& win, float squareSize);
    Board(sf::RenderWindow& win);
    void Draw();
    float getSquareSize();
private:
    float m_squareSize = 50;
    void SetUp();
    sf::RenderWindow& m_window;
    //sf::Texture m_brownTexture;
    //sf::Texture m_tanTexture;
};

Board::Board(sf::RenderWindow& win, float squareSize) : m_window(win) {
   
    m_squareSize = squareSize;
    SetUp();
}

Board::Board(sf::RenderWindow& win) : m_window(win) {
    SetUp();
}

float Board::getSquareSize() {
    return m_squareSize;
}

void Board::SetUp() {
    bool isBlack = true;
    for (int i = 0; i < 8; i++) {
        for (int j = 0; j < 8; j++) {
            m_board[i][j] = sf::RectangleShape(sf::Vector2f(m_squareSize, m_squareSize));

            if (isBlack) m_board[i][j].setFillColor(sf::Color(151,65,32));
            if (!isBlack)m_board[i][j].setFillColor(sf::Color(236,206,154));

            isBlack = !isBlack;

            m_board[i][j].setPosition(sf::Vector2f(i * m_squareSize, j * m_squareSize));
        }

        isBlack = !isBlack;
    }
}

void Board::Draw() {
    for (int i = 0; i < 8; i++) {
        for (int j = 0; j < 8; j++) {
            m_window.draw(m_board[i][j]);
        }
    }
}

#endif // !BOARD_H