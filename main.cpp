
#include "UserFlow.h"
#include "SH_List.h"
#include <ctime>
#include <chrono>

#include "O_List.h"

int main()
{
	std::cout << std::left;
	SO_List::filePath = "shlist.txt";
	SO_List::readFromFile();
	
	SH_List::setList();
	C_List::readCustomers();
	V_List::ReadVolunteers();
	O_List::filePath = "olist.txt";
	O_List::readFromFile();

	UserFlow::welcomeScreen();
}
