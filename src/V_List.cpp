#include"../include/V_List.h"
#include "../include/SH_List.h"
#include <sstream>

/// Members
std::vector<std::shared_ptr<Volunteer>> V_List::VOLUNTEERS;
std::fstream V_List::dataFile;
std::string V_List::filePath = "VolunteerList.txt";

/// Getters
int V_List::getVolunteersCount()
{
	return VOLUNTEERS.size();
}

void V_List::setFilePath(const char* fP)
{
	filePath = fP;
}

/// Methods
void V_List::addVolunteer(std::shared_ptr<Volunteer> Volunteer)
{
	VOLUNTEERS.push_back(Volunteer);
}


void V_List::readVolunteers()
{
	dataFile.open(filePath, std::ios::in);
	if (!dataFile)
		throw filePath.c_str();

	std::string username;
	std::string password;
	std::string name;
	int age = 0;
	int availableTime1{};
	int availableTime2{};
	int shopIdx{};
	double balance = 0.00;
	std::string address;
	std::string transport;
	std::string blank;
	std::string shopInfo;

	while (std::getline(dataFile, username))
	{
		std::getline(dataFile, password);
		std::getline(dataFile, name);
		dataFile >> age;
		dataFile >> balance;
		dataFile.ignore();
		std::getline(dataFile, address);
		std::getline(dataFile, transport);
		dataFile >> availableTime1;
		dataFile >> availableTime2;
		dataFile.ignore();
		std::shared_ptr<Volunteer> volunteer = std::make_shared<Volunteer>(username, password);
		std::getline(dataFile, shopInfo);
		std::istringstream s(shopInfo);
		while (s >> shopIdx)
		{
			volunteer->registerToShop(shopIdx);
			SH_List::SHOPS[shopIdx]->addVolunteer(volunteer);
		}
		volunteer->setName(name);
		volunteer->setAge(age);
		volunteer->setBalance(balance);
		volunteer->setLocation(Location(address));
		volunteer->setTransport(transport);
		volunteer->setAvailableTimes({availableTime1, availableTime2});
		addVolunteer(volunteer);
		std::getline(dataFile, blank);
	}

	dataFile.close();
}

void V_List::writeVolunteers()
{
	dataFile.open(filePath, std::ios::out);
	if (!dataFile)
		throw filePath.c_str();
	
	for (int i = 0; i < getVolunteersCount(); i++)
	{
		dataFile << VOLUNTEERS[i]->getUsername() << std::endl;
		dataFile << VOLUNTEERS[i]->password << std::endl;
		dataFile << VOLUNTEERS[i]->getName() << std::endl;
		dataFile << VOLUNTEERS[i]->getAge() << std::endl;
		dataFile << VOLUNTEERS[i]->getBalance() << std::endl;
		Location address = VOLUNTEERS[i]->getLocation();
		dataFile << address.getAddress() << std::endl;
		dataFile << VOLUNTEERS[i]->getTransport() << std::endl;
		dataFile << VOLUNTEERS[i]->getAvailableTimes().first.getHour()
			<< " " << VOLUNTEERS[i]->getAvailableTimes().second.getHour() << std::endl;
		bool hasRegistered = false;
		VOLUNTEERS[i]->registeredShops.resize(SH_List::SHOPS.size(), false);
		for (int j = 0; j < SH_List::SHOPS.size(); j++)
		{
			if (VOLUNTEERS[i]->registeredShops[j])
			{
				dataFile << j << " ";
				hasRegistered = true;
			}
		}
		if (hasRegistered) dataFile << std::endl;
		if (i != getVolunteersCount() - 1) dataFile << std::endl;
		if (i == getVolunteersCount() - 1 && !hasRegistered) dataFile << std::endl;
	}
	dataFile.close();
}
