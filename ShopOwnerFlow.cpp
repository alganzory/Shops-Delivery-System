#include "ShopOwnerFlow.h"

#include <iomanip>


#include "Helper.h"
#include "UserFlow.h"

std::shared_ptr <ShopOwner> ShopOwnerFlow::currentSO;

void ShopOwnerFlow::editItem(const std::shared_ptr<Item> item)
{
	std::cout << "Edit item" << std::endl;
}

void ShopOwnerFlow::addNewItem()
{
	std::cout << "Add Item\n";	
}

void ShopOwnerFlow::myShop()
{
	std::cout << "My Shop\n";
}

void ShopOwnerFlow::mainMenu()
{
	while (true) {
		std::cout << "Welcome " << currentSO->getName() << '\n';
		std::cout << "Your balance: " << currentSO->getBalance() << "\n";
		Helper::dLine();
		std::cout << "Choose an option from the following:\n";

		std::vector <std::string > menuOptions = {
			"My Shop", "Pending orders", "All Orders", "My profile", "Log out"
		};

		Helper::displayMenu(menuOptions);
		Helper::line();
		std::cout << "Your choice: ";
		int choice = Helper::readChoice(1, 5);


		switch (choice)
		{
		case 1: myShop();
			break;
		case 2: /*allOrders(true);*/
			break;
		case 3: /*allOrders();*/
			break;
		case 4: /*UserFlow::myProfile();*/
			break;
		default:
			currentSO= nullptr;
			/*UserFlow::logout();*/
		}

	}
}
