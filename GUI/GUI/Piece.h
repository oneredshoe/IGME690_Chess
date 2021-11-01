#ifndef PIECE_H
#define PIECE_H
#include <string>
#include <vector>
#include <array>

/*
Broad
  A  B  C  D  E  F  G  H
  0  1  2  3  4  5  6  7
0
1	[black pieces]
2
3
4
5
6	[white pieces]
7

a white piece is denoted as 0
a black piece is denoted as 1
a empty square is denotd as 2

*/

using namespace std;

enum PieceType { HORSE, CASTLE, BISHOP, PAWN, KING, QUEEN, NONE };

enum Letters {A = 0, B = 1, C = 2, D = 3, E = 4, F = 5, G = 6, H = 7};

class Piece
{
public:
	Piece(PieceType name, int x, int y, bool isBlack);
	~Piece();
	PieceType getName();
	int* getPosition();
	bool isBlack();

	
	virtual void Draw();
	virtual bool Move(int position[], int board[8][8]);
	virtual vector< array<int, 2>>PossibleMoves(int board[8][8]);
	
protected:
	PieceType m_name;
	int m_position[2]{0, 0};
	bool m_isBlack;
	vector<array<int, 2>> CheckSides( int board[8][8]);
	vector<array<int, 2>> CheckDiagonals(int board[8][8]);
};

Piece::Piece(PieceType name, int x, int y, bool isBlack )
{
	m_name = name;

	m_position[0] = x;
	m_position[1] = y;
	m_isBlack = isBlack;
}

Piece::~Piece()
{
	delete []m_position;
}

PieceType Piece::getName() {
	return m_name;
}

int* Piece::getPosition() {
	return m_position;
}

bool Piece::isBlack() {
	return m_isBlack;
}

 vector<array<int, 2>> Piece::CheckSides( int board[8][8])
{
	vector<array<int, 2>> retVal;

	for (int i = m_position[0] + 1; i < 8; i++) {
		if (board[i][m_position[1]] == 2) {
			retVal.push_back({ i, m_position[1] });
		}
		else if (board[i][m_position[1]] != (int)m_isBlack) {
			retVal.push_back({ i, m_position[1] });
			break;
		}
	}

	for (int i = m_position[0] - 1; i >= 0; i--) {
		if (board[i][m_position[1]] == 2) {
			retVal.push_back({ i, m_position[1] });
		}
		else if (board[i][m_position[1]] != (int)m_isBlack) {
			retVal.push_back({ i, m_position[1] });
			break;
		}
	}

	for (int i = m_position[1] + 1; i < 8; i++) {
		if (board[m_position[0]][i] == 2) {
			retVal.push_back({ m_position[0], i });
		}
		else if (board[m_position[0]][i] != (int)m_isBlack) {
			retVal.push_back({ m_position[0], i });
			break;
		}
	}

	for (int i = m_position[1] - 1; i >= 0; i--) {
		if (board[m_position[0]][i] == 2) {
			retVal.push_back({ m_position[0], i });
		}
		else if (board[m_position[0]][i] != (int)m_isBlack) {
			retVal.push_back({ m_position[0], i });
			break;
		}
	}

	return retVal;
}

 vector<array<int, 2>> Piece::CheckDiagonals(int board[8][8])
{
	 vector<array<int, 2>> retVal;

	 bool first = true, second = true, third = true, forth = true;

	 for (int i = 1; i < 8; i++) {

		 if (first && m_position[0] + i < 8 && m_position[1] + i < 8) {
			 if (board[m_position[0] + i][m_position[1] + i] != (int)m_isBlack) {
				 retVal.push_back({ m_position[0] + i , m_position[1] + i });
			 }
			 else {
				 first = false;
			 }
		 }

		 if (second && m_position[0] + i < 8 && m_position[1] - i >= 0) {
			 if(board[m_position[0] + i][m_position[1] - i] != (int)m_isBlack) {
				 retVal.push_back({ m_position[0] + i , m_position[1] - i });
			 }
			 else {
				second = false;
			 }
		 }

		 if (third && m_position[0] - i < 8 && m_position[1] - i >= 0) {
			 if (board[m_position[0] - i][m_position[1] - i] != (int)m_isBlack) {
				 retVal.push_back({ m_position[0] - i , m_position[1] - i });
			 }
			 else {
				 third = false;
			 }
		 }

		 if (forth && m_position[0] - i < 8 && m_position[1] + i >= 0) {
			 if (board[m_position[0] - i][m_position[1] + i] != (int)m_isBlack) {
				 retVal.push_back({ m_position[0] + i , m_position[1] - i });
			 }
			 else {
				 forth = false;
			 }
		 }

	 }

	 return retVal;
}

bool Piece::Move(int position[], int board[8][8]) {
	vector <array<int, 2>> check = PossibleMoves(board);

	for (array<int, 2> possibility : check) {
		if (position[0] == possibility[0] && position[1] == possibility[1]) {
			return true;
		}
	}

	return false;
}

void Piece::Draw()
{
	
}
#endif // !PIECE_H