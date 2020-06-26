#include "Shop.h"

#include <iomanip>


#include "ShopOwner.h"

/// Constructors
Shop::Shop()
{

}

Shop::Shop(std::weak_ptr <ShopOwner> shopOwner, std::string name, Location location) :
	shopOwner(shopOwner),
	name(name),
	location(location)
{
}

/// Getters
std::weak_ptr <ShopOwner> Shop::getShopOwner() const
{
	return shopOwner;
}

std::string Shop::getName() const
{
	return name;
}

std::pair <Time, Time> Shop::getAvailableTimes() const
{
	return operationTimes;
}

const std::vector<std::shared_ptr<Item>> & Shop::getItems() 
{
	return items;
}

int Shop::getItemsCount() const
{
	return items.size();
}

bool Shop::isOperating(Time time)
{
	const bool available = true;
	if (time > operationTimes.first && time < operationTimes.second) {
		return available;
	}
	else return !available;
}

Location Shop::getLocation() const
{
	return location;
}

/// Setters
void Shop::setShopOwner(std::weak_ptr <ShopOwner> shopOwner)
{
	this->shopOwner = shopOwner;
}

void Shop::setName(std::string name)
{
	this->name = name;
}

void Shop::setItems(std::vector<std::shared_ptr<Item>> items)
{
	this->items = items;
}

void Shop::setLocation(Location location)
{
	this->location = location;
}

void Shop::setAvailableTimes(std::pair<int, int> availableTimes)
{
	this->operationTimes = std::pair < Time, Time>(Time(availableTimes.first, 0), Time(availableTimes.second, 0));
}

/// Methods
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

void Shop::display(char userType) 
{

	std::cout << std::setw(20) << getName();
	if (getLocation().getAddress().length() <= 23)
	{
		std::cout << std::setw(25);
		std::cout << getLocation().getAddress();
	}
	else
	{
		for (int i = 0; i < 20; i++)
		{
			std::cout << getLocation().getAddress().at(i);
		}
		std::cout << "...  ";
	};
	std::cout << operationTimes.first << "-" << std::setw(8)<<operationTimes.second;
}

void Shop::recieveOrder(std::shared_ptr<Order> cart)
{
	shopOwner.lock()->addOrder(cart);
}

void Shop::removeOrder(const std::shared_ptr<Order>& order)
{
	shopOwner.lock()->removeOrder(order);
}


void Shop::addVolunteer(const std::shared_ptr<Volunteer>& volunteer)
{
	shopOwner.lock()->registeredVolunteers.emplace_back(volunteer);
}

void Shop::removeVolunteer(const std::shared_ptr<Volunteer>& volunteer)
{
	try
	{
		auto volFound = std::find(shopOwner.lock()->registeredVolunteers.begin(),
			shopOwner.lock()->registeredVolunteers.end(), volunteer);
		if (volFound == shopOwner.lock()->registeredVolunteers.end())
			throw "Not Found";
		shopOwner.lock()->registeredVolunteers.erase(volFound);
	}
	catch (const char* e)
	{
		std::cout << e << std::endl;
		return;
	}
}


