#pragma once
#include "Shop.h"
#include "User.h"
#include "Volunteer.h"

class ShopOwner :
	public User,
	public std::enable_shared_from_this<ShopOwner>
{
private:
	Shop shop;
	std::vector <std::shared_ptr<Volunteer> > availableVolunteers;
public:

	ShopOwner(std::string username, std::string password);
	void setInfo(std::string name, int age, double balance, Location location) override;

	Shop getShop() const;
	std::shared_ptr <Shop> getShopPtr();
	void createShop(std::string shopName, Location shopLocation);

	void respondToOrder(std::shared_ptr < Order> order);
	void assignVolunteer(std::shared_ptr < Order> order);
	void addToStock(std::shared_ptr<Item> newItem, int quantity, bool isNew);
	void sellItem(std::shared_ptr<Item> item, int quantity);
	void rewardVolunteer(std::shared_ptr <Volunteer> volunteer, double reward);
	void welcome();
	std::string getShopName() const;
	int getShopSize() const;
	void setInfoFile(const std::string& cs, int age, double balance, const std::string& location, const std::string& shopname, const std::string& shoplocation);
	friend class ShopOwnerFlow;
};

