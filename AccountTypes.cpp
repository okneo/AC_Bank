#include "AccountTypes.h"


#if (INCLUDE_ACCOUNT_CLASS)
AccountTypes::AccountTypes(string path)
{
	system("cls");
	//Clear the screen after logging in.

	_path = path;
	//_path points to the account's folder.
}

bool AccountTypes::Message()
{
	//the message file is named as message.io in the destination directory.
	//This function is designed to simply print every line in the file on screen.
	
	fstream MessageFile;
	//create a file object.

	MessageFile.open(find_path("message.io"));
	if (!MessageFile.is_open())
	{
		cout << "We cannot open the message file. Maybe it is missing.\n";
		return true;
	}
	//Open the message file and determine whether it is able to read or not.
	//Not being able to open and read a file may because various kinds of issues,
	//which are not considered as the main point in this project.

#if IS_DEBUG_TIME
	cout << "$$Reading message.io\n";
#endif
	//In this project, we will use a lot of design-time code to enhance the debug power.
	//When the debug is completed officially, the condition will be changed
	//and those code will not be compiled into the final program.

	string temp_s;
	getline(MessageFile, temp_s);
	if (temp_s.length() == 0)
		cout << "## No messages." << endl;

	while (temp_s.length() != 0)
	{
		cout << "# " << temp_s << endl;
		getline(MessageFile, temp_s);
	}
	//To determine whether we have reached the end of the file
	//and print every line on screen.

	return false;
}

AccountTypes::~AccountTypes()
{
	cout << "You have successfully logged out.\n";
	//Prompt when logging out.

	Sleep(1000);
	//system("cls");
	//We decide to clear screen every time while logging in or out
	//to wipe some unnecessary trace and usage.
}

string AccountTypes::find_path(string item)
{
	return _path + '/' + item;
	//returns the destination of a file in an account folder.
}

bool AccountTypes::reset_pwd()
{
	string temp_pwd;
	char acc_type;
	cout << "Enter old password: ";
	cin >> temp_pwd;
	ifstream id;
	string pwd;
	id.open(find_path("ID.cre"), ios::in);
	if (!id.is_open())
	{
		cout << "Cannot access this account properly. Please check the availability of this account." << endl;
		return true;
	}
	id >> acc_type;
	id >> pwd;

	id.close();
	
	if (temp_pwd == pwd)
	{
		cout << "Enter new password: ";
		cin >> temp_pwd;
		cout << "Re-enter password:  ";
		cin >> pwd;
		if (temp_pwd == pwd)
		{
			ofstream out;
			out.open(find_path("ID.cre"), ios::out);
			out << acc_type << endl;
			out << pwd << endl;
			out.close();
			cout << "Password reset successfully." << endl;
			return false;
		}
		else
		{
			cout << "Password not match." << endl;
			return true;
		}
	}
	else
	{
		cout << "Password not match." << endl;
		return true;
	}
}

/*
const std::string AccountTypes::currentDateandTime()
{
	time_t     now = time(0);
	struct tm  tstruct;
	char       buf[80];
	tstruct = *localtime(&now);
	strftime(buf, sizeof(buf), "%Y-%m-%d.%X", &tstruct);
	return buf;
}
*/
const std::string AccountTypes::currentDateandTime()
{
	struct tm newtime;
	char am_pm[] = "AM";
	__time64_t long_time;
	char timebuf[26];
	errno_t err;

	// Get time as 64-bit integer.  
	_time64(&long_time);
	// Convert to local time.  
	err = _localtime64_s(&newtime, &long_time);
	if (err)
	{
		printf("Invalid argument to _localtime64_s.");
		exit(1);
	}
	string time;
	time = to_string(newtime.tm_year + 1900) + "-";
	if (newtime.tm_mon + 1 < 10)
	{
		time += "0";
	}
	time += to_string(newtime.tm_mon + 1) + "-";
	if (newtime.tm_mday < 10)
	{
		time += "0";
	}
	time += to_string(newtime.tm_mday) + ".";
	if (newtime.tm_hour < 10)
	{
		time += "0";
	}
	time += to_string(newtime.tm_hour) + ":";
	if (newtime.tm_min < 10)
	{
		time += "0";
	}
	time += to_string(newtime.tm_min) + ":";
	if (newtime.tm_sec < 10)
	{
		time += "0";
	}
	time += to_string(newtime.tm_sec);
	return time;
}

int AccountTypes::get_char(char & c)
{
	string temp_s;
	cin >> temp_s;
	return get_char(c, temp_s);
}

int AccountTypes::get_char(char & c, string s)
{
	if (s.length())
	{
		c = s[0];
		return s.length() != 1;
	}
	else
	{
		c = '0';
		return -1;
	}
}

int AccountTypes::get_num(double & n)
{
	string temp_s;
	cin >> temp_s;
	return get_num(n, temp_s);
}

int AccountTypes::get_num(double & n, string s)
{
	if (s.length())
	{
		int len = s.length();
		int p_position = len;
		bool is_found = 0;
		for (int i = 0; i < len; ++i)
		{
			if (s[i] == '.')
			{
				if (is_found)
				{
					n = 0;
					return -1;
				}
				p_position = i;
				is_found = true;
			}
			else if (s[i]<'0' || s[i]>'9')
			{
				n = 0;
				return -1;
			}
		}
		n = 0;

		double power = 1;

		for (int i = p_position - 1; i >= 0; --i)
		{
			n += (s[i] - '0') * power;
			power *= 10;
		}

		power = 0.1;
		for (int i = p_position + 1; i < len; ++i)
		{
			n += (s[i] - '0') * power;
			power *= 0.1;
		}

		return 0;

	}
	else
	{
		n = 0;
		return -1;
	}
}

bool AccountTypes::list_credit_card()
{
	ifstream in;
	in.open("PublicInfo/CreditCardTemplates/credit_cards.info", ios::in);
	if (!in.is_open())
	{
		cout << "Some file missing or damaged." << endl;
		return true;
	}
	struct card
	{
		string serial;
		string name;
	};

	card card_info[32];
	int num = 0;

	while (getline(in, card_info[num].serial))
	{
		getline(in, card_info[num].name);
		++num;
	}

	in.close();

	cout << num << " credit card(s) found." << endl;
	for (int i = 0; i < num; ++i)
	{
		cout << "Serial number: " << card_info[i].serial << "   " << "Card name: " << card_info[i].name << endl;
	}

	return 0;
}

bool AccountTypes::credit_card_details(string serial)
{
	ifstream in;
	in.open("PublicInfo/CreditCardTemplates/" + serial + ".intro", ios::in);
	if (!in.is_open())
	{
		cout << "Some file missing or damaged." << endl;
		return true;
	}
	string temp_s;
	getline(in, temp_s);
	if (temp_s.length() == 0)
		cout << "## No introduction." << endl;

	while (temp_s.length() != 0)
	{
		cout << "# " << temp_s << endl;
		getline(in, temp_s);
	}

	in.close();

	return 0;
}

bool AccountTypes::send_message(string target_acc, string msg)
{
	ofstream app;
	app.open(target_acc + "/" + "message.io", ios::app);
	if (!app.is_open())
	{
		cout << "The target account cannot be accessed properly. Message cannot be sent." << endl;
		return true;
	}
	/*
	string temp_msg;
	while (getline(cin, temp_msg))
	{
		app << temp_msg << endl;
	}
	*/
	app << msg << endl;
	app.close();
	return 0;
}

/*
double AccountTypes::get_number(string filename, string title)
{
	ifstream in;
	in.open(find_path(filename), ios::in);
	string temp;
	double result;
	bool is_found = true;
	int i;
	int len;
	len = title.length();
	do
	{
		getline(in, temp);
		if (temp[len] != '=')
		{
			is_found = false;
			continue;
		}
		for (i = 0; i < len; ++i)
		{
			if (temp[i] != title[i])
				is_found = false;
		}
	} while ((temp[0] != EOF) && !is_found);
	for (i = 0; i < title.length(); ++i)
	{
		if (temp[i] != title[i])
			return 0;
	}
	string temp_result;
	for (i = len + 1; i < temp.length(); ++i)
	{
		temp_result[i - len - 1] = temp[i];
	}
	stringstream convert(temp_result);
	convert >> result;
	in.close();
	return result;
}*/

/*
string AccountTypes::get_string(string filename, string title)
{
	ifstream in;
	in.open(find_path(filename), ios::in);
	string temp;
	string result;
	bool is_found = true;
	int i;
	int len;
	len = title.length();
	
	do
	{
		is_found = true;
		getline(in, temp);
		if (temp[len] != '=')
		{
			is_found = false;
			continue;
		}
		for (i = 0; i < len; ++i)
		{
			if (temp[i] != title[i])
				is_found = false;
		}
	} while ((temp[0] != EOF) && !is_found);
	
	for (i = 0; i < title.length(); ++i)
	{
		if (temp[i] != title[i])
			return 0;
	}
	
	for (i = len + 1; i < temp.length(); ++i)
	{
		result[i - len - 1] = temp[i];
	}
	
	in.close();
	return result;
}
*/
bool AccountTypes::transfer(string from_card_number, string to_card_number, double amount)
{
	if (amount <= 0)
	{
		cout << "Input error. Transfer amount must be positive." << endl;
		return true;
	}

	ifstream from, to;
	from.open(from_card_number + "/asset.rec", ios::in);
	if (!from.is_open())
	{
		cout << "Some file missing. Operation cannot be done." << endl;
		return true;
	}

	double asset_from;
	from >> asset_from;

	from.close();

	if (amount < asset_from)
	{

		to.open(to_card_number + "/asset.rec", ios::in);
		if (!to.is_open())
		{
			cout << "Target account not available or some file missing. Operation cannot be done." << endl;
			return true;
		}
		double asset_to;
		to >> asset_to;

		to.close();

		asset_to += amount;
		asset_from -= amount;

		ofstream out;
		out.open(from_card_number + "/asset.rec", ios::out);
		out << asset_from << endl;
		out.close();
		out.open(to_card_number + "/asset.rec", ios::out);
		out << asset_to << endl;
		out.close();

		ofstream record;
		record.open(from_card_number + "/transactions.rec", ios::app);
		if (!record.is_open())
		{
			cout << "Some file missing." << endl;
		}
		record << currentDateandTime() << "   transfer  -" << amount << "USD" << endl;
		record.close();

		record.open(to_card_number + "/transactions.rec", ios::app);
		if (!record.is_open())
		{
			cout << "Some file missing." << endl;
		}
		record << currentDateandTime() << "   transfer  +" << amount << "USD" << endl;
		record.close();

		char acc_type;
		ifstream acc;
		acc.open(from_card_number + "/ID.cre", ios::in);
		if (!acc.is_open())
		{
			cout << "Some file missing." << endl;
		}
		acc >> acc_type;
		acc.close();
		if (acc_type == 'c')
		{
			string temp_date;
			temp_date = currentDateandTime();
			string date;
			date = "0000-00";
			//date[7] = '\0';
			for (int i = 0; i < 7; i++)
			{
				date[i] = temp_date[i];
			}
			ofstream rec;
			rec.open(from_card_number + "/transactions/" + date + ".rec", ios::app);
			rec << currentDateandTime() << "   transfer  -" << amount << "USD" << endl;
			rec.close();
			rec.open(from_card_number + "/transactions/" + date + ".ass", ios::out);
			rec << asset_from << endl;
			rec.close();
		}

		acc.open(to_card_number + "/ID.cre", ios::in);
		if (!acc.is_open())
		{
			cout << "Some file missing." << endl;
		}
		acc >> acc_type;
		acc.close();
		if (acc_type == 'c')
		{
			string temp_date;
			temp_date = currentDateandTime();
			string date;
			date = "0000-00";
			//date[7] = '\0';
			for (int i = 0; i < 7; i++)
			{
				date[i] = temp_date[i];
			}
			ofstream rec;
			rec.open(to_card_number + "/transactions/" + date + ".rec", ios::app);
			rec << currentDateandTime() << "   transfer  +" << amount << "USD" << endl;
			rec.close();
			rec.open(to_card_number + "/transactions/" + date + ".ass", ios::out);
			rec << asset_to << endl;
			rec.close();
		}

		return 0;
	}
	else
	{
		cout << "No enough balance to transfer." << endl;
		return true;
	}

	cin.clear();
	cin.sync();
}


