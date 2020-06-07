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
	while (true)
	{
		std::cout << currentSO->getShopName() << '\n'; //update
		Helper::dLine();
		int numItems = currentSO->getShopSize();
		std::vector <std::shared_ptr <Item> > currItems = currentSO->getShop().getItems();
		std::cout << "Number of Items: " << numItems << '\n';  //update
		Helper::line();
		if (numItems) {
			std::cout << "Here is the list of items your shop:\n";
			Helper::line(60);
			std::cout << std::left << std::setw(33) << "Item name" << std::setw(20)
				<< "Price" << "Quantity" << '\n';
			Helper::line(60);
			int counter = 0;


			for (auto& item : currItems)
			{
				std::cout << ++counter << "- ";
				(*item).display();
			}

			Helper::line(60);
			std::cout << "Press N to add a new item,\n"
				<< "Enter an item Number to change its info, or Press B to go back\n";
		}
		else
		{
			std::cout << "No items to show, maybe add one?\n";
			Helper::line(60);
			std::cout << "Press N to add a new item or Press B to go back\n";

		}

		Helper::line(60);
		std::cout << "Your choice:";
		int choice;
		if (numItems) choice = Helper::readChoice(1, 10, "nNbB");
		else choice = Helper::readChoice(0, 0, "nNbB");



		if (choice == 'n' or choice == 'N') ShopOwnerFlow::addNewItem();
		if (choice == 'b' or choice == 'B') break;

		try {
			ShopOwnerFlow::editItem(currItems.at(choice - 1));
		}
		catch (const std::out_of_range& error)
		{
			std::cout << "Please choose an item from the ones shown\n";
			continue;
		}
	}
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
