#include "User.h"

User::User()
{
}

User::User(std::string username, std::string password):
	username(username), password(password)
{
}

std::string User::getUsername() const
{
	return username;
}

void User::setUsername(const std::string username)
{
	this->username = username;
}

std::string User::getName() const
{
	return name;
}

void User::setName(const std::string name)
{
	this->name = name;
}

int User::getAge() const
{
	return age;
}

void User::setAge(const int age)
{
	this->age = age;
}

double User::getBalance() const
{
	return balance;
}

void User::setBalance(const double balance)
{
	this->balance = balance;
}

Location User::getLocation() const
{
	return location;
}

void User::setLocation(const Location location)
{
	this->location = location;
}

void User::addOrder(std::shared_ptr<Order> newOrder)
{
	orders.push_back(newOrder);
}

void User::removeOrder(std::shared_ptr<Order> order)
{
	orders.erase(find(orders.begin(), orders.end(), order));

}

bool User::isAuth(std::string username, std::string password) const
{
	return this->username == username && this->password == password;
}


User::~User()
{

}

bool operator==(const User& lhs, const User& rhs)
{
	return lhs.username == rhs.username;
}