#if (INCLUDE_ROOT_ACCOUNT)
root::root(string path)
	: AccountTypes(path)
{
	//the properties file of accounts is named as properties.info in the destination directory.
	/*
	fstream acc_info;
	acc_info.open('/' + _path + '/' + "properties.info");
	*/
	//Interface();
	setProperties();
	//The constructor makes the function call to set properties and values of the account.
}

bool root::Interface()
{
	//Function Interface() gathers all the sub-functions and provides the user interface.
	//Remembering every command seems stupid.

	cout << endl << "Welcome to AC Bank super management system!" << endl << endl;
	//Welcome.

	Message();
	//Interface() calls the Message() function to show messages to users after logging in.

	cout << endl;
	ifstream asset;
	asset.open(find_path("asset.rec"), ios::in);
	if (!asset.is_open())
	{
		cout << "Cannot open asset.rec. Check the availability of this file." << endl;
	}
	else
	{
		double total_asset, backup_asset, debt;
		asset >> total_asset >> backup_asset >> debt;
		cout << "Asset: " << total_asset << "   Back-up: " << backup_asset << "   Debt: " << debt << endl;
		asset.close();
	}

	cout << endl;

	char feature;
	while (true)
	{
		//A UI should always looping in order to accept a command rather than running once,
		//until a command tells it to exit.
		cout << "Services List" << endl
			<< "1: Account Management" << endl
#if INCLUDE_FINANCIAL_SERVICES
			<< "2: Financial Services Management" << endl
#endif
			<< "3: Password Reset" << endl
			<< "#: Logout" << endl
			<< "Please choose a service: ";
		//fflush(stdin);
		
		cin >> feature;
		//Links the main feature of a root account.
		
		//The main interface function links the following feature:
		//Account Managemet;
		//Financial Services Management;
		//Logout.

		switch (feature)
		{
		case '1':account_management(); break;
#if (INCLUDE_FINANCIAL_SERVICES)
		case '2':financial_services_management(); break;
#endif
		case '3':reset_pwd(); break;
		case '#':return false;			//Caution when logging out.
		default:cout << "Input error. Please input again." << endl;
		}
		//switch statement determines which feature to activate and continues the loop after the feature or after no feature.
		//only exit the infinite loop when user enters a '#' to logout.
	}
	//Most UI functions in this project use the same format as this one.
	//We use '*' and '#' to tell caller functions where to return, just like visiting a telephone bank.
	//The bool return type is both simple and meaningful.
	//For some functions, the bool return type also stands for whether an action is successful or not.
}

bool root::account_management()
{
	//sub-function account_management(). Provides account management services for root account.
	//This function is not a leaf node, so it is still necessary to use a loop.

	cout << endl << "Welcome to Account Management Section!" << endl << endl;
	//Welcome.

	char feature;
	//bool previous_or_main;
	while (true)
	{
		cout << "Services List" << endl
			<< "0: Publish A Credit Card" << endl
			<< "1: Credit Card Approve" << endl
			<< "2: Credit Limit Management" << endl
			<< "3: Interest Management" << endl
			<< "4: Build A New Bank" << endl
			//<< "*: Back to Previous" << endl
			<< "#: Go back" << endl
			<< "Please choose a service: ";
		cin >> feature;
		//Input a character standing for a service.
		
		//Account management feature contains the following features:
		//View a card;
		//Credit Card Approve;
		//Credit Limit Management;
		//Interest Management;
		//Build A New Bank;
		//Back to Previous;
		//Back to Main Menu.

		switch (feature)
		{
		case '0':publish_credit_card(); break;
		case '1':credit_card_approve(); break;
		case '2':credit_limit_management(); break;
		case '3':interest_management(); break;
#if INCLUDE_ROOT_ACCOUNT_ADDITIONAL_FEATURES
		case '4':build_new_bank(); break;
#endif
		//case '*':return false;
		case '#':return 0;			//false to previous and true to main menu.
		default:cout << "Input error. Please input again." << endl;
		}
		
		//switch sentence determines which function to activate.
		//the return value stands for return destination, previous or main.
	}
	//Use the same format as the main UI function.
	cin.clear();
	cin.sync();

	return false;
}

bool root::publish_credit_card()
{
	ifstream in;
	in.open(find_path("CreditCardInfo/CreditCard.info"), ios::in);
	if (!in.is_open())
	{
		cout << "Cannot open CreditCard.info. Please check the availability of this file." << endl;
		return true;
	}
	struct card_info
	{
		string serial;
		string name;
		string annual_fee;
	};
	card_info card[32];
	int num = 0;
	while (getline(in, card[num].serial))
	{
		getline(in, card[num].name);
		getline(in, card[num].annual_fee);
		++num;
	}

	in.close();

	string temp_serial;
	//bool have_same = false;

	cout << "We have these credit card(s), currently." << endl;
	list_credit_card();
	cout << "Please enter a new credit card information." << endl;
	cout << "Serial number: ";
	getchar();
	getline(cin, temp_serial);
	
	for (int i = 0; i < num; ++i)
	{
		if (card[i].serial == temp_serial)
		{
			cout << "Sorry, we have already had this serial number." << endl
				<< "Returning..." << endl;
			return true;
		}
	}

	card[num].serial = temp_serial;
	cout << "Card name:     ";
	getline(cin, card[num].name);
	cout << "Annual fee:    ";
	getline(cin, card[num].annual_fee);
	++num;

	ofstream out;
	out.open(find_path("CreditCardInfo/CreditCard.info"), ios::out);
	for (int i = 0; i < num; ++i)
	{
		out << card[i].serial << endl
			<< card[i].name << endl
			<< card[i].annual_fee << endl;
	}
	out.close();

	ofstream intro_file;
	intro_file.open("PublicInfo/CreditCardTemplates/" + card[num - 1].serial + ".intro", ios::out);
	string temp_msg;
	cout << "Please add some introduction about this card:" << endl;
	while (getline(cin, temp_msg))
	{
		intro_file << temp_msg << endl;
	}
	intro_file.close();

	ofstream info_file;
	info_file.open("PublicInfo/CreditCardTemplates/credit_cards.info", ios::app);
	if (!info_file.is_open())
	{
		cout << "Cannot open credit_cards.info. Check the availability of this file." << endl;
		return true;
	}
	info_file << card[num - 1].serial << endl
		<< card[num - 1].name << endl;
	info_file.close();


	cout << "OK. The new credit card has been added." << endl;

	//getchar();
	cin.clear();
	cin.sync();

	return 0;
}

