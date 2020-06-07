#include "Shop.h"

Shop::Shop()
{

}

Shop::Shop(ShopOwner* shopOwner, std::string name, Location location) :
	shopOwner(shopOwner),
	name(name),
	location(location)
{
}

ShopOwner* Shop::getShopOwner() const
{
	return shopOwner;
}

void Shop::setShopOwner(ShopOwner* shopOwner)
{
	this->shopOwner = shopOwner;
}

std::string Shop::getName() const
{
	return name;
}

void Shop::setName(std::string name)
{
	this->name = name;
}

const std::vector<std::shared_ptr<Item>> & Shop::getItems() 
{
	return items;
}

void Shop::setItems(std::vector<std::shared_ptr<Item>> items)
{
	this->items = items;
}

Location Shop::getLocation() const
{
	return location;
}

void Shop::setLocation(Location location)
{
	this->location = location;
}

void Shop::storeItem(std::shared_ptr<Item> newItem, int quantity, bool isNew)
{
	auto findItem = find(items.begin(), items.end(), newItem->getName());

	if (findItem != items.end())
	{
		if (isNew) throw "Item already exists!";
		(*findItem)->addQuantity(quantity);
	}

	else
	{
		items.push_back(newItem);
	}
}

void Shop::sellItem(std::shared_ptr<Item> item, int quantity)
{
	if (item->getInStock() < quantity)
		throw "Not enough of this item\n";
	else
	{
		item->subQuantity(quantity);
	}
}

int Shop::getItemsCount() const
{
	return items.size();
}

void Shop::display() 
{

	std::cout << getName() << '\t' << getLocation().getAddress() << "\n";

}
