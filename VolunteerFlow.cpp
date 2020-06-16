#include "VolunteerFlow.h"


#include <iomanip>


#include "Helper.h"

std::shared_ptr<Volunteer> VolunteerFlow::currentVolunteer;
std::shared_ptr<Order> VolunteerFlow::currentOrder = nullptr;



void VolunteerFlow::ongoingOrder()
{
	while (true) {
		Helper::dLine(110);
		std::cout << std::setw(18) << "Shop"
			<< std::setw(15) << "Shop Address"
			<< std::setw(20) << "Order's Destination"
			<< std::setw(20) << "Delivery Time"
			<< '\n';
		Helper::line(110);
		currentOrder->summary('v');
		std::cout << "Do you want to hand over the order (H) "
			<< "or go back (B) ?\n";
		int option = Helper::readChoice(0, 0, "HhBb");
		if (option == 'B' || option == 'b') {
			break;
		}
		else if (option == 'H' || option == 'h') {
			currentOrder->setStatus(Order::Complete);
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
			if (pendingOnly)
				std::cout << "No pending orders yet." << std::endl;
			if (!pendingOnly)
				std::cout << "No complete orders yet." << std::endl;
			break;
			
		}

		Helper::dLine(110);
		std::cout << std::setw(4) << "No." << std::setw(20) << "Shop Name"
			<< std::setw(20) << "Shop Address"
			<< std::setw(20) << "Customer Address" << std::setw(15)
			<< "Delivery Time" << std::endl;
		
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

		std::cout << "press B to go back\n";
		int choice = Helper::readChoice(1, orders.size(), "PpBb");
		
	
		if (choice=='P'||choice=='p')
		{
			pendingOnly=!pendingOnly;
			continue;
		}
		
		if(choice=='B'||choice=='b')
		{
			break;
		}
	
		viewOrder(orders[choice - 1]);
	}
}

void VolunteerFlow::mainMenu()
{
	while (true) {
		std::cout << "Welcome " << currentVolunteer->getName() << '\n';
		std::cout << "Your balance: " << currentVolunteer->getBalance() << "\n";
		Helper::dLine();
		std::cout << "Choose an option from the following:\n";

		std::vector <std::string > menuOptions = {
			"Ongoing delivery", "Pending orders",
			"Complete orders", "Register for a shop", "My profile", "Log out"
		};

		Helper::displayMenu(menuOptions);
		Helper::line();
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
		case 4: /*registerShop();*/
			break;
		case 5: /*UserFlow::myProfile();*/
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
		std::cout << "View Order\n";
		Helper::dLine(110);
		std::cout << ">>> Order Status: " << order->getStatus() << "\n";
		Helper::line(110);
				
		std::cout << std::setw(20) << "Shop Name"
			<< std::setw(20) << "Shop Address"
			<< std::setw(20) << "Customer Address" << std::setw(15)
			<< "Delivery Time" << std::endl;
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

		if (choice == 'b' || choice == 'B') break;
		if (choice == 'D' || choice == 'd')
		{
			order->setStatus(Order::Delivering);
			currentOrder = order;
			std::cout << "Delivering this order \n";
		}
		// this function will display the order summary according to the information useful for
		// the volunteer, like the address of the shop and the customer
		// if the order is not yet under delivery and there IS NO ONGOING ORDER, the volunteer
		// should be prompted with "deliver this order" and then it should become the current order
		// and its status should change to delivery
		// if the order is completed, then the summary should be displayed and that's it

	}
}
