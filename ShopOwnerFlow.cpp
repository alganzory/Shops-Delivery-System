#include "ShopOwnerFlow.h"

#include <iomanip>


#include "Helper.h"
#include "UserFlow.h"
#include "User.h"

/// Members
std::shared_ptr <ShopOwner> ShopOwnerFlow::currentSO;

/// Methods
void ShopOwnerFlow::editItem(const std::shared_ptr<Item> item)
{
	while (true)
	{
		system("CLS");
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
			std::cout << "Enter the new name: ";
			std::string newName;
			getline(std::cin, newName);
			item->setName(newName);
			continue;
		}
		if (choice == 'q' || choice == 'Q') {
			Helper::line(60);
			std::cout << "Enter the new quantity: ";
			int newQuantity{};
			std::cin >> newQuantity;
			std::cin.ignore();
			item->setInStock(newQuantity);
		}
		else if (choice == 'p' || choice == 'P') {
			Helper::line(60);
			std::cout << "Enter the new price: ";
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
		system("CLS");
		std::cout << "\nAdd Item\n";
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
		system("CLS");
		std::cout<<'\n' << currentSO->getShopName() << '\n'; //update
		Helper::dLine();
		int numItems = currentSO->getShopSize();
		std::vector <std::shared_ptr <Item> > currItems = currentSO->getShopPtr()->getItems();
		std::cout << "Number of Items: " << numItems << '\n';  //update
		Helper::line(45);
		if (numItems) {
			std::cout << "Here is the list of items your shop:\n";
			Helper::line(60);
			std::cout << std::left<<std::setw(4)<<"No." << std::setw(30) << "Item name" << std::setw(20)
				<< "Price" << "Quantity" << '\n';
			Helper::line(60);
			int counter = 0;


			for (auto& item : currItems)
			{
				std::cout<<std::setw(4) << ++counter ;
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
		if (choice == 'b' or choice == 'B') {
			system("CLS");
			break;
		}

		try {
			ShopOwnerFlow::editItem(currItems.at(choice - 1));
		}
		catch (const std::out_of_range& error)
		{
			std::cout << "Please choose an item from the ones shown\n";
			Helper::delay(1000);
			continue;
		}
	}
}

void ShopOwnerFlow::mainMenu()
{
	
	while (true) {
		system("CLS");
		std::string welcoming = "\nWelcome " + currentSO->getName() + '\n';
		Helper::stringDisplay(welcoming);
		Helper::line(currentSO->getName().length() + 8);
		std::cout << "Your balance: " << currentSO->getBalance() << "\n";
		Helper::dLine();
		std::cout << "Choose an option from the following:\n";

		int anyOngoing = 0;
		for (const auto& order : currentSO->orders)
		{
			if (order->getStatus() < Order::Complete) {
				anyOngoing++;
			}
		}

		std::vector <std::string > menuOptions = {
			"My Shop", "Ongoing orders (" + std::to_string(anyOngoing)+")", "All Orders ("+ std::to_string(currentSO->orders.size())+")", "My profile", "Log out"
		};

		Helper::displayMenu(menuOptions);
		Helper::line(45);
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
		case 4: UserFlow::myProfile();
			system("CLS");
			break;
		default:
			currentSO= nullptr;
			UserFlow::logout();
		}

	}
}

void ShopOwnerFlow::allOrders(bool ongoingOnly)
{
	
	while (true)
	{
		system("CLS");

		// if empty go back
		
		if (currentSO->orders.empty())
		{
			system("CLS");
			std::cout << "No Order Yet." << std::endl;
			Helper::line(45);
			Helper::delay(2500);
			break;
		}
		// sorting the list of orders
		std::sort(currentSO->orders.begin(), currentSO->orders.end());

		// Title
		ongoingOnly ? std::cout << "Ongoing Orders\n" : std::cout << "All Orders\n";
		Helper::dLine(123);

		
		// vector to store indices of ongoing orders in case we want to see only ongoing orders
		std::vector <int > ongoingOrders;

		// enumerate the list of orders, if the order is ongoing and overdue, change it to canceled and notify
		bool anyOverdue = false;
		auto cancelIfOverDue = [ongoingOnly, &anyOverdue](const std::shared_ptr <Order>& order)
		{
			if (order->getStatus() == Order::Pending)
				if (order->isOverdue()) {
					anyOverdue = true;
					order->cancelOrder();
					std::cout << "The order from " << order->getCustomerName()
						<< " due on " << order->getDeliveryTime()
						<< " has been canceled due to being overdue\n";
					if (ongoingOnly)
						std::cout << " You can find it in all orders menu\n";
				}
		};
		std::for_each(currentSO->orders.begin(), currentSO->orders.end(), cancelIfOverDue);
		if (anyOverdue)
		{
			Helper::delay(3000);
			continue;
		}// notify and reload the page
		
		// heading
		std::cout << std::setw(4) << "No." << std::setw(20) << "Customer Name"
			<< std::setw(17) << "Payment status" << std::setw(23) << "Status"
			<< std::setw(15)<< "Delivery Time" << std::setw(20) <<  "Total Price (RM)" 
			<< std::setw(20) << "Customer's Health Status" << std::endl;
		Helper::line(123);
		

		int count = 0;
		for (int i = 0; i < currentSO->orders.size(); i++)
		{
			
			if (ongoingOnly) {
				ongoingOrders.reserve(currentSO->orders.size());
				
				if ((currentSO->orders[i]->getStatus() < Order::Complete))
					ongoingOrders.push_back(i);
				else
					continue;	
			}

			std::cout << std::setw(4) << ++count;
			currentSO->orders[i]->summary('s');
		}

		
		if (ongoingOnly && ongoingOrders.empty())
		{
			std::cout << "No ongoing orders at the moment." << std::endl;
			Helper::delay(1000);
			break;
		}

		// Prompt to choose
		Helper::line(123);
		std::cout << "Choose the order number to view detail\n"
			<< "or press O to view";
		(ongoingOnly) ? std::cout << "All Orders\n" : std::cout << "Ongoing Orders";
		std::cout << "or press B to go back.\n";

		std::cout << "Your choice: ";
		int choice;

		if (!ongoingOnly)
			choice = Helper::readChoice(1, currentSO->orders.size(), "OoBb");
		else
			choice = Helper::readChoice(1, ongoingOrders.size(), "oOBb");

		if (choice == 'B' || choice == 'b')
		{
			system("CLS");
			break;
		}
		
		if (choice == 'o' || choice == 'O')
		{
			ongoingOnly = !ongoingOnly;
			continue;
		}
		if (ongoingOnly)
			viewOrder(currentSO->orders[ongoingOrders[choice - 1]]);
		else
			viewOrder(currentSO->orders.at(choice - 1));

	}

}

void ShopOwnerFlow::assignVolunteer(const std::shared_ptr<Order>& order)
{
	while (true) {
		system("CLS");
		std::cout << "Assign a Volunteer for this Order\n";
		Helper::dLine(80);
		std::cout << "Order time: " << order->getDeliveryTime()
			<< std::setw(50) << std::right << "Customer location: " << order->getDlvryAddress()
			<< '\n' << std::left;
		Helper::dLine(80);
		auto avlblVol = findAvailableVolunteers(order->getDeliveryTime());

		if (avlblVol.empty())
		{
			std::cout << "No available volunteers at this time, you will be directed...\n";

			Helper::delay(1000);			break;
		}

		std::cout <<std::setw(4)<<"No."<< std::setw(18) << "Name"
			<< std::setw(26) << "Location"
			<< "Available Times"
			<< '\n';
		Helper::line(80);

		for (int i = 0; i < avlblVol.size(); i++)
		{
			std::cout << i + 1 << "-";
			avlblVol[i]->display();
		}

		Helper::line(80);
		std::cout << "Choose a volunteer to assign to this order or press B to go back: ";
		int choice = Helper::readChoice(1, avlblVol.size(), "Bb");

		if (choice == 'B' || choice == 'b') break;
		order->setStatus(Order::VolunteerFound);
		order->setDelivery(avlblVol[choice - 1]);
		avlblVol[choice - 1]->addOrder(order);
		std::cout << "Volunteer assigned and notified, you will be sent back...\n";

		Helper::delay(1000);		break;
	}
}

void ShopOwnerFlow::viewOrder(std::shared_ptr<Order>& order)
{
	while (true) {
		system("CLS");
		std::cout << "\nOrder Details: \n";
		Helper::dLine(120);
		std::cout << std::setw(20) << "Customer Name"
			<< std::setw(17) << "Payment status" << std::setw(23) << "Status"
			<< std::setw(15) << "Delivery Time" << std::setw(20) << "Total Price (RM)"
			<< std::setw(20) << "Customer's Health Status" << std::endl;
		Helper::line(120);
		order->summary('s');
		Helper::dLine(120);
		std::cout << "\nOrder Content: \n";
		Helper::dLine(70);
		order->display();
		Helper::line(70);

		bool preparationDone = false;
		//-> if the order is ongoing:
		if (order->isReady() && order->getDelivery() == nullptr) {
			std::cout << "Assign a volunteer (A), ";
			preparationDone = true;
		}
		
		if (order->getStatus() <= Order::Preparing)
			std::cout << "Cancel the order (C), "
			<< "preparation list (S), ";

		std::cout << "Go back (B) ?\n";
		Helper::line(60);
		std::cout << "Your choice: ";

		int action{};
		if (order->getStatus() <= Order::Preparing)
			action = (preparationDone) ?
			Helper::readChoice(0, 0, "aABbCcSs") :
			Helper::readChoice(0, 0, "BbCcSs");
		
		else action = Helper::readChoice(0, 0, "Bb");

		if (action == 'B' || action == 'b') {
			break;
		}

		else if (action == 'A' || action == 'a') {
			assignVolunteer(order);
			continue;
		}
		else if (action == 'C' || action == 'c') {
			
			order->cancelOrder();
			return;
		}
		else if (action == 'S' || action == 's') {
			orderPreparation(order);
		}
	}
}

void ShopOwnerFlow::orderPreparation(std::shared_ptr<Order>order)
{
	while (true)
	{
		system("CLS");
		Helper::dLine(110);
		std::cout << "Delivery Time: " << order->getDeliveryTime() << std::endl;
		Helper::line(110);
		order->display(true);


		Helper::line(110);
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
			order->setPreparationStatus(choice - 1);
			order->setStatus(Order::Preparing);
		}
	}
}

std::vector<std::shared_ptr<Volunteer>> ShopOwnerFlow::findAvailableVolunteers(Time time)
{
	std::vector<std::shared_ptr<Volunteer>> availableVolunteers;
	availableVolunteers.reserve(currentSO->registeredVolunteers.size());
	for (auto& volunteer: currentSO->registeredVolunteers)
	{
		if (volunteer->isAvailable(time))
			availableVolunteers.emplace_back(volunteer);
	}
	return availableVolunteers;
}

