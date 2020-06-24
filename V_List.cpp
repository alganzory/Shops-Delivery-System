#include"V_List.h"
#include "SH_List.h"
#include <sstream>
std::vector<std::shared_ptr<Volunteer>> V_List::ALL_VOLUNTEERS;
std::fstream V_List::vFile;
std::string V_List::filePath = "VolunteerList.txt";

int V_List::getVolunteersCount() {
	return ALL_VOLUNTEERS.size();
}

void V_List::AddVolunteer(std::shared_ptr<Volunteer> Volunteer) {
	ALL_VOLUNTEERS.push_back(Volunteer);
}

void V_List::RemoveVolunteer(std::shared_ptr<Volunteer> Volunteer) {
	ALL_VOLUNTEERS.erase(std::find(ALL_VOLUNTEERS.begin(), ALL_VOLUNTEERS.end(), Volunteer));
}

void V_List::ReadVolunteers() {

	vFile.open(filePath, std::ios::in);
	if (!vFile)
	{
		std::cout << "fail" << std::endl;
	}

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

	while (std::getline (vFile, username))
	{
		
		std::getline(vFile, password);
		std::getline(vFile, name);
		vFile >> age;
		vFile >> balance;
		vFile.ignore();
		std::getline(vFile, address);
		std::getline(vFile, transport);
		vFile >> availableTime1;
		vFile >> availableTime2;
		vFile.ignore();
		std::shared_ptr<Volunteer> volunteer = std::make_shared <Volunteer>(username, password);
		std::getline(vFile, shopInfo);
		std::istringstream s(shopInfo);
		while (s>>shopIdx)
		{
			volunteer->registerToShop (shopIdx);
			SH_List::SHOPS[shopIdx]->addVolunteer(volunteer);
		}
		volunteer->setName(name);
		volunteer->setAge(age);
		volunteer->setBalance(balance);
		volunteer->setLocation(Location(address));
		volunteer->setTransport(transport);
		volunteer->setAvailableTimes({ availableTime1,availableTime2 });
		AddVolunteer(volunteer);
		std::getline(vFile, blank);
	} 

	vFile.close();
}

void V_List::WriteVolunteers() {
	//std::fstream Vfile;
	vFile.open("VolunteerList.txt",std::ios::out);
	//to write volunteers into file
	for (int i = 0; i < getVolunteersCount(); i++) {
		vFile << ALL_VOLUNTEERS[i]->getUsername() << std::endl;
		vFile << ALL_VOLUNTEERS[i]->password << std::endl;
		vFile << ALL_VOLUNTEERS[i]->getName() << std::endl;
		vFile << ALL_VOLUNTEERS[i]->getAge() << std::endl;
		vFile << ALL_VOLUNTEERS[i]->getBalance() << std::endl;
		Location address = ALL_VOLUNTEERS[i]->getLocation();
		vFile << address.getAddress() << std::endl;
		vFile << ALL_VOLUNTEERS[i]->getTransport() << std::endl;
		vFile << ALL_VOLUNTEERS[i]->getAvailableTimes().first.getHour()
			<< " " << ALL_VOLUNTEERS[i]->getAvailableTimes().second.getHour() << std::endl;
		bool hasRegistered = false;
		ALL_VOLUNTEERS[i]->registeredShops.resize(SH_List::SHOPS.size(),false);
		for (int j = 0; j < SH_List::SHOPS.size(); j++){
		
			if (ALL_VOLUNTEERS[i]->registeredShops[j]) {
				vFile << j << " ";
				hasRegistered = true;
			}
			
		}
		if (hasRegistered) vFile << std::endl;
		if (i!= getVolunteersCount()-1) vFile << std::endl;
		if (i == getVolunteersCount() - 1 && !hasRegistered) vFile << std::endl;
	}
	vFile.close();
}