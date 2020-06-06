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


		// Display header
		// Display Shops
		CustomerFlow::displayShops();
		
		// Choose shop or go back

		// set currentShop to chosen shop out of availableShops
		// vieShop
		CustomerFlow::viewShop();
	}
}




void CustomerFlow::myCart()
{
	while (true) {
		std::cout << "My cart:\n";
		Helper::dLine(60);
		int choice;

		// check if cart is empty
		// else display cart : define display function in order class (to display any order not just cart)
		if (currentCustomer->cart->getOrderSize()==0)
		{
			std::cout << "No Products Yet." << std::endl;
			std::cout << "Press B to go back." << std::endl;
			choice=Helper::readChoice(0,0,"Bb");
			break;
		}
		else
		{
			currentCustomer->cart->orderDisplay();
			std::cout << "Choose an Item number to remove it from the cart\n"
				<< "or press B to go back or C to checkout\n"
				<< "Your Choice: ";
			choice = Helper::readChoice(1,currentCustomer->cart->getOrderSize(),"BbCc");
			if (choice == 'B' || choice == 'b')
			{
				break;
			}
			else if (choice == 'C' || choice == 'c')
			{
				currentCustomer->placeOrder();
			}
			else
			{
				std::pair<std::shared_ptr<Item>, int> item=currentCustomer->cart->getItem(choice);
				std::cout << "You choose to remove:\n"
					<< item.first->getName() << "\tRM" << item.first->getPrice() << "\tquantity: " << item.second << std::endl;
				std::cout << "Enter the quantity you want reduce or press D to remove the item.\n"
					<< "or press B to go back\n";
				choice = Helper::readChoice(0, item.second, "dDbB");
				if (choice == 'd' || choice == 'D')
				{
					currentCustomer->cart->removeItem(item);
				}
				else if (choice == 'b' || choice == 'B')
				{
					continue;
				}
				else
				{
					currentCustomer->cart->removeItem(item);
					item.second -= choice;
					currentCustomer->cart->addItem(item.first,item.second);
				}
			}
		}	
		

		// call respective functions
		// if item number call removeItem
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
		case 2:/* myOrders();*/
			break;
		case 3: myCart();
			break;
		case 4:/* UserFlow::myProfile();*/
			break;
		default:
			currentCustomer = nullptr;
			/*UserFlow::logout();*/
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

	// loop through shops and display
	// better define display function in shop class
}

void CustomerFlow::viewShop()
{
	while (true)
	{
		std::cout << "List of items in ";
		// display the shop
		
		// list shop items

		Helper::line(60);
		std::cout << "Choose an item number followed by quantity to add it to cart,\n"
			<< " press C to go to cart or press B to go back: ";

		
		// call respective functions
		
	}
}
