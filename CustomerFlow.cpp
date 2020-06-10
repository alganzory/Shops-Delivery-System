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

		CustomerFlow::displayShops();
		int shopChoices = currentCustomer->availableShops.size();
		Helper::line(60);
		std::cout << "Please select a shop "
			<< "or Press B to go back: ";
		int chosenShop = Helper::readChoice(1, shopChoices, "Bb");
		if (chosenShop == 'B' || chosenShop == 'b') {
			break;
		}
		currentShop = currentCustomer->availableShops[chosenShop - 1];
		CustomerFlow::viewShop();
	}
}

void CustomerFlow::checkout()
{
	while (true)
	{
		// Display the order and the total price
		std::cout << "Review Order\n";
		Helper::dLine(60);
		currentCustomer->cart->display();
		Helper::line(70);
		// ask for delivery time
		std::cout << "Enter delivery time in (HH:MM) format or Press B to go back to cart: ";
		std::string input;
		getline(std::cin, input);
		std::stringstream inputStream(input);
		int hour{};
		char character;
		int minutes{};
		bool isTime = true;
		inputStream >> hour;
		if (inputStream.fail())
		{
			isTime = false;
		}

		inputStream >> character;
		if (isTime) inputStream >> minutes;

		if (!isTime) break;
		currentCustomer->cart->setDeliveryTime(hour);
		Helper::line(80);
		// place or cancel
		std::cout << "All set, press P to proceed with the checkout or Press B to go back to cart\n";
		Helper::line(80);
		std::cout << "Your choice: ";
		int choice = Helper::readChoice(0, 0, "PBbp");
		if (choice == 'B' || choice == 'b') break;
		if (currentCustomer->getBalance() < currentCustomer->cart->getTotalPrice())
		{
			std::cout << "Insufficient balance, taking you back to cart...";
			break;
		}
		currentCustomer->cart->setShop(currentShop);
		// add to list of orders for the respective shop
		currentShop->recieveOrder(currentCustomer->cart);
		currentCustomer->cart->setCustomer(currentCustomer);
		// add to list of orders
		currentCustomer->placeOrder();
		std::cout << "Your order has been placed successfully, you will be directed to main menu...\n";
		mainMenu();
	}
	
}


void CustomerFlow::myCart()
{
	while (true) {
		std::cout << "My cart:\n";
		Helper::dLine(60);
		int choice{};

		if (currentCustomer->cart->getOrderSize()==0)
		{
			std::cout << "No Items Yet." << '\n';
			std::cout << "You will be directed back...\n";
			break;
		}
		std::cout << std::setw(4) << "No." << std::setw(20)
			<< "Name" << std::setw(5) << "Qty" << "Price (RM)"
			<< '\n';
		Helper::line(60);
		currentCustomer->cart->display();
		Helper::line(60);
		std::cout << "Choose an Item number to remove it from the cart\n"
			<< "or press B to go back or C to checkout\n";
		Helper::line(60);
		std::cout << "Your Choice: ";
		choice = Helper::readChoice(1, currentCustomer->cart->getOrderSize(), "BbCc");
		if (choice == 'B' || choice == 'b')
		{
			break;
		}
		else if (choice == 'C' || choice == 'c')
		{
			CustomerFlow::checkout();
		}
		else
		{
			std::pair<std::shared_ptr<Item>, int>& item = currentCustomer->cart->getItem(choice - 1);
			std::cout << "You choose to remove:\n\n"
				<< item.first->getName() << "\tRM"
				<< item.first->getPrice() << "\tQuantity: " << item.second << '\n';
			Helper::line(60);
			std::cout << "Enter the quantity you want reduce, press R to remove the item.\n"
				<< "or press B to go back\n";
			choice = Helper::readChoice(0, item.second, "rRbB");
			if (choice == 'r' || choice == 'R')
			{
				currentCustomer->cart->removeItem(item);
			}
			else if (choice == 'b' || choice == 'B')
			{
				continue;
			}
			else
			{
				int quantity = item.second - choice;
				currentCustomer->cart->removeItem(item);
				currentCustomer->cart->addItem(item.first, quantity);
			}

		}	
		
	}

}

void CustomerFlow::myOrders(bool pendingOnly)
{

	
	// displaying from the order vector

	// shop, customer, number of items, *status*, delivery status, payment status
	
	// select an order to view, view only pending orders or go back
	
	// viewOrder (order);
	// 
	// if customer asks to see only pending orders -> myOrders (true)
	// break;
}

void CustomerFlow::viewOrder(std::shared_ptr<Order> order)
{/*
	-view order :
	-see details :
	
		- if the order is pending : cancel the order
			- removeOrder(); // undoing the order placement
				- balance goes back
				- return the items to the shop -> similar?
				- we remove it from the array of orders
					- for both the shopOwner and the Customer
			
		- if it's a past order: reOrder:
			- currentCustomer -> cart = that order;
			- send them to the cart
		*/
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
		case 2: myOrders();
			break;
		case 3: myCart();
			break;
		case 4:/* UserFlow::myProfile();*/
			break;
		default:
			currentCustomer = nullptr;
			UserFlow::logout();
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
	int numShops = currentCustomer->availableShops.size();
	// loop through shops and display
	for (int i = 1; i <= numShops; i++) {
		std::cout << i << ". ";
		currentCustomer->availableShops[i - 1]->display();
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
		Helper::dLine(60);
		// list shop items
		int numItems = currentShop->getItemsCount();
		std::vector<std::shared_ptr<Item>> shopItems = currentShop->getItems();
		std::cout << std::left << std::setw(30) << "Name"
			<< std::setw(20) << "Price" << "In Stock" << "\n";
		for (int i = 1; i <= numItems; i++) {
			std::cout << i << "- ";
			shopItems[i - 1]->display();
		}

		Helper::line(60);
		std::cout << "Choose an item number followed by quantity to add it to cart,\n"
			<< " press C to go to cart or press B to go back:\n";
		Helper::line(60);
		std::cout << "Your choice: ";
		int itemChoice, itemQuantity;

		itemChoice = Helper::readChoice(1, numItems, "CcBb");
		if (itemChoice == 'C' || itemChoice == 'c') {
			myCart();
		}
		else if (itemChoice == 'B' || itemChoice == 'b') {
			break;
		}
		else {
			std::cout << "Quantity: ";
			itemQuantity = Helper::readChoice(0, shopItems[itemChoice - 1]->getInStock());
			currentCustomer->addToCart(shopItems[itemChoice - 1], itemQuantity);
		}
		
		
		// call respective functions
	}
}
