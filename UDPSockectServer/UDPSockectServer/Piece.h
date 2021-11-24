#ifndef PIECE_H
#define PIECE_H
#include <string>
#include <vector>
#include <array>
#include <cmath> 
#include <iostream>

/*
Broad
  A  B  C  D  E  F  G  H
  0  1  2  3  4  5  6  7
0
1	[black pieces]
2
3
4
5
6	[white pieces]
7

a white piece is denoted as 0
a black piece is denoted as 1
a empty square is denotd as 2

*/

using namespace std;

enum PieceType { HORSE, CASTLE, BISHOP, PAWN, KING, QUEEN, NONE };

enum Letters {A = 0, B = 1, C = 2, D = 3, E = 4, F = 5, G = 6, H = 7};

class Piece
{
public:
	Piece(PieceType name, int x, int y, bool isBlack);
	Piece();
	~Piece();
	PieceType getName();
	int* getPosition();
	bool isBlack();

	vector<array<int, 2>>PossibleMoves(int board[8][8]);
	
protected:
	PieceType m_name;
	int m_position[2]{0, 0};
	bool m_isBlack;
	vector<array<int, 2>> CheckSides( int board[8][8]);
	vector<array<int, 2>> CheckDiagonals(int board[8][8]);
};

Piece::Piece(PieceType name, int x, int y, bool isBlack )
{
	m_name = name;

	m_position[0] = x;
	m_position[1] = y;
	m_isBlack = isBlack;
}

Piece::Piece()
{
	m_name = NONE;
	m_position[0] = -1;
	m_position[1] = -1;
	m_isBlack = false;
}

Piece::~Piece()
{
	
}

PieceType Piece::getName() {
	return m_name;
}

int* Piece::getPosition() {
	return m_position;
}

bool Piece::isBlack() {
	return m_isBlack;
}

 vector<array<int, 2>> Piece::CheckSides( int board[8][8])
{
	vector<array<int, 2>> retVal;

	for (int i = m_position[0] + 1; i < 8; i++) {
		if (board[i][m_position[1]] == 2) {
			retVal.push_back({ i, m_position[1] });
		}
		else if (board[i][m_position[1]] != (int)m_isBlack) {
			retVal.push_back({ i, m_position[1] });
			break;
		}
	}

	for (int i = m_position[0] - 1; i >= 0; i--) {
		if (board[i][m_position[1]] == 2) {
			retVal.push_back({ i, m_position[1] });
		}
		else if (board[i][m_position[1]] != (int)m_isBlack) {
			retVal.push_back({ i, m_position[1] });
			break;
		}
	}

	for (int i = m_position[1] + 1; i < 8; i++) {
		if (board[m_position[0]][i] == 2) {
			retVal.push_back({ m_position[0], i });
		}
		else if (board[m_position[0]][i] != (int)m_isBlack) {
			retVal.push_back({ m_position[0], i });
			break;
		}
	}

	for (int i = m_position[1] - 1; i >= 0; i--) {
		if (board[m_position[0]][i] == 2) {
			retVal.push_back({ m_position[0], i });
		}
		else if (board[m_position[0]][i] != (int)m_isBlack) {
			retVal.push_back({ m_position[0], i });
			break;
		}
	}

	return retVal;
}

 vector<array<int, 2>> Piece::CheckDiagonals(int board[8][8])
{
	 vector<array<int, 2>> retVal;

	 bool first = true, second = true, third = true, forth = true;

	 for (int i = 1; i < 8; i++) {

		 if (first && m_position[0] + i < 8 && m_position[1] + i < 8) {
			 if (board[m_position[0] + i][m_position[1] + i] != (int)m_isBlack) {
				 retVal.push_back({ m_position[0] + i , m_position[1] + i });
			 }
			 else {
				 first = false;
			 }
		 }

		 if (second && m_position[0] + i < 8 && m_position[1] - i >= 0) {
			 if(board[m_position[0] + i][m_position[1] - i] != (int)m_isBlack) {
				 retVal.push_back({ m_position[0] + i , m_position[1] - i });
			 }
			 else {
				second = false;
			 }
		 }

		 if (third && m_position[0] - i < 8 && m_position[1] - i >= 0) {
			 if (board[m_position[0] - i][m_position[1] - i] != (int)m_isBlack) {
				 retVal.push_back({ m_position[0] - i , m_position[1] - i });
			 }
			 else {
				 third = false;
			 }
		 }

		 if (forth && m_position[0] - i < 8 && m_position[1] + i >= 0) {
			 if (board[m_position[0] - i][m_position[1] + i] != (int)m_isBlack) {
				 retVal.push_back({ m_position[0] + i , m_position[1] - i });
			 }
			 else {
				 forth = false;
			 }
		 }

	 }

	 return retVal;
}

