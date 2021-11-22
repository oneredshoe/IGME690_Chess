#pragma once
#define SFML_Static
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>

#ifndef PIECE_H
#define PIECE_H


#include <string>
#include <vector>
#include <array>

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
	Piece(PieceType name, int x, int y, bool isBlack, sf::RenderWindow& win);
	Piece(sf::RenderWindow& win);
	~Piece();
	PieceType getName();
	int* getPosition();
	bool isBlack();
	int getGlobalMultiplier();

	

	virtual bool Move(int position[], int board[8][8]);
	virtual vector<array<int, 2>>PossibleMoves(int board[8][8]);
	virtual void Draw();
	
protected:
	PieceType m_name;
	int m_position[2]{0, 0};
	bool m_isBlack;
	sf::RenderWindow& m_window;
	vector<array<int, 2>> CheckSides( int board[8][8]);
	vector<array<int, 2>> CheckDiagonals(int board[8][8]);
};

class Horse : public Piece {
public:
	Horse(int x, int y, bool isBlack, sf::RenderWindow& win);
	vector<array<int, 2>>PossibleMoves(int board[8][8]) override;
	void Draw();
};
class King : public Piece {
public:
	King(int x, int y, bool isBlack, sf::RenderWindow& win);
	vector<array<int, 2>>PossibleMoves(int board[8][8]) override;
	void Draw();
};

class Queen : public Piece {
public:
	Queen(int x, int y, bool isBlack, sf::RenderWindow& win);
	vector<array<int, 2>>PossibleMoves(int board[8][8]) override;
	void Draw();
};
class Bishop : public Piece {
public:
	Bishop(int x, int y, bool isBlack, sf::RenderWindow& win);
	vector<array<int, 2>>PossibleMoves(int board[8][8]) override;
	void Draw();
};

class Castle : public Piece {
public:
	Castle(int x, int y, bool isBlack, sf::RenderWindow& win);
	vector<array<int, 2>>PossibleMoves(int board[8][8]) override;
	void Draw();
};
class Pawn : public Piece
{
public:
	Pawn(int x, int y, bool isBlack, sf::RenderWindow& win);
	bool Move(int position[], int board[8][8]) override;
	vector<array<int, 2>>PossibleMoves(int board[8][8]) override;
	void Draw();

private:
	bool m_hasMoved;
};

#endif // !PIECE_H