#pragma once
#include <vector>
#include <string>
#include <fstream> 

class C_List
{
	Public:
		std::vector <shared_ptr<Customer>> ALL_CUSTOMERS;
	
	Public:
		static int getCustomerCount() const;
		static void addCustomer(Customer *customer);
		static void removeCustomer(Customer *customer);
		static void readCustomers();
		static void writeCustomer();
};