bool root::financial_services_management()
{
	string current_asset;
	//string current_backup;
	//string current_debt;
	string last_asset;
	ifstream current_f, last_f;
	current_f.open(find_path("asset.rec"), ios::in);
	if (!current_f.is_open())
	{
		cout << "Cannot open asset.rec. Check the availability of this file." << endl;

		cin.clear();
		cin.sync();

		return true;
	}

	getline(current_f, current_asset);
	//getline(current_f, current_backup);
	//getline(current_f, current_debt);

	current_f.close();

	last_f.open("PublicInfo/FinancialServices/acb.info", ios::in);
	if (!last_f.is_open())
	{
		cout << "Cannot open acb.info. Check the availability of this file." << endl;

		cin.clear();
		cin.sync();

		return true;
	}

	getline(last_f, last_asset);

	last_f.close();

	cout << "Current asset is        $" << current_asset << endl
		 << "Last published asset is $" << last_asset << endl;

	cout << endl;

	char c;
	cout << "Update information? (y or n) ";
	cin >> c;
	if (c == 'y')
	{
		ofstream update;
		update.open("PublicInfo/FinancialServices/acb.info", ios::out);
		update << current_asset << endl;

		update.close();

		cout << "Returning..." << endl;

		cin.clear();
		cin.sync();

		return 0;
	}
	else
	{
		cout << "Returning..." << endl;
		
		cin.clear();
		cin.sync();

		return true;
	}
}
/*
bool root::view_card()
{
	string card_number;
	cout << "Please enter a card number to view: ";
	cin >> card_number;
	ifstream check;
	check.open(card_number + "/ID.cre", ios::in);
	if (!check.is_open())
	{
		cout<<"Cannot open ID.cre of account "<<card_number<<". Please check the availability of this account." << endl
			<< "Returning..." << endl;
	}
	char account_type;
	check >> account_type;
#if INCLUDE_ROOT_ACCOUNT_ADDITIONAL_FEATURES
	switch (account_type)
	{
	case 'r':view_root_account(card_number); break;
	case 'b':view_bank_account(card_number); break;
	case 'c':view_creditcard_account(card_number); break;
	case 'd':view_debitcard_account(card_number); break;
	case 'o':view_onlinebanking_account(card_number); break;
	default:cout << "Unknown account type. Returning...";
	}
#endif
#if !(INCLUDE_ROOT_ACCOUNT_ADDITIONAL_FEATURES)
	switch (account_type)
	{
	case 'r':cout << "$$view_root_account(" << card_number << ")" << endl; break;
	case 'b':cout << "$$view_bank_account(" << card_number << ")" << endl; break;
	case 'c':cout << "$$view_creditcard_account(" << card_number << ")" << endl; break;
	case 'd':cout << "$$view_debitcard_account(" << card_number << ")" << endl; break;
	case 'o':cout << "$$view_onlinebanking_account(" << card_number << ")" << endl; break;
	default:cout << "$$Unknown account type. Returning...";
	}
#endif
	cout << "Returning..." << endl;
	return false;
}

*/
bool root::credit_card_approve()
{
	double annual_fee;
	//double debit_discount;

	struct Application
	{
		string to_solve;
		string applicants_name;
		string applicants_ID;
		string gender;
		string age;
		string applicants_address;
		string applicants_postcode;
		string applicants_phone;
		string salary;
		string serial_number;
	};
	Application inst[32];
	int num_applicants = 0;
	//variables for credit card approve feature.

	ifstream application;
	application.open(find_path("CreditCardApplication/applications.info"), ios::in);
	if (!application.is_open())
	{
		cout << "Sorry, we cannot open applications.info properly." << endl;

		cin.clear();
		cin.sync();

		return true;
	}

	while (getline(application, inst[num_applicants].to_solve))
	{
		/*
		if (application.eof())
		{
			break;
		}
		*/

		//getline(application, inst[num_applicants].to_solve);

		//application >> inst[num_applicants].applicants_name;
		getline(application, inst[num_applicants].applicants_name);
		//application >> inst[num_applicants].applicants_ID;
		getline(application, inst[num_applicants].applicants_ID);
		//application >> inst[num_applicants].gender;
		getline(application, inst[num_applicants].gender);
		getline(application, inst[num_applicants].age);
		//application >> inst[num_applicants].applicants_address;
		getline(application, inst[num_applicants].applicants_address);
		getline(application, inst[num_applicants].applicants_postcode);
		//application >> inst[num_applicants].applicants_phone;
		getline(application, inst[num_applicants].applicants_phone);
		//application >> inst[num_applicants].salary;
		getline(application, inst[num_applicants].salary);
		//application >> inst[num_applicants].serial_number;
		getline(application, inst[num_applicants].serial_number);

		num_applicants++;
	}

	application.close();

	struct CreditCardInfo
	{
		string serial_number;
		string card_name;
		string annual_fee;
	};
	CreditCardInfo credit_card[32];

	ifstream credit;
	credit.open(find_path("CreditCardInfo/CreditCard.info"), ios::in);
	if (!credit.is_open())
	{
		cout << "Sorry, we cannot open CreditCard.info properly." << endl;

		cin.clear();
		cin.sync();

		return true;
	}

	int num_card = 0;
	while (getline(credit, credit_card[num_card].serial_number))
	{
		//getline(credit, credit_card[num_card].serial_number);
		
		/*		
		if (credit_card[num_card].serial_number[0] == EOF)
		{
			break;
		}
		*/


		getline(credit, credit_card[num_card].card_name);
		getline(credit, credit_card[num_card].annual_fee);
		//credit >> credit_card[num_card + 1].serial_number;
		
		num_card++;
	}

	credit.close();

	cout << num_applicants << " applications found." << endl;
	for (int i = 0; i < num_applicants; ++i)
	{
		//cout << i + 1 << ": " << applicants[i] << endl;
		cout << i + 1 << ": " << inst[i].gender << " " << inst[i].applicants_name << " applying for card " << inst[i].serial_number << endl;
	}
	cout << "0: Go previous." << endl;
	cout << endl;
	//show all credit card applications

	int n;

	while (true)
	{
		cout << "Please choose an application: ";
		cin >> n;

		n--;
		
		if (n == -1)
		{
			cout << "Returning..." << endl;
			break;
		}

		else if (n >= 0 && n <= num_applicants - 1)
		{
			
			if (inst[n].to_solve=="0")
			{
				cout << "This application has already been processed." << endl;
				continue;
			}
			int i;
			for (i = 0; i < num_card; i++)
			{
				if (inst[n].serial_number == credit_card[i].serial_number)
				{
					break;
				}
			}
			if (i >= num_card)
			{
				cout << "The application is applying for a invalid credit card." << endl;
				continue;
			}
			//To find application errors.
			//and make sure which credit card the applicant is applying for.

			cout << "Details of Applicant:" << endl
				<< "Applicant:  " << inst[n].gender << " " << inst[n].applicants_name << endl
				<< "ID:         " << inst[n].applicants_ID << endl
				<< "Age:        " << inst[n].age << endl
				<< "Address:    " << inst[n].applicants_address << endl
				<< "Postcode:   " << inst[n].applicants_postcode << endl
				<< "Phone:      " << inst[n].applicants_phone << endl
				<< "Salary:     " << inst[n].salary << endl;
			cout << "Details of The Card being Applied:" << endl
				<< "Serial:     " << credit_card[i].serial_number << endl
				<< "Card Name:  " << credit_card[i].card_name << endl
				<< "Annual Fee: " << credit_card[i].annual_fee << endl;

			cout << endl;
			
			string confirm_msg;
			cout << "Approve or not? (Type \"yes\" to approve, \"no\" to decline, others to back) ";
			cin >> confirm_msg;
			if (confirm_msg == "no")
			{
				inst[n].to_solve = "0";
				cout << "This application has been rejected." << endl;
				continue;
			}
			else if (confirm_msg == "yes")
			{
				srand(time(NULL));
				ifstream temp_file;
				string card_number;
				int CVN;
				CVN = rand() % 1000;
				if (CVN < 100)
				{
					CVN *= 10;
				}
				string valid_date;
				string temp_date;
				temp_date = currentDateandTime();
				//valid_date = temp_date[5] + temp_date[6] + "23";
				valid_date = "0023";
				valid_date[0] = temp_date[5];
				valid_date[1] = temp_date[6];
				//valid_date += "23";
				string billing_date;
				billing_date = "00";
				billing_date[0] = temp_date[8];
				billing_date[1] = temp_date[9];
				
				do 
				{
					card_number = "5257";
					int temp;
					for (int k = 0; k < 12; ++k)
					{
						temp = rand() % 10;
						card_number += to_string(temp);
					}
					temp_file.open(card_number + "/ID.cre", ios::in);
				} while (temp_file.is_open());
				
				inst[n].to_solve = "0";

				cout << "What's the credit limit to allocate? ";
				double credit_limit;
				cin >> credit_limit;

				get_num(annual_fee, credit_card[i].annual_fee);

				cout << "Okay." << endl
					<< "The credit card number is: " << card_number << endl
					<< "Valid date:                " << valid_date << endl
					<< "CVN code:                  " << CVN << endl
					<< "Billing date:              " << billing_date << endl
					<< "Credit limit is set to:    " << credit_limit << endl
					<< endl
					<< "Initial password is        000000" << endl << endl;
#if INCLUDE_ROOT_ACCOUNT_ADDITIONAL_FEATURES
				createNewCreditCard(card_number, valid_date, CVN, billing_date, annual_fee, credit_limit, inst[n].applicants_name, inst[n].gender, inst[n].applicants_ID, inst[n].applicants_phone, inst[n].applicants_address, inst[n].applicants_postcode);
#endif
#if !(INCLUDE_ROOT_ACCOUNT_ADDITIONAL_FEATURES)
				cout << "$$To process function createNewCreditCard..." << endl;
#endif

				continue;

			}
			else
			{
				cout << "Returning..." << endl;
				continue;
			}
		}
		
		else
		{
			cout << "Input error. Try again." << endl;
		}
	}
	/*
	else if (n >= 1 && n <= num_applicants)
	{
		ifstream in;
		in.open(find_path("CreditCardApplication/" + applicants[n - 1]), ios::in);
		if (!in.is_open())
		{
			cout << "Cannot open this application. Maybe some file missing." << endl;
			return true;
		}
		string temp_s;
		getline(in, temp_s);
		if (temp_s[0] == EOF)
			cout << "## No messages." << endl;
		while (temp_s[0] != EOF)
		{
			cout << "# " << temp_s << endl;
			getline(in, temp_s);
		}
		return false;
	}
	*/

	ofstream replace;
	replace.open(find_path("CreditCardApplication/applications.info"), ios::trunc);
	for (int j = 0; j < num_applicants; j++)
	{
		if (inst[j].to_solve == "0")
		{
			continue;
		}

		replace << inst[j].to_solve << endl
			<< inst[j].applicants_name << endl
			<< inst[j].applicants_ID << endl
			<< inst[j].gender << endl
			<< inst[j].age << endl
			<< inst[j].applicants_address << endl
			<< inst[j].applicants_postcode << endl
			<< inst[j].applicants_phone << endl
			<< inst[j].salary << endl
			<< inst[j].serial_number << endl;
	}
	replace.close();

	cin.clear();
	cin.sync();


	return false;
}
#if INCLUDE_ROOT_ACCOUNT_ADDITIONAL_FEATURES
bool root::createNewCreditCard(string card_number, string valid_date, int CVN, string billing_date, double annual_fee, double credit_limit, string name, string gender, string ID, string phone, string address, string postcode)
{
	char temp_number[32];
	int len = card_number.length();
	//temp_number[0] = '/';
	for (int i = 0; i < len; i++)
	{
		temp_number[i] = card_number[i];
	}
	temp_number[len] = '\0';

	if (_mkdir(temp_number) != 0)
	{
		cout << "Cannot make the directory." << endl;

		cin.clear();
		cin.sync();

		return true;
	}

	string temp_tran = "/transactions";
	for (int i = len; i < len + 14; i++)
	{
		temp_number[i] = temp_tran[i - len];
	}

	if (_mkdir(temp_number) != 0)
	{
		cout << "Cannot make the directory." << endl;

		cin.clear();
		cin.sync();

		return true;
	}

	ofstream out_f;

	out_f.open(card_number + "/asset.rec", ios::out);
	if (annual_fee > 0)
	{
		out_f << "-" << annual_fee << endl;
	}
	else
	{
		out_f << "0" << endl;
	}
		

	out_f.close();

	out_f.open(card_number + "/credit_card.info", ios::out);
	out_f << billing_date << endl
		<< credit_limit << endl
		<< "0" << endl;

	out_f.close();

	out_f.open(card_number + "/ID.cre", ios::out);
	out_f << "c" << endl
		<< "000000" << endl;

	out_f.close();

	out_f.open(card_number + "/message.io", ios::out);
	out_f << currentDateandTime() << "   Welcome aboard! " << gender << " " << name << "!" << endl;
	
	out_f.close();

	out_f.open(card_number + "/points.rec", ios::out);
	out_f << "0" << endl;

	out_f.close();

	out_f.open(card_number + "/properties.info", ios::out);
	out_f << valid_date << endl
		<< CVN << endl
		<< billing_date << endl
		<< annual_fee << endl
		<< credit_limit << endl
		<< name << endl
		<< gender << endl
		<< ID << endl
		<< phone << endl
		<< address << endl
		<< postcode << endl;

	out_f.close();

	out_f.open(card_number + "/transactions.rec", ios::out);
	
	out_f.close();

	return 0;

}
#endif
bool root::credit_limit_management()
{
	string card_number;
	string valid_date;
	string CVN;
	string billing_date;
	string annual_fee;
	string credit_limit;
	string name;
	string gender;
	string ID;
	string phone;
	string address;
	string postcode;
	cout << "Please enter the credit card number: ";
	cin >> card_number;

	ifstream check_cre;
	check_cre.open(card_number + "/ID.cre", ios::in);
	if (!check_cre.is_open())
	{
		cout << "Cannot open ID.cre of account " << card_number << ". Please check the availability of this account." << endl
			<< "Returning..." << endl;

		cin.clear();
		cin.sync();

		return true;
	}
	char tmp_type;
	check_cre >> tmp_type;
	if (tmp_type != 'c')
	{
		cout << "Card " << card_number << " is not a credit card." << endl
			<< "Returning..." << endl;

		check_cre.close();

		cin.clear();
		cin.sync();


		return true;
	}

	check_cre.close();


	ifstream in;
	in.open(card_number + "/properties.info", ios::in);
	
	if (!in.is_open())
	{
		cout << "Cannot open properties.info of account " << card_number << ". Please check the availability of this account." << endl
			<< "Returning..." << endl;

		cin.clear();
		cin.sync();

		return true;
	}

	//in >> valid_date;
	//in >> CVN;
	//in >> billing_date;
	//in >> annual_fee;
	//in >> credit_limit;
	getline(in, valid_date);
	getline(in, CVN);
	getline(in, billing_date);
	getline(in, annual_fee);
	getline(in, credit_limit);
	getline(in, name);
	getline(in, gender);
	getline(in, ID);
	getline(in, phone);
	getline(in, address);
	getline(in, postcode);

	in.close();

	cout << "The current credit limit of credit card " << card_number << " is " << credit_limit << "." << endl;
	cout << "Please enter the new limit: ";
	cin >> credit_limit;
	cout << "OK. The new credit limit is set to " << credit_limit << endl;

	ofstream out;
	out.open(card_number + "/properties.info", ios::in);
	out << valid_date << endl
		<< CVN << endl
		<< billing_date << endl
		<< annual_fee << endl
		<< credit_limit << endl
		<< name << endl
		<< gender << endl
		<< ID << endl
		<< phone << endl
		<< address << endl
		<< postcode << endl;
	out.close();

	cout << "Returning..." << endl;

	cin.clear();
	cin.sync();


	return false;
}
bool root::build_new_bank()
{
	string bank_name;
	ifstream test;
	do 
	{
		cout << "Enter the desired bank name: ";
		cin >> bank_name;
		test.open(bank_name + "/ID.cre", ios::in);
	} while (test.is_open());

	char temp_number[32];
	int len = bank_name.length();
	//temp_number[0] = '/';
	for (int i = 0; i < len; i++)
	{
		temp_number[i] = bank_name[i];
	}
	temp_number[len] = '\0';

	if (_mkdir(temp_number) != 0)
	{
		cout << "Cannot make the directory." << endl;

		cin.clear();
		cin.sync();

		return true;
	}

	ofstream out;
	out.open(bank_name + "/ID.cre", ios::out);
	out << "b" << endl
		<< "000000" << endl;

	out.close();

	out.open(bank_name + "/message.io", ios::out);
	out << currentDateandTime() << "   Welcome on board!" << endl;

	out.close();

	out.open(bank_name + "/properties.info", ios::out);

	out.close();

	cout << "Completed. Initial password is 000000. Returning..." << endl;

	cin.clear();
	cin.sync();


	return 0;
}
bool root::interest_management()
{
	ifstream credit, debit;
	credit.open("PublicInfo/CreditInterest.info", ios::in);
	if (!credit.is_open())
	{
		cout << "Cannot open CreditInterest.info. Please check the integrity of PublicInfo." << endl
			<< "Returning..." << endl;

		cin.clear();
		cin.sync();

		return true;
	}

	debit.open("PublicInfo/DebitInterest.info", ios::in);
	if (!credit.is_open())
	{
		cout << "Cannot open DebitInterest.info. Please check the integrity of PublicInfo." << endl
			<< "Returning..." << endl;

		cin.clear();
		cin.sync();

		return true;
	}

	double credit_interest;
	double debit_interest;

	credit >> credit_interest;
	debit >> debit_interest;

	credit.close();
	debit.close();

	cout << "Current credit interest is: " << credit_interest << endl
		 << "Current debit interest is:  " << debit_interest << endl;
	string select;
	cout << "Please select an interest to change: (input c for credit, d for debit, others for return.)";
	cin >> select;
	if (select == "c")
	{
		cout << "Enter a new credit interest: ";
		cin >> credit_interest;
		ofstream out;
		out.open("PublicInfo/CreditInterest.info", ios::out);
		out << credit_interest;
		out.close();
		cout << "The credit interest is set to " << credit_interest << endl;
	}
	else if (select == "d")
	{
		cout << "Enter a new debit interest: ";
		cin >> debit_interest;
		ofstream out;
		out.open("PublicInfo/DebitInterest.info", ios::out);
		out << debit_interest;
		out.close();
		cout << "The debit interest is set to " << debit_interest << endl;
	}
	cout << "Returning..." << endl;

	cin.clear();
	cin.sync();

	return false;
}
bool root::setProperties()
{
	return 0;
}
#endif

