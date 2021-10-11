#ifndef PIECE_H
#define PIECE_H
#include <string>

using namespace std;

enum PieceType { HORSE, CASTLE, BISHOP, PAWN, KING, QUEEN };

class Piece
{
public:
	Piece(PieceType name, int x, int y, bool isBlack);
	~Piece();
	PieceType getName();
	int* getPosition();
	bool isBlack();

	virtual bool Move(int position[]);
	virtual int* PossibleMoves();
	
protected:
	PieceType m_name;
	int m_position[2]{0, 0};
	bool m_isBlack;
};

Piece::Piece(PieceType name, int x, int y, bool isBlack)
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
#endif // !PIECE_H