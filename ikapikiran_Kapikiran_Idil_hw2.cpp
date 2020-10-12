//ÝDÝL KAPIKIRAN 26721
#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <vector>

using namespace std;
//a struct to construct the data types of what a node will be consisting of
struct node
{
	int month, year;
	vector<string> cards;
	node *next;		
	// default constructor
	node::node ()
		:month(0), year(0), next(NULL)
	{}
};
//a function to check if the characters of the inputted searching card number have only digits
bool cardCheck(string searchNumber)
{
	for(int i=0; i< searchNumber.length(); i++)
	{
		if('0' <= searchNumber[i] && searchNumber[i] <= '9')
		{
			continue;
		}
		else
		{
			return false;
		}
	}
	return true;
}
//a function to delete the cards in the node of expiration date that user inputs
void opt3(int searchMonth, node *&head, int searchYear)
{
	int n=1;
	node *prev=NULL;
	node *temp2 = head;	
	while(temp2 !=NULL) //while temp is not null, find the node that is inputted and delete the node
	{		
		if(searchMonth == temp2->month && searchYear == temp2 -> year)//if there is a node with that exp date
		{
			if(temp2-> month == head-> month && temp2-> year == head -> year)//if the node to be deleted is in first node shift head by one node
			{
				cout << "Node with expiration date " <<  searchMonth << " " << searchYear << " and the following credit cards have been deleted!" <<endl;
				for(int i=0;i<temp2->cards.size();i++)
				{
					cout << i+1 << ")  " << temp2->cards[i]<< endl;
				}
				head=head->next; //if the one that is deleted is pointed by head, shift the head to next node
				delete temp2;
			}
			else//if it is not the first node
			{
				cout << "Node with expiration date " <<  searchMonth << " " << searchYear << " and the following credit cards have been deleted!" <<endl;
				for(int i=0;i<temp2->cards.size();i++)
				{
					cout << i+1 << ")  " << temp2->cards[i]<< endl;
				}
				prev -> next = temp2; //change the next of the previous node to next of temp2 so they have wiring
				prev-> next = temp2->next;
				delete temp2;	
			}// delete the node user entered
			n=0;
			break;
		}
		else
		{
			prev=temp2;
			temp2=temp2->next;//if the node you are in isnt the inputted node, check the next one and continue
			continue;
		}
	}
	if(n==1)//if there is no node with the input expiration date
	{
		cout << "There is no node with expiration date " << searchMonth << " " << searchYear <<", nothing deleted!" <<endl;
	}

}
//if the option user enters is 2 search for the card number in nodes and print the expiration date for that number
void opt2(string searchNumber, string cardNum, node *head)
{
	node *temp2=head;
	cout << "Please enter the credit card number: ";
	cin >> searchNumber;
	while(!cardCheck(searchNumber) || searchNumber.length() !=16)//if the car number has less or more than 16 numbers or it has other chars than digits ask for number again
	{
		cout << "Invalid format!" <<endl;
		cout << "Please enter the credit card number: ";
		cin >> searchNumber;
	}
	int a=1;
	while(temp2 != NULL)
	{
		for(int i=0; i<(temp2->cards).size();i++)
		{
			if(searchNumber == temp2->cards[i])//if the card number is located in a node
			{
				a=0;
				cout << "There exists a credit card given number " << searchNumber << " with expiration date: " << temp2->month << " " << temp2->year <<endl;
				break;
			}
			else
			{
				continue;
			}
		}
		temp2 = temp2 -> next;
	}	
	if(a==1)//if there is no node consisting that card number 
	{
		cout << "There is no credit card with given credit card number: " << cardNum <<endl;
	}
}
//check all the nodes in the linked list if the node for that expiration date exists
bool checkExist(node *head, int expMonth, int expYear, node *&ptr)
{
	node *temp=head;
	while(temp != NULL)
	{
		if(expMonth==(*temp).month && expYear==(*temp).year)
		{
			ptr=temp;
			return true;
		}
		temp = temp->next;
	}
	return false;
}
//sort the nodes from smaller dates to bigger dates in the option 1
void sortNodes(node * &ptr, node * &head, int expMonth, int expYear, string cardNum)
{
	node *tempData = head;
	ptr=head;
	while(ptr!=NULL)
	{
		if(head->next == NULL && ((expMonth < head-> month && expYear == head-> year ) || expYear < head -> year)) // same year smaller month or smaller year AND next is not null,,,, ptr ->  
		{ //if there is no node after head pointer and the month in the read line(expMonth) is smaller than the one that is pointed by head pointer,
			//create new node and push it previous side of the node 
			ptr-> next = new node;			
			ptr = ptr-> next;
			ptr -> month = expMonth;
			ptr -> year = expYear;
			ptr -> cards.push_back(cardNum);			
			head->next=NULL;
			ptr->next=head;
			head=ptr;
			break;
		}
		else if(head->next != NULL && ((expMonth < head-> month && expYear == head-> year) || expYear < head -> year))
		{  //if there is a node after the head pointer node and the month in the read line(expMonth) is smaller that the one that is pointed by head pointer,
			// add a new node before the one pointing to head
			tempData=head->next;
			ptr->next=new node;
			ptr=ptr-> next;
			ptr -> month = expMonth;
			ptr -> year = expYear;
			ptr -> cards.push_back(cardNum);
			head->next=NULL;
			ptr->next=head;
			head->next=tempData;
			head=ptr;
			break;
		}
		else if(ptr-> next == NULL && ((expMonth > ptr-> month && expYear == ptr-> year ) || expYear > ptr -> year)) //sonuncuya ekler
		{  //add a new node after the ptr pointed one becouse the one in our getline is bigger
			ptr->next=new node;
			ptr=ptr->next;
			ptr-> month = expMonth;
			ptr -> year= expYear;
			ptr->cards.push_back(cardNum);
			break;
		}
		else if( (expMonth < ptr-> next -> month && expYear == ptr-> next-> year ) || expYear < ptr -> next -> year )
		{  //add the nodes which have bigger dates, to the end of the linked list
			tempData=ptr->next;
			ptr-> next = new node;
			ptr = ptr->next;
			ptr-> month=expMonth;
			ptr-> year=expYear;
			ptr->cards.push_back(cardNum);
			ptr->next=tempData;
			break;
		}
		else
		{ //check the other nodes if no swapping needed
			ptr=ptr->next;
			continue;
		}
	}
}
//if the option is 1 display the nodes in order of smaller to bigger
void opt1(node * head)
{
	node *temp = head;
	if(head == NULL) //if the list is empty so head equals to null
	{
		cout << "List is empty!" << endl;
	}
	else if(head->month == 0 && head-> year == 0)//becouse i create a new node in main if there is a defaultly constructured node then the list is still empty no data being pushed to nodes
	{
		cout << "List is empty!" << endl;
	}
	else
	{
		while(temp != NULL) //there are nodes, print data of them 
		{
			cout << "Expiration Date: " << temp->month << " " << temp->year<< endl;
			for(int i=0; i< temp->cards.size(); i++)
			{
				cout << i+1 << ")  " << temp -> cards[i] <<endl;
			}
			cout << "-------------------" << endl;
			temp = temp -> next;
		}
	}
}
// a function that adds and prints nodes
void nodePrint(int expMonth, int expYear, string cardNum, node *&head)
{
	static bool state=1;
	node *temp;
	node *ptr = head;
	if (state)
	{// add the first node and first data
		head->cards.push_back(cardNum);
		head->month=expMonth;
		head->year=expYear;
		state=0;
		cout << "New node is created with expiration date: " << expMonth << " " << expYear <<endl;
		cout << "Credit card " << cardNum << " added to node " << expMonth << " " <<expYear << endl;
		cout << "***************"<<endl;
	}
	else if(checkExist(head, expMonth, expYear, temp))
	{//if there is a node with the same date pushback the credit card				
		(temp -> cards).push_back(cardNum);		
		cout << "Node with expiration date " << expMonth << " " << expYear <<  " already exists " << endl;
		cout << "Credit card " << cardNum << " added to node "<< expMonth << " " << expYear << endl;
		cout << "***************"<<endl;
	}
	else		
	{//add a new node
		sortNodes(ptr, head, expMonth, expYear, cardNum);//check where the node should be located
		cout << "New node is created with expiration date: " << expMonth << " " << expYear <<endl;
		cout << "Credit card " << cardNum << " added to node " << expMonth << " " <<expYear << endl;
		cout << "***************"<<endl;
	}
}
// delete all the nodes in the linklist using a ptr pointer, not to have memory leak
void deleteNodes(node *&head)
{
	/* Begin: code taken from linkedList.cpp */ 
	node *ptr;
	while(head!=NULL)
	{
		ptr=head;
		head=head->next;
		delete ptr;			
	}
	/* End: code taken from ptrfunc.cpp */
}

