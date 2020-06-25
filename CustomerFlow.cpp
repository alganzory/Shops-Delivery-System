#include "CustomerFlow.h"

#include <iomanip>
#include <sstream>

#include "Helper.h"
#include "SH_List.h"

/// Members
std::shared_ptr<Customer> CustomerFlow::currentCustomer;
std::shared_ptr<Shop> CustomerFlow::currentShop;

/// Methods
void CustomerFlow::makeAnOrder()
{
	findAvailableShops();
	while (true)
	{
		system("CLS");
		std::cout << "\nList of available shops for you at this time\n";
		Helper::dLine(70);
		CustomerFlow::displayShops();
		Helper::line(70);

		int shopChoices = currentCustomer->availableShops.size();
		if(shopChoices==0)
		{
			system("CLS");
			std::cout << "No available shop right now.";
			Helper::delay(1000);
			mainMenu();
			break;
		}
		std::cout << "Please select a shop "
			<< "or Press B to go back: ";
		int chosenIdx = Helper::readChoice(1, shopChoices, "Bb");
		if (chosenIdx == 'B' || chosenIdx == 'b') {
			system("CLS");
			break;
		}
		auto chosenShop = currentCustomer->availableShops[chosenIdx - 1];
		if (!currentCustomer->cart->isEmpty() && 
			currentCustomer -> cart -> getShop() != chosenShop  )
		{
			std::cout << "This will clear your current cart. Proceed? Y(yes)/N(no)" << std::endl;
			int choice = Helper::readChoice(0, 0, "YyNn");
			if (choice == 'N' || choice == 'n')
			{
				continue;
			}
			currentCustomer->cart = std::make_shared<Order>();
		}	

		currentShop = chosenShop;
		
		CustomerFlow::viewShop();
	}
}

