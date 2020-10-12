#include <iostream>
#include "HW8DynIntQueue.h"
#include <thread>
#include <chrono>
#include <mutex>
#include <random>
#include <ctime>
#include <time.h>
#include <iomanip>
using namespace std;
HW8DynIntQueue dynQue;
mutex outMutex, myMutex;
int total_customer_count, cashier2_threshold, min_arrival, max_arrival, min_checkout_time, max_checkout_time, counter=0, customerID=1;

int random_range(const int & min, const int & max) //random generator
{
	static mt19937 generator(time(0));
	uniform_int_distribution<int> distribution(min, max);
	return distribution(generator);
}

void customer()
{
	int queSize1;
	while (customerID <= total_customer_count) 
	{  					
		myMutex.lock();		//lock the mutex so no other operation happens in the queue
		dynQue.enqueue(customerID);	
		queSize1= dynQue.getCurrentSize();//get current size inside mutex so it wont mix up
		myMutex.unlock();
		
		time_t tt = chrono::system_clock::to_time_t(chrono::system_clock::now()); 
		struct tm *ptm = new struct tm; 
		localtime_s(ptm, &tt); 	
		outMutex.lock(); //lock the output mutex so output lines wont mix up
		cout << "New customer with ID " << customerID << " has arrived (queue size is " << queSize1 << "): " << put_time(ptm,"%X") <<endl;			
		outMutex.unlock();			
		int sleeptime=random_range(min_arrival, max_arrival); //sleep the customers
		this_thread::sleep_for(chrono::seconds(sleeptime));			
		customerID++;
	}
}

void cashier(const int & cashierID)
{	
	int ID, queSize2;
	int sleeptime=random_range(min_checkout_time, max_checkout_time);//sleep the cashiers at first
	this_thread::sleep_for(chrono::seconds(sleeptime));
	while(counter < total_customer_count)
	{		
		myMutex.lock();	//lock the mutex so no other operation happens in the queue
		if(!dynQue.isEmpty() && ( (cashierID==2 && dynQue.getCurrentSize()>=cashier2_threshold) || cashierID==1) )
		{  	
			dynQue.dequeue(ID);	
			counter++;
			queSize2= dynQue.getCurrentSize();
			myMutex.unlock();	
			
			outMutex.lock();
			time_t tt = chrono::system_clock::to_time_t(chrono::system_clock::now()); 
			struct tm *ptm = new struct tm; 
			localtime_s(ptm, &tt);
			cout <<"Cashier " << cashierID << " started transaction with customer "<< ID << " (queue size is "<< queSize2 << "): " << put_time(ptm,"%X") <<endl;
			outMutex.unlock();

			sleeptime=random_range(min_checkout_time, max_checkout_time);//sleep the cashiers
			this_thread::sleep_for(chrono::seconds(sleeptime));		

			outMutex.lock();
			tt = chrono::system_clock::to_time_t(chrono::system_clock::now()); 	
			localtime_s(ptm, &tt); 
			cout <<"Cashier "<< cashierID <<" finished transaction with customer "<<ID << " " << put_time(ptm,"%X") <<endl;
			outMutex.unlock();				
		}
		else
		{
			myMutex.unlock();
		}
	}
}
int main()
{
	//get inputs
	cout << "Please enter the total number of customers: ";
	cin >> total_customer_count;
	cout << "Please enter the number of customers waiting in the queue to open the second cashier: ";
	cin >> cashier2_threshold;
	cout << "Please enter the inter-arrival time range between two customers: " <<endl;
	cout << "Min: ";
	cin >> min_arrival;
	cout << "Max: " ;
	cin >> max_arrival;
	cout << "Please enter the checkout time range of cashiers: " <<endl;
	cout << "Min: " ;
	cin >> min_checkout_time;
	cout << "Max: " ;
	cin >> max_checkout_time;

	time_t tt = chrono::system_clock::to_time_t(chrono::system_clock::now());
	struct tm *ptm = new struct tm;  
	localtime_s(ptm, &tt);
	cout << "Simulation starts " <<  put_time(ptm,"%X") << endl; // print out starting time
	//child threads
	thread arrivingCust(&customer); 
	thread cashier2(&cashier, 2);		
	thread cashier1(&cashier, 1);

	arrivingCust.join();	
	cashier2.join();
	cashier1.join();	

	tt = chrono::system_clock::to_time_t(chrono::system_clock::now());
	localtime_s(ptm, &tt);
	cout << "End of the simulation ends: " << put_time(ptm,"%X") << endl;
	return 0;
}