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

int UserFlow::verify(std::string username,std::string password)
{
	//return 0 -> username does not exist
	//return 1 -> username exist, password incorrect
	//return 2 -> username exist, password correct
	for (int i = 0; i < C_List::getCustomerCount(); i++)
	{
		if (username == C_List::ALL_CUSTOMERS[i]->getUsername())
		{
			if (C_List::ALL_CUSTOMERS[i]->isAuth(username, password))
			{
				return 2;
			}
			else
			{
				return 1;
			}
		}
	}
	for (int j = 0; j < V_List::getVolunteersCount(); j++)
	{
		if (username == V_List::ALL_VOLUNTEERS[j]->getUsername())
		{
			if (V_List::ALL_VOLUNTEERS[j]->isAuth(username, password))
			{
				return 2;
			}
			else
			{
				return 1;
			}
		}
	}
	for (int k = 0; k < SO_List::getCount(); k++)
	{
		if (username == SO_List::SHOPOWNERS[k]->getUsername())
		{
			if (SO_List::SHOPOWNERS[k]->isAuth(username, password))
			{
				return 2;
			}
			else
			{
				return 1;
			}
		}
	}
	return 0;
}

void UserFlow::login()
{

}

void UserFlow::signUp()
{

}