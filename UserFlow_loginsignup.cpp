#include<iostream>
#include"UserFlow_loginsignup.h"
#include"User.h"

void Login() {
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
	if (Verify(userName, password)==1) {
		MainMenu();
	}
	else {
		int choice;
		std::cout << "Do you wish to sign up or try again? ";
		std::cout << "Enter 1 for sign up while 2 to login again.";
		std::cin >> choice;
		switch (choice) {
			case 1: SignUp();
			case 2: break;
			default: std::cout << "This choice does not exist.";
					 break;
		}
	}
	}
}

void SignUp() {
	//ask for username,p/w,name,age,balance,location,transport,availabletime
	//depends on volunteer,shopowner,user
	std::string userName, password, name, age, location, healthStatus,shop;
	double balance;
	while(true){
		int character;
		std::cout << "Who are you? \n";
		std::cout << "1: Customer \n 2: Shop Owner \n 3: Volunteer\n";
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
		switch (character) {
		case 1: std::cout<<"Enter your health status: ";
				std::cin >> healthStatus;
				Customer.setInfo(name, age, balance, location);
				//add customer into list
				writeCustomer();
		case 2: std::cout << "Enter your shop(s): ";
				std::cin >> shop;
				ShopOwner.setInfo(name, age, balance, location);
				//add so into list
				writeToFile();
		case 3: balance = 0;
				Volunteer.setInfo(name, age, balance, location);
				//add volunteer into list
				WriteVolunteers();

		default:std::cout << "This choice does not exist.";
				break;
		}
	}
}
