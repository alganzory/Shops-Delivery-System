#pragma once
#include<iostream>
#include"User.h"

class userFlow {
	static void login();
	static void welcomeScreen();
	static void signUp();
	static void mainMenu();
	static int verify(std::string userName, std::string password);
	static std::shared_ptr<User> currentUser;
};
