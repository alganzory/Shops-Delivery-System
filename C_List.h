#pragma once
#include <vector>
#include <string>
#include <fstream> 
#include "customer.h"

class C_List
{
	private:
		static std::fstream dataFile;
		std::string filePath;
		
	public:
		static std::vector<std::shared_ptr<Customer>> ALL_CUSTOMERS;
	
	public:
		static int getCustomerCount() const;
		static void addCustomer(std::shared_ptr<Customer> customer);
		static void removeCustomer(std::shared_ptr<Customer> customer);
		static void readCustomers();
		static void writeCustomer();
};
