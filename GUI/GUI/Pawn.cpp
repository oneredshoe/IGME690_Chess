#include "Piece.h"
#include <cmath>  



class Pawn: public Piece
{
public:
	Pawn(int x, int y, bool isBlack);
	bool Move(int position[], int board[8][8]) override; 
	vector<array<int, 2>>PossibleMoves(int board[8][8]) override;

private:
	bool m_hasMoved;
};

Pawn::Pawn(int x, int y, bool isBlack) : Piece(PAWN, x, y, isBlack){
	m_hasMoved = false;
}

bool Pawn::Move(int position[], int board[8][8]) {
	vector <array<int, 2>> check = PossibleMoves(board);

	for (array<int, 2> possibility : check) {
		if (position[0] == possibility[0] && position[1] == possibility[1]) {
			m_hasMoved = true;
			return true;
		}
	}

	return false;
}

vector<array<int, 2>> Pawn::PossibleMoves(int board[8][8]) {
	vector<array<int, 2>> retVal;

	int multiplier = 1;
	if (!m_isBlack) multiplier = -1;

	//make sure not at the dge of the board
	if (m_position[0] + multiplier >= 8 || m_position[0] + multiplier < 0) {
		return retVal;
	}

	//see if u can move forward
	if (board[m_position[0] + multiplier][m_position[1]] == 2) {
		retVal.push_back({ m_position[0] + multiplier, m_position[1] });
		if (!m_hasMoved && board[m_position[0] + multiplier * 2][m_position[1]] == 2 && m_position[0] + multiplier*2 < 8 && m_position[0] + multiplier*2 >= 0) {
			retVal.push_back({ m_position[0] + multiplier * 2, m_position[1] });
		}
	}

	//see if u can attack
	if (m_position[1] + 1 < 8 && m_position[1] + 1 >= 0 && board[m_position[0] + multiplier][m_position[1] + 1] == !m_isBlack) {
		retVal.push_back({ m_position[0] + multiplier, m_position[1] + 1 });
	}

	if (m_position[1] - 1 < 8 && m_position[1] - 1 >= 0 && board[m_position[0] + multiplier][m_position[1] - 1] == !m_isBlack) {
		retVal.push_back({ m_position[0] + multiplier, m_position[1] - 1 });
	}
	return retVal;
}
