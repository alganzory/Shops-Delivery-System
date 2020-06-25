#include "VolunteerFlow.h"


#include <iomanip>


#include "Helper.h"
#include "SH_List.h"

/// Members
std::shared_ptr<Volunteer> VolunteerFlow::currentVolunteer;
std::shared_ptr<Order> VolunteerFlow::currentOrder = nullptr;

/// Methods
void VolunteerFlow::ongoingOrder()
{
	while (true) {
		system("CLS");
		std::cout << "\nOngoing Order:\n";
		Helper::dLine(110);
		if (currentOrder == nullptr)
		{
			system("CLS");
			std::cout << "No ongoing orders, you will be directed back to the main menu\n";
			Helper::line(45);
			Helper::delay(1000);
			break;
		}
		std::cout << std::setw(20) << "Shop"
			<< std::setw(20) << "Shop Address"
			<< std::setw(20) << "Order's Destination"
			<< std::setw(15) << "Delivery Time"
			<<std::setw(20)<<"Customer's Health Status"
			<< '\n';
		Helper::line(110);
		currentOrder->summary('v');
		Helper::line(110);
		std::cout << "Order Total Price: " << currentOrder->getTotalPrice() << "\n";
		std::cout << "Payment Status: ";
		(currentOrder->getPaymentStatus() == true) ? std::cout << "Paid\n" : std::cout<< "Pending\n";
		std::cout << "Customer's name: " << currentOrder->getCustomerName() << "\n";
		std::cout << "Customer's health status: " << currentOrder->customer->getHealthStatus() << "\n";
		Helper::line(110);
		
		if (currentOrder->getContactlessDlvr()==true) {
			std::cout << "This customer needs a contactless delivery\n"
				<< "For your safety and theirs, please hand over the order contactlessly\n";
		}
		else {
			std::cout << "This customer does not need a contactless delivery.\n"
				<< "For your safety and theirs, make sure you wear a mask\n";
		}
		Helper::line(110);
		std::cout << "Do you want to hand over the order (H) "
			<< "or go back (B)?: ";
		int option = Helper::readChoice(0, 0, "HhBb");
		if (option == 'B' || option == 'b') {
			system("CLS");
			break;
		}
		if (option == 'H' || option == 'h') {
			system("CLS");
			currentOrder->setStatus(Order::Complete);
			double reward = currentOrder->getReward();
			if (reward > 0) {
				currentVolunteer->getReward(reward); 
				std::cout << "You have been tipped: " << reward << "\n";
			}
			else
			{
				system("CLS");
			}
			currentOrder = nullptr;
			std::cout << "Thanks for serving the community...\n";
			Helper::line(45);
			Helper::delay(1000);
			break;
		}
	}
}

void VolunteerFlow::myOrders(bool pendingOnly)
{
	// This function displays the list of orders
	// if the pendingOnly flag is activated, only the orders that have the 
	// VolunteerFound status should be displayed
	// if not then display the order with status complete
	// then the user should be prompted to choose to view an Order
	while (true)
	{
		system("CLS");
		std::cout << std::endl;
		std::sort(currentVolunteer->orders.begin(), currentVolunteer->orders.end());
		
		std::vector<std::shared_ptr<Order>> orders;
		orders.reserve(currentVolunteer->orders.size());
		
		for (int i=0; i<currentVolunteer->orders.size();i++)
		{
			if (pendingOnly && currentVolunteer->orders[i]->getStatus() == Order::VolunteerFound)
			{
				orders.push_back(currentVolunteer->orders[i]);
				
			}
			else if (!pendingOnly&& currentVolunteer->orders[i]->getStatus() == Order::Complete)
			{
				orders.push_back(currentVolunteer->orders[i]);
			}
		}
	
		if (orders.empty())
		{
			system("CLS");
			if (pendingOnly)
			{
				std::cout << "No pending orders yet." << std::endl;
				Helper::line(45);
				Helper::delay(1000);
			}
			if (!pendingOnly)
			{
				std::cout << "No complete orders yet." << std::endl;
				Helper::line(45);
				Helper::delay(1000);
			}
			break;
			
		}

		Helper::dLine(110);
		std::cout << std::setw(4) << "No." << std::setw(20) << "Shop Name"
			<< std::setw(20) << "Shop Address"
			<< std::setw(20) << "Customer Address" << std::setw(15)
			<< "Delivery Time" <<std::setw(20)<<"Customer's Health Status"<< std::endl;
		
		Helper::line(110);
		
		for (int j = 0; j < orders.size(); j++)
		{
			std::cout << std::setw(4) << j + 1;
			orders[j]->summary('v');

		}
		
		Helper::line(110);

		std::cout << "Enter the order number to view the details or ";
		if (pendingOnly)
			std::cout << "press P to view Complete Orders or";
		else
			std::cout << "press P to view Pending Orders or";

		std::cout << "press B to go back\nYour choice: ";
		int choice = Helper::readChoice(1, orders.size(), "PpBb");
		
	
		if (choice=='P'||choice=='p')
		{
			pendingOnly=!pendingOnly;
			continue;
		}
		
		if(choice=='B'||choice=='b')
		{
			system("CLS");
			break;
		}
	
		viewOrder(orders[choice - 1]);
	}
}

