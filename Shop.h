#pragma once
#include <memory>
#include <vector>

#include "Item.h"
#include "User.h"


class ShopOwner;

class Shop
{
private:
	std::weak_ptr <ShopOwner> shopOwner;
	std::string name;
	std::vector<std::shared_ptr<Item> > items;
	Location location;

public:


	Shop();

	Shop(std::weak_ptr <ShopOwner> shopOwner, std::string name, Location location);

	std::weak_ptr <ShopOwner> getShopOwner() const;
	void setShopOwner(std::weak_ptr <ShopOwner> shopOwner);
	std::string getName() const;
	void setName(std::string name);
	const std::vector<std::shared_ptr<Item>>& getItems();
	void setItems(std::vector<std::shared_ptr<Item>> items);
	Location getLocation() const;
	void setLocation(Location location);

	void storeItem(std::shared_ptr <Item> newItem, int quantity, bool isNew = false);
	void sellItem(std::shared_ptr<Item> item, int quantity);
	int getItemsCount() const;

	void display(char useType ='c');
	void recieveOrder(std::shared_ptr<Order> cart);
	void removeOrder(const std::shared_ptr<Order>& order);
	void removeVolunteer(const std::shared_ptr<Volunteer>& volunteer);
	void addVolunteer(const std::shared_ptr<Volunteer>& shared);
	friend class Order;
	//void addBalance(double amount);

};

