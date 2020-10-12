//ÝDÝL KAPIKIRAN 26721
#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <iomanip>
#include <sstream>

using namespace std;
void findEnclosed(int , int , vector<vector<char>>);
void coordinateOut(int, int, const vector<int>, const vector<int>);
//check if the coordinates are in correct range
bool coordinateCheck(int coorX, int coorY, const vector<vector<char>> & mat)
{
	if(coorX < mat.size() && coorY < mat[0].size() && coorX >= 0 && coorY >= 0)
	{
		return true;
	}
	else if(coorX==-1 &&coorY==-1)
	{
		return true;
	}
	else
	{
		return false;
	}
}
//get coordinates untill they are valid and print appropriate messages
void coordinatePrints(vector<vector<char>> mat)
{
	int coorX, coorY;
	cout << "Please enter starting coordinates, first row X then column Y: ";
	cin >> coorX >> coorY;
	if(coorX==-1 && coorY ==-1) //exit
	{
		cout << "Terminating..." << endl;
	}
	else
	{
		while(!coordinateCheck(coorX, coorY, mat) || cin.fail() || (coorX==-1 && coorY ==-1)) //while coordinate are not valid or exit is wanted
		{				
			if(cin.fail())// if the user enters string
			{								
					cout << "Invalid Coordinates" << endl;
					cout << "Please enter starting coordinates, first row X then column Y: ";
					cin.clear();
					cin.ignore(numeric_limits<streamsize>::max(), '\n');
					cin >> coorX >> coorY;						
			}
			else if(!coordinateCheck(coorX, coorY, mat)) //if the coordinate is not in the range
			{						
					cout << "Invalid Coordinates" << endl;
					cout << "Please enter starting coordinates, first row X then column Y: ";
					cin.clear();
					cin.ignore(numeric_limits<streamsize>::max(), '\n');
					cin >> coorX >> coorY;				
			}	
			else //if user wants to exit and input -1 -1
			{
				cout << "Terminating..." << endl;
				break;
			}
		}	
		if (coordinateCheck(coorX, coorY, mat)) //if valid coordinates, check if the area is enclosed
		{			
			findEnclosed(coorX, coorY, mat);
		}
	}
}
//a function to find an enclosed area
void findEnclosed(int coorX, int coorY, vector<vector<char>> mat)
{	
	int i=1;
	vector<int> locationX;
	vector<int> locationY;
	vector<vector<char>> matTemp= mat; //
	if(matTemp[coorX][coorY]!='x') // if the given coordinate isnt occupied
	{
		cout << "This cell is not occupied!" <<endl;
	}
	else if(matTemp[coorX][coorY]=='x')
	{	
		int counter=0;
		locationX.push_back(coorX); //add the first occupied cell to x vector
		locationY.push_back(coorY); //add the first occupied cell to y vector
		matTemp[coorX][coorY]='p';
		int visit=1;
		while(coorX < matTemp.size() && coorY < matTemp[0].size() &&  coorX >= 0 && coorY >= 0) //check while the coordinates are in the valid range
		{				
			if(coorY+i < matTemp[0].size() && matTemp[coorX][coorY+i]=='x') //check right side of the cell
			{
				coorY+=i;                       //if the cell if occupied add the x and y coordinates to the vectors 
				locationY.push_back(coorY);
				locationX.push_back(coorX);    //and replace x with p to indicate we have been there before
				matTemp[coorX][coorY]='p';		//do the same for every other direction
			}
			else if(coorX+i <  matTemp.size() && matTemp[coorX+i][coorY]=='x') // check down side of the cell
			{
				coorX+=i;
				locationX.push_back(coorX);
				locationY.push_back(coorY);
				matTemp[coorX][coorY]='p';				
			}		
			else if (coorY-i >= 0 && matTemp[coorX][coorY-i]=='x' ) //check left side of the cell
			{
				coorY-=i;
				locationX.push_back(coorX);
				locationY.push_back(coorY);
				matTemp[coorX][coorY]='p';				
			}			
			else if (coorX-i >= 0 && matTemp[coorX-i][coorY]=='x') //check up side of the cell
			{					
				coorX-=i;
				locationY.push_back(coorY);
				locationX.push_back(coorX);
				matTemp[coorX][coorY]='p';				
			}		
			else if (visit<2) //if the loop did not enter to the directions indicating surrounding of our coordinate is not occupied
			{
				visit++;
				if(counter>=3) //if the directions were not occupied for the next 3 or more itirations,
				{  // change the first index of the matTemp so the first coordinate given by user from p to x again to check if the area is enclosed so first index is same with last
					matTemp[locationX[0]][locationY[0]]='x';
				}
				else
				{
					break;
				}
			}			
			else 
			{
				break;
			}
			counter++;
		}
		coordinateOut(coorX, coorY, locationX, locationY); //print the coordinates program has added to the locationX and Y matrices
	}	
	coordinatePrints(mat);
}

