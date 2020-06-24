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
protected:
	std::string username;
	std::string password;
	std::string name;
	int age{};
	double balance{};
	Location location;
	std::vector <std::shared_ptr<Order> > orders;

public:

	User();
	User(std::string username, std::string password);
	User(const User& other) = delete;

	std::string getUsername() const;
	//useless
	void setUsername(const std::string username);
	std::string getName() const;
	void setName(const std::string name);
	int getAge() const;
	void setAge(const int age);
	double getBalance() const;
	void setBalance(const double balance);
	Location getLocation() const;
	void setLocation(const Location location);
	virtual void setInfo(std::string name, int age, double balance, Location location) = 0;
	friend bool operator==(const User& lhs, const User& rhs);
	friend bool operator==(const std::shared_ptr<User> & lhs, const std::string& username);
	void addOrder(std::shared_ptr<Order> newOrder);

	void removeOrder(std::shared_ptr <Order> order);

	bool isAuth(std::string username, std::string password) const;
	
	void addBalance(double amount);
	void subtractBalance (double amount);
	virtual ~User();
	virtual void welcome() = 0;
	void setPassword(const std::string& cs);
	friend class UserFlow;
};





