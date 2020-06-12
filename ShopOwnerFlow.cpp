#include "ShopOwnerFlow.h"

#include <iomanip>


#include "Helper.h"
#include "UserFlow.h"
#include "User.h"

bool sortByDeliveryTime(const std::shared_ptr<Order> lhs, const std::shared_ptr<Order> rhs) { return lhs->getDeliveryTime() < rhs->getDeliveryTime(); }


std::shared_ptr <ShopOwner> ShopOwnerFlow::currentSO;

void ShopOwnerFlow::editItem(const std::shared_ptr<Item> item)
{
	while (true)
	{
		std::cout << '\n'; //clrscr
		std::cout << "Edit item" << std::endl;
		Helper::line(60);
		std::cout << std::setw(30) << "Name" << std::setw(20)
			<< "Price" << "Quantity" << '\n';
		item->display();
		Helper::line(60);
		std::cout << "Press N to change Item Name, P to change price,\n"
			<< "Q to change quantity, or B to go back: ";
		int choice = Helper::readChoice(0, 0, "nbNBPQpq");
		if (choice == 'N' || choice == 'n') {
			Helper::line(60);
			std::cout << "Enter the new name: \n";
			std::string newName;
			getline(std::cin, newName);
			item->setName(newName);
			continue;
		}
		if (choice == 'q' || choice == 'Q') {
			Helper::line(60);
			std::cout << "Enter the new quantity: \n";
			int newQuantity{};
			std::cin >> newQuantity;
			std::cin.ignore();
			item->setInStock(newQuantity);
		}
		else if (choice == 'p' || choice == 'P') {
			Helper::line(60);
			std::cout << "Enter the new price: \n";
			double newPrice{};
			std::cin >> newPrice;
			std::cin.ignore();
			item->setPrice(newPrice);
		}
		else break;
	}
}

void ShopOwnerFlow::addNewItem()
{
	while (true) {
		std::cout << "Add Item\n";
		Helper::dLine();

		std::cout << "Enter the name of the new item: ";
		std::string itemName;
		getline(std::cin, itemName);

		std::cout << "Enter Item price: ";
		double itemPrice{};
		std::cin >> itemPrice;
		std::cin.ignore();

		std::cout << "Enter item quantity: ";
		int quantity{};
		std::cin >> quantity;
		std::cin.ignore();
		auto newItem = std::make_shared<Item>(itemName, itemPrice, quantity);
		char ans;

		try {
			currentSO->addToStock(newItem, quantity, true);
		}
		catch (const char* itemExists) {
			std::cout << itemExists
				<< ", Do you want to add the quantity to it instead (Y/N)? : ";
			std::cin >> ans;
			std::cin.ignore();

			if (ans == 'y' || ans == 'Y')
			{
				currentSO->addToStock(newItem, quantity, false);
			}
			else {
				std::cout << "Item discarded\n";
				break;
			}
		}

		std::cout << "Item updated!\n"
			<< "Press N to add a new one or B to go back: ";
		std::cin >> ans;
		std::cin.ignore();

		if (ans == 'B' or ans == 'b') break;
	}

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
		case 2: allOrders(true);
			break;
		case 3: allOrders();
			break;
		case 4: /*UserFlow::myProfile();*/
			break;
		default:
			currentSO= nullptr;
			UserFlow::logout();
		}

	}
}


