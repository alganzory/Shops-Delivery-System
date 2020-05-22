#pragma once
#include "User.h"
#include "Volunteer.h"

class Customer:public User
{
	private:
		std::string healthStatus;
		std::vector <std::shared_ptr<Shop> > availableShops;
		std::shared_ptr <Order> cart;
	public:
		Customer(std::string username, std::string password);
		void setHealthStatus(std::string healthStatus);
		std::string getHealthStatus() const;
		void setInfo(std::string name, int age, double balance, Location location);
		void placeOrder();
		void rewardVolunteer (std::shared_ptr<Volunteer> volunteer, double reward);
		void addToCart(std::shared_ptr <Item> item, int quantity);
		void removeFromCart(std::pair<std::shared_ptr<Item>, int> itemReq);
};

