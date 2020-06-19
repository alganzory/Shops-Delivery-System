#pragma once
#include <vector>
#include <string>
#include <fstream>
#include <memory>
#include "Customer.h"


class C_List
{
	private:
		static std::fstream dataFile;
		static std::string filePath;
		
	public:
		static std::vector<std::shared_ptr<Customer>> ALL_CUSTOMERS;
	
	public:
		static int getCustomerCount();
		static void addCustomer(std::shared_ptr<Customer> customer);
		static void removeCustomer(std::shared_ptr<Customer> customer);
		static void readCustomers();
		static void writeCustomer();
		friend std::istream& operator >>(std::istream& input, const Customer::HealthStatus& health);
};
