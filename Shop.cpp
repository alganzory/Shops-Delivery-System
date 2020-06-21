#include "Shop.h"

#include <iomanip>


#include "ShopOwner.h"

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

void Shop::display(char userType) 
{

	std::cout << std::setw(20) << getName();
	if (userType == 'v') std::cout << std::setw(25);
	std::cout << getLocation().getAddress();

}

void Shop::recieveOrder(std::shared_ptr<Order> cart)
{
	shopOwner->addOrder(cart);
}

void Shop::removeOrder(const std::shared_ptr<Order>& order)
{
	shopOwner->removeOrder(order);
}

void Shop::removeVolunteer(const std::shared_ptr<Volunteer>& volunteer)
{
	try
	{
		auto volFound = std::find(shopOwner->registeredVolunteers.begin(),
			shopOwner->registeredVolunteers.end(), volunteer);
		if (volFound == shopOwner->registeredVolunteers.end())
			throw "Not Found";
		shopOwner->registeredVolunteers.erase(volFound);
	}
	catch (const char* e)
	{
		std::cout << e << std::endl;
		return;
	}	
}

void Shop::addVolunteer(const std::shared_ptr<Volunteer>& volunteer)
{
	shopOwner->registeredVolunteers.emplace_back(volunteer);
}
