#pragma once
#include "ShopOwner.h"
#include <algorithm>

class ShopOwnerFlow
{
public:
	static std::shared_ptr <ShopOwner> currentSO;
public:
	static void editItem(const std::shared_ptr<Item> item);
	static void addNewItem();
	static void myShop();
	static void mainMenu();
	static void allOrders(bool pendingOnly = false);
	static void assignVolunteer(const std::shared_ptr<Order>& order);
	static void viewOrder(const std::shared_ptr<Order>& order);
	static void todoList(std::shared_ptr<Order>order);
	static std::vector<std::shared_ptr<Volunteer>> findAvailableVolunteers(double time);
};

