#include <iostream>
#include <string>
#include <fstream>
using namespace std;
//check if the bit is 1
bool index1(unsigned char c, unsigned int i)
{
	if((c & (1 << i) ) == (1<<i))
	{
		return true;
	}
	else
	{
		return false;
	}
}
//permute the bits of the char
//check all the bits like the first one
unsigned char permute(unsigned char chText, unsigned char chKey)
{
	unsigned char result= chText; //assaign a new chars bits to chText's bits
	if(index1(chText, 0)) //if the 0th bit is 1
	{
		result=result|((1<<0)<<2); //set the result's bit(1) to 2 left side bit with or operator
	}
	else //if the 0th bit is 0
	{
		result=result & ~((1<<0)<<2); //set the result's bit(0) to 2 left side bit with complement
	}

	if(index1(chText, 1)) 
	{
		result=result|((1<<1)>>1);
	}
	else
	{
		result=result & ~((1<<1)>>1);
	}

	if(index1(chText, 2))
	{
		result=result|((1<<2)<<1);
	}
	else
	{
		result=result & ~((1<<2)<<1);
	}

	if(index1(chText, 3))
	{
		result=result|((1<<3)>>2);
	}
	else
	{
		result=result & ~((1<<3)>>2);
	}

	if(index1(chText, 4))
	{
		result=result|((1<<4)<<2);
	}
	else
	{
		result=result & ~((1<<4)<<2);
	}

	if(index1(chText, 5))
	{
		result=result|((1<<5)>>1);
	}
	else
	{
		result=result & ~((1<<5)>>1);
	}	

	if(index1(chText, 6))
	{
		result=result|((1<<6)<<1);
	}
	else
	{
		result=result & ~((1<<6)<<1);
	}	

	if(index1(chText, 7))
	{
		result=result|((1<<7)>>2);
	}
	else
	{
		result=result & ~((1<<7)>>2);
	}
	//apply xor operator
	result= result ^ chKey;
	return result;
}
int main()
{
	string key, plaintext;
	unsigned char mResult;
	cout << "*** Welcome to the Simple Data Encryption Application ***" << endl;
	cout << "Please enter the encryption key: ";	
	getline(cin, key);
	cin.clear();	
	cout << "Please enter the plaintext to be encrypted: ";
	while(getline(cin, plaintext)) //get text till ^z is given
	{
		cout << "Ciphertext: " ;
		for (unsigned int i = 0; i < plaintext.length(); i++)
		{
			mResult=permute(plaintext.at(i), key.at(i%key.length()));
			cout << hex << (int) mResult;
		}	
		cout << endl;
		cin.clear();
		cout << "Please enter the plaintext to be encrypted: ";
	}	
	return 0;
}