#include "C_List.h"

std::fstream C_List::dataFile;
std::string C_List::filePath="CustomerList.txt";
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
	dataFile.open(filePath,std::ios::in); 
	
	std::string username;
	std::string password;
	std::string name;
	int age;
	double balance;
	std::string address;
	std::string healthStatus;

	do
	{
		std::getline(dataFile, username);
		std::getline(dataFile, password);
		std::getline(dataFile, name);
		dataFile >> age;
		dataFile >> balance;
		std::getline(dataFile, address);
		std::getline(dataFile, healthStatus);
		std::shared_ptr<Customer> customer(new Customer(username, password));
		Location location(address);
		customer->setInfo(name, age, balance, location);
		addCustomer(customer);
	} while (username != "\0");

	dataFile.close();
}

void C_List::writeCustomer()
{
	dataFile.open(filePath,std::ios::out);
	for (int i = 0; i < ALL_CUSTOMERS.size; i++)
	{
		dataFile << ALL_CUSTOMERS[i]->getUsername << std::endl;
		//dataFile << ALL_CUSTOMERS[i]->password << std::endl;
		dataFile << ALL_CUSTOMERS[i]->getName << std::endl;
		dataFile << ALL_CUSTOMERS[i]->getAge << std::endl;
		dataFile << ALL_CUSTOMERS[i]->getBalance << std::endl;
		Location address = ALL_CUSTOMERS[i]->getLocation;
		dataFile << address.getAddress << std::endl;
		dataFile << ALL_CUSTOMERS[i]->getHealthStatus << std::endl << std::endl;
	}
	dataFile.close();
}
