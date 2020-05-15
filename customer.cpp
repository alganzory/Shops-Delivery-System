#include "customer.h"

Customer::Customer(string _username, string _password):User(_username,_password)
{
	cout<<"Enter the health status: ";
	cin>>healthStatus;
}
void Customer::setHS(string hs)
{
	healthStatus=hs;
}
string Customer::getHS()
{
	return healthStatus;
}
void Customer::setInfo(string _name, int _age, double _balance, Location _location)
{
	name=_name;
	age=_age;
	balance=_balance;
	location=_location;
}
void Customer::placeOrder(Order *_order)
{
	addOrder(_order);
}
void Customer::rewardVolunteer (Volunteer *volunteer,string reward)
{
	volunteer->getReward(reward);
}
