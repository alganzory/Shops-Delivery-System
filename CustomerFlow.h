#pragma once
#include "Customer.h"
#include "UserFlow.h"

class CustomerFlow
{
	/// Members
public:
	static std::shared_ptr<Customer> currentCustomer;
	static std::shared_ptr<Shop> currentShop;

	/// Methods
public:
	static void mainMenu();
	static void findAvailableShops();
	static void displayShops();
	static void viewShop();
	static void makeAnOrder();
	static void checkout();
	static void myCart();
	static void myOrders(bool ongoingOnly = false);
	static void viewOrder(const std::shared_ptr <Order>& order);

};

