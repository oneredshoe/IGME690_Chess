#pragma once
#include <string>


using namespace std;

class PlayerInput{
private:
	struct ChessPiece {
		//Name being knight1, knight2, pawn1-8, etc
		string name;
		//a-h
		char xPos;
		//1-8
		int yPos;

		ChessPiece() : name(""), xPos('0'), yPos(0) {};
		ChessPiece(string _name, char _xPos, int _yPos) : name(_name), xPos(_xPos), yPos(_yPos) {};
	};

public:
	//Rules
	//If Knight, math to L shape
	//pawn move forward
	//

};