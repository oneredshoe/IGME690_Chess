#include "Piece.h"
#include <cmath>  
#include <string>
#include <vector>
#include <array>

using namespace std;

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
		if (board[posY][m_position[1]] != (int)m_isBlack) retVal.push_back({ posY, m_position[1] });
		if (negX >= 0 && board[posY][negX] != (int)m_isBlack) retVal.push_back({ posY, negX });
	}
	if (negY >= 0) {
		if (board[negY][m_position[1]] != (int)m_isBlack) retVal.push_back({ negY, m_position[1] });
		if (posX < 8 && board[negY][posX] != (int)m_isBlack) retVal.push_back({ negY, posX });
	}

	return retVal;
}

vector<array<int, 2>> Bishop::PossibleMoves(int board[8][8])
{
	return CheckDiagonals(board);
}

vector<array<int, 2>> Castle::PossibleMoves(int board[8][8])
{
	return CheckSides(board);
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
		if (!m_hasMoved && board[m_position[0] + multiplier * 2][m_position[1]] == 2 && m_position[0] + multiplier * 2 < 8 && m_position[0] + multiplier * 2 >= 0) {
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


vector<array<int, 2>> Horse::PossibleMoves(int board[8][8])
{
	vector<array<int, 2>> retVal;

	if (m_position[0] + 2 < 8) {
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