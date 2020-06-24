
#include "UserFlow.h"
#include "SH_List.h"
#include "O_List.h"
#include "Time.h"
#include <stdio.h>
#include <time.h>
#include <chrono>

int main()
{
	std::cout <<std::left;
	Time::calcLocalTime();
	SO_List::filePath = "shlist.txt";
	SO_List::readFromFile();
	
	SH_List::setList();
	C_List::readCustomers();
	V_List::ReadVolunteers();
	O_List::filePath = "olist.txt";
	O_List::readFromFile();

	UserFlow::welcomeScreen();
}
