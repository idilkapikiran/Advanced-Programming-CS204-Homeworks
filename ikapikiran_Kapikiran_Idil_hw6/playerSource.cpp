#include "playerHeader.h"
#include "boardHeader.h"
#include <iostream>
using namespace std;

Player& Player::move(const int& cellToMove)
{
	if(direction==1)//clockwise
	{
		int count=cellToMove;
		while(count!=0)
		{
			if(row==1 && column==0) //if the cell is on the edge
			{
				row=0; //go upper cell
				column=0;
			}
			else if(row==0 && column==5) //if the cell is on the edge
			{
				row=1; //go  downer cell
				column=5;
			}
			else if(row==0) //if the cell is on upper row increment the column
			{
				column+=1;
			}
			else if(row==1) //if the cell is on down row decrement the column
			{
				column-=1;
			}
			count--;
		}
		if (board.getOwner(row, column)=='-')
		{
			board.setOwner(row, column, this->playerChar);
		}
	}
	else if(direction==0)//counter-clockwise
	{
		int count=cellToMove;
		while(count!=0)
		{
			if(row==1 && column==5) //if the cell is on downer edge go up
			{
				row=0;
				column=5;
			}
			else if(row==0 && column==0) // if cell is on starting point go down
			{
				row=1;
				column=0;
			}
			else if(row==0) //if the cell is on down row decrement the column
			{
				column-=1;
			}
			else if(row==1) //if the cell is on upper row increment the column
			{
				column+=1;
			}
			count--;
		}
		if (board.getOwner(row, column)=='-') //if there is no owner to the cell, own the cell
		{
			board.setOwner(row, column, this->playerChar);
		}
	}
	return *this;
}
void Player::claimOwnership()
{
	if(board.getOwner(row, column)=='-') //if the cell is empty own the cell
	{
		board.setOwner(row, column, this->playerChar);
	}
}
bool Player::wins() //if the player wins return true
{
	if(board.countOwnedCells(this->playerChar)==7)
	{
		return true;
	}
	return false;
}
int Player::getRow()
{
	return row;
}
int Player::getCol()
{
	return column;
}