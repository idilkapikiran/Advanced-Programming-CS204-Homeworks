//IDIL KAPIKIRAN 26721
#include <iostream>
#include <sstream>
#include <fstream>
#include <string>
#include "ikapikiran_Kapikiran_Idil_hw3.h"
using namespace std;

void opt1(int &option, CardList &expirationList) //upload cards from given file
{
	string creditFile;
	ifstream input;
	cout << "Please enter file name: ";
	cin >> creditFile;
	input.open(creditFile.c_str());
	if(input.fail())
	{
		cout << "Could not find a file named " << creditFile <<endl;
	}
	string line;
	expirationList.insertNodeAndCard(input);
}

int main()
{
	CardList expirationList;//the doubly linked list with expiration dates
	int option=0;	
	while(option != 6)
	{
		option=0;
		cout <<endl;
		cout << "1) Upload Card(s) from a File "<< endl;
		cout<<	"2) Display List Chronological" << endl;
		cout<< "3) Display List Reverse Chronological" << endl;
		cout <<"4) Card Search" <<endl;
		cout << "5) Bulk Delete" <<endl;
		cout<<"6) Exit" << endl;
		cout <<endl;		
		cout << "Please choose option from the menu: ";
		cin >> option;
		if(option==1)//display list wrt to dates
		{
			opt1(option,expirationList );
		}
		else if(option == 2)
		{
			expirationList.opt2();
		}
		else if(option == 3)
		{
			expirationList.opt3();
		}
		else if(option == 4)
		{
			expirationList.opt4(option);
		}
		else if(option==5)
		{	
			expirationList.opt5(option);
		}
		else if(option==6)//exit and delete all the nodes
		{
			expirationList.deleteNodes();
			cout << "Terminating!!!" <<endl;
			return 0;
		}
		else
		{
			cout<<"Invalid input!" << endl;
			cin.clear();
			cin.ignore(numeric_limits<streamsize>::max(), '\n');
		}
	}	
	return 0;
}