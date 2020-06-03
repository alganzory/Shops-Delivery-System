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
			case 99:exitScreen();
					break;
			default:std::cout << "Please choose the correct number." << std::endl;
		}
	}
	
}

bool UserFlow::verify(std::string username,std::string password)
{
	std::shared_ptr<User> ToCheck;

	C_List CustomerList;
	CustomerList.readCustomers();
	for (int i = 0; i < CustomerList.getCustomerCount; i++)
	{
		ToCheck = CustomerList.ALL_CUSTOMERS[i];
		if (ToCheck->isAuth(username, password))
		{
			return true;
		}
	}
	
	V_List VolunteerList;
	VolunteerList.ReadVolunteers();
	for (int j = 0; j < VolunteerList.getVolunteersCount; j++)
	{
		ToCheck = VolunteerList.ALL_VOLUNTEERS[j];
		if (ToCheck->isAuth(username, password))
		{
			return true;
		}
	}

	SO_List ShopOwnerList;
	ShopOwnerList.readFromFile();
	for (int k = 0; k < ShopOwnerList.getCount; k++)
	{
		ToCheck = ShopOwnerList.SHOPOWNERS[k];
		if (ToCheck->isAuth(username, password))
		{
			return true;
		}
	}
	
	return false;
}