#include "Piece.h"
#include <cmath>  

class Pawn: public Piece
{
public:
	Pawn(int x, int y, bool isBlack);
	bool Move(int* position, int board[8][8]) override;

private:
	bool m_hasMoved;
};

Pawn::Pawn(int x, int y, bool isBlack) : Piece(PAWN, x, y, isBlack){
	m_hasMoved = false;
}

bool Pawn::Move(int* position, int board[8][8]) {
	int numDif = position[0] - m_position[0];
	int letterDif = position[1] - m_position[1];

	if (!m_isBlack) {
		numDif = -numDif;
	}

	if (numDif <= 0) {
		return false;
	}

	if (m_hasMoved && numDif > 1) {
		return false;
	}
	else if (!m_hasMoved && (numDif > 2 || (numDif == 2 && letterDif != 0))) {
		return false;
	}

	if (abs(letterDif) > 1) {
		return false;
	}
	else if (abs(letterDif) == 1 && board[position[0]][position[1]] != (int)(!m_isBlack)) {
		return false;
	}
	else if (board[position[0]][position[1]] != 3) {
		return false;
	}

	m_position[0] = position[0];
	m_position[1] = position[1];

	return true;
}
