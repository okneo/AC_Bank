#pragma once
#include<string>
#include<iostream>
#include<fstream>
#include<Windows.h>
#include<sstream>
#include<iomanip>
#include<direct.h>

#define IS_DEBUG_TIME false

#define INCLUDE_ACCOUNT_CLASS true

#define INCLUDE_ROOT_ACCOUNT true
#define INCLUDE_BANK_ACCOUNT true
#define INCLUDE_USER_ACCOUNT true

#define INCLUDE_FINANCIAL_SERVICES true
#define INCLUDE_ROOT_ACCOUNT_ADDITIONAL_FEATURES true

using namespace std;

//A user is allowed to login as an administrator of banks, a bank, a bank card or an online banking account.
//Logging in as an individual is meaningless and not allowed.

#if (INCLUDE_ACCOUNT_CLASS)
class AccountTypes
{
public:
	AccountTypes(string path);
	//clear the screen and pass the folder destination.
	
	virtual bool Message();
	//Message function is designed for every account to help communication across different accounts.
	//Meanwhile, a function to send message is also needed.
	//But sending messages differs from different account types.
	//So we think it is meaningless to declare those functions here.
	
	~AccountTypes();
	//We want to clear the screen every time logging in or out for privacy concerns.
	//Also, a prompt of successfully logging out is essencial.

	virtual bool Interface() = 0;
	//To avoid remembering every command at run time, users interact with several UI functions.
	//The UI funcions do not really do any calculation or such operation, they performs as guides.
protected:
	string _path;
	string find_path(string item);
	
	/*
	double get_number(string filename, string title);
	string get_string(string filename, string title);
	bool set_string(string filename, string title, string content);			//return true for set failure.
	bool set_number(string filename, string title, double num);
	*/

	virtual bool setProperties() = 0;
	//set property functions are designd to initiallize values of properties of the active account.
	//The definition of this type of functions are related to the specific account types,
	//so we declare it as a pure virtual function here.

	virtual bool reset_pwd();

	const std::string currentDateandTime();

	int get_char(char &c);
	int get_char(char &c, string s);
	int get_num(double &n); //only support nonnegative value.
	int get_num(double &n, string s); //only support nonnegative value.

	bool list_credit_card();
	bool credit_card_details(string serial);

	bool send_message(string target_acc, string msg);

	virtual bool transfer(string from_card_number, string to_card_number, double amount);

	//int get_current_root_asset(double &asset, double &backup, double &debt);
	//int set_current_root_asset(double &asset, double &backup, double &debt);
};

#if (INCLUDE_ROOT_ACCOUNT)
class root :public AccountTypes
{
	/*
	There is only one root account allowed in this system.
	The root account is designed for top management over other accounts.
	*/
public:
	root(string path);
	virtual bool Interface();
private:

	bool account_management();
	//Account management feature contains the following features:
	//View a card;
	//Credit Card Approve;
	//Credit Limit Management;
	//Interest Management;
	//Build A New Bank;
	//Back to Previous;
	//Back to Main Menu.

	bool publish_credit_card();
	/*
	To withdraw a credit card type is not allowed, because there may be someone already approved of this card.
	But we can always disapprove applications of this card type in the future ;)
	*/

#if(INCLUDE_FINANCIAL_SERVICES)
	bool financial_services_management();
#endif
	
	//bool view_card();
#if INCLUDE_ROOT_ACCOUNT_ADDITIONAL_FEATURES
	/*
	bool view_root_account(string card_number);
	bool view_bank_account(string card_number);
	bool view_creditcard_account(string card_number);
	bool view_debitcard_account(string card_number);
	bool view_onlinebanking_account(string card_number);
	*/
#endif

	bool credit_card_approve();
	//All credit card applications in a folder "CreditCardApplication".
	//This function offers the channel of credit card approve.
	//The credit card approve contains approve or not, which card to approve and credit limit distribution.
	/*
	bool getCreditCardApplication();
	//Designed for fetching outlines of all applications.
	//Reads from file applications.info
	//solved_or_not, application_time, applicants_name, 
	bool getCreditCardApplication(string app);
	//Designed for fetching details of an exact application.
	*/
#if INCLUDE_ROOT_ACCOUNT_ADDITIONAL_FEATURES
	bool createNewCreditCard(string card_number, string valid_date, int CVN, string billing_date, double annual_fee, double credit_limit, string name, string gender, string ID, string phone, string address, string postcode);
#endif
	
