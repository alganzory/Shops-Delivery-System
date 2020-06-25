#pragma once
#include "Shop.h"
#include "User.h"
#include "Volunteer.h"

class ShopOwner :
	public User,
	public std::enable_shared_from_this<ShopOwner>
{
	/// Members
private:
	std::shared_ptr<Shop> shop;
	std::vector<std::shared_ptr<Volunteer>> registeredVolunteers;

public:
	/// Constructors
	ShopOwner(std::string username, std::string password);

	/// Getters
	std::shared_ptr<Shop> getShopPtr();
	std::string getShopName() const;
	int getShopSize() const;

	/// Setters
	void setShopName(const std::string& cs);
	void setShopAdress(const std::string& cs);

	/// Methods
	void setInfo(std::string name, int age, double balance, Location location) override;
	void createShop(std::string shopName, Location shopLocation, int startTime, int endTime);
	void respondToOrder(std::shared_ptr<Order> order);
	void assignVolunteer(std::shared_ptr<Order> order);
	void addToStock(std::shared_ptr<Item> newItem, int quantity, bool isNew);
	void sellItem(std::shared_ptr<Item> item, int quantity);
	void rewardVolunteer(std::shared_ptr<Volunteer> volunteer, double reward);
	void welcome() override;
	void setInfoFile(const std::string& cs, int age, double balance, const std::string& location,
	                 const std::string& shopname, const std::string& shoplocation, int availableTime1,
	                 int availableTime2);

	/// Friend Classes
	friend class ShopOwnerFlow;
	friend class O_List;
	friend class Shop;
	friend class SO_List;
};
