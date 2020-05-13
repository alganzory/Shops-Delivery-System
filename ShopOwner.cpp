#include "ShopOwner.h"


ShopOwner::ShopOwner(std::string username, std::string password):
	User(username, password)
{
}

void ShopOwner::setInfo(std::string name, int age, double balance, Location location)
{
	this->name = name;
	this->age = age;
	this->balance = balance;
	this->location = location;

	// prompt to ask for shop name:
	// cout << "Enter your shop Info":
	std::string shopName;
	getline(std::cin, shopName);
	
	// ask if location is same, if not get new location
	// what is you location?
	//
	Location shopLocation;
	createShop(shopName, shopLocation);
}

Shop ShopOwner::getShop() const
{
	return shop;
}

std::shared_ptr<Shop> ShopOwner::getShopPtr()
{
	return std::shared_ptr<Shop>(&shop);
}

void ShopOwner::createShop(std::string shopName, Location shopLocation)
{
	this->shop = Shop(this, shopName, shopLocation);
}

void ShopOwner::respondToOrder(std::shared_ptr<Order> order)
{
	orders.push_back(order);
}

void ShopOwner::assignVolunteer(std::shared_ptr <Order> order)
{
	const auto availableVolunteer = find_if(availableVolunteers.begin(), availableVolunteers.end(),
	                                        [](std::shared_ptr<Volunteer> volunteer) {return volunteer->isAvailable(); });
	if (availableVolunteer!= availableVolunteers.end())
	{
		order->setDelivery(*availableVolunteer);
	}
}

void ShopOwner::addToStock(std::shared_ptr<Item> newItem, int quantity)
{
	this->shop.storeItem(newItem, quantity);

}

void ShopOwner::sellItem(std::shared_ptr<Item> item, int quantity)
{
	this->shop.sellItem(item, quantity);
}

void ShopOwner::rewardVolunteer(std::shared_ptr<Volunteer> volunteer, double reward)
{
	volunteer->getReward(reward);
}
