//IDIL KAPIKIRAN 26721
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include "intStackHeader.h"
#include <iomanip>

using namespace std;
//delete the matrix at the end of the program
void deleteMatrix(char**& matrix, int rowNumber)//delete the matrix
{
	/* Begin: code taken from matrix.cpp and updated*/
	for(int i = 0; i < rowNumber; ++i)
	{
		delete[] matrix[i];
	}
	delete[] matrix;
	/* End: code taken from matrix.cpp and updated*/	
}
//print the matrix that is filled
void printMatrix(char** matrix, int rowNumber, int columnNumber)//print the matrix that is filled
{
	for(int i=0; i<rowNumber;i++)
	{
		for(int j=0; j< columnNumber; j++)
		{
			cout << setw(2) << matrix[i][j];
		}
		cout <<endl;
	}	
}
//check if the coordinates that are being checked in the range of the matrix
bool inRange(int rowNumber, int columnNumber, int coorX, int coorY)
{
	if(coorX<=rowNumber-1 && coorY<=columnNumber-1)
	{
		return true;
	}
	else
	{
		return false;
	}
}
//fill the empty spaces with the fill char 
void fillMatrix(char**& matrix, char fillCh, intStack stack, int startRow, int startColumn, int rowNumber, int columnNumber)
{
	bool finish=false;	
	int coorX=startRow, coorY=startColumn;
	stack.push(coorX, coorY);  //push the first coordinate that is inputted by user
	matrix[coorX][coorY]=fillCh; //fill it with fill char

	while(inRange(rowNumber, columnNumber, coorX, coorY)&& finish==false)//while the coordinates that are checked are in range
	{
		//check if the coordinate has a empty space in any 4 directions
		if(matrix[coorX-1][coorY]==' ')//check up(north)
		{
			coorX-=1; //update the coordinates
			stack.push(coorX, coorY); //push the coordinates to the stack
			matrix[coorX][coorY]=fillCh; //fill the space with the fill char
		}
		else if (matrix[coorX][coorY+1]==' ')//check right
		{
			coorY+=1;
			stack.push(coorX, coorY);
			matrix[coorX][coorY]=fillCh;
		}
		else if(matrix[coorX+1][coorY]==' ')//check down
		{
			coorX+=1;
			stack.push(coorX, coorY);
			matrix[coorX][coorY]=fillCh;
		}
		else if(matrix[coorX][coorY-1]==' ')// check left
		{
			coorY-=1;
			stack.push(coorX, coorY);
			matrix[coorX][coorY]=fillCh;
		}
		else //if all 4 of the directions are occupied 
		{
			if(stack.isEmpty()) //if satck is empty then the area is filled, print the matrix
			{
				printMatrix(matrix, rowNumber, columnNumber);
				deleteMatrix(matrix, rowNumber); //delete the matrix at the end of printing
				finish=true; //if matrix is printed end the program
			}
			else //if stack is empty then pop the value that is pushed the last
			{
				stack.pop(coorX, coorY);
			}
		}
	}
}
int main()
{	
	intStack stack; //create a stack
	string rowNum, columnNum, fileName, line;
	int startRow, startColumn;	
	ifstream input;
	char ch, fillCh;

	//get the number of rows and check if it is valid if not want another inout from user
	cout << "Enter the number of rows: ";
	cin >> rowNum;
	bool rowValid=false;
	while(rowValid==false)
	{
		bool rowFail=false;
		for(int i=0; i< rowNum.length();i++) 
		{
			if(!(rowNum[i]<='9' && rowNum[i] >='0'))//check if all the characters are numerical
			{
				rowFail=true;
			}
		}
		if(rowFail) //if there are non numerical characters in the row input, get the row count from user again
		{
			cout << rowNum<<" is not valid!" <<endl;
			cin.clear();
			cin.ignore(numeric_limits<streamsize>::max(), '\n');
			cout << "Enter the number of rows: ";
			cin >> rowNum;
		}
		else if(stoi(rowNum) <= 2) //if the given row number is smaller than 3, get the row count from user again
		{
			cout << rowNum<<" is not valid!" <<endl;
			cin.clear();
			cin.ignore(numeric_limits<streamsize>::max(), '\n');
			cout << "Enter the number of rows: ";
			cin >> rowNum;
		}
		else
		{
			rowValid=true;
		}
	}

	//get the number of columns and check if it is valid if not want another inout from user
	cout << "Enter the number of columns: ";
	cin >> columnNum;
	bool colValid=false;
	while(colValid==false)
	{
		bool colFail=false;
		for(int i=0; i< columnNum.length();i++)
		{
			if(!(columnNum[i]<='9' && columnNum[i] >='0'))
			{
				colFail=true;
			}
		}
		if(colFail)  //if there are non numerical characters in the column input, get the column count from user again
		{
			cout << columnNum<<" is not valid!" <<endl;
			cin.clear();
			cin.ignore(numeric_limits<streamsize>::max(), '\n');
			cout << "Enter the number of columns: ";
			cin >> columnNum;
		}
		else if(stoi(columnNum) <= 2) //if the given column number is smaller than 3, get the column count from user again
		{
			cout << columnNum<<" is not valid!" <<endl;
			cin.clear();
			cin.ignore(numeric_limits<streamsize>::max(), '\n');
			cout << "Enter the number of columns: ";
			cin >> columnNum;
		}
		else
		{
			colValid=true;
		}
	}

	//get file name
	cout << "Please enter file name: ";
	cin >> fileName;
	input.open(fileName.c_str());
	while(input.fail())
	{		
		cin.clear();
		cin.ignore(numeric_limits<streamsize>::max(), '\n');
		cout << "Cannot find a file named " << fileName <<endl;
		cout << "Please enter file name: ";
		cin >> fileName;
		input.open(fileName.c_str());
	}

	//convert the row and column numbers to integers
	int rowNumber=stoi(rowNum);
	int columnNumber=stoi(columnNum);

	//create a 2d array
	char** matrix = new char*[rowNumber];
	for(int i =0; i<rowNumber; i++)
	{
		matrix[i] = new char[columnNumber];
	}

	//read the file line by line
	int m=0;
	while(getline(input, line))
	{
		istringstream input(line);
		int j=0;
		while(input>> noskipws >> ch && m<rowNumber && j<columnNumber)
		{
				matrix[m][j]=ch; //push the X's and whitespaces to the array
			j++;		
		}
		m++;
	}

	//get the starting points
	cout << "Enter the starting point: ";
	cin >> startRow >> startColumn;
	while(cin.fail() || startRow >= rowNumber || startColumn >= columnNumber || startColumn<0 || startRow < 0)//if the starting coordinates are not in the area
	{		
		cin.clear();
		cin.ignore(numeric_limits<streamsize>::max(), '\n');
		cout << "Invalid coordinate!"<< endl;
		cout << "Enter the starting point: ";
		cin >> startRow >> startColumn;
	}

	if(matrix[startRow][startColumn]=='X') //if the user inputs an ocuppied cell, delete matrix and end the program
	{
		cout << "Starting point is already occupied."<< endl;
		cout << "Terminating!"<< endl;
		deleteMatrix(matrix, rowNumber);		
	}
	else	
	{
		//if the starting coordinates are valid, ask for a filling char
		cout << "Enter the filling char: ";
		cin>> fillCh;
		while(cin.fail() || fillCh=='x' || fillCh=='X')
		{		
			cout << "Filling char is not valid!" <<endl;
			cin.clear();
			cin.ignore(numeric_limits<streamsize>::max(), '\n');
			cout << "Enter the filling char: ";
			cin>> fillCh;
		}	
		//if filling char is valid, fill the matrix
		fillMatrix(matrix, fillCh, stack, startRow, startColumn, rowNumber, columnNumber);
	}	
	return 0;
}