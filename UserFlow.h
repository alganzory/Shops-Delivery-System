#pragma once
#include<iostream>
#include"User.h"

class UserFlow {
public:
	static void login();
	static void welcomeScreen();
	static void signUp();
	static void mainMenu();
	static std::shared_ptr<User> verifyUsername(std::string username);
	static std::shared_ptr<User> currentUser;
};




