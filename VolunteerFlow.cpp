#include "VolunteerFlow.h"

#include "Helper.h"


std::shared_ptr<Volunteer> VolunteerFlow::currentVolunteer;


void VolunteerFlow::mainMenu()
{
	while (true) {
		std::cout << "Welcome " << currentVolunteer->getName() << '\n';
		std::cout << "Your balance: " << currentVolunteer->getBalance() << "\n";
		Helper::dLine();
		std::cout << "Choose an option from the following:\n";

		std::vector <std::string > menuOptions = {
			"Deliver an order", "My delivered orders", "Register for a shop", "My profile", "Log out"
		};

		Helper::displayMenu(menuOptions);
		Helper::line();
		std::cout << "Your choice: ";
		int choice = Helper::readChoice(1, 5);


		switch (choice)
		{
		case 1: /*deliverAnOrder();*/
			break;
		case 2: /*myOrders();*/
			break;
		case 3: /*registerShop();*/
			break;
		case 4: /*UserFlow::myProfile();*/
			break;
		default:
			currentVolunteer= nullptr;
			/*UserFlow::logout();*/
		}

	}
}
