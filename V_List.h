#pragma once
#include"Volunteer.h"
#include <fstream>
#include <memory>
#include<vector>
#include<string>

class V_List
{
public:
	/// Members
	static std::vector<std::shared_ptr<Volunteer>> ALL_VOLUNTEERS;
	static std::fstream vFile;
	static std::string filePath;

	/// Getters
	static int getVolunteersCount();

	/// Methods
	static void AddVolunteer(std::shared_ptr<Volunteer> Volunteer);
	//useless
	static void RemoveVolunteer(std::shared_ptr<Volunteer> Volunteer);
	static void ReadVolunteers();
	static void WriteVolunteers();
};
