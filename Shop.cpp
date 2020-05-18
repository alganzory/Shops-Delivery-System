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

std::vector<std::shared_ptr<Item>> Shop::getItems() const
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

void Shop::storeItem(std::shared_ptr<Item> newItem, int quantity)
{
	auto findItem = find(items.begin(), items.end(), newItem);

	if (findItem != items.end())
	{
		newItem->addQuantity(quantity);
	}

	else
	{
		items.push_back(newItem);
		newItem->addQuantity(quantity);
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
