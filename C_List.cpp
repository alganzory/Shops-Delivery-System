#include "C_List.h"

std::ifstream C_List::fin;
std::ofstream C_List::fout;
std::string C_List::filePath="file.txt";

static int C_List::getCustomerCount() const
{
	return ALL_CUSTOMERS.size();
}

static void C_List::addCustomer(std::shared_pte<Customer> customer)
{
	ALL_CUSTOMERS.push_back(customer);
}

static void C_List::removeCustomer(std::shared_pte<Customer> customer)
{
	auto foundCustomer=std::find(ALL_CUSTOMERS.begin(),ALL_CUSTOMERS.end(),customer);
	ALL_CUSTOMERS.erase(i);

}

static void C_List::readCustomers()
{
	fin.open(filepath); 
	//input
	fin.close();
}

static void C_List::writeCustomer()
{
	fout.open(filepath);
	//output
	fout.close();
}
