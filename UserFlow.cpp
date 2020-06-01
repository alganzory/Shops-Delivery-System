#include<iostream>
#include"UserFlow.h"
#include"User.h"
#include"C_List.h"
#include"V_List.h"
#include"SO_List.h"

std::shared_ptr<User> currentUser;

void userFlow::signUp() {
	//ask for username,p/w,name,age,balance,location,transport,availabletime
	//depends on volunteer,shopowner,user
	//use currentUser shared ptr
	std::string userName, password, name, location, healthStatus, shop;
	int age;
	double balance;
	while (true) {
		char character;
		std::cout << "Who are you? \n";
		std::cout << "C: Customer \n S: Shop Owner \n V: Volunteer\n";
		std::cin >> character;
		std::cout << "Enter your username: ";
		std::cin >> userName;
		std::cout << "Enter a password: ";
		std::cin >> password;
		std::cout << "Enter your name: ";
		std::cin >> name;
		std::cout << "How old are you? ";
		std::cin >> age;
		std::cout << "Enter your location: ";
		std::cin >> location;
		if (character == 'C' || character == 'c') {
			std::cout << "Enter your health status: ";
			std::cin >> healthStatus;
			std::shared_ptr <Customer> newCustomer = std::make_shared<Customer>(userName, password);
			currentUser = newCustomer;
			C_List::addCustomer(newCustomer);
			
		}
		else if (character == 'S' || character == 's') {
			std::cout << "Enter your shop(s): ";
			std::cin >> shop;
			std::shared_ptr <ShopOwner> newShopOwner = std::make_shared<ShopOwner>(userName, password);
			currentUser = newShopOwner;
			SO_List::addShopOwner(newShopOwner);
			
		}
		else if (character == 'V' || character == 'v') {
			balance = 0;
			//add volunteer into list
			std::shared_ptr <Volunteer> newVolunteer = std::make_shared<Volunteer>(userName, password);
			currentUser = newVolunteer;
			V_List::AddVolunteer(newVolunteer);
			
		}
		else {
			std::cout << "This choice does not exist.";
			break;
		}
		currentUser->setInfo(name, age, balance, location);
	}
}

void userFlow::login() {
	//ask for username,p/w,verifythemfromHelperFunction
	//if not ask to sign up,if gt then cont verify the p/w
	//if p/w correct then show menu screen
	//incorrect ask to enter again
	while (true)
	{
		std::string userName, password;
		std::cout << "Username: ";
		std::cin >> userName;
		std::cout << "Password: ";
		std::cin >> password;
		if (verify(userName, password) == 0) {
			//sign up if username wrong
			signUp();
			break;
		}
		else if (verify(userName, password) == 1) {
			//incorrect pw
			break;
		}
		else if (verify(userName, password) == 2) { //correct
			mainMenu();
			break;
		}
	}
}

void userFlow::mainMenu() {
}
void userFlow::welcomeScreen() {
}
int userFlow::verify(std::string username, std::string password) {
}