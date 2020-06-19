#pragma once
#include "Volunteer.h"
#include "UserFlow.h"
#include <algorithm>


class VolunteerFlow
{
public:
	static std::shared_ptr<Volunteer> currentVolunteer;
	static std::shared_ptr<Order> currentOrder;
public:
	static void ongoingOrder();
	static void myOrders(bool pendingOnly = false);
	static void mainMenu();
	static void viewOrder(const std::shared_ptr<Order>& order);
	//friend class Customer;
};