#endif

#if INCLUDE_BANK_ACCOUNT
bank::bank(string path)
	:AccountTypes(path)
{
	setProperties();
}

bool bank::Interface()
{
	Message();
	//Interface() calls the Message() function to show messages to users after logging in.

	cout << endl;

	string feature;
	while (true)
	{
		//A UI should always looping in order to accept a command rather than running once,
		//until a command tells it to exit.
		cout << endl
			<< "Services List" << endl
			<< "1: Associate Online Banking" << endl
			<< "2: Create New Debit Card" << endl
			<< "3: Create Online Banking Account" << endl
			<< "4: Reset User Account Password" << endl
			<< "5: View Account Info" << endl
			<< "6: Adjust Credit Card Temp Limit" << endl
			<< "7: Apply New Credit Card" << endl
			<< "8: Password Reset" << endl
			<< "#: Logout" << endl
			<< "Please enter the serial number to choose a service ;) ";
		cin >> feature;
		if (feature == "1")
		{
			string online_acc;
			string card_num;
			cout << "Please input online banking account:   ";
			cin >> online_acc;
			cout << "Please input card number to associate: ";
			cin >> card_num;
			AssociateOnlineBanking(online_acc, card_num);
		}
		else if (feature == "2")
		{
			createNewDebitCard();
		}
		else if (feature == "3")
		{
			createNewOnlineBankingAcc();
		}
		else if (feature == "4")
		{
			string acc;
			cout << "Please input the account: ";
			cin >> acc;
			reset_user_account_pwd(acc);
		}
		else if (feature == "5")
		{
			string acc;
			cout << "Please input the account: ";
			cin >> acc;
			view_account(acc);
		}
		else if (feature == "6")
		{
			string acc;
			cout << "Please input the account: ";
			cin >> acc;
			adjust_temp_credit_limit(acc);
		}
		else if (feature == "7")
		{
			apply_credit_card();
		}
		else if (feature == "8")
		{
			reset_pwd();
		}
		else if (feature == "#")
		{

			cin.clear();
			cin.sync();

			return 0;
		}
		else
		{
			cout << "Input error. Try again." << endl;
		}
	}
}

bool bank::AssociateOnlineBanking(const string & OnlineBankingAccount, const string & CardNumber)
{
	char type;
	ifstream type_f;
	type_f.open(OnlineBankingAccount + "/ID.cre", ios::in);
	if (!type_f.is_open())
	{
		cout << "Cannot load the online banking account properly. Operation cannot be done." << endl;

		cin.clear();
		cin.sync();

		return true;
	}
	type_f >> type;

	type_f.close();

	if (type != 'o')
	{
		cout << "This is not an online banking account." << endl;

		cin.clear();
		cin.sync();

		return true;
	}

	string name;
	string ID;
	string transaction_acc;

	ifstream online_banking_acc;
	online_banking_acc.open(OnlineBankingAccount + "/properties.info", ios::in);
	if (!online_banking_acc.is_open())
	{
		cout << "Cannot load the online banking account properly. Operation cannot be done." << endl;

		cin.clear();
		cin.sync();

		return true;
	}

	getline(online_banking_acc, name);
	getline(online_banking_acc, ID);
	getline(online_banking_acc, transaction_acc);

	online_banking_acc.close();

	char type_t;
	ifstream type_tf;
	type_tf.open(CardNumber + "/ID.cre", ios::in);
	if (!type_tf.is_open())
	{
		cout << "Cannot load the online banking account properly. Operation cannot be done." << endl;

		cin.clear();
		cin.sync();

		return true;
	}
	type_tf >> type_t;

	type_tf.close();

	string t_ID;

	if (type_t == 'c')
	{
		ifstream auth;
		auth.open(CardNumber + "/properties.info", ios::in);
		getline(auth, t_ID);
		getline(auth, t_ID);
		getline(auth, t_ID);
		getline(auth, t_ID);
		getline(auth, t_ID);
		getline(auth, t_ID);
		getline(auth, t_ID);
		getline(auth, t_ID);

		if (t_ID == ID)
		{
			ofstream out;
			out.open(OnlineBankingAccount + "/OnlineAccounts.exchange", ios::app);
			out << CardNumber << endl;

			out.close();

		}
		else
		{
			cout << "Error: The destination card does not belong to the online banking account holder." << endl;

			cin.clear();
			cin.sync();

			return true;
		}
	}
	else if (type_t == 'd')
	{
		ifstream auth;
		auth.open(CardNumber + "/properties.info", ios::in);
		getline(auth, t_ID);
		getline(auth, t_ID);
		getline(auth, t_ID);

		if (t_ID == ID)
		{
			ofstream out;
			out.open(OnlineBankingAccount + "/OnlineAccounts.exchange", ios::app);
			out << CardNumber << endl;

			out.close();

		}
		else
		{
			cout << "Error: The destination card does not belong to the online banking account holder." << endl;

			cin.clear();
			cin.sync();

			return true;
		}
	}
	else
	{
		cout << "Unknown card type. Operation cannot be done.";

		cin.clear();
		cin.sync();

		return true;
	}
}

