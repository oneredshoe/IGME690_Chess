#include "Piece.h"

class Bishop : public Piece{
public:
	Bishop(int x, int y, bool isBlack);
	vector<array<int, 2>>PossibleMoves(int board[8][8]) override;
};

Bishop::Bishop(int x, int y, bool isBlack) : Piece(BISHOP, x, y, isBlack) {}

vector<array<int, 2>> Bishop::PossibleMoves(int board[8][8])
{
	return CheckDiagonals(board);
}

//Draw Method:


/*
*           //Origin being supposedly the draw corner of the square this piece is on
            origin[0] = 0;
            origin[1] = 0;


            //make it "dynamic"
            int b_TopHeight = 3;
            int b_HeadHeight = 6;
            int b_BodyHeight = 20;

            //sfml shapes
            sf::CircleShape b_Top(b_TopHeight);
            sf::CircleShape b_Head(b_HeadHeight);
            sf::RectangleShape b_Body(sf::Vector2f(5, b_BodyHeight));
            sf::RectangleShape b_Base(sf::Vector2f(13, 5));

            //outline color is if we wanted to display it on black and white only, need to set outline weight tho
            if (isBlack)
            {
                b_Top.setFillColor(sf::Color::Black);
                b_Head.setFillColor(sf::Color::Black);
                b_Body.setFillColor(sf::Color::Black);
                b_Base.setFillColor(sf::Color::Black);
                b_Top.setOutlineColor(sf::Color::White);
                b_Head.setOutlineColor(sf::Color::White);
                b_Body.setOutlineColor(sf::Color::White);
                b_Base.setOutlineColor(sf::Color::White);

            }
            else
            {
                b_Top.setFillColor(sf::Color::White);
                b_Head.setFillColor(sf::Color::White);
                b_Body.setFillColor(sf::Color::White);
                b_Base.setFillColor(sf::Color::White);
                b_Top.setOutlineColor(sf::Color::Black);
                b_Head.setOutlineColor(sf::Color::Black);
                b_Body.setOutlineColor(sf::Color::Black);
                b_Base.setOutlineColor(sf::Color::Black);

            }

            //"dynamic" placement with particular hardcoded numbers when I gave up
            b_Top.setPosition(origin[0] += (shift*4), origin[1] += 10);
            b_Head.setPosition(origin[0] -= b_TopHeight, origin[1] += b_TopHeight * 1.5);
            b_Body.setPosition(origin[0] += 4.5, origin[1] += b_HeadHeight * 1.5);
            b_Base.setPosition(origin[0] -= b_TopHeight* 1.1, origin[1] += b_BodyHeight);


            window.draw(b_Top);
            window.draw(b_Head);
            window.draw(b_Body);
            window.draw(b_Base);




*/