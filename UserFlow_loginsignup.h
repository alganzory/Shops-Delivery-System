#pragma once
#include<iostream>

class UserFlow {
	static void Login();
	static void SignUp();
	static void MainMenu();
	static bool Verify(std::string,std::string);
};
