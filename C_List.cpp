#include "C_List.h"

/// Members
std::fstream C_List::dataFile;
std::string C_List::filePath="CustomerList.txt";
std::vector<std::shared_ptr<Customer>> C_List::ALL_CUSTOMERS;

/// Getters
int C_List::getCustomerCount()
{
	return ALL_CUSTOMERS.size();
}

/// Methods
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
	if (!dataFile)
	{
		std::cout << "fail" << std::endl;
	}
	
	std::string username;
	std::string password;
	std::string name;
	int age=0;
	double balance=0.00;
	std::string address;
	std::string health;
	std::string blank;

	while (std::getline(dataFile, username))
	{
		std::getline(dataFile, password);
		std::getline(dataFile, name);
		dataFile >> age;
		dataFile >> balance;
		dataFile.ignore();
		std::getline(dataFile, address);
		std::getline(dataFile, health);
		std::shared_ptr<Customer> customer(std::make_shared <Customer>(username, password));
		customer->setName(name);
		customer->setAge(age);
		customer->setBalance(balance);
		customer->setLocation(Location(address));
		//check equals to what
		if (health == "H" || health == "h") {
			customer->setHealthStatus(Customer::Healthy);
		}
		else if (health == "S" || health == "s") {
			customer->setHealthStatus(Customer::ShowSymptoms);
		}
		else if (health == "I" || health == "i") {
			customer->setHealthStatus(Customer::Infected);
		}
		addCustomer(customer);
		std::getline(dataFile, blank);
	}
	dataFile.close();
}

void C_List::writeCustomer()
{
	dataFile.open(filePath,std::ios::out);
	for (int i = 0; i < getCustomerCount(); i++)
	{
		dataFile << ALL_CUSTOMERS[i]->username << std::endl;
		dataFile << ALL_CUSTOMERS[i]->password << std::endl;
		dataFile << ALL_CUSTOMERS[i]->name << std::endl;
		dataFile << ALL_CUSTOMERS[i]->age << std::endl;
		dataFile << ALL_CUSTOMERS[i]->balance << std::endl;
		Location address = ALL_CUSTOMERS[i]->getLocation();
		dataFile << address.getAddress() << std::endl;
		if (ALL_CUSTOMERS[i]->healthStatus == Customer::Healthy) {
			dataFile << "H" << std::endl;
		}
		else if (ALL_CUSTOMERS[i]->healthStatus == Customer::Infected) {
			dataFile << "I" << std::endl;
		}
		else if (ALL_CUSTOMERS[i]->healthStatus == Customer::ShowSymptoms) {
			dataFile << "S" << std::endl;
		}
		if (i != getCustomerCount() - 1)	dataFile << std::endl;
	}
	dataFile.close();
}

/*std::istream& operator >>(std::istream& input, const Customer::HealthStatus& health) {
	//const char* i = "0";
	switch (health)
	{
	case Customer::Healthy: input >> health;
		break;
	case Customer::ShowSymptoms: input >> health;
		break;
	case Customer::Infected:  input >> health;
		break;
	}
	return input;
}*/
