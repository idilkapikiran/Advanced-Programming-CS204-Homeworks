#include "ikapikiran_Kapikiran_Idil_hw5_IntegerSet.h"
#include <iostream>

using namespace std;
//default constructor
IntegerSet::IntegerSet()
{
	setSize=0;
	intArray=new int[];
}
//constructor with parameters
IntegerSet::IntegerSet(int arraySize)
{	
	setSize = arraySize;
	intArray= new int[arraySize];
	for (int i = 0; i < arraySize; i++)
	{
		intArray[i]=i;
	}
}
//deep copy constructor
IntegerSet::IntegerSet(const IntegerSet & copySet)
{
	setSize = copySet.setSize;
	intArray = new int[setSize]; // deep copy

	for(int i = 0; i < setSize; i++)
	{
		intArray[i] = copySet.intArray[i]; //copy the elements
	}
}
//destructor
IntegerSet::~IntegerSet()
{	
	delete[] intArray;
	setSize = 0;
}
// set element in the specified index
void IntegerSet::setElement(int index, int element)
{
	intArray[index] = element;
}
// get element in the specified index
int IntegerSet::getElement(int index) const
{
	return intArray[index];
}
// set size of the set
void IntegerSet::SetSize(int arraySize)
{
	setSize = arraySize;
	intArray = new int[setSize];
}
// get size of the set
int IntegerSet::getSize() const
{
	return setSize;
}
//add rhs to the array itself
IntegerSet& IntegerSet::operator += (const IntegerSet & rhs)
{
	*this=*this+rhs; // add the set in the rhs to the set in the lhs
	return *this; //retur the lhs list with rhs's elements in it
}
//union of two sets 
IntegerSet IntegerSet::operator+(const IntegerSet &rhs)const
{
	IntegerSet unionSet(setSize);

	for (int i = 0; i < setSize; i++) 
	{
		unionSet.intArray[i]=intArray[i]; //add the elements of lhs to unionSet
	}
	for (int j = 0; j < rhs.setSize; j++)
	{
		unionSet=unionSet+rhs.intArray[j]; // add the elements of rhs to unionSet, if they have same elements + operator will filter
	}
	return unionSet;
}
//adding new integer to a set
IntegerSet IntegerSet::operator+(const int& rhs) const
{
	bool flag=0;
	for (int i = 0; i < setSize; i++)
	{
		if(intArray[i] == rhs)
		{
			flag=1;
		}
	}
	if(flag==1) //if the integer is already in the set, don't add
	{
		return *this; //return the set as it is
	}
	else
	{
		IntegerSet Set(setSize+1); //create a set

		for(int i = 0; i < setSize; i++)
		{
			Set.intArray[i] = intArray[i]; // assign content
		}
		Set.intArray[setSize]=rhs;//last index would be the integer assaigned
		return Set; //return the element added set
	}	
}
// assaignment operator to assaign lhs to rhs
IntegerSet & IntegerSet::operator = (const IntegerSet & rhs)
{
	/* Begin: code taken from MathVector.cpp and updated*/
	if (this != &rhs) // if they are not already equal
	{
		// first delete left hand side
		setSize = 0;
		delete[] intArray;

		// create new vector for left hand side
		setSize = rhs.setSize;
		intArray = new int[setSize];

		for(int i = 0; i < setSize; i++)
		{
			intArray[i] = rhs.intArray[i]; // assign content
		}
	}
	return *this;
	/* End: code taken from MathVector.cpp and updated */	
}
//!= operator checks if two integer sets are equal
bool IntegerSet::operator != (const IntegerSet & rhs)
{
	int size=0;
	for(int i = 0; i < setSize; i++)  
	{  
		for(int j = 0; j < rhs.setSize; j++)
		{ 
			if (getElement(i) == rhs.getElement(j)) //if element in lhs is equal to element in rhs
			{
				size++;//increment size for same element 
			}
		}
	}
	return !(size==rhs.setSize); //if two sets are equal then they must have same size, and this size must be equal to "size"
}
// ostream operator to display
ostream& operator << (ostream &output, const IntegerSet &IntSet)
{
	bool flag=true;
	output << "{";
	for(int i=0;i < IntSet.getSize();i++)
	{		
		if(flag==false)
		{
			output << ", ";
		}
		output << IntSet.getElement(i);
		flag=false;
	}
	output << "}" <<endl;

	return output;
}
// find the intersection of sets
IntegerSet IntegerSet::operator *(const IntegerSet & rhs) const
{	
	int counter =0;
	for(int j=0;j< setSize;j++)
	{
		for(int i=0;i< rhs.setSize;i++)
		{
			if(intArray[j]==rhs.intArray[i])
			{
				counter++; // find the count of same elements in both sets to create a set and know its size
			}		
		}	
	}
	IntegerSet intersectionSet(counter);
	int count =0;
	for(int j=0;j< setSize;j++)
	{
		for(int i=0;i< rhs.setSize;i++)
		{
			if(intArray[j]==rhs.intArray[i])
			{
				intersectionSet.intArray[count]=rhs.intArray[i];//add the elements to intersectionSet
				count++;
			}
		}		
	}
	return intersectionSet;
}
//check if lhs is subset of rhs
//if set in lhs has at least one equivalent element with the one in rhs, return true
bool operator <=(const IntegerSet & lhs, const IntegerSet & rhs)
{
	int counter=0;
	for(int j=0;j< lhs.getSize();j++)
	{
		for(int i=0;i < rhs.getSize();i++)
		{
			if(lhs.getElement(j)==rhs.getElement(i))
			{
				counter++; 
			}
		}		
	}
	return( counter >0);
}
//check if an integer is in the set
bool operator <=(const int& lhs, const IntegerSet & rhs)
{
	int counter=0;
	for(int i=0;i< rhs.getSize();i++)
	{
		if(lhs==rhs.getElement(i))//if the element in lhs is in the set in rhs
		{
			return true;
		}
	}	
	return false;
}