bool bank::createNewDebitCard()
{
	string name;
	string gender;
	string ID;
	string phone;
	string address;
	string postcode;

	getchar();

	cout << "Please enter applicant's information:" << endl;
	cout << "Name:         ";
	getline(cin, name);
	cout << "Appellation:  ";
	getline(cin, gender);
	cout << "ID:           ";
	getline(cin, ID);
	cout << "Phone number: ";
	getline(cin, phone);
	cout << "Address:      ";
	getline(cin, address);
	cout << "Postcode:     ";
	getline(cin, postcode);

	cout << endl;

	cout << "Just to confirm:" << endl
		<< "Name:         " << name << endl
		<< "Appellation:  " << gender << endl
		<< "ID:           " << ID << endl
		<< "Phone number: " << phone << endl
		<< "Address:      " << address << endl
		<< "Postcode:     " << postcode << endl;

	string confirm;
	cout << endl
		<< "Confirm? (y to confirm) ";
	cin >> confirm;
	if (confirm == "y")
	{
		srand(time(NULL));
		ifstream temp_file;
		string card_number;
		do
		{
			card_number = "62";
			int temp;
			for (int k = 0; k < 17; ++k)
			{
				temp = rand() % 10;
				card_number += to_string(temp);
			}
			temp_file.open(card_number + "/ID.cre", ios::in);
		} while (temp_file.is_open());

		char temp_number[32];
		int len = card_number.length();
		//temp_number[0] = '/';
		for (int i = 0; i < len; i++)
		{
			temp_number[i] = card_number[i];
		}
		temp_number[len] = '\0';

		if (_mkdir(temp_number) != 0)
		{
			cout << "Cannot make the directory." << endl;

			cin.clear();
			cin.sync();

			return true;
		}

		ofstream out;
		out.open(card_number + "/asset.rec", ios::out);
		out << "0" << endl;

		out.close();

		out.open(card_number + "/ID.cre", ios::out);
		out << "d" << endl
			<< "000000" << endl;

		out.close();

		out.open(card_number + "/message.io", ios::out);
		out << currentDateandTime() << "   Welcome on board! " << gender << " " << name << "!" << endl;
		
		out.close();

		out.open(card_number + "/properties.info", ios::out);
		out << name << endl
			<< gender << endl
			<< ID << endl
			<< phone << endl
			<< address << endl
			<< postcode << endl;

		out.close();

		out.open(card_number + "/transactions.rec", ios::out);

		out.close();

		cout << "The card number is: " << card_number << "   Initial password is 000000" << endl
			<< "Returning..." << endl;

		cin.clear();
		cin.sync();


		return 0;
	}
	else
	{
		cout << "OK. Cancelled. Returning..." << endl;

		cin.clear();
		cin.sync();

		return true;
	}
}

bool bank::createNewOnlineBankingAcc()
{
	ifstream test;

	string name;
	string ID;
	string acc;
	do
	{
		cout << "Please input a desired user name: ";
		cin >> acc;
		test.open(acc + "/ID.cre", ios::in);
	} while (test.is_open());

	getchar();

	cout << "Please input your name: ";
	getline(cin, name);
	cout << "Please input your ID:   ";
	getline(cin, ID);

	cout << endl
		<< "Just to confirm:" << endl
		<< "User name: " << acc << endl
		<< "Name:      " << name << endl
		<< "ID:        " << ID << endl;

	string confirm;
	cout << "Enter y to confirm, others to reject: ";
	cin >> confirm;
	if (confirm == "y")
	{
		char temp_number[32];
		int len = acc.length();
		//temp_number[0] = '/';
		for (int i = 0; i < len; i++)
		{
			temp_number[i] = acc[i];
		}
		temp_number[len] = '\0';

		if (_mkdir(temp_number) != 0)
		{
			cout << "Cannot make the directory." << endl;

			cin.clear();
			cin.sync();

			return true;
		}

		ofstream out;
		out.open(acc + "/ID.cre", ios::out);
		out << "o" << endl
			<< "000000" << endl;

		out.close();

		out.open(acc + "/message.io", ios::out);
		out << currentDateandTime() << "   Welcome on board!" << endl;

		out.close();

		out.open(acc + "/OnlineAccounts.exchange", ios::out);

		out.close();

		out.open(acc + "/properties.info", ios::out);
		out << name << endl
			<< ID << endl
			<< "0" << endl;

		out.close();
		
		cout << "Completed. The initial password is 000000." << endl;
	}
	else
	{
		cout << "Rejected. Returning..." << endl;

		cin.clear();
		cin.sync();

		return true;
	}
}

bool bank::reset_user_account_pwd(string acc)
{
	ifstream type_f;
	type_f.open(acc + "/ID.cre", ios::in);
	if (!type_f.is_open())
	{
		cout << "Cannot access this account properly. Operation cannot be done." << endl;

		cin.clear();
		cin.sync();

		return true;
	}
	char type;
	type_f >> type;

	type_f.close();

	string pwd;
	if (type == 'c' || type == 'd' || type == 'o')
	{
		cout << "Enter new password: ";
		cin >> pwd;
		ofstream reset;
		reset.open(acc + "/ID.cre", ios::out);
		reset << type << endl
			<< pwd << endl;

		reset.close();

		cout << "Password successfully reset." << endl;

		cin.clear();
		cin.sync();


		return 0;
	}
	else
	{
		cout << "Unknown account type or this account cannot be reset." << endl;

		cin.clear();
		cin.sync();

		return true;
	}
}

bool bank::view_account(string acc)
{
	ifstream in;
	in.open(acc + "/ID.cre", ios::in);
	if (!in.is_open())
	{
		cout << "Unable to access the account properly. Returning..." << endl;

		cin.clear();
		cin.sync();

		return true;
	}
	char type;
	in >> type;
	
	in.close();

	if (type == 'c')
	{
		view_credit_acc(acc);

		cin.clear();
		cin.sync();

		return 0;
	}
	else if (type == 'd')
	{
		view_debit_acc(acc);

		cin.clear();
		cin.sync();

		return 0;
	}
	else if (type == 'o')
	{
		view_onlinebanking_acc(acc);

		cin.clear();
		cin.sync();

		return 0;
	}
	else
	{
		cout << "Unknown card type." << endl;

		cin.clear();
		cin.sync();

		return true;
	}
}

bool bank::view_credit_acc(string acc)
{

	ifstream asset_f;
	asset_f.open(acc + "/asset.rec", ios::in);
	if (asset_f.is_open())
	{
		string balance;
		asset_f >> balance;

		asset_f.close();

		cout << "Balance: " << balance << endl;
	}


	ifstream last_bill_f;
	last_bill_f.open(acc + "/last_bill.rec", ios::in);
	if (last_bill_f.is_open())
	{
		double last_bill;
		double minimum;
		last_bill_f >> last_bill
			>> minimum;

		last_bill_f.close();

		cout << "Last bill: " << last_bill << "   Minimum repayment: " << minimum << endl;
	}

	ifstream points_f;
	points_f.open(acc + "/points.rec", ios::in);
	if (points_f.is_open())
	{
		double points;
		points_f >> points;

		points_f.close();

		cout << "Points: " << points << endl;
	}

	string valid_date;
	string CVN;
	string billing_date;
	string annual_fee;
	string credit_limit;
	string name;
	string gender;
	string ID;
	string phone;
	string address;
	string postcode;

	ifstream in_f;
	in_f.open(acc + "/properties.info", ios::in);
	getline(in_f, valid_date);
	getline(in_f, CVN);
	getline(in_f, billing_date);
	getline(in_f, annual_fee);
	getline(in_f, credit_limit);
	getline(in_f, name);
	getline(in_f, gender);
	getline(in_f, ID);
	getline(in_f, phone);
	getline(in_f, address);
	getline(in_f, postcode);

	in_f.close();

	cout << "Valid date:   " << valid_date << endl
		<< "CVN code:     " << CVN << endl
		<< "Billing date: " << billing_date << endl
		<< "Annual fee:   " << annual_fee << endl
		<< "Credit limit: " << credit_limit << endl
		<< "Name:         " << name << endl
		<< "ID:           " << ID << endl
		<< "Phone:        " << phone << endl
		<< "Address:      " << address << endl
		<< "Postcode:     " << postcode << endl;

	cin.clear();
	cin.sync();


	return 0;
}

bool bank::view_debit_acc(string acc)
{
	ifstream asset_f;
	asset_f.open(acc + "/asset.rec", ios::in);
	if (asset_f.is_open())
	{
		string balance;
		asset_f >> balance;

		asset_f.close();

		cout << "Balance: " << balance << endl;
	}

	ifstream prop_f;
	prop_f.open(acc + "/properties.info", ios::in);
	if (prop_f.is_open())
	{
		string name;
		string gender;
		string ID;
		string phone;
		string address;
		string postcode;

		getline(prop_f, name);
		getline(prop_f, gender);
		getline(prop_f, ID);
		getline(prop_f, phone);
		getline(prop_f, address);
		getline(prop_f, postcode);

		prop_f.close();

		cout << "Name:     " << name << endl
			<< "ID:       " << ID << endl
			<< "Phone:    " << phone << endl
			<< "Address:  " << address << endl
			<< "Postcode: " << postcode << endl;
	}

	cin.clear();
	cin.sync();


	return 0;
}

bool bank::view_onlinebanking_acc(string acc)
{
	ifstream prop;
	prop.open(acc + "/properties.info", ios::in);
	if (prop.is_open())
	{
		string name;
		string ID;
		string transaction_acc;

		getline(prop, name);
		getline(prop, ID);
		getline(prop, transaction_acc);

		prop.close();

		cout << "Name:                           " << name << endl
			<< "ID:                             " << ID << endl
			<< "Transaction Account Associated: " << transaction_acc << endl;
	}

	ifstream ass_acc_f;
	ass_acc_f.open(acc + "/OnlineAccounts.exchange", ios::in);
	if (ass_acc_f.is_open())
	{
		cout << "Associated Account:" << endl;
		string account;
		while (getline(ass_acc_f, account))
		{
			cout << account << endl;
		}

		ass_acc_f.close();

	}

	cin.clear();
	cin.sync();


	return 0;
}

bool bank::adjust_temp_credit_limit(string acc)
{
	ifstream type_f;
	type_f.open(acc + "/ID.cre", ios::in);
	if (!type_f.is_open())
	{
		cout << "Cannot access this account properly. Operation cannot be done." << endl;

		cin.clear();
		cin.sync();

		return true;
	}

	char type;
	type_f >> type;

	type_f.close();

	if (type == 'c')
	{
		string billing_date;
		string limit;
		string temp_limit;

		ifstream credit_card_f;
		credit_card_f.open(acc + "/credit_card.info", ios::in);
		if (!credit_card_f.is_open())
		{
			cout << "Cannot find credit_card.info. Operation cannot be done." << endl;

			cin.clear();
			cin.sync();

			return true;
		}
		getline(credit_card_f, billing_date);
		getline(credit_card_f, limit);
		getline(credit_card_f, temp_limit);

		credit_card_f.close();

		cout << "The current temp limit is " << temp_limit << endl;
		cout << "Enter the new temp limit: ";
		cin >> temp_limit;

		ofstream out;
		out.open(acc + "/credit_card.info", ios::out);
		out << billing_date << endl
			<< limit << endl
			<< temp_limit << endl;

		out.close();
	}
	else
	{
		cout << "This is not a credit card." << endl;

		cin.clear();
		cin.sync();

		return true;
	}
}

