#include "VolunteerFlow.h"

#include "Helper.h"


std::shared_ptr<Volunteer> VolunteerFlow::currentVolunteer;
std::shared_ptr<Volunteer> VolunteerFlow::currentOrder;


void VolunteerFlow::ongoingOrder()
{
	// This function keeps track of the order which state is Delivery
	// actually this order is the one called currentOrder
	// it display the order summary and the option to hand over the order
	// if the volunteer chooses to handover the order, its state should then change
	// to complete order and if the order had any tips it should be added to his balance
	// and notify him about that tip
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
