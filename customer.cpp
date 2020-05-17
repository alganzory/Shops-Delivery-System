#include "customer.h"

Customer::Customer(std::string username, std::string password):User(username,password)
{
	
}
void Customer::setHealthStatus(std::string healthStatus)
{
	this->healthStatus=healthStatus;
}
std::string Customer::getHealthStatus() const
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
	getline (cin, this->healthStatus);
}
void Customer::placeOrder()
{
	orders.push_back(cart);
	balance -= cart->getTotalPrice;
	cart = std::make_shared<Order>();
}
void Customer::rewardVolunteer (Volunteer *volunteer,double reward)
{
	//exception check to see if there is enough balance
	volunteer->getReward(reward);
	balance -= reward;
}

void Customer::addToCart(std::shared_ptr<Item> item, int quantity)
{
	this->cart->addItem(item, quantity);
}

void Customer::removeFromCart(std::pair<std::shared_ptr<Item>, int> itemReq)
{
	this->cart->removeItem(itemReq);
}
