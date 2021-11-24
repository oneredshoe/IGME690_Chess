#include "Piece.h"

class Castle : public Piece{
public:
	Castle(int x, int y, bool isBlack);
	vector<array<int, 2>>PossibleMoves(int board[8][8]) override;
};

Castle::Castle(int x, int y, bool isBlack) : Piece(CASTLE, x, y, isBlack) {}

vector<array<int, 2>> Castle::PossibleMoves(int board[8][8])
{
	return CheckSides(board);
}


//Draw Method

/*
            //make it "dynamic"
            int r_TopHeight = 10;
            int r_HeadHeight = 5;
            int r_BodyHeight = 20;

            //Origin being supposedly the draw corner of the square this piece is on
            origin[0] = 0;
            origin[1] = 0;


            //sfml shapes
            sf::RectangleShape r_Top(sf::Vector2f(12,r_TopHeight));
            sf::RectangleShape r_Head(sf::Vector2f(8, r_HeadHeight));
            sf::RectangleShape r_Body(sf::Vector2f(5, r_BodyHeight));
            sf::RectangleShape r_Base(sf::Vector2f(15, 5));


            //outline color is if we wanted to display it on black and white only, need to set outline weight tho
            if (isBlack)
            {
                r_Top.setFillColor(sf::Color::Black);
                r_Head.setFillColor(sf::Color::Black);
                r_Body.setFillColor(sf::Color::Black);
                r_Base.setFillColor(sf::Color::Black);
                r_Top.setOutlineColor(sf::Color::White);
                r_Head.setOutlineColor(sf::Color::White);
                r_Body.setOutlineColor(sf::Color::White);
                r_Base.setOutlineColor(sf::Color::White);

            }
            else
            {
                r_Top.setFillColor(sf::Color::White);
                r_Head.setFillColor(sf::Color::White);
                r_Body.setFillColor(sf::Color::White);
                r_Base.setFillColor(sf::Color::White);
                r_Top.setOutlineColor(sf::Color::Black);
                r_Head.setOutlineColor(sf::Color::Black);
                r_Body.setOutlineColor(sf::Color::Black);
                r_Base.setOutlineColor(sf::Color::Black);

            }

            //"dynamic" placement with particular hardcoded numbers when I gave up
            r_Top.setPosition(origin[0] += (shift*3), origin[1] += 10);
            r_Head.setPosition(origin[0] += 2, origin[1] += r_TopHeight);
            r_Body.setPosition(origin[0] += 1.5f, origin[1] += r_HeadHeight);
            r_Base.setPosition(origin[0] -= 4.5f, origin[1] += r_BodyHeight);

           window.draw(r_Top);
           window.draw(r_Head);
           window.draw(r_Body);
           window.draw(r_Base);





*/