bool bank::apply_credit_card()
{
	string cserial;
	string cname;
	ifstream overall;
	while (true)
	{
		overall.open("PublicInfo/CreditCardTemplates/credit_cards.info", ios::in);
		if (!overall.is_open())
		{
			cout << "Some file missing. Operation cannot be done." << endl;

			cin.clear();
			cin.sync();

			return true;
		}

		cout << "Currently, these cards are available." << endl;
		while (getline(overall, cserial))
		{
			getline(overall, cname);
			cout << cserial << "   " << cname << endl;
		}

		overall.close();

		string serial;
		cout << "Please choose a serial number: (enter back to return) ";
		cin >> serial;
		
		if (serial == "back")
		{
			break;
		}

		ifstream intro;
		intro.open("PublicInfo/CreditCardTemplates/" + serial + ".intro", ios::in);
		if (!intro.is_open())
		{
			cout << "Cannot find this card." << endl;
			continue;
		}
		string temp_intro;
		while (getline(intro, temp_intro))
		{
			cout << temp_intro << endl;
		}

		intro.close();

		string confirm;
		cout << "Apply this card? (y to confirm) ";
		cin >> confirm;
		if (confirm == "y")
		{
			string applicants_name;
			string applicants_ID;
			string gender;
			string age;
			string applicants_address;
			string applicants_postcode;
			string applicants_phone;
			string salary;
			cout << "Please provide the information of the applicant:" << endl;
			getchar();
			cout << "Name:        ";
			getline(cin, applicants_name);
			cout << "ID:          ";
			getline(cin, applicants_ID);
			cout << "Appellation: ";
			getline(cin, gender);
			cout << "Age:         ";
			getline(cin, age);
			cout << "Address:     ";
			getline(cin, applicants_address);
			cout << "Postcode:    ";
			getline(cin, applicants_postcode);
			cout << "Phone:       ";
			getline(cin, applicants_phone);
			cout << "Salary:      ";
			getline(cin, salary);

			cout << "Just to confirm:" << endl
				<< "Name:        " << applicants_name << endl
				<< "ID:          " << applicants_ID << endl
				<< "Appellation: " << gender << endl
				<< "Age:         " << age << endl
				<< "Address:     " << applicants_address << endl
				<< "Postcode:    " << applicants_postcode << endl
				<< "Phone:       " << applicants_phone << endl
				<< "Salary:      " << salary << endl
				<< "Serial:      " << serial << endl;

			cout << "Confirm or not? (y to confirm) ";
			cin >> confirm;
			if (confirm == "y")
			{
				ofstream appl;
				appl.open("root/CreditCardApplication/applications.info", ios::app);
				appl << "1" << endl
					<< applicants_name << endl
					<< applicants_ID << endl
					<< gender << endl
					<< age << endl
					<< applicants_address << endl
					<< applicants_postcode << endl
					<< applicants_phone << endl
					<< salary << endl
					<< serial << endl;

				appl.close();

				cout << "Application sent. Thank you very much!" << endl;
				continue;
			}
			else
			{
				cout << "Cancelled. Returning..." << endl;
				continue;
			}
		}
		else
		{
			cout << "Returning..." << endl;
			continue;
		}
	}

	cin.clear();
	cin.sync();


	return 0;
}

bool bank::setProperties()
{
	return false;
}

#endif

#if INCLUDE_USER_ACCOUNT
card::card(string path)
	: AccountTypes(path)
{
	//setProperties();
}


credit_card::credit_card(string path)
	:card(path)
{
	setProperties();
	
	string temp_date;
	temp_date = currentDateandTime();
	string date;
	date = "00";
	date[0] = temp_date[8];
	date[1] = temp_date[9];
	if (date == billing_date)
	{
		ifstream asset;
		asset.open(find_path("asset.rec"), ios::in);
		double ass;
		asset >> ass;

		asset.close();

		ofstream bill;
		bill.open(find_path("last_bill.rec"), ios::out);
		if (ass >= 0)
		{
			bill << 0 << endl
				<< 0 << endl;
		}
		else
		{
			bill << abs(ass) << endl
				<< abs(ass)*0.1 << endl;
		}

		bill.close();

	}

	cin.clear();
	cin.sync();

}

bool credit_card::Interface()
{
	//Function Interface() gathers all the sub-functions and provides the user interface.
	//Remembering every command seems stupid.

	cout << endl << "Welcome to back, " << gender << " " << name << "!" << endl << endl;
	//Welcome.

	Message();
	//Interface() calls the Message() function to show messages to users after logging in.

	cout << endl;

	ifstream balance_f;
	balance_f.open(find_path("asset.rec"), ios::in);
	double balance;
	balance_f >> balance;
	balance_f.close();
	cout << "At the time of login, your balance is $" << balance << endl
		<< "Credit limit is set to $" << credit_limit << endl;

	cout << endl;

	string feature;
	while (true)
	{
		//A UI should always looping in order to accept a command rather than running once,
		//until a command tells it to exit.
		cout << endl
			<< "Services List" << endl
			<< "1: Credit" << endl
			<< "2: Debit" << endl
			<< "3: Transfer" << endl
			<< "4: View Bills" << endl
			<< "5: View Card Info" << endl
			<< "6: Password Reset" << endl
			<< "#: Logout" << endl
			<< "Please enter the serial number to choose a service ;) ";
		cin >> feature;
		//Links the main feature of a credit card account.


		if (feature == "1")
		{
			double amount;
			cout << "Please enter the amount you want to credit: ";
			while (get_num(amount))
			{
				cout << "Input error. You can just input 0 to return." << endl;
			}
			if (amount <= 0)
			{
				continue;
			}
			credit_or_debit(amount);
		}
		else if (feature == "2")
		{
			double amount;
			cout << "Please enter the amount you want to debit: ";
			while (get_num(amount))
			{
				cout << "Input error. You can just input 0 to return." << endl;
			}
			if (amount <= 0)
			{
				continue;
			}
			amount *= -1;
			credit_or_debit(amount);
		}
		else if (feature == "3")
		{
			string card_num;
			double amount;
			cout << "Please input the destination card number: ";
			/*
			if (getline(cin, card_num))
			{
				continue;
			}
			*/
			//getline(cin, card_num);

			cin.clear();
			cin.sync();

			getchar();

			cin >> card_num;
			cout << "Please input amount to transfer: ";
			while (get_num(amount))
			{
				cout << "Input error. You can just input 0 to return." << endl;
			}
			if (amount <= 0)
			{
				continue;
			}
			transfer(_path, card_num, amount);
		}
		else if (feature == "4")
		{
			string date;
			cout << "Please input the date: (eg. 2018-06) ";
			cin >> date;
			view_bills(date);
		}
		else if (feature == "5")
		{
			view_info();
		}
		else if (feature == "6")
		{
			reset_pwd();
		}
		else if (feature == "#")
		{
			cin.clear();
			cin.sync();

			return false;
		}
		else
		{
			cout << "Input error. Please input again." << endl;
		}

	}
}

bool credit_card::setProperties()
{
	ifstream prop;
	prop.open(find_path("properties.info"), ios::in);
	if (!prop.is_open())
	{
		cout << "Some file missing. The account cannot be set up." << endl;

		cin.clear();
		cin.sync();

		return true;
	}
	card_number = _path;
	getline(prop, valid_date);
	
	string temp_CVN_s;
	double temp_CVN_d;
	getline(prop, temp_CVN_s);
	get_num(temp_CVN_d, temp_CVN_s);
	CVN = temp_CVN_d;
	
	getline(prop, billing_date);

	string temp_af;
	getline(prop, temp_af);
	get_num(annual_fee, temp_af);

	string temp_cl;
	getline(prop, temp_cl);
	get_num(credit_limit, temp_cl);

	getline(prop, name);
	getline(prop, gender);
	getline(prop, ID);
	getline(prop, phone);

	getline(prop, address);
	getline(prop, postcode);

	prop.close();

	prop.open(find_path("credit_card.info"), ios::in);
	if (!prop.is_open())
	{
		cout << "Some file missing. The account cannot be set up." << endl;

		cin.clear();
		cin.sync();

		return true;
	}
	prop >> temp_limit;
	prop >> temp_limit;
	prop >> temp_limit;

	prop.close();
}

/*
bool credit_card::credit(double amount)
{
	ifstream asset_f;
	asset_f.open(find_path("asset.rec"), ios::in);
	if (!asset_f.is_open())
	{
		cout << "Some file misssing. Returning..." << endl;
		return true;
	}
	double balance;
	asset_f >> balance;
	
	asset_f.close();

	balance += amount;
	ofstream asset_out;
	asset_out.open(find_path("asset.rec"), ios::out);
	asset_out << balance << endl;
	
	asset_out.close();

	ofstream record;
	record.open(find_path("transactions.rec"), ios::app);
	record << currentDateandTime() << "   credit  +" << amount << "USD" << endl;
	record.close();
	string temp_date;
	temp_date = currentDateandTime();
	string date;
	date = temp_date;
	date[7] = '\0';
	record.open(find_path("transactions/" + date + ".rec"), ios::app);
	record << currentDateandTime() << "   credit  +" << amount << "USD" << endl;
	record.close();

	record.open(find_path("transactions/" + date + ".ass"), ios::out);
	record << balance << endl;

	record.close();

	ifstream asset_rf;
	asset_rf.open("root/asset.rec", ios::in);
	double asset_total;
	double asset_backup;
	double asset_debt;

	asset_rf.close();

	asset_total += amount;
	asset_backup += amount;
	asset_debt += amount;

	ofstream asset_out;
	asset_out.open("root/asset.rec", ios::out);
	asset_out << asset_total << endl
		<< asset_backup << endl
		<< asset_debt << endl;

	asset_out.close();

	cout << "Credit " << amount << "USD" << " successfully." << endl
		<< "Thank you very much!" << endl;

	return 0;
}
*/