void ShopOwnerFlow::allOrders(bool pendingOnly)
{
	// do I need to sort them based on something?
	// I will want to sort them based on time? ex: bonus
	// display the orders from the list of orders:
	// prompt the shopOwner to view a certain order //delivery status & amount paid
	// if he was viewing all orders, u prompt to see only pending ones
	// or else go back
	const std::string status[] = { "Pending","Preparing","Delivering","Complete" };
	while (true)
	{
		if (currentSO->orders.size() == 0)
		{
			Helper::dLine();
			std::cout << "No Order Yet." << std::endl;
			Helper::line();
			break;
		}
		Helper::dLine();
		std::cout << std::setw(4) << "No." << std::setw(15) 
			<< "Delivery Time" << std::setw(10) << "Status" << "Total Price (RM)" << std::endl;
		Helper::line();
		std::vector <std::shared_ptr<Order> > sortedOrder;


		std::sort(currentSO->orders.begin(), currentSO->orders.end(), sortByDeliveryTime);
		for (int i = 0; i < currentSO->orders.size(); i++)
		{
			if (pendingOnly) {

				if ((currentSO->orders[i]->getStatus() <= Order::Preparing))
					sortedOrder.push_back(currentSO->orders[i]);
				else
					continue;
			}

			currentSO->orders[i]->summary('s');

		}

		Helper::line();
		if (pendingOnly)
		{
			std::cout << "Choose the order number to view detail\n"
				<< "or press P to view all Orders\n" 
				<< "or press B to go back.\n";
		}
		else
		{
			std::cout << "Choose the order number to view detail\n" 
				<< "or press P to view Pending Orders only\n" 
				<< "or press B to go back.\n";
		}
		std::cout << "Your choice: ";
		int choice{};
		
		if (!pendingOnly) 
			choice = Helper::readChoice(1, currentSO->orders.size(), "PpBb");
		else 
			choice = Helper::readChoice(1, sortedOrder.size(), "pPBb");

		if (choice == 'B' || choice == 'b')
		{
			break;
		}
		else if (choice == 'P' || choice == 'p')
		{
			pendingOnly = !pendingOnly;
			continue;
		}
		else
		{
			if (pendingOnly)
				viewOrder(sortedOrder.at(choice - 1));
			else
				viewOrder(currentSO->orders.at(choice - 1));
		}
	}
	
}

void ShopOwnerFlow::viewOrder(std::shared_ptr<Order>& order)
{
	
	while (true) {
		Helper::dLine(60);
		std::cout << "Order Details: \n";
		Helper::dLine(60);
		order->summary('s');
		//-> if the order is pending:
		if (order->getDelivery() == nullptr)
			std::cout << "Assign a volunteer (A), ";

		if (order->getStatus() <= Order::Preparing)
			std::cout << "Cancel the order (C), "
			<< ", preparation list (S), ";

		std::cout << "Go back (B) ?\n";
		Helper::line(60);
		std::cout << "Your choice: ";
		
		int action{};
		if (order->getStatus() <= Order::Preparing)
			action = (order->getDelivery() == nullptr) ?
			Helper::readChoice(0, 0, "aABbCcSs") : Helper::readChoice(0, 0, "BbCcSs");
		else action = Helper::readChoice(0, 0, "Bb");
					 
		if (action == 'B' || action == 'b') {
			break;
		}

		else if (action == 'A' || action == 'a') {
			//- assign volunteer: releaseOrder();
		}
		else if (action == 'C' || action == 'c') {
			order->cancelOrder();
			std::cout << "Order has been canceled, redirecting you to main menu...\n";
			mainMenu();
			break;
		}
		else if (action == 'S' || action == 's') {
			todoList(order);
		}

		
	}
}


void ShopOwnerFlow::todoList(std::shared_ptr<Order>order)
{
	while (true)
	{
		Helper::dLine();
		std::cout << "Delivery Time: " << order->getDeliveryTime() << std::endl;
		Helper::line();
		std::cout << std::setw(4) << "No." << std::setw(20)
			<< "Item Name" << std::setw(5)
			<< "Qty" << "Preparation Status" << '\n';
		Helper::line();
		order->summary('t');

		if (!order->isReady())
			std::cout << "Enter the item number that has prepared or ";

		std::cout << "press B to go back\n";
		std::cout << "Your choice: ";
		int choice = Helper::readChoice(1, order->getOrderSize(), "Bb");
		if (choice == 'b' || choice == 'B')
		{
			break;
		}
		else
		{
			order->setPreparationStatus(choice-1);
		}
	}

}

