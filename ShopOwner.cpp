#include "ShopOwner.h"

#include "ShopOwnerFlow.h"


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

	std::cout << "What is the name of your Shop?\n";
	std::string shopName;
	getline(std::cin, shopName);

	std::cout << "What is the address of your shop?\n";
	std::string shopAddress;
	std::getline(std::cin, shopAddress);
	shop = std::make_shared <Shop>();
	shop->setShopOwner(shared_from_this());
	Location shopLocation(shopAddress);
	createShop(shopName, shopLocation);
}

//Shop ShopOwner::getShop() const
//{
//	return shop;
//}

std::shared_ptr<Shop> ShopOwner::getShopPtr()
{
	return shop;
}

void ShopOwner::createShop(std::string shopName, Location shopLocation)
{

	shop->setName(shopName);
	shop->setLocation(shopLocation);
}

void ShopOwner::respondToOrder(std::shared_ptr<Order> order)
{
	orders.push_back(order);
}

void ShopOwner::assignVolunteer(std::shared_ptr <Order> order)
{
	const auto availableVolunteer = find_if(registeredVolunteers.begin(), registeredVolunteers.end(),
		[order](std::shared_ptr<Volunteer> volunteer) {return volunteer->isAvailable(order->getDeliveryTime()); });
	if (availableVolunteer!= registeredVolunteers.end())
	{
		order->setDelivery(*availableVolunteer);
	}
}

void ShopOwner::addToStock(std::shared_ptr<Item> newItem, int quantity, bool isNew)
{
	this->shop->storeItem(newItem, quantity,isNew);

}

void ShopOwner::sellItem(std::shared_ptr<Item> item, int quantity)
{
	this->shop->sellItem(item, quantity);
}

void ShopOwner::rewardVolunteer(std::shared_ptr<Volunteer> volunteer, double reward)
{
	volunteer->getReward(reward);
}


void ShopOwner::welcome()
{
	ShopOwnerFlow::currentSO = shared_from_this();
	ShopOwnerFlow::mainMenu();
}

std::string ShopOwner::getShopName() const
{
	return shop->getName();
}

int ShopOwner::getShopSize() const
{
	return shop->getItemsCount();
}

void ShopOwner::setInfoFile(const std::string& cs, int age, double balance, const std::string& location,
	const std::string& shopname, const std::string& shoplocation)
{
	this->name = cs;
	this->age = age;
	this->balance = balance;
	this->location = Location(location);
	this->shop = std::make_shared <Shop>();
	shop->setShopOwner(shared_from_this());
	createShop(shopname, Location (shoplocation));
}

void ShopOwner::setShopName(const std::string& cs)
{
	shop->setName(cs);
}

void ShopOwner::setShopAdress(const std::string& cs)
{
	shop->setLocation(Location(cs));
}
