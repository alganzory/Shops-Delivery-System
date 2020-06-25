#pragma once
#include <memory>
#include <vector>

#include "Item.h"
#include "User.h"


class ShopOwner;

class Shop
{
	/// Members
private:
	std::weak_ptr<ShopOwner> shopOwner;
	std::string name;
	std::vector<std::shared_ptr<Item>> items;
	Location location;
	std::pair<Time, Time> availableTimes;

public:

	/// Constructors
	Shop();
	Shop(std::weak_ptr<ShopOwner> shopOwner, std::string name, Location location);

	/// Getters
	std::weak_ptr<ShopOwner> getShopOwner() const;
	std::string getName() const;
	std::pair<Time, Time> getAvailableTimes() const;
	const std::vector<std::shared_ptr<Item>>& getItems();
	int getItemsCount() const;
	bool isAvailable(Time time);
	Location getLocation() const;

	/// Setters
	void setShopOwner(std::weak_ptr<ShopOwner> shopOwner);
	void setName(std::string name);
	//useless
	void setItems(std::vector<std::shared_ptr<Item>> items);
	void setLocation(Location location);
	void setAvailableTimes(std::pair<int, int> availableTimes);

	/// Methods
	void storeItem(std::shared_ptr<Item> newItem, int quantity, bool isNew = false);
	void sellItem(std::shared_ptr<Item> item, int quantity);
	void display(char useType = 'c');
	void recieveOrder(std::shared_ptr<Order> cart);
	//useless
	void removeOrder(const std::shared_ptr<Order>& order);
	//useless
	void removeVolunteer(const std::shared_ptr<Volunteer>& volunteer);
	void addVolunteer(const std::shared_ptr<Volunteer>& shared);

	/// Friend Classes
	friend class Order;
};
