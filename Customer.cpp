#include "Customer.h"

#include <memory>

#include "CustomerFlow.h"
#include "Shop.h"
#include "Helper.h"

/// Constructors
Customer::Customer(std::string username, std::string password) :User(username, password)
{
	cart = std::make_shared<Order>();
}

/// Getters
Customer::HealthStatus Customer::getHealthStatus() const
{
	return healthStatus;
}

/// Setters
void Customer::setHealthStatus(HealthStatus healthStatus)
{
	this->healthStatus = healthStatus;
}


/// Methods
void Customer::setInfo(std::string name, int age, double balance, Location location)
{
	this->name = name;
	this->age = age;
	this->balance = balance;
	this->location = location;
	std::cout << "Enter your health status (Healthy (H), Showing Symptoms (S) or Infected (I)\nYour choice: ";
	int health = Helper::readChoice(0, 0, "HhSsIi");
	if (health == 'H' || health == 'h') {
		setHealthStatus(HealthStatus::Healthy);
	}
	else if (health == 'S' || health == 's') {
		setHealthStatus(HealthStatus::ShowSymptoms);
	}
	else if (health == 'I' || health == 'i') {
		setHealthStatus(HealthStatus::Infected);
	}
}
void Customer::placeOrder()
{
	cart->buyItems();
	orders.push_back(cart);
	balance -= cart->getTotalPrice();
	cart = std::make_shared<Order>();

}

void Customer::addToCart(std::shared_ptr<Item> item, int quantity)
{
	this->cart->addItem(item, quantity);
}

void Customer::addToCart(int itemIdx, int quantity)
{
	this->cart->addItem(itemIdx, quantity);
}

void Customer::removeFromCart(std::pair<std::shared_ptr<Item>, int>& itemReq)
{
	this->cart->removeItem(itemReq);
}

void Customer::welcome()
{
	CustomerFlow::currentCustomer = shared_from_this();
	system("CLS");
	CustomerFlow::mainMenu();
}

/// Operators
std::ostream& operator<<(std::ostream& output, const Customer::HealthStatus& healthStatus)
{
	const char* c = "0";
	switch (healthStatus)
	{
	case Customer::Healthy: c = "Healthy";
		break;
	case Customer::ShowSymptoms: c = "Show Symptoms";
		break;
	case Customer::Infected:  c = "Infected";
		break;
	}
	output << c;
	return output;
}