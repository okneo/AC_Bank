#include "FileService.h"
#include<iostream>
#include<fstream>
using namespace std;

FileService::FileService(string username, string password)
{
	ifstream acc;
	//acc.open('/' + username + '/' + "ID.cre", ios::in);			//The account type and password is stored in file ID.cre.
	acc.open(username + '/' + "ID.cre", ios::in);
	if (!acc.is_open())
	{
#if !(INCLUDE_ACCOUNT_CLASS)
		cout << "$$warnings: file not opened." << endl;
#endif
		is_logged_in = false;
		return;
	}
	char account_type;
	acc >> account_type;
	string pwd;
	acc >> pwd;
	if (pwd == password)
	{
		is_logged_in = true;
#if INCLUDE_ACCOUNT_CLASS
		switch (account_type)
		{
#if INCLUDE_ROOT_ACCOUNT
		case 'r':account = new root(username); break;
#endif
#if INCLUDE_BANK_ACCOUNT
		case 'b':account = new bank(username); break;
#endif
#if INCLUDE_USER_ACCOUNT
		case 'c':account = new credit_card(username); break;
		case 'd':account = new debit_card(username); break;
		case 'o':account = new online_banking(username); break;
#endif
		default:is_logged_in = false;
		}
#endif

#if !(INCLUDE_ACCOUNT_CLASS)
		switch (account_type)
		{
		case 'r':cout << "$$Root account, username " << username << endl; break;
		case 'b':cout << "$$Bank account, username " << username << endl; break;
		case 'c':cout << "$$Credit Card account, username " << username << endl; break;
		case 'd':cout << "$$Debit Card account, username " << username << endl; break;
		case 'o':cout << "$$Online Banking account, username " << username << endl; break;
		default:is_logged_in = false;
		}
		cout << "$$is_logged_in = " << is_logged_in << endl;
#endif
	}
	else
	{
		is_logged_in = false;
#if !(INCLUDE_ACCOUNT_CLASS)
		cout << "$$is_logged_in = " << is_logged_in << endl;
#endif
	}
	acc.close();
}

bool FileService::Interface()
{
	if (!is_logged_in)
	{
		cout << "Sorry, failed to log in." << endl;
		return true;			//true for login failure.
	}

#if (INCLUDE_ACCOUNT_CLASS)
	return account->Interface();
#endif

#if !(INCLUDE_ACCOUNT_CLASS)
	cout << "$$to process function account->Interface()" << endl;
	return false;
#endif
}

FileService::~FileService()
{
	if (is_logged_in)
	{
#if (INCLUDE_ACCOUNT_CLASS)
		delete account;
		system("cls");
#endif

#if !(INCLUDE_ACCOUNT_CLASS)
		cout<< "$$to process delete account" << endl;
#endif
	}
}
