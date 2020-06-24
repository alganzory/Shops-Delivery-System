#pragma once
#include "User.h"
#include "Volunteer.h"

class Customer :
	public User,
	public std::enable_shared_from_this<Customer>
{
public:
	enum HealthStatus {
		Healthy,
		ShowSymptoms,
		Infected
	};
private:
	HealthStatus healthStatus;
	std::vector <std::shared_ptr<Shop> > availableShops;
	std::shared_ptr <Order> cart;
	//bool contactless;
public:
	Customer(std::string username, std::string password);
	void setHealthStatus(HealthStatus health);
	HealthStatus getHealthStatus() const;
	//useless
	void setInfo(std::string name, int age, double balance, Location location);
	void placeOrder();
	//useless
	void rewardVolunteer(std::shared_ptr<Volunteer> volunteer, double reward);
	//useless
	void addToCart(std::shared_ptr <Item> item, int quantity);
	//useless
	void addToCart(int itemIdx, int quantity);
	//useless
	void removeFromCart(std::pair<std::shared_ptr<Item>, int> itemReq);
	//useless
	void welcome() override;
	friend class CustomerFlow;
	friend std::ostream& operator << (std::ostream& output, const Customer::HealthStatus& healthStatus);
	friend class O_List;
	friend class C_List;
};