void CustomerFlow::checkout()
{
	while (true)
	{
		system("CLS");
		// Display the order and the total price
		std::cout << "\nReview Order\n";
		Helper::dLine(70);
		currentCustomer->cart->display();
		Helper::line(70);
		// ask for delivery time

		while (true) {
			std::cout << "The operation hour of the shop: " << currentShop->getAvailableTimes().first << " - " << currentShop->getAvailableTimes().second << std::endl;
			std::cout << "Enter delivery time in (HH:MM) 24 format or Press B to go back to cart: \n";
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

			if (!isTime)
			{
				system("CLS");
				return;
			}

			try {
				currentCustomer->cart->setDeliveryTime(hour, minutes);
				if (currentCustomer->cart->getDeliveryTime().getTimeDiff().second < 0)
				{
					throw "The time has passed. Please enter the time 30 mins after now.";
				}
				else if (currentCustomer->cart->getDeliveryTime().getTimeDiff().first == 0 && currentCustomer->cart->getDeliveryTime().getTimeDiff().second < 30)
				{
					throw "The time should be at least 30 mins after now.";
				}
				else if (!currentShop->isAvailable(currentCustomer->cart->getDeliveryTime()))
				{
					throw "The shop is not operating on this time.";
				}
				break;
			}
			catch (const char* errorMsg) {
				std::cout << errorMsg << std::endl;
				continue;
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
		Helper::line(80);
		std::cout<<"Do you wish to tip the volunteer? Y (Yes) or N (No): ";
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
			system("CLS");
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
		std::weak_ptr <ShopOwner> shopOwner = currentShop->getShopOwner();
		shopOwner.lock()->addBalance(currentCustomer->cart->getTotalPrice());
		currentCustomer->placeOrder();
		Helper::delay(10000);
		std::cout << "Your order has been placed successfully,\nyou will be directed to main menu...\n";
		Helper::line(40);
		mainMenu();
		break;
	}
	
}


void CustomerFlow::myCart()
{
	system("CLS");
	while (true) {
		

		if (currentCustomer->cart->getOrderSize()==0)
		{
			
			std::cout << "Your cart has no items yet." << '\n';
			std::cout << "You will be directed back...\n";
			Helper::dLine(70);
			Helper::delay(1000);
			system("CLS");
			
			break;
		}
		std::cout << "\nMy cart:\n";
		Helper::dLine(70);
		int choice{};

		currentCustomer->cart->display();
		Helper::line(70);
		std::cout << "Choose an Item number to remove it from the cart\n"
			<< "or press B to go back or C to checkout\n";
		Helper::line(70);
		std::cout << "Your Choice: ";
		choice = Helper::readChoice(1, currentCustomer->cart->getOrderSize(), "BbCc");
		if (choice == 'B' || choice == 'b')
		{
			system("CLS");
			break;
		}
		else if (choice == 'C' || choice == 'c')
		{
			CustomerFlow::checkout();
		}
		else
		{
			std::pair<std::shared_ptr<Item>, int>& item = currentCustomer->cart->getItem(choice - 1);
			std::cout << std::endl;
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
				system("CLS");
			}
			else if (choice == 'b' || choice == 'B')
			{
				system("CLS");
				continue;
				
			}
			else
			{
				/*int quantity = item.second - choice;
				currentCustomer->cart->addItem(item.first, quantity);
				currentCustomer->cart->removeItem(item);*/
				system("CLS");
				currentCustomer->cart->reduceItem(choice, item);
				

			}

		}	
		
	}

}

void CustomerFlow::myOrders(bool ongoingOnly)
{
	while (true)
	{
		system("CLS");
		std::cout << (ongoingOnly ? "\nOngoing Orders" : "\nAll Orders") << '\n';
		Helper::dLine(110);
		int ongoingCount = 0;
		std::vector <std::shared_ptr<Order> > ongoingOrders;

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
		std::for_each(currentCustomer->orders.begin(),currentCustomer->orders.end(), cancelIfOverDue);
		if (anyOverdue)
		{
			Helper::delay(3000);
			continue;
		}
		
		
		if (currentCustomer->orders.empty())
		{
			system("CLS");
			Helper::delay(1000);
			std::cout << "No orders yet, you will be directed to main menu...\n";
			Helper::line();
			mainMenu();
		}

		else if (ongoingOnly)
		{
			ongoingOrders.reserve(currentCustomer->orders.size());
			for (const auto& order : currentCustomer->orders)
			{
				if (order->getStatus() < Order::Complete) {
					ongoingCount++;
					ongoingOrders.emplace_back(order);
				}
			}
			
			if (!ongoingCount) {
				system("CLS");
				Helper::delay(1000);
				std::cout << "No ongoing orders, you will be directed to main menu...\n";
				Helper::line();
				mainMenu();
			}
		}
		
		std::cout << std::setw(4) << "No."
			<< std::setw(20) << "Shop"
			<< std::setw(15) << "Total Price"
			<< std::setw(17) << "Payment Status"
			<< std::setw(20) << "Order Status"
			<< '\n';
		Helper::line(110);

		int counter{};
		if (!ongoingOnly) {
			for (const auto& order : currentCustomer->orders)
			{
				std::cout<<std::setw(4) << ++counter ;
				order->summary('c');
			}
		}

		else if (ongoingOnly) {
			for (const auto& order : ongoingOrders)
			{
				std::cout << std::setw(4) << ++counter;
				order->summary('c');
			}
		}

		// can select an order to view or simply go back
		Helper::line(110);
		std::cout << "Select an order to view in detail, "
			<< (!ongoingOnly ? "Press O to view Ongoing orders " : " ")
			<< "or press B to back\n";

		Helper::line(110);
		std::cout << "Your choice: ";
		int choice = (!ongoingOnly ? Helper::readChoice(1, currentCustomer->orders.size(), "bOBo")
			: Helper::readChoice(1, ongoingCount, "bB"));

		if (choice == 'B' || choice == 'b')
		{
			system("CLS");
			break;
		}
		if (!ongoingOnly && (choice == 'O' || choice == 'o')) myOrders(true);
		else 
			try {
			if (!ongoingOnly)
				viewOrder(currentCustomer->orders.at(choice - 1));
			else if (ongoingOnly)
				viewOrder(ongoingOrders.at(choice - 1));
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
		system("CLS");
		// Display:
		std::cout << "\nView Order\n";
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
			if (!currentCustomer->cart->isEmpty())
			{
				std::cout << "This will clear your current cart. Proceed? (Y/N)" << std::endl;
				int choice = Helper::readChoice(0, 0, "YyNn");
				if (choice == 'N' || choice == 'n')
				{
					continue;
				}
			}
			currentShop = order->getShop();
			currentCustomer->cart->reorder(order);
			system("CLS");
			std::cout << "Order added to cart, you will be directed to your cart...\n";
			myCart();
			break;
		}
		if (choice == 'C' || choice == 'c') {
			order->cancelOrder();
			system("CLS");
			std::cout << "Order has been canceled, you will be directed to main menu...\n";
			Helper::line();
			break;
		}

	}
}


void CustomerFlow::mainMenu()
{
	while (true) {
		system("CLS");
		std::string welcoming = "\nWelcome " + currentCustomer->getName() +'\n';
		Helper::stringDisplay(welcoming);
		Helper::line(currentCustomer->getName().length() + 8);
		std::cout << "Your balance: " << currentCustomer->balance << "\n";
		Helper::dLine(40);
		std::cout << "Choose an option from the following:\n";

		sort(currentCustomer->orders.begin(), currentCustomer->orders.end());

		int anyOngoing = 0;
		for (const auto& order : currentCustomer->orders)
		{
			if (order->getStatus() < Order::Complete) {
				anyOngoing++;
			}
		}

		int cartItem = currentCustomer->cart->getOrderSize();

			std::string ongoingOrders = " (" + std::to_string(anyOngoing) + ")";
			std::string cart = " (" + std::to_string(cartItem) + ")";

		std::vector <std::string > menuOptions = {
			"Make an order", "My orders"+ongoingOrders, "My cart"+cart, "My profile", "Log out"
		};

		Helper::displayMenu(menuOptions);
		Helper::line(40);
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
			system("CLS");
			break;
		default:
			currentCustomer = nullptr;
			UserFlow::logout();
		}

	}
	
	
}

