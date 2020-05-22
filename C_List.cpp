#include "C_List.h"

std::fstream C_List::dataFile;
std::string C_List::filePath="file.txt";

static int C_List::getCustomerCount() const
{
	return ALL_CUSTOMERS.size();
}

static void C_List::addCustomer(std::shared_ptr<Customer> customer)
{
	ALL_CUSTOMERS.push_back(customer);
}

static void C_List::removeCustomer(std::shared_ptr<Customer> customer)
{
	auto foundCustomer=std::find(ALL_CUSTOMERS.begin(),ALL_CUSTOMERS.end(),customer);
	ALL_CUSTOMERS.erase(foundCustomer);

}

static void C_List::readCustomers()
{
	dataFile.open(filepath); 
	//input
	dataFile.close();
}

static void C_List::writeCustomer()
{
	dataFile.open(filepath);
	//output
	dataFile.close();
}
