#include "UserFlow.h"

int main ()
{

	C_List::readCustomers();
	V_List::ReadVolunteers();
	UserFlow::welcomeScreen();
	
	std::cin.get();

}
