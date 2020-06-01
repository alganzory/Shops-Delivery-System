#pragma once
#include <iostream>
#include "User.h"
#include "C_List.h"
#include "V_List.h"
#include "SO_List.h"
#include "Customer.h"
#include "ShopOwner.h"
#include "Volunteer.h"

class UserFlow
{
	public:
		void welcomeScreen();
		int verify(std::string,std::string);
		void login();
		void signUp();
		//void exitScreen();
};