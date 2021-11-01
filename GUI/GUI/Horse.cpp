#include "Piece.h"

class Horse : public Piece {
public:
	Horse(int x, int y, bool isBlack);
	vector<array<int, 2>>PossibleMoves(int board[8][8]) override;
};

Horse::Horse(int x, int y, bool isBlack) : Piece(HORSE, x, y, isBlack){}

vector<array<int, 2>> Horse::PossibleMoves(int board[8][8])
{
	vector<array<int, 2>> retVal;

	if (m_position[0] + 2< 8) {
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
}
