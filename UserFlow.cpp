#include "UserFlow.h"


#include "CustomerFlow.h"
#include "Helper.h"
#include "ShopOwnerFlow.h"
#include "VolunteerFlow.h"


std::shared_ptr<User> UserFlow::currentUser;
void UserFlow::welcomeScreen()
{
	int choice = -1;
	while (choice != 99)
	{
		std::cout << "\nCOVID-19 SHOPS DELIVERY SYSTEM" << std::endl;
		Helper::dLine();
		Helper::displayMenu({ "Log in", "Sign up", "Exit" });
		Helper::line();
		std::cout << "Your choice: ";
		choice = Helper::readChoice(1, 3);

		switch (choice)
		{
		case 1:	login();
			break;
		case 2:	signUp();
			break;
		case 3:return;
			break;
		default:std::cout << "Please choose the correct number." << std::endl;
		}
	}

}

std::shared_ptr<User> UserFlow::verifyUsername(std::string username)
{
	for (int i = 0; i < C_List::getCustomerCount(); i++)
	{
		if (username==C_List::ALL_CUSTOMERS[i]->getUsername())
		{
			return C_List::ALL_CUSTOMERS[i];
		}
	}
	for (int j = 0; j < V_List::getVolunteersCount(); j++)
	{
		if (username==V_List::ALL_VOLUNTEERS[j]->getUsername())
		{
			return V_List::ALL_VOLUNTEERS[j];
		}
	}
	for (int k = 0; k < SO_List::getCount(); k++)
	{
		if (username==SO_List::SHOPOWNERS[k]->getUsername())
		{
			return SO_List::SHOPOWNERS[k];
		}
	}
	return nullptr;
}

void UserFlow::logout()
{
	currentUser = nullptr;
	welcomeScreen();
}