bool card::credit_or_debit(double amount)
{
	ifstream acc_type;
	acc_type.open(find_path("ID.cre"), ios::in);
	char tmp_type;
	acc_type >> tmp_type;

	acc_type.close();

	bool is_credit_card;
	if (tmp_type == 'c')
	{
		is_credit_card = true;
	}
	else
	{
		is_credit_card = false;
	}

	bool to_debit;
	if (amount < 0)
	{
		to_debit = true;
	}
	else
	{
		to_debit = false;
	}

	ifstream asset_rf;
	asset_rf.open("root/asset.rec", ios::in);
	double asset_total;
	double asset_backup;
	double asset_debt;

	asset_rf >> asset_total
		>> asset_backup
		>> asset_debt;

	asset_rf.close();

	ifstream asset_f;
	asset_f.open(find_path("asset.rec"), ios::in);
	if (!asset_f.is_open())
	{
		cout << "Some file misssing. Returning..." << endl;

		cin.clear();
		cin.sync();

		return true;
	}
	double balance;
	asset_f >> balance;	//current account balance;

	asset_f.close();

	//balance += amount;

	if (to_debit)
	{
		if (abs(balance + amount) < credit_limit + temp_limit)
		{
			if (asset_backup + amount >= 0)
			{
				if (balance + amount > 0)
				{
					asset_total += amount;
					asset_backup += amount;
					asset_debt += amount;
				}
				else if (balance > 0)
				{
					asset_total -= balance;
					asset_backup += amount;
					asset_debt -= balance;
				}
				else
				{
					asset_backup += amount;
				}
			}//if there is still enough money to take out.
			else
			{
				cout << "Unknown error." << endl;

				cin.clear();
				cin.sync();

				return true;
			}
		}
		else
		{
			cout << "Balance exceeded." << endl;

			cin.clear();
			cin.sync();

			return true;
		}
	}
	else //to credit
	{
		if (balance > 0)
		{
			asset_total += amount;
			asset_backup += amount;
			asset_debt += amount;
		}
		else if (balance + amount > 0)
		{
			asset_total += balance + amount;
			asset_backup += amount;
			asset_debt += balance + amount;
		}
		else
		{
			asset_backup += amount;
		}
	}

	/*
	if (is_credit_card)
	{
		asset_total += amount;
	}
	asset_backup += amount;
	asset_debt += amount;
	*/


	balance += amount;
	ofstream asset_out;
	asset_out.open(find_path("asset.rec"), ios::out);
	asset_out << balance << endl;

	asset_out.close();

	ofstream record;
	record.open(find_path("transactions.rec"), ios::app);
	if (!to_debit)
	{
		record << currentDateandTime() << "   +" << amount << "USD" << endl;
	}
	else
	{
		record << currentDateandTime() << "   " << amount << "USD" << endl;
	}
	record.close();

	if (is_credit_card)
	{
		string temp_date;
		temp_date = currentDateandTime();
		string date;
		//date = temp_date;
		date = "0000-00";
		//date[7] = '\0';
		for (int i = 0; i < 7; i++)
		{
			date[i] = temp_date[i];
		}
		record.open(find_path("transactions/" + date + ".rec"), ios::app);
		if (!record.is_open())
		{
			record.open(find_path("transactions/" + date + ".rec"), ios::out);
		}
		if (!to_debit)
		{
			record << currentDateandTime() << "   +" << amount << "USD" << endl;
		}
		else
		{
			record << currentDateandTime() << "   " << amount << "USD" << endl;
		}
		record.close();

		record.open(find_path("transactions/" + date + ".ass"), ios::out);
		record << balance << endl;

		record.close();

		if (!to_debit)
		{
			ifstream repay_in;
			repay_in.open(find_path("last_bill.rec"), ios::in);
			if (!repay_in.is_open())
			{
				cout << "Some file missing." << endl;
			}
			else 
			{
				double total, minimum;
				repay_in >> total >> minimum;
				
				repay_in.close();

				total -= amount;
				if (total < 0)
				{
					total = 0;
				}
				ofstream repay_out;
				repay_out.open(find_path("last_bill.rec"), ios::out);
				repay_out << total << endl
					<< minimum << endl;

				repay_out.close();
			}
		}
	}


	ofstream asset_out2;
	asset_out2.open("root/asset.rec", ios::out);
	asset_out2 << asset_total << endl
		<< asset_backup << endl
		<< asset_debt << endl;

	asset_out2.close();

	//cout << "Credit " << amount << "USD" << " successfully." << endl
	//	<< "Thank you very much!" << endl;
	if (!to_debit)
	{
		cout << "Credit " << abs(amount) << "USD" << " successfully." << endl
			<< "Thank you very much!" << endl;
	}
	else
	{
		cout << "Debit " << abs(amount) << "USD" << " successfully." << endl
			<< "Thank you very much!" << endl;
	}

	cin.clear();
	cin.sync();


	return 0;
}

bool credit_card::view_bills(string date)
{
	ifstream asset_rec;
	asset_rec.open(find_path("transactions/") + date + ".ass", ios::in);
	if (!asset_rec.is_open())
	{
		cout << "Cannot find the required bill. Maybe it does not exist or it is missing." << endl
			<< "For more information, please contact AC Bank." << endl;

		cin.clear();
		cin.sync();

		return true;
	}
	double asset;
	asset_rec >> asset;
	/*
	The billing balance is stored in file *date.ass as a double value.
	*/

	asset_rec.close();

	ifstream bill;
	bill.open(find_path("transactions/") + date + ".rec", ios::in);
	if (!bill.is_open())
	{
		cout << "Cannot find the required bill. Maybe it does not exist or it is missing." << endl
			<< "For more information, please contact AC Bank." << endl;

		cin.clear();
		cin.sync();

		return true;
	}
	string temp_tran;
	while (getline(bill, temp_tran))
	{
		cout << temp_tran << endl;
	}

	bill.close();

	cout << "Billing amount:  ";
	if (asset >= 0)
	{
		cout << "0. No repayment." << endl;
	}
	else if (asset < 0)
	{
		cout << abs(asset) << "." << endl
			<< "Minimum payment: " << abs(asset*0.1) << "." << endl
			<< " Please pay off the minimum payment before the 5th of next month." << endl;
	}

	cin.clear();
	cin.sync();

	return 0;
}

bool credit_card::view_info()
{
	cout << "Card number:      " << card_number << endl
		<< "Valid date:       " << valid_date << endl
		<< "CVN code:         " << CVN << endl
		<< "Billing date:     " << billing_date << endl
		<< "Annual fee:       " << annual_fee << endl
		<< "Credit limit:     " << credit_limit << endl
		<< "Temp limit:       " << temp_limit << endl
		<< "Card holder name: " << name << endl
		<< "ID:               " << ID << endl
		<< "Phone:            " << phone << endl
		<< "Address:          " << address << endl
		<< "Postcode:         " << postcode << endl;

	cin.clear();
	cin.sync();

	return false;
}

bool credit_card::calculate_interest()
{
	return false;
}

debit_card::debit_card(string path)
	:card(path)
{
	setProperties();
}

bool debit_card::Interface()
{
	//Function Interface() gathers all the sub-functions and provides the user interface.
	//Remembering every command seems stupid.

	cout << endl << "Welcome to back, " << gender << " " << name << "!" << endl << endl;
	//Welcome.

	Message();
	//Interface() calls the Message() function to show messages to users after logging in.

	cout << endl;

	ifstream asset_f;
	asset_f.open(find_path("asset.rec"), ios::in);
	double balance;
	if (!asset_f.is_open())
	{
		cout << "Some file missing." << endl;
		balance = 0;
	}
	else
	{
		asset_f >> balance;

		asset_f.close();

		cout << "At the time of login, your balance is $" << balance << endl;
	}

	cout << endl;

	string feature;
	while (true)
	{
		//A UI should always looping in order to accept a command rather than running once,
		//until a command tells it to exit.
		cout << "Services List" << endl
			<< "1: Credit" << endl
			<< "2: Debit" << endl
			<< "3: Transfer" << endl
			<< "4: View Transactions" << endl
			<< "5: View Card Info" << endl
			<< "6: Password Reset" << endl
			<< "#: Logout" << endl
			<< "Please enter the serial number to choose a service ;) ";
		cin >> feature;
		//Links the main feature of a credit card account.


		if (feature == "1")
		{
			double amount;
			cout << "Please enter the amount you want to credit: ";
			while (get_num(amount))
			{
				cout << "Input error. You can just input a non-positive number to return." << endl;
			}
			if (amount <= 0)
			{
				continue;
			}
			credit_or_debit(amount);
		}
		else if (feature == "2")
		{
			double amount;
			cout << "Please enter the amount you want to debit: ";
			while (get_num(amount))
			{
				cout << "Input error. You can just input a non-positive number to return." << endl;
			}
			if (amount <= 0)
			{
				continue;
			}
			amount *= -1;
			credit_or_debit(amount);
		}
		else if (feature == "3")
		{
			string card_num;
			double amount;
			cout << "Please input the destination card number: ";
			getchar();
			if (!getline(cin, card_num))
			{
				continue;
			}
			cout << "Please input amount to transfer: ";
			while (get_num(amount))
			{
				cout << "Input error. You can just input a non-positive number to return." << endl;
			}
			if (amount <= 0)
			{
				continue;
			}
			transfer(_path, card_num, amount);
		}
		else if (feature == "4")
		{
			view_transactions();
		}
		else if (feature == "5")
		{
			view_info();
		}
		else if (feature == "6")
		{
			reset_pwd();
		}
		else if (feature == "#")
		{

			cin.clear();
			cin.sync();

			return false;
		}
		else
		{
			cout << "Input error. Please input again." << endl;
		}
	}
}

bool debit_card::setProperties()
{
	credit_limit = 0;
	temp_limit = 0;
	ifstream prop;
	prop.open(find_path("properties.info"), ios::in);
	if (!prop.is_open())
	{
		cout << "Some file missing. Cannot set up account." << endl;

		cin.clear();
		cin.sync();

		return true;
	}
	card_number = _path;
	getline(prop, name);
	getline(prop, gender);
	getline(prop, ID);
	getline(prop, phone);
	getline(prop, address);
	getline(prop, postcode);

	cin.clear();
	cin.sync();

	return 0;
}

bool debit_card::view_info()
{
	cout << "Card number:      " << card_number << endl
		<< "Card holder name: " << name << endl
		<< "ID:               " << ID << endl
		<< "Phone:            " << phone << endl
		<< "Address:          " << address << endl
		<< "Postcode:         " << postcode << endl;

	cin.clear();
	cin.sync();

	return false;
}

bool debit_card::view_transactions()
{
	ifstream bill;
	bill.open(find_path("transactions.rec"), ios::in);
	if (!bill.is_open())
	{
		cout << "Some file missing." << endl
			<< "For more information, please contact AC Bank." << endl;

		cin.clear();
		cin.sync();

		return true;
	}
	string temp_tran;
	while (getline(bill, temp_tran))
	{
		cout << temp_tran << endl;
	}

	bill.close();
}

bool debit_card::calculate_interest()
{
	return false;
}

