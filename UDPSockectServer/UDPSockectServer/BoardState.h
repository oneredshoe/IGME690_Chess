#ifndef BOARDSTATE_H
#define BOARDSTATE_H

#include "Piece.h"
#include <iostream>
#include <map>


class BoardState
{
public:
	BoardState();
	~BoardState();
	bool movePiece(int startPos[], int endPos[]);
	bool getGameOver();
	bool getWinner();

private:
	int m_board[8][8];
	Piece m_pieces[8][8];

	int whiteKingPos[2];
	int blackKingPos[2];

	bool isBlackTurn;

	bool gameOver;
	bool didBlackWin;
};

 BoardState::BoardState(){

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
			m_board[i][j] = 0;
		}
	}

	for (int i = 0; i < 8; i++) {
		for (int j = 0; j < 8; j++) {
			cout << m_board[i][j];
		}
		cout << endl;
	}

	//pawns
	for (int i = 0; i < 8; i++) {
		m_pieces[1][i] = Pawn(1, i, true);
		m_pieces[6][i] = Pawn(6, i, false);
	}

	//CASTLE
	m_pieces[0][0] = Castle(0, 0, true);
	m_pieces[0][7] = Castle(0, 7, true);

	m_pieces[7][0] = Castle(7, 0, false);
	m_pieces[7][7] = Castle(7, 7, false);

	//horse
	m_pieces[0][1] = Horse(0, 1, true);
	m_pieces[0][6] = Horse(0, 6, true);

	m_pieces[7][1] = Horse(7, 1, false);
	m_pieces[7][1] = Horse(7, 6, false);

	//bishop
	m_pieces[0][2] = Bishop(0, 2, true);
	m_pieces[0][5] = Bishop(0, 5, true);

	m_pieces[7][2] = Bishop(7, 2, false);
	m_pieces[7][5] = Bishop(7, 5, false);

	//queen
	m_pieces[0][3] = Queen(0, 3, true);
	m_pieces[7][3] = Queen(7, 3, false);

	//king
	m_pieces[0][4] = King(0, 4, true);
	m_pieces[7][4] = King(7, 4, false);

	whiteKingPos[0] = 7;
	whiteKingPos[1] = 4;

	blackKingPos[0] = 0;
	blackKingPos[1] = 4;

}

/// <summary>
/// move a piece and will switch turns if the move is successfull
/// </summary>
/// <param name="startPos"></param>
/// <param name="endPos"></param>
/// <returns></returns>
bool BoardState::movePiece(int startPos[], int endPos[]) {
	//make sure piece is correct turn
	for (int i = 0; i < 8; i++) {
		for (int j = 0; j < 8; j++) {
			cout << m_board[i][j];
		}
		cout << endl;
	}

	if (m_board[startPos[0]][startPos[1]] != (int)isBlackTurn) {
		return false;
	}

	int endPosValue = m_board[endPos[0]][endPos[1]];

	cout << m_pieces[startPos[0]][startPos[1]].getName() << endl;

	vector<array<int, 2>> check =  m_pieces[startPos[0]][startPos[1]].PossibleMoves(m_board);
	cout << "check" << check.size() << endl;
	bool moved = false;
	for (array<int, 2> possibility : check) {
		cout << "hello" << possibility[0] << possibility[1] << endl;
		if (endPos[0] == possibility[0] && endPos[1] == possibility[1]) {
			moved = true;
			break;
		}
	}

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

		
		m_pieces[endPos[0]][endPos[1]] = m_pieces[startPos[0]][startPos[1]];

		m_pieces[startPos[0]][startPos[1]] = Piece();

		//see if we have to update the king pos
		if (m_pieces[endPos[0]][endPos[1]].getName() == KING) {
			if (isBlackTurn) {
				blackKingPos[0] = endPos[0];
				blackKingPos[1] = endPos[1];
			}else{
				whiteKingPos[0] = endPos[0];
				whiteKingPos[1] = endPos[1];
			}
		}
		
	}

	isBlackTurn = !isBlackTurn;

	return true;

}

bool BoardState::getGameOver()
{
	return gameOver;
}

//returns true if black won the game
bool BoardState::getWinner() {
	return didBlackWin;
}

BoardState::~BoardState()
{
}

#endif
