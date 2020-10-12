#ifndef PLAYERHEADER_H
#define PLAYERHEADER_H
#include "boardHeader.h"
using namespace std;
class Player
{
private:	
		Board &board; //Referenced variable (shared object between two players)
		char playerChar;
		int direction;
		int row, column;
public:
	Player();
	Player(Board &myBoard, char p, int d) //constructor
		:board(myBoard), playerChar(p), direction(d), row(0), column(0)
	{}
	Player& move(const int&);
	void claimOwnership();//set ownership
	bool wins();//return true if any player wins
	int getRow(); //return player's row
	int getCol(); //return player's column
};
#endif