	bool credit_limit_management();
	//Offers to change the credit limit of a credit card.

#if INCLUDE_ROOT_ACCOUNT_ADDITIONAL_FEATURES
	bool build_new_bank();
	//Starts a new bank-level account.
	//bool terminate_bank();
	//Terminate a bank-level account.
#endif

	bool interest_management();
	//Provides the management of credit/debit interest.

	virtual bool setProperties();
	//basic service function called by constructor to initiallize some values.

};
#endif

#if (INCLUDE_BANK_ACCOUNT)
class bank :public AccountTypes
{
public:
	bank(string path);
	//A bank account provides management of the details of a user account.
	virtual bool Interface();
private:	
	bool AssociateOnlineBanking(const string &OnlineBankingAccount, const string &CardNumber);  
	//remember to verify identity.
	//To salute some silly banks.

	bool createNewDebitCard();

	bool createNewOnlineBankingAcc();

	//bool account_management();
	bool reset_user_account_pwd(string acc);

	bool view_account(string acc);
	//bool acc_operations(string acc);

	bool view_credit_acc(string acc);
	bool view_debit_acc(string acc);
	bool view_onlinebanking_acc(string acc);

	//bool adjust_acc(string acc);
	//bool disable_acc(string acc);
	bool adjust_temp_credit_limit(string acc);

	bool apply_credit_card();


	virtual bool setProperties();
};
#endif

#if (INCLUDE_USER_ACCOUNT)
class card :public AccountTypes
{
	//to insert some functions here.
public:
	card(string path);
	virtual bool Interface() = 0;
protected:
	//virtual bool credit(double amount) = 0;
	//virtual bool debit(double amount) = 0;
	virtual bool calculate_interest() = 0;
	//virtual bool setInterest(double x);

	//virtual bool transfer(string from_card_number, string to_card_number, double amount);

	virtual bool credit_or_debit(double amount);
	virtual bool setProperties() = 0;
	//virtual bool intelligent_UI(string command);
	//string card_number;
	//string card_holder_name
	double credit_limit;
	double temp_limit;
};

class credit_card :public card
{
public:
	credit_card(string path);
	virtual bool Interface();
private:
	virtual bool setProperties();
	//double interest_of_Cash_withdrawal_fee;
	//double minimum_Cash_withdrawal_fee;
	//double Overdraft_interest;

	//bool account_management();
	//bool credit(double amount);   //put money into bank
	//bool debit(double amount);	//take money from bank

	virtual bool view_bills(string date);
	bool view_info();
	//change password;
	//transfer;

	virtual bool calculate_interest();

	//bool financial_services();

	
	string card_number;
	string valid_date;
	int CVN;
	string billing_date;
	double annual_fee;
	//double credit_limit;
	string name;
	string gender;
	string ID;
	string phone;
	string address;
	string postcode;
	//double temp_limit;
	//double balance;
	
};

class debit_card :public card
{
public:
	debit_card(string path);
	virtual bool Interface();
private:
	virtual bool setProperties();

	bool view_info();

	bool view_transactions();

	virtual bool calculate_interest();

	string card_number;
	//string valid_date;
	//int CVN;
	//string billing_date;
	//double annual_fee;
	//double credit_limit;
	string name;
	string gender;
	string ID;
	string phone;
	string address;
	string postcode;
	//double temp_limit;
	//double balance;
};

class online_banking :public card
{
public:
	online_banking(string path);
	virtual bool Interface();
private:
	virtual bool setProperties();
	//virtual bool intelligent_UI(string command);
	//card bank_card;

	virtual bool calculate_interest();

	bool setup_tran();

	bool financial();

	string cards[32];
	int card_num;
	string name;
	string ID;
	string transaction_account;
	bool transaction_account_is_set;

	double total_asset = 0;
	double total_debt = 0;
};
#endif

#endif