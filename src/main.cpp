#include "../include/UserFlow.h"
#include "../include/SH_List.h"
#include "../include/O_List.h"
#include "../include/Time.h"
#include <Windows.h> 
#include "../include/Helper.h"


void readFromFiles()
{
	bool allRead = false;
	while (!allRead){
		try {
			SO_List::setFilePath("../data/ShopOwnersList.txt");
			SO_List::readShopOwners();
			SH_List::readShops();
			C_List::setFilePath("../data/CustomersList.txt");
			C_List::readCustomers();
			V_List::setFilePath("../data/VolunteersList.txt");
			V_List::readVolunteers();
			O_List::setFilePath("../data/OrdersList.txt");
			O_List::readOrders();
			allRead = true;
		
		}
		catch (const char* filePath)
		{
			std::cout << ">ERROR: " << "FILE " << filePath << " COULD NOT BE OPENED.\n";
			std::cout << "Please verify it exists and press a key to try again\n";
			std::cin.get();
		}
	}
}
void writeToFiles()
{
	bool allwritten = false;
	
	while (!allwritten) {
		try {
			C_List::writeCustomers();
			V_List::writeVolunteers();
			SO_List::writeShopOwners();
			O_List::writeOrders();
			allwritten = true;
		}
		catch (const char* filePath)
		{
			std::cout << ">ERROR: " << "FILE " << filePath << " COULD NOT BE OPENED.\n";
			std::cout << "Please verify it exists and press a key to try again\n";
			std::cin.get();
		}
	}
	
}

// To catch closing of console event on windows
// to write files
BOOL WINAPI CtrlHandler(DWORD fdwCtrlType)
{
	switch (fdwCtrlType)
	{
	case CTRL_CLOSE_EVENT:
		writeToFiles();
		Beep(1000, 500);
		Beep(750, 500);
		Beep(450, 500);
		return TRUE;

	default:
		return FALSE;
	}
}



int main()
{
	readFromFiles();
	
	SetConsoleCtrlHandler(CtrlHandler, TRUE);

	try
	{
		std::cout << std::left;
		Time::calcLocalTime();
		UserFlow::welcomeScreen();
	}
	catch (const char* exit)
	{
		Helper::stringDisplay(exit);
	}

	writeToFiles();

	return 0;
}
