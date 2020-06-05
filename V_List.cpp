#include"V_List.h"

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
	double balance = 0.00;
	std::string address;
	std::string transport;
	std::string blank;
	

	do
	{
		username = "\0";
		std::getline(vFile, username);
		if (username == "\0")
		{
			break;
		}
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
		volunteer->setName(name);
		volunteer->setAge(age);
		volunteer->setBalance(balance);
		volunteer->setLocation(Location(address));
		volunteer->setTransport(transport);
		volunteer->setAvailableTimes({ availableTime1,availableTime2 });
		AddVolunteer(volunteer);
		std::getline(vFile, blank);
	} while (username != "\0");

	vFile.close();
}

void V_List::WriteVolunteers() {
	//std::fstream Vfile;
	vFile.open("VolunteerList.txt");
	//to write volunteers into file
	for (int i = 0; i < getVolunteersCount(); i++) {
		vFile << ALL_VOLUNTEERS[i];
	}
	vFile.close();
}