
#ifndef _HEADER_H
#define _HEADER_H
#include <string>
using namespace std;

struct creditCardNode //singly
{ 
	string creditCardNo;
	creditCardNode * next; 
	creditCardNode::creditCardNode()
		:creditCardNo(0), next(NULL)
	{}

	creditCardNode::creditCardNode(const string &s, creditCardNode * next)
		: creditCardNo(s), next(next)
	{}
};

struct expirationNode //doubly
{
	int month, year;
	creditCardNode * cHead;
	expirationNode * next; 
	expirationNode * prev;
	expirationNode::expirationNode()
		:month(0), year(0), cHead(NULL), next(NULL), prev(NULL)
	{}

	expirationNode::expirationNode(int m, int y, creditCardNode * cHead, expirationNode * next, expirationNode * prev)
		: month(m), year(y), cHead(cHead), next(next), prev(prev)
	{}
};
class CardList 
{ 
public:
	CardList(); //default constructor that creates an empty list 
	
	void opt2 (); //displays entire structure in chronological order
	void opt3 (); //displays entire structure in reverse chronological order
	void opt4 ( int &); //displays all of the occurrences of the given card number
	void opt5 (int &); //deletes all nodes up to and including given expiration date 
	void deleteNodes (); //deletes the entire structure
	void insertNodeAndCard(ifstream &);//inserts a new card to the structure in sorted fashion
private: 
	expirationNode * head;
	expirationNode * tail;
};

#endif