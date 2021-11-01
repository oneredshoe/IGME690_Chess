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