void CustomerFlow::findAvailableShops()
{
	currentCustomer->availableShops.clear(); 
	for (const auto& shop : SH_List::SHOPS)
	{
		Time::calcLocalTime();
		if (shop->isAvailable(Time(Time::localHour, Time::localMinute)))
			currentCustomer->availableShops.emplace_back(shop);
	}
}

void CustomerFlow::displayShops()
{
	int numShops = currentCustomer->availableShops.size();
	// loop through shops and display
	std::cout <<std::setw(4)<<"No."<< std::setw(20) << "Shop Name" <<std::setw(25)<< "Shop Address"<<"Operation hours\n";
	Helper::line(70);
	for (int i = 1; i <= numShops; i++) {
		std::cout << std::setw(4) << i ;
		currentCustomer->availableShops[i - 1]->display('c');
		std::cout << "\n";
	}
	// better define display function in shop class
}


void CustomerFlow::viewShop()
{

	system("CLS");
	while (true)
	{
		std::cout << "\nList of items in ";
		// display the shop
		std::cout << currentShop->getName() << " :\n";
		std::cout <<"Shop Address"<< currentShop->getLocation().getAddress() << std::endl;
		Helper::dLine(65);
		// list shop items
		int numItems = currentShop->getItemsCount();
		std::vector<std::shared_ptr<Item>> shopItems = currentShop->getItems();
		std::cout << std::left<<std::setw(4)<<"No." << std::setw(30) << "Name"
			<< std::setw(20) << "Price" << "In Stock" << "\n";
		Helper::line(65);
		for (int i = 1; i <= numItems; i++) {
			std::cout <<std::setw(4)<< i ;
			shopItems[i - 1]->display();
		}
		Helper::line(65);

		std::cout << "Choose an item number followed by quantity to add it to cart,\n"
			<< " press C to go to cart or press B to go back:\n";

		Helper::line(65);
		std::cout << "Your choice: ";

		int itemChoice = Helper::readChoice(1, numItems, "CcBb");
		if (itemChoice == 'C' || itemChoice == 'c') {
			myCart();
			break;
		}
		if (itemChoice == 'B' || itemChoice == 'b') {
			system("CLS");
			break;
		}
		while (true) {
			std::cout << "Quantity: ";
			int itemQuantity = Helper::readChoice(0, INT_MAX, "bB");
			if (itemQuantity == 'B' || itemQuantity == 'b') break;

			try {
				currentCustomer->cart->setShop(currentShop);
				currentCustomer->cart->addItem(itemChoice - 1, itemQuantity);
				system("CLS");
				std::cout << itemQuantity << " " << shopItems[itemChoice - 1]->getName() << " is added into the cart.\n";
				Helper::line(65);
				break;
			}
			catch (int maxQuantity)
			{
				currentCustomer->cart->setShop(nullptr);
				system("CLS");
				std::cout << "You can only add up to " << maxQuantity << " of this item\nplease try again or press B to cancel...\n";
			}			
		}
	}
}
