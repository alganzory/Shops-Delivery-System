#include"VList.h"
#include<iostream>
#include<fstream>

std::vector<std::shared_ptr<Volunteer>> V_List::ALL_VOLUNTEERS;
std::fstream V_List::vFile;
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
	//std::fstream vFile;
	vFile.open("VolunteerList.txt");
	if (vFile.is_open()) {
		vFile.close();
	}
	else {
		std::cout << "File not opened.";
	}
	
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