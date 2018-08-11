/*
Programmed by Robert as the final homework of C++ in the summer of 2018.
Though as a personal work, the word "we" is preferred in the program.
Without the inspiration from my teacher, best friends and family, it's impossible for me to finish the project.
*/

/*
Limited by my energy, time and creativity, there will be some unavoidable bugs in the project,
though elegance and serenity have always been my pursuit of software design.
*/

#include<iostream>
#include<string>
#include"FileService.h"

using namespace std;

int main()
{
	string account, pwd;
	while (true)
	{
		cout << endl << "Please log in." << endl;
		cout << "Account: ";
		cin >> account;
		cout << "Password: ";
		cin >> pwd;
		FileService *acc;
		acc = new FileService(account, pwd);
		acc->Interface();
		delete acc;
		//system("cls");
	}
	return 0;
}
