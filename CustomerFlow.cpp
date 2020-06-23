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
		Helper::dLine(70);
		currentCustomer->cart->display();
		Helper::line(70);
		// ask for delivery time

		while (true) {
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
			try {
				currentCustomer->cart->setDeliveryTime(hour, minutes);
				break;
			}
			catch (const char* errorMsg) {
				std::cout << errorMsg << std::endl;

			}
		}
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
		std::cout<<"Do you wish to tip the volunteer? Y (Yes) or N (No)"<<std::endl;
		int ans= Helper::readChoice(0,0,"YyNn");
		double reward=0;
		if (ans=='Y'||ans=='y')
		{
			std::cout << "Your balance: " << currentCustomer->getBalance() - currentCustomer->cart->getTotalPrice() << std::endl;
			std::cout<<"Enter the amount of the tip: RM";
			reward=Helper::readChoice(0,currentCustomer->getBalance()-currentCustomer->cart->getTotalPrice());
			currentCustomer->cart->setReward(reward);
			currentCustomer->balance -= reward;
		}
		Helper::line(80);
		if (currentCustomer->getHealthStatus() >= Customer::ShowSymptoms) {
			std::cout << "For your safety and the volunteer's, you will be offered contactless delivery\n"
				<< "We wish you a speedy recovery!\n";
			currentCustomer->cart->setContactlessDlvr(true);
		}
		else {
			Helper::line(80);
			std::cout << "Do you want a contactless delivery? Yes(Y) or No(N): ";
			int delivery = Helper::readChoice(0, 0, "YyNn");
			if (delivery == 'Y' || delivery == 'y') {
				std::cout << "You will be offered contactless delivery. Stay safe! \n";
				currentCustomer->cart->setContactlessDlvr(true);
			}
			else {
				std::cout << "For your safety and the volunteer's make sure you wear a mask. Stay safe!\n";
				currentCustomer->cart->setContactlessDlvr(false);
			}
		}
		Helper::line(80);
		currentCustomer->cart->setShop(currentShop);
		currentShop->recieveOrder(currentCustomer->cart);
		currentCustomer->cart->setCustomer(currentCustomer);
		currentCustomer->cart->setPaymentStatus(true);
		currentCustomer->placeOrder();
		std::cout << "Your order has been placed successfully, you will be directed to main menu...\n";
		mainMenu();
	}
	
}


