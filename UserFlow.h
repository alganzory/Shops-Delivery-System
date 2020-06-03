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
		std::shared_ptr<User> verifyUsername(std::string);
		bool verifyPassword(std::shared_ptr<User>, std::string);

};