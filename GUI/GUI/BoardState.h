#ifndef BOARDSTATE_H
#define BOARDSTATE_H

#include "Horse.cpp"
#include "King.cpp"
#include "Queen.cpp"
#include "Bishop.cpp"
#include "Castle.cpp"
#include "Pawn.cpp"
#include "Horse.cpp"
#include <map>


class BoardState
{
public:
	BoardState();
	~BoardState();
	bool movePiece(int startPos[], int endPos[]);

private:
	int m_board[8][8];
	map<int, Piece> m_pieces;

	int whiteKingPos[2];
	int blackKingPos[2];

	Piece possibleDeath;

	bool isBlackTurn;

	bool gameOver;
	bool didBlackWin;
};

BoardState::BoardState(): possibleDeath(NONE, -1, -1, false){

	gameOver = false;
	didBlackWin = true;

	isBlackTurn = false;

	for (int i = 2; i < 6; i++) {
		for (int j = 0; j < 8; j++) {
			m_board[i][j] = 2;
		}
	}

	for (int i = 0; i < 2; i++) {
		for (int j = 0; j < 8; j++) {
			m_board[i][j] = 1;
		}
	}

	for (int i = 6; i < 8; i++) {
		for (int j = 0; j < 8; j++) {
			m_board[i][j] = 1;
		}
	}

	//pawns
	for (int i = 8; i < 16; i++) {
		m_pieces.insert(make_pair(i, Pawn(1, i, true)));
		m_pieces.insert(make_pair(48 + i, Pawn(6, i, false)));
	}

	//CASTLE
	m_pieces.insert(make_pair(0, Castle(0, 0, true)));
	m_pieces.insert(make_pair(7, Castle(0, 7, true)));

	m_pieces.insert(make_pair(56, Castle(7, 0, false)));
	m_pieces.insert(make_pair(63, Castle(7, 7, false)));

	//horse
	m_pieces.insert(make_pair(1, Horse(0, 1, true)));
	m_pieces.insert(make_pair(6, Horse(0, 6, true)));

	m_pieces.insert(make_pair(57, Horse(7, 1, false)));
	m_pieces.insert(make_pair(62, Horse(7, 6, false)));

	//bishop
	m_pieces.insert(make_pair(2, Bishop(0, 2, true)));
	m_pieces.insert(make_pair(6, Bishop(0, 5, true)));

	m_pieces.insert(make_pair(58, Bishop(7, 2, false)));
	m_pieces.insert(make_pair(61, Bishop(7, 5, false)));

	//queen
	m_pieces.insert(make_pair(3, Queen(0, 3, true)));
	m_pieces.insert(make_pair(59, Queen(7, 3, false)));

	//king
	m_pieces.insert(make_pair(4, King(0, 4, true)));
	m_pieces.insert(make_pair(60, King(7, 4, false)));

	whiteKingPos[0] = 7;
	whiteKingPos[1] = 4;

	blackKingPos[0] = 0;
	blackKingPos[1] = 4;

}

bool BoardState::movePiece(int startPos[], int endPos[]) {
	//make sure piece is correct turn
	if (m_board[startPos[0]][startPos[1]] != (int)isBlackTurn) {
		return false;
	}

	int endPosValue = m_board[endPos[0]][endPos[1]];

	bool moved = m_pieces[startPos[0] * 8 + startPos[1]].Move(endPos, m_board);

	if (!moved) {
		return false;
	}

	if (endPosValue != 2) {
		if (blackKingPos[0] == endPos[0] && blackKingPos[1] == endPos[1]) {
			didBlackWin = false;
			gameOver = true;
		}

		if (whiteKingPos[0] == endPos[0] && whiteKingPos[1] == endPos[1]) {
			didBlackWin = true;
			gameOver = true;
		}

		
		m_pieces[endPos[0] * 8 + endPos[1]] = m_pieces[startPos[0] * 8 + startPos[1]];

		m_pieces.erase(startPos[0] * 8 + startPos[1]);

		if (m_pieces[endPos[0] * 8 + endPos[1]].getName() == KING) {
			
		}
		
	}

	return true;

}

BoardState::~BoardState()
{
}

#endif
