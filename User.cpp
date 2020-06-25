#include "User.h"


/// Constructors
User::User()
{
}

User::User(std::string username, std::string password):
	username(username), password(password)
{
}

/// Getters
std::string User::getUsername() const
{
	return username;
}
std::string User::getName() const
{
	return name;
}

int User::getAge() const
{
	return age;
}

double User::getBalance() const
{
	return balance;
}


Location User::getLocation() const
{
	return location;
}

bool User::isAuth(std::string username, std::string password) const
{
	return this->username == username && this->password == password;
}


/// Setters
void User::setUsername(const std::string username)
{
	this->username = username;
}

void User::setName(const std::string name)
{
	this->name = name;
}

void User::setAge(const int age)
{
	this->age = age;
}
void User::setBalance(const double balance)
{
	this->balance = balance;
}
void User::setLocation(const Location location)
{
	this->location = location;
}
void User::setPassword(const std::string& cs)
{
	password = cs;
}

/// Methods
void User::addOrder(std::shared_ptr<Order> newOrder)
{
	orders.push_back(newOrder);
}

void User::removeOrder(std::shared_ptr <Order> order)
{
	orders.erase(find(orders.begin(), orders.end(), order));

}

void User::addBalance(double amount)
{
	balance += amount;
}

void User::subtractBalance(double amount)
{
	balance -= amount;
}


/// Operators
bool operator==(const User& lhs, const User& rhs)
{
	return lhs.username == rhs.username;
}

bool operator==(const std::shared_ptr<User>& lhs, const std::string &username)
{
	return lhs->username == username;
}

/// Destructor
User::~User()
{

}