void VolunteerFlow::registerShop()
{
	while (true)
	{
		system("CLS");
		std::cout << "\nAvailable Shops for you:\n";
		Helper::dLine(110);
		int numShops = SH_List::SHOPS.size();
		// loop through shops and display
		for (int i = 1; i <= numShops; i++) {
			std::cout << i << ". ";
			SH_List::SHOPS[i - 1]->display('v');

			if (currentVolunteer->registeredShops[i - 1])
				std::cout << std::setw(18)<< "Registered"<<std::left;
			else std::cout << std::setw(18) << "Not Registered" << std::left;
			std::cout << "\n";
		
		}

		Helper::line(100);
		std::cout << "Choose a shop to register/unregister for or press B to go back: ";
		int choice = Helper::readChoice(1, numShops, "bB");
		if (choice == 'b' || choice == 'B') break;
		if (currentVolunteer->registeredShops[choice - 1] == true)
		{
			std::cout << "You are registered for this shop, are you sure you want to unregister? (Y/N)?: ";
			int ans = Helper::readChoice(0, 0, "YyNn");
			if (ans == 'n' || ans == 'N') continue;
			else
			{
				currentVolunteer->registeredShops[choice - 1] = false;
				SH_List::SHOPS[choice - 1]->removeVolunteer(currentVolunteer);
				continue;
			}
		}
		else
		{
			currentVolunteer->registerToShop(choice - 1);
			SH_List::SHOPS[choice - 1]->addVolunteer(currentVolunteer);
			system("CLS");
			std::cout << "You have successfully register for this shop\n";
			Helper::delay(1000);
			continue;
	
		}
	}
}

void VolunteerFlow::mainMenu()
{
	
	while (true) {
		system("CLS");
		std::string welcoming = "\nWelcome " + currentVolunteer->getName() +'\n';
		Helper::line(currentVolunteer->getName().length() + 8);
		Helper::stringDisplay(welcoming);
		std::cout << "Your balance: " << currentVolunteer->getBalance() << "\n";
		Helper::dLine();
		std::cout << "Choose an option from the following:\n";

		int anyPending = 0;
		for (const auto& order : currentVolunteer->orders)
		{
			if (order->getStatus() == Order::VolunteerFound) {
				anyPending++;
			}
		}

		
		std::vector <std::string > menuOptions = {
			"Ongoing delivery (" + std::to_string (currentOrder != nullptr) + ")",
			"Pending orders ("+std::to_string(anyPending)+")",
			"Complete orders", "Register for a shop", "My profile", "Log out"
		};

		Helper::displayMenu(menuOptions);
		Helper::line(45);
		std::cout << "Your choice: ";
		int choice = Helper::readChoice(1, menuOptions.size());


		switch (choice)
		{
		case 1: ongoingOrder();
			break;
		case 2: myOrders(true);
			break;
		case 3: myOrders(false);
			break;
		case 4: registerShop();
			system("CLS");
			break;
		case 5: UserFlow::myProfile();
			system("CLS");
			break;
		default:
			currentVolunteer= nullptr;
			UserFlow::logout();
		}

	}
}

void VolunteerFlow::viewOrder(const std::shared_ptr<Order>& order)
{
	while (true) {
		system("CLS");
		std::cout << "\nView Order\n";
		Helper::dLine(110);
		std::cout << ">>> Order Status: " << order->getStatus() << "\n";
		Helper::line(110);
				
		std::cout << std::setw(20) << "Shop Name"
			<< std::setw(20) << "Shop Address"
			<< std::setw(20) << "Customer Address" << std::setw(15)
			<< "Delivery Time" << std::setw(20) << "Customer's Health Status" << std::endl;
		Helper::line(110);
		order->summary('v');
		Helper::line(110);
		std::cout << "Order Total Price: " << order->getTotalPrice() << "\n";
		std::cout << "Payment Status: " << order->getPaymentStatus() << "\n";
		std::cout << "Customer's name: " << order->getCustomerName() << "\n";
		Helper::line(110);
		if (order->getStatus() == Order::VolunteerFound && currentOrder == nullptr)
			std::cout << "Press (D) to deliver this order, ";
		std::cout << "Press B to go back\n";
		int choice = Helper::readChoice(0, 0, "DdBb");

		if (choice == 'b' || choice == 'B')
		{
			system("CLS");
			break;
		}
		if (choice == 'D' || choice == 'd')
		{
			order->setStatus(Order::Delivering);
			currentOrder = order;
			ongoingOrder();

		}
		// this function will display the order summary according to the information useful for
		// the volunteer, like the address of the shop and the customer
		// if the order is not yet under delivery and there IS NO ONGOING ORDER, the volunteer
		// should be prompted with "deliver this order" and then it should become the current order
		// and its status should change to delivery
		// if the order is completed, then the summary should be displayed and that's it

	}
}
