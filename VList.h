#pragma once
#include"volunteer.h"
#include<iostream>
#include<vector>
class V_List {
	public:
		static std::vector<std::shared_ptr<Volunteer>> ALL_VOLUNTEERS;
		static std::fstream vFile;
		static int getVolunteersCount();
		static void AddVolunteer(std::shared_ptr<Volunteer> Volunteer);
		static void RemoveVolunteer(std::shared_ptr<Volunteer> Volunteer);
		static void ReadVolunteers();
		static void WriteVolunteers();
};