vector<array<int, 2>> Piece::PossibleMoves(int board[8][8])
{
	vector<array<int, 2>> retVal;
	switch (m_name) {
	case HORSE:
	{
		if (m_position[0] + 2 < 8) {
			if (m_position[1] + 1 < 8 && board[m_position[0] + 2][m_position[1] + 1] != (int)m_isBlack) retVal.push_back({ m_position[0] + 2, m_position[1] + 1 });
			if (m_position[1] - 1 >= 0 && board[m_position[0] + 2][m_position[1] - 1] != (int)m_isBlack) retVal.push_back({ m_position[0] + 2, m_position[1] - 1 });
		}

		if (m_position[0] - 2 >= 0) {
			if (m_position[1] + 1 < 8 && board[m_position[0] - 2][m_position[1] + 1] != (int)m_isBlack) retVal.push_back({ m_position[0] - 2, m_position[1] + 1 });
			if (m_position[1] - 1 >= 0 && board[m_position[0] - 2][m_position[1] - 1] != (int)m_isBlack) retVal.push_back({ m_position[0] - 2, m_position[1] - 1 });
		}

		if (m_position[1] + 2 < 8) {
			if (m_position[0] + 1 < 8 && board[m_position[0] + 1][m_position[1] + 2] != (int)m_isBlack) retVal.push_back({ m_position[0] + 1, m_position[1] + 2 });
			if (m_position[0] - 1 >= 0 && board[m_position[0] - 1][m_position[1] + 2] != (int)m_isBlack) retVal.push_back({ m_position[0] - 1, m_position[1] + 2 });
		}

		if (m_position[1] - 2 >= 0) {
			if (m_position[0] + 1 < 8 && board[m_position[0] + 1][m_position[1] - 2] != (int)m_isBlack) retVal.push_back({ m_position[0] + 1, m_position[1] - 2 });
			if (m_position[0] - 1 >= 0 && board[m_position[0] - 1][m_position[1] - 2] != (int)m_isBlack) retVal.push_back({ m_position[0] - 1, m_position[1] - 2 });
		}

		return retVal;
		break;
	}
	case CASTLE:
	{
		return CheckSides(board);
		break;
	}
	case BISHOP:
	{
		return CheckDiagonals(board);
		break;
	}
	case PAWN:
	{
		int multiplier = 1;
		if (!m_isBlack) multiplier = -1;

		bool hasMoved = false;
		if ((m_isBlack && m_position[0] != 1) || (!m_isBlack && m_position[0] != 6)) {
			hasMoved = true;
		}

		//make sure not at the dge of the board
		if (m_position[0] + multiplier >= 8 || m_position[0] + multiplier < 0) {
			return retVal;
		}

		//see if u can move forward
		if (board[m_position[0] + multiplier][m_position[1]] == 2) {
			retVal.push_back({ m_position[0] + multiplier, m_position[1] });
			if (!hasMoved && board[m_position[0] + multiplier * 2][m_position[1]] == 2 && m_position[0] + multiplier * 2 < 8 && m_position[0] + multiplier * 2 >= 0) {
				retVal.push_back({ m_position[0] + multiplier * 2, m_position[1] });
			}
		}

		//see if u can attack
		if (m_position[1] + 1 < 8 && m_position[1] + 1 >= 0 && board[m_position[0] + multiplier][m_position[1] + 1] == (int)!m_isBlack) {
			retVal.push_back({ m_position[0] + multiplier, m_position[1] + 1 });
		}

		if (m_position[1] - 1 < 8 && m_position[1] - 1 >= 0 && board[m_position[0] + multiplier][m_position[1] - 1] == (int)!m_isBlack) {
			retVal.push_back({ m_position[0] + multiplier, m_position[1] - 1 });
		}
		return retVal;
		break;
	}
	case QUEEN:
	{
		vector<array<int, 2>> sides = CheckSides(board);
		vector<array<int, 2>> diagonals = CheckDiagonals(board);
		retVal.reserve(sides.size() + diagonals.size());
		retVal.insert(retVal.end(), sides.begin(), sides.end());
		retVal.insert(retVal.end(), diagonals.begin(), diagonals.end());

		return retVal;
		break;
	}
	case KING:
	{
		int posY = m_position[0] + 1;
		int posX = m_position[1] + 1;

		int negY = m_position[0] - 1;
		int negX = m_position[1] - 1;

		if (posX < 8) {
			if (board[m_position[0]][posX] != (int)m_isBlack) retVal.push_back({ m_position[0], posX });
			if (posY < 8 && board[posY][posX] != (int)m_isBlack) retVal.push_back({ posY, posX });
		}
		if (negX >= 0) {
			if (board[m_position[0]][negX] != (int)m_isBlack) retVal.push_back({ m_position[0], negX });
			if (negY >= 0 && board[negY][negX] != (int)m_isBlack) retVal.push_back({ negY, negX });
		}

		if (posY < 8) {
			if (board[posY][m_position[1]] != (int)m_isBlack) retVal.push_back({ posY, m_position[1] });
			if (negX >= 0 && board[posY][negX] != (int)m_isBlack) retVal.push_back({ posY, negX });
		}
		if (negY >= 0) {
			if (board[negY][m_position[1]] != (int)m_isBlack) retVal.push_back({ negY, m_position[1] });
			if (posX < 8 && board[negY][posX] != (int)m_isBlack) retVal.push_back({ negY, posX });
		}

		return retVal;
		break;
	}
	}
	return vector<array<int, 2>>();
}


