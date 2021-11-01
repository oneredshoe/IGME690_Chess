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