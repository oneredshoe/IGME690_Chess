#include "Piece.h"

class Queen : public Piece {
public:
	Queen(int x, int y, bool isBlack);
	vector<array<int, 2>>PossibleMoves(int board[8][8]) override;
};

Queen::Queen(int x, int y, bool isBlack) : Piece(QUEEN, x, y, isBlack) {}

vector<array<int, 2>> Queen::PossibleMoves(int board[8][8])
{
	vector<array<int, 2>> sides = CheckSides(board);
	vector<array<int, 2>> diagonals = CheckDiagonals(board);

	vector<array<int, 2>> retVal;
	retVal.reserve(sides.size() + diagonals.size());
	retVal.insert(retVal.end(), sides.begin(), sides.end());
	retVal.insert(retVal.end(), diagonals.begin(), diagonals.end());

	return retVal;
}