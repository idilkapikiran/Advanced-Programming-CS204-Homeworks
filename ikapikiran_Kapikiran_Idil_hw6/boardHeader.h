#ifndef BOARDHEADER_H
#define BOARDHEADER_H
using namespace std;
class Board
{
private:
	char theBoard[2][6];

public:
	Board();//default constructor
	void displayBoard()const; //displays the current state of the board
	char getOwner(const int&, const int&); // return the char of who owns the cell or empty("-")
	Board& setOwner(const int&, const int&, char); // set the ownership of the cell
	bool isFull(); //return true if the board is full
	int countOwnedCells(char); //return the number of cells occupied by the given owner
};
#endif