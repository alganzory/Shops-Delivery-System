
#include "UserFlow.h"
#include "SH_List.h"
#include "Time.h"

int main()
{
	Time::calcLocalTime();
	SO_List::filePath = "shlist.txt";
	SO_List::readFromFile();
	SH_List::setList();
	C_List::readCustomers();
	V_List::ReadVolunteers();
	UserFlow::welcomeScreen();
}