#pragma once
#include "ShopOwner.h"

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
	static void viewOrder(std::shared_ptr <Order> order);
	
};