/////////////Classes////////////////////////////////////////////

class Horse : public Piece {
public:
	Horse(int x, int y, bool isBlack);
};

Horse::Horse(int x, int y, bool isBlack) : Piece(HORSE, x, y, isBlack) {}
/*
			sf::ConvexShape horse;

			//Corner of square the piece is on
			origin[0] = 0;
			origin[1] = 0;


			horse.setPointCount(14);
			horse.setPoint(0, sf::Vector2f(10, 10));
			horse.setPoint(1, sf::Vector2f(14, 14));
			horse.setPoint(2, sf::Vector2f(18, 24));
			horse.setPoint(3, sf::Vector2f(20, 29));
			horse.setPoint(4, sf::Vector2f(20, 39));
			horse.setPoint(5, sf::Vector2f(23, 39));
			horse.setPoint(6, sf::Vector2f(23, 44));
			horse.setPoint(7, sf::Vector2f(2, 44));
			horse.setPoint(8, sf::Vector2f(2, 39));
			horse.setPoint(9, sf::Vector2f(5, 39));
			horse.setPoint(10, sf::Vector2f(5, 29));
			horse.setPoint(11, sf::Vector2f(0, 29));
			horse.setPoint(12, sf::Vector2f(2, 24));
			horse.setPoint(13, sf::Vector2f(6,14));

			if (isBlack)
			{
				horse.setFillColor(sf::Color::Black);
			}
			else
			{
				horse.setFillColor(sf::Color::White);
			}
			horse.setPosition(origin[0] += 10, origin[1] += 10);
			window.draw(horse);



*/


class King : public Piece {
public:
	King(int x, int y, bool isBlack);
};

King::King(int x, int y, bool isBlack) : Piece(KING, x, y, isBlack) {}