void UserFlow::myProfile()
{
	bool isSO = false, isCu = false, isVol = false;

	while (true){
		std::cout << "My Profile\n";
		Helper::dLine(110);
		std::cout << "Here are your info, press the letter corresponding to the info to change it...\n"
			<< "or press B to go back\n";
		Helper::line(110);
		std::cout << "(N) Name: " << currentUser->name << "\n";
		Helper::line(110);
		std::cout << "(D) Password Change" << "\n";
		Helper::line(110);
		std::cout << "(A) Age: " << currentUser->age << "\n";
		Helper::line(110);
		std::cout << "(L) Location: " << currentUser->location.getAddress() << "\n";
		Helper::line(110);
		std::cout << "(U) Balance: " << currentUser->balance << "\n";
		Helper::line(110);
		if (CustomerFlow::currentCustomer != nullptr)
		{
			isCu = true;
			std::cout << "(H) Health Status: " << CustomerFlow::currentCustomer->getHealthStatus() << "\n";
			Helper::line(110);
		}
		else if (VolunteerFlow::currentVolunteer != nullptr)
		{
			isVol = true;
			std::cout << "(T) Transportation: " << VolunteerFlow::currentVolunteer->getTransport() << "\n";
			Helper::line(110);
			std::cout << "(V) Available Time: " << VolunteerFlow::currentVolunteer->getAvailableTimes().first
				<< " - " << VolunteerFlow::currentVolunteer->getAvailableTimes().second << "\n";
			Helper::line(110);
		}
		else if (ShopOwnerFlow::currentSO != nullptr)
		{
			isSO = true;
			std::cout << "(S) Shop Name: " << ShopOwnerFlow::currentSO->getShopName() << "\n";
			Helper::line(110);
			std::cout << "(P) Shop Location: " << ShopOwnerFlow::currentSO->getShopPtr()->getLocation().getAddress() << "\n";
			Helper::line(110);
		}
		std::cout << "Your choice: ";
		int choice{};
		if (isCu)
			choice = Helper::readChoice(0, 0, "NndDAaLluUbBHh");
		else if (isVol)
			choice = Helper::readChoice(0, 0, "NndDAaLluUtbBTVv");
		else
			choice = Helper::readChoice(0, 0, "NndDAaLluUbBSsPp");


		//======

		if (choice == 'B' || choice == 'b') break;
		if (choice == 'N' || choice == 'n')
		{
			std::cout << "Enter the updated name or press C to cancel: ";
			std::string updatedName{};
			getline(std::cin, updatedName);
			if (updatedName == "C" || updatedName == "c") continue;
			currentUser->setName(updatedName);
			Helper::line(110);
			std::cout << "Your name has been updated\n";
			continue;
		}
		if (choice == 'd' || choice == 'D')
		{
			std::cout << "Enter the updated password or press C to cancel: ";
			std::string updatedPass{};
			getline(std::cin, updatedPass);
			if (updatedPass == "C" || updatedPass == "c") continue;
			currentUser->setPassword(updatedPass);
			Helper::line(110);
			std::cout << "Your password has been updated\n";
			continue;
		}
		if (choice == 'A' || choice == 'a')
		{
			std::cout << "Enter the updated age or press C to cancel: ";
			int updatedAge{};
			std::cin >> updatedAge;
			std::cin.ignore();
			if (updatedAge == 'c' || updatedAge =='C') continue;
			currentUser->setAge(updatedAge);
			Helper::line(110);
			std::cout << "Your age has been updated\n";
			continue;
		}
		if (choice == 'L' || choice == 'l')
		{
			std::cout << "Enter the updated address or press C to cancel: ";
			std::string updatedAddress{};
			getline(std::cin, updatedAddress);
			if (updatedAddress == "C" || updatedAddress == "c") continue;
			currentUser->setLocation(Location(updatedAddress));
			Helper::line(110);
			std::cout << "Your Location has been updated\n";
			continue;
		}
		if (choice == 'U' || choice == 'u')
		{
			std::cout << "Enter the amount to top up or press C to go back:\n";
			int choice = Helper::readChoice(0, 10000, "Cc");
			if (choice == 'C' || choice == 'c') continue;
			currentUser->setBalance(currentUser->balance + choice);
			Helper::line(110);
			std::cout << "Your balance has been updated\n";
			continue;
		}
		if (choice == 'H' || choice == 'h')
		{
			std::cout << "Enter updated health status (Healthy (H), Showing Symptoms (S) or Infected (I),\n"
				<< "or Press C to cancel: ";
			int choice = Helper::readChoice(0, 0, "HhSsIiCc");
			if (choice == 'c' || choice == 'C') continue;
			if (choice == 'H' || choice == 'h') {
				CustomerFlow::currentCustomer->setHealthStatus(Customer::HealthStatus::Healthy);
			}
			else if (choice == 'S' || choice == 's') {
				CustomerFlow::currentCustomer->setHealthStatus(Customer::HealthStatus::ShowSymptoms);
			}
			else if (choice == 'I' || choice == 'i') {
				CustomerFlow::currentCustomer->setHealthStatus(Customer::HealthStatus::Infected);
			}
			Helper::line(110);
			std::cout << "Your Health Status has been updated\n";
			continue;
		}
		if (choice == 'T' || choice == 't')
		{
			std::cout << "Enter updated transportation or press C to cancel ";
			std::string updatedTransport{};
			getline(std::cin, updatedTransport);
			if (updatedTransport == "C" || updatedTransport == "c") continue;
			VolunteerFlow::currentVolunteer->setTransport(updatedTransport);
			Helper::line(110);
			std::cout << "Your transportation has been updated\n";
			continue;
			
		}
		if (choice == 'V' || choice == 'v')
		{
			std::cout << "Update available hours or Press C to go back: \n"
				<< "Start hour: ";
			int startHour = Helper::readChoice(0,24, "cC");
			if (startHour == 'C' || startHour == 'c') continue;
			std::cout << "End hour: ";
			int endHour = Helper::readChoice(startHour, 24, "cC");
			if (endHour == 'C' || endHour == 'c') continue;

			VolunteerFlow::currentVolunteer->setAvailableTimes({ startHour,endHour });
			Helper::line(110);
			std::cout << "Your available hours have been updated\n";
			continue;
		}
		if (choice == 'S' || choice == 's')
		{


			std::cout << "Update the name of your Shop or press C to go back:\n";
			std::string shopName;
			getline(std::cin, shopName);
			if (shopName == "C" || shopName == "c") continue;
			ShopOwnerFlow::currentSO->setShopName(shopName);
			Helper::line(110);
			std::cout << "Your shop name has been updated\n";
			continue;
		}
		if (choice == 'P' || choice == 'p')
		{
			std::cout << "Update the address of your Shop or press C to go back:\n";
			std::string shopAdress;
			getline(std::cin, shopAdress);
			if (shopAdress == "C" || shopAdress == "c") continue;
			ShopOwnerFlow::currentSO->setShopAdress(shopAdress);
			Helper::line(110);
			std::cout << "Your shop address has been updated\n";
		}


	}
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
	int character;
	while (true) {
		
		std::cout << "\nSign up\n";
		Helper::dLine();
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

		Helper::line();
		std::cout << "I am a? \n";
		std::cout << "C: Customer \nS: Shop Owner \nV: Volunteer\n";
		character = Helper::readChoice(0, 0, "CcsSvV");

		Helper::line();
		std::cout << "We will need some additional info...\n";
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

		std::cout << "Just a few more questions...\n";
		currentUser->setInfo(name, age, balance, location);
		Helper::line();
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
		std::cout << "\nLogin\n";
		Helper::dLine();
		std::string userName, password;
		std::cout << "Username: ";
		std::cin >> userName;
		std::cout << "Password: ";
		std::cin >> password;
		std::cin.ignore();

		currentUser = verifyUsername(userName);
		if (currentUser == nullptr)
		{
			std::cout << "This user does not exist,\npress S to sign up, "
				<< "or press B to go back instead: ";

			char choice;
			std::cin >> choice;
			std::cin.ignore();

			if (choice == 's' || choice == 'S') signUp();
			if (choice == 'b' || choice == 'B') welcomeScreen();
			break;
		}

		if (currentUser->isAuth(userName, password))
			currentUser->welcome();
		else
		{
			std::cout << "Incorrect password, please try again...\n";
		}
	}
}


