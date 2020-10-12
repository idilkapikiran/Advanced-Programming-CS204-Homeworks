#ifndef INTSTACKHEADER_H
#define INTSTACKHEADER_H
struct stackNode
{
	int coordX, coordY;
	stackNode *next;
	stackNode::stackNode() //default constructor
		:coordX(0), coordY(0), next(NULL)
	{}
	stackNode::stackNode(int x, int y, stackNode *next)//constructor
		:coordX(x), coordY(y), next(next)
	{}
};
class intStack
{
private:
	int coordX;
	int coordY;
	stackNode *ptr;
public:
	intStack();//constructor
	~intStack();//destructor
	void push(int, int); //push the coordinates to the stack
	void pop(int &, int &); //remove the coordinates with the principle last in first out
	bool isEmpty(void); //return true if stack is empty
};
#endif