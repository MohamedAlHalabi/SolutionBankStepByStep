


#include <iostream>
#include "clsBankClient.h" 
using namespace std; 


int main()
{
	clsBankClient Client = clsBankClient::Find("A101");
	Client.Print();


	clsBankClient Client1 = clsBankClient::Find("A101" , "1111");
	Client1.Print();
	cout << Client.IsClientExist("A101"); 

}

