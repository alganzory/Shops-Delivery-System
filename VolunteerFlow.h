#pragma once
#include "Volunteer.h"
#include "UserFlow.h"

class VolunteerFlow
{
public:
	static std::shared_ptr<Volunteer> currentVolunteer;
public:
	static void mainMenu();
	
};

