#include<iostream>
#include"UserFlow.h"
#include"User.h"
#include"C_List.h"
#include"V_List.h"
#include"SO_List.h"


std::shared_ptr<User> UserFlow::currentUser;

std::shared_ptr<User> UserFlow::verifyUsername(std::string username)
{

	return nullptr;
}


void UserFlow::signUp() {
	//ask for username,p/w,name,age,balance,location,transport,availabletime
	//depends on volunteer,shopowner,user
	//use currentUser shared ptr

	// read the input, username and password
	// check the existence of this user with this username
	// we will prompt them to login instead
	
	std::string userName, password, name, location, healthStatus, shop;
	int age {};
	double balance {};
	while (true) {
		char character;
		std::cout << "Who are you? \n";
		std::cout << "C: Customer \n S: Shop Owner \n V: Volunteer\n";
		std::cin >> character;
		std::cout << "Enter your username: ";
		std::cin >> userName;
		std::cout << "Enter a password: ";
		std::cin >> password;
		std::cin.ignore();

		// perform the check of the user

		if (verifyUsername(userName) != nullptr)
		{
			std::cout << "This user already exists, press L to login instead or press B to go back\n";
			char choice;
			std::cin >> choice;
			std::cin.ignore();

			if (choice == 'L' || choice == 'l') login();
			else if (choice == 'B' || choice == 'b') welcomeScreen();
		}


		//
		std::cout << "We will need some additional info\n";
		std::cout << "Enter your name: ";
		std::getline(std::cin, name);
		std::cout << "How old are you? ";
		std::cin >> age;
		std::cin.ignore();
		std::cout << "Enter your location: ";
		std::getline(std::cin, location);
		if (character == 'C' || character == 'c') {
			std::shared_ptr <Customer> newCustomer = std::make_shared<Customer>(userName, password);
			currentUser = newCustomer;
			C_List::addCustomer(newCustomer);
		}
		else if (character == 'S' || character == 's') {
			std::shared_ptr <ShopOwner> newShopOwner = std::make_shared<ShopOwner>(userName, password);
			currentUser = newShopOwner;
			SO_List::addShopOwner(newShopOwner);
			
		}
		else if (character == 'V' || character == 'v') {
			std::shared_ptr <Volunteer> newVolunteer = std::make_shared<Volunteer>(userName, password);
			currentUser = newVolunteer;
			V_List::AddVolunteer(newVolunteer);
		}
		else {
			std::cout << "This choice does not exist.";
			continue;
		}

		std::cout << "few more questions...\n";
		currentUser->setInfo(name, age, balance, location);

		std::cout << "Account registered successfully, you will be directed to main Menu\n";
		welcomeScreen();
	}
}

void UserFlow::login() {
	//ask for username,p/w,verify them from Helper Function
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
		std::cin.ignore();

		currentUser = verifyUsername(userName);
		if (currentUser == nullptr)
		{
			std::cout << "This user does not exist,\nPress S to sign up instead: "
				<< "or press B to go back instead\n";

			// read the answer

			// act		
		}

		currentUser->welcome();
	}
}

void UserFlow::mainMenu() {
}
void UserFlow::welcomeScreen() {
}
