#pragma once
#include <memory>
#include <vector>

#include "Item.h"
#include "User.h"


class ShopOwner;

class Shop
{
private:
	ShopOwner* shopOwner{};
	std::string name;
	std::vector<std::shared_ptr<Item> > items;
	Location location;

public:


	Shop();

	Shop(ShopOwner* shopOwner, std::string name, Location location);

	ShopOwner* getShopOwner() const;
	void setShopOwner(ShopOwner* shopOwner);
	std::string getName() const;
	void setName(std::string name);
	const std::vector<std::shared_ptr<Item>>& getItems();
	void setItems(std::vector<std::shared_ptr<Item>> items);
	Location getLocation() const;
	void setLocation(Location location);

	void storeItem(std::shared_ptr <Item> newItem, int quantity, bool isNew = false);
	void sellItem(std::shared_ptr<Item> item, int quantity);
	int getItemsCount() const;
};

