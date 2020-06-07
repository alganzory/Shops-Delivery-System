#pragma once

#include "C_List.h"
#include "V_List.h"
#include "SO_List.h"


class UserFlow {
public:
	static void login();
	static void welcomeScreen();
	static void signUp();
	static std::shared_ptr<User> verifyUsername(std::string username);
	static void logout();
	static std::shared_ptr<User> currentUser;
};

