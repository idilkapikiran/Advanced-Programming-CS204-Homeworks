#ifndef  IKAPIKIRAN_KAPIKIRAN_IDIL_HW5_INTEGERSET_H
#define  IKAPIKIRAN_KAPIKIRAN_IDIL_HW5_INTEGERSET_H
#include <iostream>
using namespace std;
class IntegerSet
{
private:
	int setSize;
	int *intArray;

public:	
	IntegerSet();//constructor
	~IntegerSet();//destructor
	IntegerSet(int); // constructor with number of elements parameter
	IntegerSet(const IntegerSet &); // deep copy constructor	
	IntegerSet& operator=(const IntegerSet &); // assignment operator (=)
	IntegerSet& operator+=(const IntegerSet &); // += operator
	IntegerSet operator+(const int&)const;// + operator
	IntegerSet operator+(const IntegerSet&)const; // union operator
	bool operator!=(const IntegerSet&); //!=operator
	IntegerSet operator*(const IntegerSet &) const; // intersection operator	

	int getSize() const; // get size of the array
	void setElement(int, int); // set element in specified index
	int getElement(int) const; // get element in specified index
	void SetSize(int); // set size of the array	
};
ostream& operator<<(ostream &output, const IntegerSet&); //ouput displaying operator
bool operator <=(const int&, const IntegerSet&); //check if an integer is in set
bool operator <=(const IntegerSet&, const IntegerSet&); // check if subset operator

#endif
