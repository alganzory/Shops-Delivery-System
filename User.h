#pragma once
#include <iostream>
#include <memory>
#include <string>
#include <vector>
#include <algorithm>
#include "Location.h"
#include "Order.h"
#include "Time.h"

class User
{
	/// Members
protected:
	std::string username;
	std::string password;
	std::string name;
	int age{};
	double balance{};
	Location location;
	std::vector<std::shared_ptr<Order>> orders;

public:

	/// Constructors
	User();
	User(std::string username, std::string password);
	User(const User& other) = delete;

	/// Getters
	std::string getUsername() const;
	std::string getName() const;
	int getAge() const;
	double getBalance() const;
	Location getLocation() const;
	bool isAuth(std::string username, std::string password) const;

	/// Setters
	void setPassword(const std::string& cs);
	//useless
	void setUsername(const std::string username);
	void setName(const std::string name);
	void setAge(const int age);
	void setBalance(const double balance);
	void setLocation(const Location location);


	/// Methods
	void addOrder(std::shared_ptr<Order> newOrder);
	void removeOrder(std::shared_ptr<Order> order);
	void addBalance(double amount);
	void subtractBalance(double amount);
	virtual void welcome() = 0;
	virtual void setInfo(std::string name, int age, double balance, Location location) = 0;

	/// Operators
	friend bool operator==(const User& lhs, const User& rhs);
	friend bool operator==(const std::shared_ptr<User>& lhs, const std::string& username);

	/// Destructor
	virtual ~User();

	/// Friend Functions

	/// Friend Classes
	friend class UserFlow;
};
