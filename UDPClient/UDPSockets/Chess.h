#ifndef CHESS_H
#define CHESS_H
#include "Board.h"
#include <unordered_map>

using namespace std;

class Chess
{
public:
	Chess(Board& board);
	~Chess();
	void Update();
private:
	Board& m_board;
	unordered_map<string, int> white;
	unordered_map<string, int> black;

};

Chess::Chess(Board& board) : m_board(board)
{


}

Chess::~Chess()
{
}

#endif // !CHESS_H
