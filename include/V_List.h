#pragma once
#include"Volunteer.h"
#include <fstream>
#include <memory>
#include<vector>
#include<string>

class V_List
{
private:
	static std::fstream dataFile;
	static std::string filePath;

public:
	/// Members
	/**
	 * \brief : list of volunteers registered
	 */
	static std::vector<std::shared_ptr<Volunteer>> VOLUNTEERS;


	/// Getters
	static int getVolunteersCount();

	/// Setters
	static void setFilePath(const char* fP);

	/// Methods
	static void addVolunteer(std::shared_ptr<Volunteer> Volunteer);

	static void readVolunteers();
	static void writeVolunteers();
};
