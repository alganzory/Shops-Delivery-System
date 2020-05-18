#include "C_List.h"

static int C_List::getCustomerCount() const
{
	return ALL_CUSTOMERS.size();
}

static void C_List::addCustomer(Customer *customer)
{
	ALL_CUSTOMERS.push_back(customer);
}

static void C_List::removeCustomer(Customer *customer)
{
	for (int i=0;i<getCustomerCount();i++)
	{
		if(ALL_CUSTOMERS[i]->getUsername==customer->getUsername&&ALL_CUSTOMERS[i]->getPassword==customer->getPassword)
		{
			ALL_CUSTOMERS.erase(ALL_CUSTOMERS.begin()+i);
			break;
		}
	}
}

static void C_List::readCustomers()
{
	ifstream fin;
	fin.open("customerList.txt"); 
	//input
	fin.close();
}

static void C_List::writeCustomer()
{
	ofstream fout;
	fout.open("customerList.txt");
	//output
	fout.close();
}
