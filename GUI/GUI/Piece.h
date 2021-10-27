#ifndef PIECE_H
#define PIECE_H
#include <string>
#include <vector>
#include <array>

using namespace std;

enum PieceType { HORSE, CASTLE, BISHOP, PAWN, KING, QUEEN };

enum Letters {A = 0, B = 1, C = 2, D = 3, E = 4, F = 5, G = 6, H = 7};

class Piece
{
public:
	Piece(PieceType name, int x, int y, bool isBlack);
	~Piece();
	PieceType getName();
	int* getPosition();
	bool isBlack();

	virtual bool Move(int position[], int board[8][8]);
	virtual vector< array<int, 2>>PossibleMoves(int board[8][8]);
	
protected:
	PieceType m_name;
	int m_position[2]{0, 0};
	bool m_isBlack;
};

Piece::Piece(PieceType name, int x, int y, bool isBlack )
{
	m_name = name;

	m_position[0] = x;
	m_position[1] = y;
	m_isBlack = isBlack;
}

Piece::~Piece()
{
	delete []m_position;
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

bool Piece::Move(int position[], int board[8][8]) {
	vector <array<int, 2>> check = PossibleMoves(board);

	for (array<int, 2> possibility : check) {
		if (position[0] == possibility[0] && position[1] == possibility[1]) {
			return true;
		}
	}

	return false;
}
#endif // !PIECE_H