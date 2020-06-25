#include "UserFlow.h"
#include "SH_List.h"
#include "O_List.h"
#include "Time.h"

int main()
{
	std::cout << std::left;
	Time::calcLocalTime();
	SO_List::filePath = "shlist.txt";
	SO_List::readFromFile();

	SH_List::setList();
	C_List::readCustomers();
	V_List::ReadVolunteers();
	O_List::filePath = "olist.txt";
	O_List::readFromFile();
	try
	{
		UserFlow::welcomeScreen();
	}
	catch (const char* e)
	{
		std::cout << "***Thanks for using our program***\n";
	}

	C_List::writeCustomer();
	V_List::WriteVolunteers();
	SO_List::writeToFile();
	O_List::writeToFile();
}
