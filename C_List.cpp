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
	int i=std::find(ALL_CUSTOMERS.begin(),ALL_CUSTOMERS.end(),customer);
	if(i!=ALL_CUSTOMERS.end())
	{
		ALL_CUSTOMERS.erase(ALL_CUSTOMERS.begin()+i);
	}
	else
	{
		std::cout<<"Customer Not Found"<<endl;
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
