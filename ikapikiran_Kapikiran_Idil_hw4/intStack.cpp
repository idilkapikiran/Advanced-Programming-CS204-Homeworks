#include <iostream>
#include "intStackHeader.h"
using namespace std;
//constructor
intStack::intStack()
{
	coordX=0;
	coordY=0;
}

//destructor
intStack::~intStack()
{
	int X, Y; //dummy variables

	while(!isEmpty())
	{
		pop(X, Y); //delete all elements
	}
}

void intStack::push(int coorX, int coorY)
{
	/* Begin: code taken from DynamicStringStack.cpp and updated*/
	stackNode *newNode;
	// Allocate a new node & store Num
	newNode = new stackNode;
	newNode->coordX = coorX;
	newNode->coordY = coorY;
	// If there are no nodes in the list
	// make newNode the first node
	if (isEmpty())
	{
		ptr = newNode;
		newNode->next = NULL;
	}
	else	// Otherwise, insert NewNode before top
	{
		newNode->next = ptr;
		ptr = newNode;
	}
	/* End: code taken from DynamicStringStack.cpp and updated*/
}

void intStack::pop(int& coorX, int& coorY)
{
	/* Begin: code taken from DynamicStringStack.cpp and updated*/	
	stackNode *temp;
	coorX = ptr->coordX;
	coorY = ptr->coordY;
	temp = ptr->next;
	delete ptr;
	ptr = temp;
	/* End: code taken from DynamicStringStack.cpp and updated */
}

bool intStack::isEmpty()
{
	bool state;
	if (ptr == NULL)
	{
		state = true;
	}
	else
	{
		state = false;
	}
	return state;
}