/*
			origin[0] = 0;
			origin[1] = 0;


			sf::ConvexShape king;

			king.setPointCount(21);

			king.setPoint(0, sf::Vector2f(7,2));

			king.setPoint(1, sf::Vector2f(5,5));
			king.setPoint(2, sf::Vector2f(2,0));
			king.setPoint(3, sf::Vector2f(2,9));
			king.setPoint(4, sf::Vector2f(0,9));
			king.setPoint(5, sf::Vector2f(0,11));
			king.setPoint(6, sf::Vector2f(7,11));
			king.setPoint(7, sf::Vector2f(2,15));
			king.setPoint(8, sf::Vector2f(2,36));
			king.setPoint(9, sf::Vector2f(-1,38));
			king.setPoint(10, sf::Vector2f(-1,40));
			king.setPoint(11, sf::Vector2f(14,40));
			king.setPoint(12, sf::Vector2f(14,38));
			king.setPoint(13, sf::Vector2f(11,36));
			king.setPoint(14, sf::Vector2f(11,15));
			king.setPoint(15, sf::Vector2f(7,11));
			king.setPoint(16, sf::Vector2f(13,11));
			king.setPoint(17, sf::Vector2f(13,9));
			king.setPoint(18, sf::Vector2f(11,9));
			king.setPoint(19, sf::Vector2f(11,0));
			king.setPoint(20, sf::Vector2f(9,5));


			if (isBlack)
			{
			king.setFillColor(sf::Color::Black);
			}
			else
			{
				king.setFillColor(sf::Color::White);
			}

			king.setPosition(origin[0] + 10, origin[1] + 10);
			window.draw(king);

*/




class Queen : public Piece {
public:
	Queen(int x, int y, bool isBlack);
};

Queen::Queen(int x, int y, bool isBlack) : Piece(QUEEN, x, y, isBlack) {}

/*
			sf::ConvexShape queen;
			origin[0] = 0;
			origin[1] = 0;

			queen.setPointCount(23);
			queen.setPoint(0, sf::Vector2f(10,1));

			queen.setPoint(1, sf::Vector2f(7,3));
			queen.setPoint(2, sf::Vector2f(4,0));
			queen.setPoint(3, sf::Vector2f(4,5));

			queen.setPoint(4, sf::Vector2f(1,5));
			queen.setPoint(5, sf::Vector2f(1,7));
			queen.setPoint(6, sf::Vector2f(3,7));
			queen.setPoint(7, sf::Vector2f(3,9));
			queen.setPoint(8, sf::Vector2f(5,9));
			queen.setPoint(9, sf::Vector2f(5,30));
			queen.setPoint(10, sf::Vector2f(1,37));
			queen.setPoint(11, sf::Vector2f(1,40));
			queen.setPoint(12, sf::Vector2f(19,40));
			queen.setPoint(13, sf::Vector2f(19,37));
			queen.setPoint(14, sf::Vector2f(15,30));
			queen.setPoint(15, sf::Vector2f(15,9));
			queen.setPoint(16, sf::Vector2f(17,9));
			queen.setPoint(17, sf::Vector2f(17,7));
			queen.setPoint(18, sf::Vector2f(19,7));
			queen.setPoint(19, sf::Vector2f(19,5));

			queen.setPoint(20, sf::Vector2f(16,5));
			queen.setPoint(21, sf::Vector2f(16,0));
			queen.setPoint(22, sf::Vector2f(13,3));

			if (isBlack)
			{
				queen.setFillColor(sf::Color::Black);
			}
			else
			{
				queen.setFillColor(sf::Color::White);
			}

			queen.setPosition(origin[0] + 10, origin[1] + 10);
			window.draw(queen);

*/




class Bishop : public Piece {
public:
	Bishop(int x, int y, bool isBlack);
};

Bishop::Bishop(int x, int y, bool isBlack) : Piece(BISHOP, x, y, isBlack) {}

/*
			origin[0] = 0;
			origin[1] = 0;

			int b_TopHeight = 3;
			int b_HeadHeight = 6;
			int b_BodyHeight = 20;
			sf::CircleShape b_Top(b_TopHeight);
			sf::CircleShape b_Head(b_HeadHeight);
			sf::RectangleShape b_Body(sf::Vector2f(5, b_BodyHeight));
			sf::RectangleShape b_Base(sf::Vector2f(13, 5));
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

			b_Top.setPosition(origin[0] += 10, origin[1] += 10);
			b_Head.setPosition(origin[0] -= b_TopHeight, origin[1] += b_TopHeight * 1.5);
			b_Body.setPosition(origin[0] += 4.5, origin[1] += b_HeadHeight * 1.5);
			b_Base.setPosition(origin[0] -= b_TopHeight* 1.1, origin[1] += b_BodyHeight);


			window.draw(b_Top);
			window.draw(b_Head);
			window.draw(b_Body);
			window.draw(b_Base);


*/




