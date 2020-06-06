#include "CustomerFlow.h"

#include <iomanip>
#include <sstream>

#include "Helper.h"
#include "SH_List.h"


std::shared_ptr<Customer> CustomerFlow::currentCustomer;
std::shared_ptr<Shop> CustomerFlow::currentShop;


void CustomerFlow::makeAnOrder()
{
	findAvailableShops();
	while (true)
	{
		std::cout << "List of available shops for you\n";
		Helper::dLine(60);


		// Display header
		// Display Shops
		CustomerFlow::displayShops();
		
		// Choose shop or go back

		// set currentShop to chosen shop out of availableShops
		// vieShop
		CustomerFlow::viewShop();
	}
}




void CustomerFlow::myCart()
{
	while (true) {
		std::cout << "My cart:\n";
		Helper::dLine(60);

		// check if cart is empty
		// else display cart : define display function in order class (to display any order not just cart)
		
		
		std::cout << "Choose an Item number to remove it from the cart\n"
			<< "or press B to go back or C to checkout\n"
			<< "Your Choice: ";

		// call respective functions
		// if item number call removeItem
	}

}


void CustomerFlow::mainMenu()
{

	while (true) {
		std::cout << "Welcome " << currentCustomer->getName() << '\n';
		std::cout << "Your balance: " << currentCustomer->getBalance() << "\n";
		Helper::dLine();
		std::cout << "Choose an option from the following:\n";

		std::vector <std::string > menuOptions = {
			"Make an order", "My orders", "My cart", "My profile", "Log out"
		};

		Helper::displayMenu(menuOptions);
		Helper::line();
		std::cout << "Your choice: ";
		int choice = Helper::readChoice(1, 5);

		
		switch (choice)
		{
		case 1: makeAnOrder();
			break;
		case 2:/* myOrders();*/
			break;
		case 3: myCart();
			break;
		case 4:/* UserFlow::myProfile();*/
			break;
		default:
			currentCustomer = nullptr;
			/*UserFlow::logout();*/
		}

	}
	
	
}

void CustomerFlow::findAvailableShops()
{
	// insert location sorting mechanism here
	// for now I will have this list equal to the list of all shops
	currentCustomer->availableShops = SH_List::SHOPS;
}

void CustomerFlow::displayShops()
{
	int numShops = availableShops.getCount();
	// loop through shops and display
	for (int i = 1; i <= numShops; i++) {
		std::cout << i << ". ";
		std::cout << availableShops[i].display() << "\n";
		//availableShops[i].display();
		//std::cout << i << ". " << availableShops.getName() << "\n";
	}
	// better define display function in shop class
}

void CustomerFlow::viewShop()
{
	while (true)
	{
		std::cout << "List of items in ";
		// display the shop
		std::cout << currentShop->getName() << " :\n";
		// list shop items
		int numItems = currentShop->getItemsCount();
		std::vector<std::shared_ptr<Item>> shopItem = currentShop->getItems();
		for (int i = 1; i <= numItems; i++) {
			//std::shared_ptr<Item> shopItems[100];
			//std::cout << i << ". " << shopItems[i]<< "\n";
			std::cout << i << shopItem[i] << "\n";
		}

		Helper::line(60);
		std::cout << "Choose an item number followed by quantity to add it to cart,\n"
			<< " press C to go to cart or press B to go back: ";
		int itemChoice, itemQuantity;
		char inputAlphabet;
		itemChoice = Helper::readChoice(1, numItems);
		std::cin >> itemQuantity;
		inputAlphabet = Helper::readChoice(0, 0, "CcBb");

		for (int c = 1; c <= numItems; c++) {
			if (itemChoice == c) {
				currentCustomer->addToCart(shopItem[c], itemQuantity);
			}
		}
		if (inputAlphabet == 'C' || inputAlphabet == 'c') {
			myCart();
		}
		else if (inputAlphabet == 'B' || inputAlphabet == 'b') {
			break;
		}
		// call respective functions
	}
}
