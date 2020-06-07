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
	
};