void coordinateOut(int coorX, int coorY, const vector<int> locationX, const vector<int> locationY)
{
	if(coorX==locationX[0] && coorY==locationY[0] && locationX.size()>4) // if the area is enclosed
	{
		cout << "Found an enclosed area. The coordinates of the followed path: " <<endl;
		for(int i=0;i<locationX.size()-1; i++)
		{
			cout << locationX[i] << " " << locationY[i] <<endl;
		}
	}
	else //if the area is not enclosed
	{
		cout <<"Cannot found an enclosed area starting with given coordinate. The coordinates of the followed path: " <<endl;
		for(int i=0;i<locationX.size(); i++)
		{
			cout << locationX[i] <<  " " << locationY[i] <<endl;
		}
	}
}

//if rows and columns of the matrix doesnt match and there are extra x or o in the matrix return false
bool charCountCheck(const vector<vector<char>> & mat)
{
	int counter = 0;
	for (int i=0; i < mat.size(); i++)
	{
		for (int j=0; j < mat[i].size(); j++)
		{
			counter++;
		}
	}
	if((mat.size())*(mat[0].size())!=counter)
	{
		return false;
	}
	else
	{
		return true;
	}
}
//check if the matrix has other chars other than x and o
bool charTypeCheck(const vector<vector<char>> & mat)
{
	int counter = 0;
	for (int i=0; i < mat.size(); i++)
	{
		for (int j=0; j < mat[i].size(); j++)
		{
			if(mat[i][j]!= 'o' && mat[i][j]!= 'x')
			{
				counter++;
			}
		}
	}
	if (counter !=0)
	{
		return false;
	}
	else
	{
		return true;
	}
}
//print the input matrix 
void getMatrix(const vector<vector<char>> & mat)
{	
	cout << "Input Matrix: " <<endl;
	for (int i=0; i< mat.size();i++)
	{
		for(int j=0; j< mat[i].size();j++)
		{
			cout << setw(3) << mat[i][j];
		}
		cout << endl;
	}	
}

int main()
{
	string matrixFile;
	cout << "Please enter a file name: ";
	cin >> matrixFile; //get file input from user
	ifstream input;
	input.open(matrixFile.c_str());
	while(input.fail())//if the file name is not valid get filename from user again
	{
		cout << "Cannot find a file named " << matrixFile <<endl;
		cout << "Please enter a file name: ";
		cin >> matrixFile;
		input.open(matrixFile.c_str());
	}
	string line;
	char ch;
	int coorX, coorY;
	vector<vector<char>> mat;	
	while(getline(input, line))//read the file line by line
	{
		vector<char> vec;
		istringstream input(line);
		while(input >> ch)
		{			
			if(ch!= ' ' || ch != '\t') //strip the space and tab characters from the file
			{
				vec.push_back(ch); //push back the chars to vector
			}		
		}
		mat.push_back(vec);		//push back the vectors to the matrix
	}
	if(!charTypeCheck(mat)) //if the matrix has invalid chars
	{
		cout << matrixFile << " includes invalid char(s)" <<endl;
	}
	else if(!charCountCheck(mat)) //if the matrix has extra chars in rows
	{
		cout << matrixFile << " is invalid matrix, does not contain same amount of char each row!"<<endl;
	}
	else
	{
		getMatrix(mat); //print the matrix
		int coorX, coorY;
		cout << "Please enter starting coordinates, first row X then column Y: ";
		cin >> coorX >> coorY;
		while(!coordinateCheck(coorX, coorY, mat) || cin.fail() || (coorX==-1 && coorY ==-1)) //while coordinate are not valid or exit is wanted
		{				
			if(cin.fail())// if the user enters string
			{								
					cout << "Invalid Coordinates" << endl;
					cout << "Please enter starting coordinates, first row X then column Y: ";
					cin.clear();
					cin.ignore(numeric_limits<streamsize>::max(), '\n');
					cin >> coorX >> coorY;						
			}
			else if(!coordinateCheck(coorX, coorY, mat)) //if the coordinate is not in the range
			{						
					cout << "Invalid Coordinates" << endl;
					cout << "Please enter starting coordinates, first row X then column Y: ";
					cin.clear();
					cin.ignore(numeric_limits<streamsize>::max(), '\n');
					cin >> coorX >> coorY;				
			}	
			else //if user wants to exit and input -1 -1
			{
				cout << "Terminating..." << endl;
				return 0;
			}
		}	
		if (coordinateCheck(coorX, coorY, mat)) //if valid coordinates, check if the area is enclosed
		{			
			findEnclosed(coorX, coorY, mat);
		}
	}
	return 0;
}
