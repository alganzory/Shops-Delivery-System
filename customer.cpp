#include "customer.h"

Customer::Customer(string _username, string _password):User(_username,_password)
{
	
}
void Customer::setHealthStatus(string hs)
{
	healthStatus=hs;
}
string Customer::getHealthStatus()
{
	return healthStatus;
}
void Customer::setInfo(string _name, int _age, double _balance, Location _location)
{
	name=_name;
	age=_age;
	balance=_balance;
	location=_location;
	cout<<"Enter the health status: ";
	cin>>healthStatus;
}
void Customer::placeOrder()
{
	orders.push_back(cart);
	cart.reset();
}
void Customer::rewardVolunteer (Volunteer *volunteer,double reward)
{
	volunteer->getReward(reward);
}
