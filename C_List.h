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
	/**
	 * \brief : list of customers registered in the system
	 */
	static std::vector<std::shared_ptr<Customer>> CUSTOMERS;
	static int getCustomerCount();


	/// Setters
	static void setFilePath(const char* fP);

	/// Methods
	static void addCustomer(std::shared_ptr<Customer> customer);
	/**
	 * \brief
	 * \param customer : the customer account to be removed.
	 * This function is not being used at the moment because the system
	 * does not allow for account removal
	 */
	static void removeCustomer(std::shared_ptr<Customer> customer);
	static void readCustomers();
	static void writeCustomer();


	//	friend std::istream& operator >>(std::istream& input, const Customer::HealthStatus& health);
};
