#pragma once
#include <vector>
#include <string>
#include <fstream> 
#include "customer.h"

class C_List
{
	private:
		static std::ifstream fin;
		static std::ofstream fout;
		std::string filePath;
		
	public:
		static std::vector<std::shared_ptr<Customer>> ALL_CUSTOMERS;
	
	public:
		static int getCustomerCount() const;
		static void addCustomer(std::shared_pte<Customer> customer);
		static void removeCustomer(std::shared_pte<Customer> customer);
		static void readCustomers();
		static void writeCustomer();
};
