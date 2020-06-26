#include "ShopOwner.h"
#include "Helper.h"
#include "ShopOwnerFlow.h"
#include "SH_List.h"

/// Constructors
ShopOwner::ShopOwner(std::string username, std::string password):
	User(username, password)
{
	
}

/// Getters
std::string ShopOwner::getShopName() const
{
	return shop->getName();
}

int ShopOwner::getShopSize() const
{
	return shop->getItemsCount();
}
std::shared_ptr<Shop> ShopOwner::getShopPtr()
{
	return shop;
}

/// Setters
void ShopOwner::setShopName(const std::string& shopName)
{
	shop->setName(shopName);
}

void ShopOwner::setShopAddress(const std::string& shopAddress)
{
	shop->setLocation(Location(shopAddress));
}


/// Methods
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
	std::cout << "When are you available?\n"
		<< "Start hour: ";
	int startHour = Helper::readChoice(0, 23);
	std::cout << "End hour: ";
	int endHour = Helper::readChoice(startHour,24);

	createShop(shopName, shopLocation,startHour,endHour);
	SH_List::addShop(shop);

}

void ShopOwner::createShop(std::string shopName, Location shopLocation,int startTime, int endTime)
{

	shop->setName(shopName);
	shop->setLocation(shopLocation);
	shop->setAvailableTimes(std::pair<int, int>(startTime, endTime));
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


void ShopOwner::welcome()
{
	ShopOwnerFlow::currentSO = shared_from_this();
	ShopOwnerFlow::mainMenu();
}

void ShopOwner::setInfoFile(const std::string& name, int age, double balance, const std::string& location,
	const std::string& shopname, const std::string& shoplocation, int availableTime1, int availableTime2)
{
	this->name = name;
	this->age = age;
	this->balance = balance;
	this->location = Location(location);
	this->shop = std::make_shared <Shop>();
	shop->setShopOwner(shared_from_this());
	createShop(shopname, Location (shoplocation), availableTime1, availableTime2);
}

//Shop ShopOwner::getShop() const
//{
//	return shop;
//}