online_banking::online_banking(string path)
	:card(path)
{
	setProperties();

	ifstream count;
	double balance = 0;
	double debt = 0;
	double temp;
	for (int i = 0; i < card_num; i++)
	{
		count.open(cards[i] + "/asset.rec", ios::in);
		if (!count.is_open())
		{
			temp = 0;
			cout << "Some file missing." << endl;
		}
		else
		{
			count >> temp;

			count.close();

		}
		if (temp >= 0)
		{
			balance += temp;
		}
		else
		{
			debt += abs(temp);
		}
	}

	if (transaction_account_is_set)
	{
		double current_asset = 0;
		double current_backup = 0;
		double current_debt = 0;
		ifstream current_asset_f;
		current_asset_f.open("root/asset.rec", ios::in);
		if (!current_asset_f.is_open())
		{
			cout << "Some file missing." << endl;
			//return true;
		}
		else

		{
			current_asset_f >> current_asset
				>> current_backup
				>> current_debt;

			current_asset_f.close();
		}

		int stock_holding = 0;
		ifstream stock_num_f;
		stock_num_f.open(transaction_account + "/financial.rec", ios::in);
		if (!stock_num_f.is_open())
		{
			cout << "Some file missing." << endl;
			//return true;
		}
		else
		{
			stock_num_f >> stock_holding;

			stock_num_f.close();

		}

		balance += (current_asset / 10000.0)*stock_holding;
	}

	total_asset = balance;
	total_debt = debt;

	cin.clear();
	cin.sync();

}

bool online_banking::Interface()
{
	//Function Interface() gathers all the sub-functions and provides the user interface.
	//Remembering every command seems stupid.

	cout << endl << "Welcome to back, " << name << "!" << endl << endl;
	//Welcome.

	Message();
	//Interface() calls the Message() function to show messages to users after logging in.

	cout << endl;

	cout << "At the time of login, your asset is $" << total_asset << ", your debt is $" << total_debt << endl;

	cout << endl;

	string feature;
	while (true)
	{
		cout << "Services List" << endl
			<< "1: Card Management" << endl
			<< "2: Financial Services" << endl
			<< "3: Password Reset" << endl
			<< "#: Logout" << endl
			<< "Please enter the serial number to choose a service ;) ";
		cin >> feature;

		if (feature == "1")
		{
			cout << card_num << "cards associated." << endl;
			for (int i = 0; i < card_num; i++)
			{
				cout << i + 1 << ": " << cards[i] << endl;
			}
			double temp;
			int choice;
			int input;
			cout << "Please choose a card: (or input 0 to return) ";
			input = get_num(temp);
			choice = temp;
			while (temp - choice != 0 || input != 0 || choice<0 || choice>card_num)
			{
				cout << "Input error. Please try again. Or you can enter 0 to return." << endl;
				input = get_num(temp);
				choice = temp;
			}
			
			if (choice == 0)
			{
				continue;
			}
			
			ifstream type_c;
			type_c.open(cards[choice - 1] + "/ID.cre", ios::in);
			if (!type_c.is_open())
			{
				cout << "Cannot find the card." << endl;
				continue;
			}
			char type;
			type_c >> type;

			type_c.close();

			card *p;

			if (type == 'c')
			{
				p = new credit_card(cards[choice - 1]);
				p->Interface();
				delete p;
			}
			else if (type == 'd')
			{
				p = new debit_card(cards[choice - 1]);
				p->Interface();
				delete p;
			}
			else
			{
				cout << "Unknown card." << endl;
			}

		}
		else if (feature == "2")
		{
			if (transaction_account_is_set)
			{
				financial();
			}
			else		//set up transaction account.
			{
				setup_tran();
			}
		}
		else if (feature == "3")
		{
			reset_pwd();
		}
		else if (feature == "#")
		{
			return 0;
		}
		else
		{
			cout << "Input error. Please try again." << endl;
		}
	}

	cin.clear();
	cin.sync();

}

bool online_banking::setProperties()
{
	ifstream cards_f;
	cards_f.open(find_path("OnlineAccounts.exchange"), ios::in);
	if (!cards_f.is_open())
	{
		cout << "Some file missing. Cannot set up the account." << endl;

		cin.clear();
		cin.sync();

		return true;
	}
	card_num = 0;
	while (getline(cards_f, cards[card_num]))
	{
		++card_num;
	}

	cards_f.close();

	ifstream acc_cre;
	acc_cre.open(find_path("properties.info"), ios::in);
	if (!acc_cre.is_open())
	{
		cout << "Some file missing. Cannot set up the account." << endl;

		cin.clear();
		cin.sync();

		return true;
	}
	getline(acc_cre, name);
	getline(acc_cre, ID);
	getline(acc_cre, transaction_account);

	acc_cre.close();

	if (transaction_account == "0")
	{
		transaction_account_is_set = false;
	}
	else
	{
		transaction_account_is_set = true;
	}

	cin.clear();
	cin.sync();

	return 0;
}

bool online_banking::calculate_interest()
{
	return false;
}

bool online_banking::setup_tran()
{
	cout << "Please set transaction account." << endl;
	for (int i = 0; i < card_num; i++)
	{
		cout << i + 1 << ": " << cards[i] << endl;
	}
	double temp;
	int choice;
	int input;
	cout << "Please choose a card: (or input 0 to return) ";
	input = get_num(temp);
	choice = temp;
	while (temp - choice != 0 || input != 0 || choice<0 || choice>card_num)
	{
		cout << "Input error. Please try again. Or you can enter 0 to return." << endl;
		input = get_num(temp);
		choice = temp;
	}

	if (choice == 0)
	{

		cin.clear();
		cin.sync();

		return true;
	}

	ifstream type_c;
	type_c.open(cards[choice - 1] + "/ID.cre", ios::in);
	if (!type_c.is_open())
	{
		cout << "Cannot find the card." << endl;

		cin.clear();
		cin.sync();

		return true;
	}
	char type;
	type_c >> type;

	type_c.close();

	if (type == 'd')
	{
		transaction_account = cards[choice - 1];
		transaction_account_is_set = true;
		ofstream out;
		out.open(find_path("properties.info"), ios::out);
		out << name << endl
			<< ID << endl
			<< transaction_account << endl;

		out.close();

		out.open(transaction_account + "/financial.rec", ios::out);
		out << "0" << endl;

		out.close();

		cout << "OK. The transaction account is not set. You may need to re-login." << endl;

		cin.clear();
		cin.sync();

		return false;
	}
	else
	{
		cout << "Sorry, but a transaction account can only be a debit card." << endl;

		cin.clear();
		cin.sync();

		return true;
	}
}

bool online_banking::financial()
{
	ifstream root_stock_f;
	root_stock_f.open("root/stock.rec", ios::in);
	if (!root_stock_f.is_open())
	{
		cout << "Some file missing." << endl;

		cin.clear();
		cin.sync();

		return true;
	}

	int stock_left;
	root_stock_f >> stock_left;

	root_stock_f.close();

	ifstream balance_f;
	balance_f.open(transaction_account + "/asset.rec", ios::in);
	if (!balance_f.is_open())
	{
		cout << "Some file missing." << endl;

		cin.clear();
		cin.sync();

		return true;
	}
	double balance;
	balance_f >> balance;

	balance_f.close();

	double last_asset;
	ifstream last_asset_f;
	last_asset_f.open("PublicInfo/FinancialServices/acb.info", ios::in);
	if (!last_asset_f.is_open())
	{
		cout << "Some file missing." << endl;

		cin.clear();
		cin.sync();

		return true;
	}

	last_asset_f >> last_asset;

	last_asset_f.close();

	double current_asset;
	double current_backup;
	double current_debt;
	ifstream current_asset_f;
	current_asset_f.open("root/asset.rec", ios::in);
	if (!current_asset_f.is_open())
	{
		cout << "Some file missing." << endl;

		cin.clear();
		cin.sync();

		return true;
	}

	current_asset_f >> current_asset
		>> current_backup
		>> current_debt;

	current_asset_f.close();

	int stock_holding;
	ifstream stock_num_f;
	stock_num_f.open(transaction_account + "/financial.rec", ios::in);
	if (!stock_num_f.is_open())
	{
		cout << "Some file missing." << endl;

		cin.clear();
		cin.sync();

		return true;
	}

	stock_num_f >> stock_holding;

	stock_num_f.close();

	cout << "Current price: $" << (current_asset / 10000) << "  ";
	if (current_asset > last_asset)
	{
		cout << "+";
	}
	cout << 100 * (current_asset - last_asset) / last_asset << "%" << "   Holding: " << stock_holding << endl;

	cout << endl;

	string operand;
	//string temp_num;
	double temp_num;
	int num;


	while (true)
	{
		cout << "Input 0 to return, 1 to buy, 2 to sell: ";
		cin >> operand;
		if (operand == "0")
		{
			break;
		}
		else if (operand == "1" || operand == "2")
		{
			cout << "Please input amount: (input 0 to return) ";
			bool not_int = 0;
			not_int = get_num(temp_num);
			num = temp_num;
			while (num - temp_num != 0 || not_int != 0 || num < 0)
			{
				cout << "Input error. Please input a non-negative integer." << endl;
				cout << "Please input amount: (input 0 to return) ";
				not_int = get_num(temp_num);
				num = temp_num;
			}
			if (num == 0)
			{
				break;
			}
			if (operand == "1")
			{
				if ((current_asset / 10000)*num*1.0008 <= balance)
				{
					//have enough money to purchase.
					if (stock_left - num > 5001)
					{
						current_asset -= (current_asset / 10000)*num*0.0008;
						balance -= (current_asset / 10000)*num*1.0008;
						stock_left -= num;
						stock_holding += num;

						ofstream record;
						record.open(transaction_account + "/transactions.rec", ios::app);
						record << currentDateandTime() << "   stock buy-in " << num << endl;

						record.close();
					}
					else
					{
						cout << "Unknown error." << endl;
						continue;
					}
				}
				else
				{
					cout << "No enough balance." << endl;
					continue;
				}
			}
			else //operand == "2"
			{
				if (num <= stock_holding)
				{
					balance += (current_asset / 10000)*num;
					stock_left += num;
					stock_holding -= num;

					ofstream record;
					record.open(transaction_account + "/transactions.rec", ios::app);
					record << currentDateandTime() << "   stock sell-out " << num << endl;

					record.close();
				}
				else
				{
					cout << "No enough stock." << endl;
					continue;
				}
			}

			ofstream root_asset_f;
			root_asset_f.open("root/asset.rec", ios::out);
			root_asset_f << current_asset << endl
				<< current_backup << endl
				<< current_debt << endl;

			root_asset_f.close();

			ofstream root_stock_left_f;
			root_stock_left_f.open("root/stock.rec", ios::out);
			root_stock_left_f << stock_left << endl;

			root_stock_left_f.close();

			ofstream account_balance;
			account_balance.open(transaction_account + "/asset.rec", ios::out);
			account_balance << balance << endl;

			account_balance.close();

			ofstream stock_hf;
			stock_hf.open(transaction_account + "/financial.rec", ios::out);
			stock_hf << stock_holding << endl;

			stock_hf.close();

			
			

			break;

		}
		else
		{
			cout << "Input error. Try again. " << endl;
			continue;
		}
	}

	cin.clear();
	cin.sync();

	return 0;
}
#endif
