#include "Piece.h"

class King : public Piece {
public:
	King(int x, int y, bool isBlack);
	vector<array<int, 2>>PossibleMoves(int board[8][8]) override;
};

King::King(int x, int y, bool isBlack) : Piece(KING, x, y, isBlack) {}

vector<array<int, 2>> King::PossibleMoves(int board[8][8])
{
	vector<array<int, 2>> retVal;
	
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
		if (board[posY][m_position[1]] != (int)m_isBlack) retVal.push_back({ posY, m_position[1]});
		if (negX >= 0 && board[posY][negX] != (int)m_isBlack) retVal.push_back({ posY, negX });
	}
	if (negY >= 0) {
		if (board[negY][m_position[1]] != (int)m_isBlack) retVal.push_back({ negY, m_position[1] });
		if (posX < 8 && board[negY][posX] != (int)m_isBlack) retVal.push_back({ negY, posX });
	}

	return retVal;
}