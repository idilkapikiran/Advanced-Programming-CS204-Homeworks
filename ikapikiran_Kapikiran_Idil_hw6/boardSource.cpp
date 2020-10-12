#include <iostream>
#include "boardHeader.h"
using namespace std;
//default constructor
Board::Board()
{
	for(int i=0; i< 2;i++)
	{
		for (int j = 0; j < 6; j++)
		{
			theBoard[i][j]='-';
		}	
	}
}
//prints board
void Board::displayBoard()const
{
	for(int i=0; i< 2;i++)
	{
		for (int j = 0; j < 6; j++)
		{
			cout << theBoard[i][j] << " ";
		}	
		cout << endl;
	}
}
//return the owner of that cell
char Board::getOwner(const int& row, const int& column)
{
	return (theBoard[row][column]);
}
//set the owner to the cell
Board& Board::setOwner(const int& row, const int& column, char owner)
{
	theBoard[row][column]=owner;
	return *this;
}
// if the board is full return true
bool Board::isFull()
{
	for(int i=0; i< 2;i++)
	{
		for (int j = 0; j < 6; j++)
		{
			if(theBoard[i][j]=='-')
			{
				return false;
			}
		}	
	}
	return true;
}
//return the amount of cells the player has
int Board::countOwnedCells(char owner)
{
	int count=0;
	for(int i=0; i< 2;i++)
	{
		for (int j = 0; j < 6; j++)
		{
			if(theBoard[i][j]==owner)
			{
				count++;
			}
		}	
	}
	return count;
}
