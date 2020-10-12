#include <iostream>
#include "ikapikiran_Kapikiran_Idil_hw3.h"
#include <string>
#include <fstream>
#include <sstream>
using namespace std;

CardList::CardList() // default constructor
	:head(NULL), tail(NULL)
{}
//a function to delete all nodes
void CardList::deleteNodes()
{
	creditCardNode *ptr;
	expirationNode *temp=head;
	expirationNode *prev;
	while(temp!=NULL)//delete the nodes
	{
		while(temp->cHead!=NULL)//delete the cards
		{
			ptr=temp->cHead;
			temp->cHead=ptr->next;
			delete ptr;		
		}		
		prev= temp;
		temp=temp->next;
		head=temp;
		delete prev;			
	}
	tail=NULL;
	delete tail;
	head=NULL;
	delete head;
}
// check if a node with the given number exists
bool checkExists(int expMonth, int expYear, expirationNode *&temp)
{
	while(temp != NULL)
	{
		if(expMonth==temp->month && expYear==temp->year)
		{
			return true;
		}
		else
			temp = temp->next;
	}
	return false;
}
bool cardExists(expirationNode *temp, string cardNum)
{
	creditCardNode *cPtr=temp->cHead;
	while(cPtr!=NULL)
	{
		if(cardNum==cPtr->creditCardNo)
		{
			return true;
		}
		else
			cPtr=cPtr->next;
	}
	return false;
}
//insert card dates and numbers with respect to the dates(sort them from smaller to bigger)
void CardList::insertNodeAndCard(ifstream &input)
{
	int expYear, expMonth;
	string cardNum;
	expirationNode *temp = head;
	creditCardNode *temp2;
	string line;
	while(getline(input, line))//read the file line by line and insert the nodes
	{
		istringstream input(line);
		input >> cardNum >> expMonth >> expYear;
		if(head==NULL)//if there is no nodes
		{
			creditCardNode *nPtr= new creditCardNode(cardNum, NULL);
			head=new expirationNode(expMonth, expYear, nPtr, NULL, NULL); 
			cout << cardNum << " " << expMonth << " " << expYear<< " : added to a new expiration date node." <<endl;
			tail = head;
		}
		else //if there are nodes
		{
			temp=head;	
			if(checkExists(expMonth, expYear, temp))//if expiration date exists add cards
			{			
				if(cardExists(temp, cardNum))
				{
					cout << cardNum << " " << expMonth << " " << expYear<< " :this card was already inserted." <<endl;
				}
				else
				{
					if(temp->cHead==NULL)//if there is a node with that exp date and there is no card int the card linked list add the credit card to that node
					{
						temp->cHead=new creditCardNode(cardNum, NULL);
						cout << cardNum << " " << expMonth << " " << expYear<< " : inserted to an existing expiration date node." << endl;						
					}
					else if(cardNum < temp->cHead->creditCardNo) //if the cards is smaller than the card than the previously added card, add to previous
					{
						temp2=temp->cHead;
						creditCardNode *temp3=temp->cHead;
						temp3=new creditCardNode(cardNum, temp2);
						temp2=NULL;
						cout << cardNum << " " << expMonth << " " << expYear<< " : inserted to an existing expiration date node." << endl;	
					}
					else //if there is a node and the card is bigger than the previously added skip the nodes or add
					{		
						temp2=temp->cHead;
						creditCardNode *previous=temp2;
						while(temp2!=NULL)
						{
							if(cardNum > temp2->creditCardNo)//skip to next node while your date is smaller than the next node
							{
								previous=temp2;
								temp2=temp2->next;
							}
							else if(cardNum < temp2->creditCardNo) //when you reach the node that is bigger than given card number
							{
								previous->next= new creditCardNode(cardNum, temp2);
								cout << cardNum << " " << expMonth << " " << expYear<< " : inserted to an existing expiration date node." << endl;
								break;
							}
						}	
						if(temp2==NULL)//add to the end of the card linked list 
						{
							temp2=new creditCardNode(cardNum, NULL);
							previous->next=temp2;
							temp2=NULL;
							cout << cardNum << " " << expMonth << " " << expYear<< " : inserted to an existing expiration date node." << endl;		
						}
					}
				}
			}
			else
			{
				creditCardNode *newCard=NULL;
				temp=head;
				if((expYear < head->year) ||( expMonth< head->month && expYear == head->year)) //if the date is smaller than the one that is pointed by head
				{
					newCard = new creditCardNode(cardNum, NULL);
					head->prev = new expirationNode(expMonth, expYear, newCard, head, NULL);
					head= head->prev;					
					cout << cardNum << " " << expMonth << " " << expYear<< " : added to a new expiration date node." <<endl;
				}
				else 
				{
					expirationNode *prev=NULL;
					expirationNode *tempExp=NULL;
					while(temp!=NULL)
					{
						if(( expMonth > temp->month && expYear == temp->year) || (expYear > temp->year)) // if date is bigger that temp's date
						{				
							prev=temp;
							temp=temp->next;
						}
						else if(( expMonth < temp->month && expYear == temp->year) || (expYear < temp->year)) //if date is smaller than temp's date, add a node before temp pointed node
						{							
							tempExp = temp->prev;
							newCard = new creditCardNode(cardNum, NULL); //add the card number of the line 
							tempExp->next = new expirationNode(expMonth, expYear, newCard, temp, tempExp);							
							temp->prev=tempExp->next;
							cout << cardNum << " " << expMonth << " " << expYear<< " : added to a new expiration date node." <<endl;							
							break;
						}
					}
					if(temp==NULL) //if the date is bigger than all the nodes add to the end
					{
						newCard= new creditCardNode(cardNum, NULL);  //add the cardnumber of the line
						temp= new expirationNode(expMonth, expYear, newCard, NULL, prev);
						prev->next=temp; 						
						cout << cardNum << " " << expMonth << " " << expYear<< " : added to a new expiration date node." <<endl;						
						tail= temp;
					}
				}
			}
		}
	}
}
//a function to check if the characters of the inputted searching card number have only digits
bool cardCheck(string searchCardNum)
{
	if(searchCardNum.length()!=16)
	{
		return false;
	}
	else
	{
		for(int i=0; i< searchCardNum.length(); i++)
		{
			if('0' <= searchCardNum[i] && searchCardNum[i] <= '9')
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
}
void CardList::opt2() //display list from earlier to later
{
	expirationNode *ptr=head;
	if(head == NULL) //if the list is empty so head equals to null
	{
		cout << "List is empty!" << endl;
	}
	else
	{
		while(ptr != NULL) //there are nodes, print data of them 
		{
			int counter =1;	
			cout << "Expiration Date: " << ptr->month << " " << ptr->year<< endl;
			creditCardNode *cPtr = ptr->cHead;
			while(cPtr!=NULL)
			{
				cout << counter << ") " << cPtr->creditCardNo<<endl;
				cPtr=cPtr->next;
				counter++;
			}
			cout << "-------------------" << endl;
			ptr = ptr -> next;
		}
	}
}

void CardList::opt3() //print list in reverse order
{
	expirationNode *ptr = tail;	
	if(head == NULL)// if list is empty
	{
		cout << "List is empty" << endl;
	}
	else
	{		
		while(ptr != head) //while ptr isn't in head
		{
			int counter=1;
			cout << "Expiration Date: " << ptr->month << " " << ptr->year<< endl;
			creditCardNode *cPtr = ptr->cHead;
			while(cPtr!=NULL)
			{
				cout << counter << ") " << cPtr->creditCardNo<<endl;
				cPtr=cPtr->next;
				counter++;
			}
			cout << "-------------------" << endl;
			ptr = ptr->prev;
		}
		//if ptr equals to head add the node in head
		int counter=1;
		cout << "Expiration Date: " << ptr->month << " " << ptr->year<< endl;
		creditCardNode *cPtr = ptr->cHead;
		while(cPtr!=NULL)
		{
			cout << counter << ") " << cPtr->creditCardNo<<endl;
			cPtr=cPtr->next;
			counter++;
		}
		cout << "-------------------" << endl;
	}
}

void CardList::opt4(int &option) //search for the user given card number
{	
	int a=1;
	creditCardNode *cPtr;
	string searchCardNum;
	cout << "Please enter the credit card number: ";
	cin >> searchCardNum;
	if(cardCheck(searchCardNum)) //search for number(s)
	{
		expirationNode *searchPtr=head;
		while(searchPtr!=NULL)
		{
			cPtr=searchPtr->cHead;
			while(cPtr!=NULL)
			{
				if(searchCardNum==cPtr->creditCardNo) //there is a card with that number
				{
					a=0;
					cout << "There exists a credit card given number " << searchCardNum << " with expiration date: "  << searchPtr->month << " " << searchPtr->year << endl;
				}
				cPtr=cPtr->next;
			}
			searchPtr=searchPtr->next;
		}
		if(a==1) //there is no card with that number
		{
			cout << "There is no credit card with given credit card number: " << searchCardNum << endl;
		}
	}
	else //return to menu
	{
		cout << "Invalid format!" <<endl;
		cin.clear();
		cin.ignore(numeric_limits<streamsize>::max(), '\n');
	}
}

void CardList::opt5(int &option) //delete the previous and if exists the inputted date nodes(bulk delete)
{
	int a=1;	
	creditCardNode *cPtr;
	expirationNode *ptr=head;
	int searchMonth, searchYear;
	cout << "Please enter month and year: ";
	cin >> searchMonth >> searchYear;	
	if(cin.fail() || searchMonth > 12 || searchMonth <1 || searchYear<0)//if the date searched is not valid
	{
		cout << "Invalid Date!" << endl;
		cin.clear();
		cin.ignore(numeric_limits<streamsize>::max(), '\n');
	}
	else
	{
		while(ptr!=NULL && ((searchMonth>=ptr->month && searchYear == ptr->year) || searchYear > ptr->year))//delete the nodes
		{
			a=0;
			cout << "Node with expiration date " << ptr->month << " " << ptr-> year << " and the following credit cards have been deleted!" << endl;
			cPtr=ptr->cHead;
			int counter=1;
			while(cPtr!=NULL) //delete the cards
			{
				cout << counter << ") " << cPtr->creditCardNo<<endl;
				counter++;
				creditCardNode *temp=cPtr;
				cPtr=cPtr->next;
				delete temp;
			}
			expirationNode *temp=ptr;
			ptr=ptr->next;
			head=ptr;
			delete temp;			
		}
		if(head==NULL && a==1) //if there is no node
		{
			cout << "List is empty!" << endl;
		}
		else if(a==1) // if the given date has no previous node
		{
			cout << "No node before this date!"<< endl;
		}
	}
}
