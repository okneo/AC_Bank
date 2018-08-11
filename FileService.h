#pragma once

#include"AccountTypes.h"

class FileService
{
public:
	FileService(string username, string password);
	bool Interface();
	~FileService();
private:

#if INCLUDE_ACCOUNT_CLASS
	AccountTypes * account;
#endif

	bool is_logged_in;
};