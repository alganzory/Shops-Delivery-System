#include "VolunteerFlow.h"

#include "Helper.h"
#include<iomanip>

std::shared_ptr<Volunteer> VolunteerFlow::currentVolunteer;
std::shared_ptr<Order> VolunteerFlow::currentOrder;


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
	// this function will display the order summary according to the information useful for
	// the volunteer, like the address of the shop and the customer
	// if the order is not yet under delivery and there IS NO ONGOING ORDER, the volunteer
	// should be prompted with "deliver this order" and then it should become the current order
	// and its status should change to delivery
	// if the order is completed, then the summary should be displayed and that's it
}