void CustomerFlow::myCart()
{
	while (true) {
		std::cout << "My cart:\n";
		Helper::dLine(70);
		int choice{};

		if (currentCustomer->cart->getOrderSize()==0)
		{
			std::cout << "No Items Yet." << '\n';
			std::cout << "You will be directed back...\n";
			break;
		}
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
	while (true)
	{

		std::cout << (pendingOnly ? "Pending Order" : "All Orders") << '\n';
		Helper::dLine(110);
		int anyPending = 0;
		std::vector <std::shared_ptr<Order> > pendingOrders;

		if (currentCustomer->orders.empty())
		{
			std::cout << "No orders yet, you will be directed to main menu...\n";
			mainMenu();
		}

		else if (pendingOnly)
		{
			pendingOrders.reserve(currentCustomer->orders.size());
			for (const auto& order : currentCustomer->orders)
			{
				if (order->getStatus() <= Order::Delivering) {
					anyPending++;
					pendingOrders.emplace_back(order);
				}
			}
			if (!anyPending) {
				std::cout << "No pending orders, you will be directed to main menu...\n";
				mainMenu();
			}
		}

		std::cout << std::setw(18) << "Shop"
			<< std::setw(15) << "Total Price"
			<< std::setw(20) << "Payment Status"
			<< std::setw(20) << "Order Status"
			<< '\n';
		Helper::line(110);

		int counter{};
		if (!pendingOnly) {
			for (const auto& order : currentCustomer->orders)
			{
				std::cout << ++counter << "- ";
				order->summary('c');
			}
		}

		else if (pendingOnly) {
			for (const auto& order : pendingOrders)
			{
				std::cout << ++counter << "- ";
				order->summary('c');
			}
		}

		// can select an order to view or simply go back
		Helper::line(110);
		std::cout << "Select an order to view in detail, "
			<< (!pendingOnly ? "Press P to view Pending orders " : " ")
			<< "or press B to back\n";

		Helper::line(110);
		std::cout << "Your choice: ";
		int choice = (!pendingOnly ? Helper::readChoice(1, currentCustomer->orders.size(), "bPBp")
			: Helper::readChoice(1, anyPending, "bB"));

		if (choice == 'B' || choice == 'b') break;
		if (!pendingOnly && (choice == 'P' || choice == 'p')) myOrders(true);
		else 
			try {
			if (!pendingOnly)
				viewOrder(currentCustomer->orders.at(choice - 1));
			else if (pendingOnly)
				viewOrder(pendingOrders.at(choice - 1));
		}
		catch (const std::out_of_range& error)
		{
			std::cout << "Please choose an order from the ones shown\n";
			continue;
		}
	}
}

void CustomerFlow::viewOrder(const std::shared_ptr<Order>& order)
{
	while (true) {
		// Display:
		std::cout << "View Order\n";
		Helper::dLine(110);
		std::cout << std::setw(18) << "Shop"
			<< std::setw(15) << "Total Price"
			<< std::setw(20) << "Payment Status"
			<< std::setw(20) << "Order Status"
			<< '\n';
		Helper::line(110);

		std::cout << ">> ";
		order->summary('c');
		// Items just like cart
		Helper::dLine(110);
		std::cout << "\nOrder content:\n";
		Helper::line(70);
		order->display();
		Helper::line(70);
		std::cout << std::setw(61) << ">>>Total: " << order->getTotalPrice() << "\n\n";
		Helper::dLine(110);

		if (order->getStatus() < Order::Delivering) std::cout << "Press C to cancel this order, ";
		std::cout << "Press O to reorder this order, or press B to go back\n";
		Helper::line(110);
		std::cout << "Your choice: ";
		int choice = Helper::readChoice(0, 0, "obOBcC");
		if (choice == 'b' || choice == 'B') break;
		if (choice == 'O' || choice == 'o')
		{
			currentCustomer->cart = order;
			std::cout << "Order added to cart, you will be directed to your cart...\n";
			myCart();
			break;
		}
		if (choice == 'C' || choice == 'c') {
			order->cancelOrder();
			std::cout << "Order has been canceled, you will be directed to main menu...\n";
			mainMenu();
			break;
		}

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
		case 2: myOrders();
			break;
		case 3: myCart();
			break;
		case 4: UserFlow::myProfile();
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
	std::cout << std::setw(20) << "Shop Name" << "Shop Address\n";
	Helper::line(80);
	for (int i = 1; i <= numShops; i++) {
		std::cout << i << ". ";
		currentCustomer->availableShops[i - 1]->display('c');
		std::cout << "\n";
	}
	// better define display function in shop class
}


void CustomerFlow::viewShop()
{
	currentCustomer->cart->setShop(currentShop);
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
		std::cout << "Item: ";

		int itemChoice = Helper::readChoice(1, numItems, "CcBb");
		if (itemChoice == 'C' || itemChoice == 'c') {
			myCart();
		}
		if (itemChoice == 'B' || itemChoice == 'b') {
			break;
		}
		while (true) {
			std::cout << "Quantity: ";
			int itemQuantity = Helper::readChoice(0, INT_MAX, "bB");
			if (itemQuantity == 'B' || itemQuantity == 'b') break;

			try {
				currentCustomer->cart->addItem(itemChoice - 1, itemQuantity);
				break;
			}
			catch (int maxQuantity)
			{
				std::cout << "You can only add up to " << maxQuantity << " of this item\nplease try again or press B to cancel...\n";
			}

		}


	}
}
