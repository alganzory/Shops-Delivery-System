#include "customer.h"

Customer::Customer(std::string username, std::string password):User(username,password)
{
	
}
void Customer::setHealthStatus(std::string healthStatus)
{
	this->healthStatus=healthStatus;
}
std::string Customer::getHealthStatus()
{
	return healthStatus;
}
void Customer::setInfo(std::string name, int age, double balance, Location location)
{
	this->name=name;
	this->age=age;
	this->balance=balance;
	this->location=location;
	cout<<"Enter the health status: ";
	cin>>healthStatus;
}
void Customer::placeOrder()
{
	orders.push_back(cart);
	balance -= cart.getTotalPrice;
	cart.make_shared();
}
void Customer::rewardVolunteer (Volunteer *volunteer,double reward)
{
	volunteer->getReward(reward);
	balance -= reward;
}
