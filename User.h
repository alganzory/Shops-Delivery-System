#pragma once
#include <iostream>
#include <memory>
#include <string>
#include <vector>
#include <algorithm>
#include "Location.h"
#include "Order.h"

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
	/**
	 * \brief: the list of orders made or received
	 */
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
	/**
	 * \brief : check whether username and password
	 *			match the input
	 * \param username : username of user
	 * \param password : password of user
	 * \return 
	 */
	bool isAuth(std::string username, std::string password) const;

	/// Setters
	void setPassword(const std::string& cs);
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
	/**
	 * will be overridden to direct to the respective
	 * user welcoming screen
	 */
	virtual void welcome() = 0;
	/**
	 * \brief : will be overridden to set and ask for
	 *			info for the respective user type
	 * \param name 
	 * \param age 
	 * \param balance 
	 * \param location 
	 */
	virtual void setInfo(std::string name, int age, double balance, Location location) = 0;

	/// Operators
	friend bool operator==(const User& lhs, const User& rhs);
	/**
	 * \brief : to find objects with string to compare username
	 * \param lhs: the user to compare 
	 * \param username :the username to compare
	 * \return if equals
	 */
	friend bool operator==(const std::shared_ptr<User>& lhs, const std::string& username);

	/// Destructor
	virtual ~User();

	/// Friend Functions

	/// Friend Classes
	friend class UserFlow;
};