class Castle : public Piece {
public:
	Castle(int x, int y, bool isBlack);
};

Castle::Castle(int x, int y, bool isBlack) : Piece(CASTLE, x, y, isBlack) {}

/*
			int r_TopHeight = 10;
			int r_HeadHeight = 5;
			int r_BodyHeight = 20;


			origin[0] = 0;
			origin[1] = 0;

			sf::RectangleShape r_Top(sf::Vector2f(12,r_TopHeight));
			sf::RectangleShape r_Head(sf::Vector2f(8, r_HeadHeight));
			sf::RectangleShape r_Body(sf::Vector2f(5, r_BodyHeight));
			sf::RectangleShape r_Base(sf::Vector2f(15, 5));
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

			r_Top.setPosition(origin[0] += 10, origin[1] += 10);
			r_Head.setPosition(origin[0] += 2, origin[1] += r_TopHeight);
			r_Body.setPosition(origin[0] += 1.5f, origin[1] += r_HeadHeight);
			r_Base.setPosition(origin[0] -= 4.5f, origin[1] += r_BodyHeight);

		   window.draw(r_Top);
		   window.draw(r_Head);
		   window.draw(r_Body);
		   window.draw(r_Base);

*/



class Pawn : public Piece
{
public:
	Pawn(int x, int y, bool isBlack);
};

Pawn::Pawn(int x, int y, bool isBlack) : Piece(PAWN, x, y, isBlack) {}

/*
*			//Corner of square that piece is on
			origin[0] = 0;
			origin[1] = 0;


			int p_TopRadius = 3;//6
			int p_HatRadius = 7;//14 //8
			int p_BodyHeight = 15;
			int p_BaseHeight = 3;
			int p_BottomHeight = 3;//5 //13

			//should be short af
			sf::CircleShape p_Top(p_TopRadius);
			//triangle hat
			sf::CircleShape p_Hat(p_HatRadius, 3); //(size, 3);
			sf::RectangleShape p_Body(sf::Vector2f(5,p_BodyHeight));
			sf::RectangleShape p_Base(sf::Vector2f(7, p_BaseHeight));
			sf::RectangleShape p_Bottom(sf::Vector2f(9, p_BottomHeight));

			//outlines are needed if we keep the game only 2 colors
			//textures can be put in later
			if (isBlack)
			{
			   p_Top.setFillColor(sf::Color::Black);
			   p_Hat.setFillColor(sf::Color::Black);
			   p_Body.setFillColor(sf::Color::Black);
			   p_Base.setFillColor(sf::Color::Black);
			   p_Bottom.setFillColor(sf::Color::Black);
			   p_Top.setOutlineColor(sf::Color::White);
			   p_Hat.setOutlineColor(sf::Color::White);
			   p_Body.setOutlineColor(sf::Color::White);
			   p_Base.setOutlineColor(sf::Color::White);
			   p_Bottom.setOutlineColor(sf::Color::White);

			}
			else
			{
				p_Top.setFillColor(sf::Color::White);
				p_Hat.setFillColor(sf::Color::White);
				p_Body.setFillColor(sf::Color::White);
				p_Base.setFillColor(sf::Color::White);
				p_Bottom.setFillColor(sf::Color::White);
				p_Top.setOutlineColor(sf::Color::Black);
				p_Hat.setOutlineColor(sf::Color::Black);
				p_Body.setOutlineColor(sf::Color::Black);
				p_Base.setOutlineColor(sf::Color::Black);
				p_Bottom.setOutlineColor(sf::Color::Black);

			}

			p_Top.setPosition(origin[0] += 10, origin[1] += 10);
			p_Hat.setPosition(origin[0] -= p_TopRadius *1.1, origin[1] += (p_TopRadius)-2);
			p_Body.setPosition(origin[0] += p_TopRadius * 1.5, origin[1] += (p_HatRadius));
			p_Base.setPosition(origin[0] -= 1, origin[1] += p_BodyHeight);
			p_Bottom.setPosition(origin[0] -= 1, origin[1] += p_BaseHeight);


			window.draw(p_Top);
			window.draw(p_Hat);
			window.draw(p_Body);
			window.draw(p_Base);
			window.draw(p_Bottom);

*/

#endif // !PIECE_H