int main()
{
	string creditFile;	
	ifstream input;	
	node *head= NULL;
	head = new node;
	cout << "Please enter file name: ";
	cin >> creditFile;
	input.open(creditFile.c_str());
	while(input.fail())
	{
		cout << "Cannot find a file named " << creditFile <<endl;
		cout << "Please enter file name: ";
		cin >> creditFile;
		input.open(creditFile.c_str());
	}
	string line;
	int expMonth, expYear, option, searchMonth, searchYear;
	string cardNum, searchNumber;
	while(getline(input, line))//read the file line by line
	{
		istringstream input(line);
		input >> cardNum >> expMonth >> expYear;
		nodePrint(expMonth, expYear, cardNum, head);
	}	
	option = 1;
	while(option!=4)
	{
		cout <<endl;	
		cout << "1)Display List" << endl;
		cout <<	"2)Card Search via Credit Number" << endl;
		cout <<	"3)Delete Card with respect to Expiration Date" <<endl;
		cout <<	"4)Exit" << endl;
		cout <<endl;		
		cout << "Please choose option from the menu: ";
		cin >> option;
		while(cin.fail()|| (option>4 && option <1))
		{
			cout << "Invalid option" << endl;
			cout << "Please choose option from the menu: ";
			cin.clear();
			cin.ignore(numeric_limits<streamsize>::max(), '\n');
			cin >> option;
		}
		if(option==1)//display list wrt to dates
		{
			opt1(head);
		}
		else if(option == 2)//card search
		{
			opt2(searchNumber, cardNum, head);
		}
		else if(option==3)//delete cards wrt exp
		{	
			cout << "Please enter month and year: ";
			cin >> searchMonth >> searchYear;	
			while(cin.fail() || searchMonth > 12 || searchMonth <1 || searchYear<0)//if the date searched is valid
			{
				cout << "Invalid Date!" << endl;
				cout << "Please enter month and year: ";
				cin.clear();
				cin.ignore(numeric_limits<streamsize>::max(), '\n');
				cin >> searchMonth >> searchYear;
			}
			opt3(searchMonth, head, searchYear);
		}
	}
	if(option==4)//exit and delete all the nodes
	{
		deleteNodes(head);
		cout << "Terminating!!!" <<endl;
	}
	return 0;
}