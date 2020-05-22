#include "C_List.h"

std::fstream C_List::dataFile;
std::string C_List::filePath="file.txt";
std::vector<std::shared_ptr<Customer>> C_List::ALL_CUSTOMERS;
int C_List::getCustomerCount()
{
	return ALL_CUSTOMERS.size();
}

void C_List::addCustomer(std::shared_ptr<Customer> customer)
{
	ALL_CUSTOMERS.push_back(customer);
}

void C_List::removeCustomer(std::shared_ptr<Customer> customer)
{
	auto foundCustomer=std::find(ALL_CUSTOMERS.begin(),ALL_CUSTOMERS.end(),customer);
	ALL_CUSTOMERS.erase(foundCustomer);

}

void C_List::readCustomers()
{
	dataFile.open(filePath); 
	//input
	dataFile.close();
}

void C_List::writeCustomer()
{
	dataFile.open(filePath);
	//output
	dataFile.close();
}
