#include "Piece.h"

class Castle : public Piece{
public:
	Castle(int x, int y, bool isBlack);
	vector<array<int, 2>>PossibleMoves(int board[8][8]) override;
};

Castle::Castle(int x, int y, bool isBlack) : Piece(CASTLE, x, y, isBlack) {}

vector<array<int, 2>> Castle::PossibleMoves(int board[8][8])
{
	vector<array<int, 2>> retVal;

	for (int i = m_position[0] + 1; i < 8; i++) {
		if (board[i][m_position[1]] == 2) {
			retVal.push_back({ i, m_position[1] });
		}else if (board[i][m_position[1]] == !isBlack) {
			retVal.push_back({ i, m_position[1] });
			break;
		}
	}

	for (int i = m_position[0] - 1; i >= 0; i--) {
		if (board[i][m_position[1]] == 2) {
			retVal.push_back({ i, m_position[1] });
		}
		else if (board[i][m_position[1]] == !isBlack) {
			retVal.push_back({ i, m_position[1] });
			break;
		}
	}

	for (int i = m_position[1] + 1; i < 8; i++) {
		if (board[m_position[0]][i] == 2) {
			retVal.push_back({ m_position[0], i });
		}
		else if (board[m_position[0]][i] == !isBlack) {
			retVal.push_back({ m_position[0], i });
			break;
		}
	}

	for (int i = m_position[1] - 1; i >= 0; i--) {
		if (board[m_position[0]][i] == 2) {
			retVal.push_back({ m_position[0], i });
		}
		else if (board[m_position[0]][i] == !isBlack) {
			retVal.push_back({ m_position[0], i });
			break;
		}
	}

	return retVal;
}
