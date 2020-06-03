#include "UserFlow.h"

void UserFlow::welcomeScreen()
{
	int choice = -1;
	while (choice != 99)
	{
		std::cout << "COVID-19 SHOPS DELIVERY SYSTEM" << std::endl;
		std::cout << "1.  Log in" << std::endl;
		std::cout << "2.  Sign up" << std::endl;
		std::cout << "99. Exit" << std::endl;
		std::cout << "Your choice: ";
		std::cin >> choice;

		switch (choice)
		{
		case 1:	login();
			break;
		case 2:	signUp();
			break;
		case 99:exit(0);
			break;
		default:std::cout << "Please choose the correct number." << std::endl;
		}
	}

}

std::shared_ptr<User> UserFlow::verifyUsername(std::string username)
{
	for (int i = 0; i < C_List::getCustomerCount(); i++)
	{
		if (username==C_List::ALL_CUSTOMERS[i]->getUsername)
		{
			return C_List::ALL_CUSTOMERS[i];
		}
	}
	for (int j = 0; j < V_List::getVolunteersCount(); j++)
	{
		if (username==V_List::ALL_VOLUNTEERS[j]->getUsername)
		{
			return V_List::ALL_VOLUNTEERS[j];
		}
	}
	for (int k = 0; k < SO_List::getCount(); k++)
	{
		if (username==SO_List::SHOPOWNERS[k]->getUsername)
		{
			return SO_List::SHOPOWNERS[k];
		}
	}
	return std::make_shared <User>("\0", "\0");
}

bool UserFlow::verifyPassword(std::shared_ptr<User> user,std::string password)
{
	while (!user->isAuth(user->getUsername, password))
	{
		std::cout << "Log in as " << user->getName << std::endl;
		std::cout << "The password that you've entered is incorrect." << std::endl;
		std::cout << "Reenter the password or enter 0 if not you."<< std::endl;
		std::cin >> password;
		if (password == "0")
		{
			return false;
		}
	}
	return true;
}