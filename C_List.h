#pragma once
#include <vector>
#include <string>
#include <fstream>
#include <memory>
#include "Customer.h"


class C_List
{	
	/// Members
	private:
		static std::fstream dataFile;
		static std::string filePath;

	public:
	/// Getters
		static std::vector<std::shared_ptr<Customer>> ALL_CUSTOMERS;
		static int getCustomerCount();

	/// Methods
		static void addCustomer(std::shared_ptr<Customer> customer);
		//useless
		static void removeCustomer(std::shared_ptr<Customer> customer);//useless
		static void readCustomers();
		static void writeCustomer();


	//	friend std::istream& operator >>(std::istream& input, const Customer::HealthStatus& health);
};
