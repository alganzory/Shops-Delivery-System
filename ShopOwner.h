#pragma once
#include "Shop.h"
#include "User.h"
#include "Volunteer.h"

class ShopOwner :
	public User,
	// to enable getting a shared_ptr from this
	public std::enable_shared_from_this<ShopOwner> 
{
	/// Members
private:
	std::shared_ptr<Shop> shop;
	/**
	 * \brief : a list of volunteer that registered to this shop
	 */
	std::vector<std::shared_ptr<Volunteer>> registeredVolunteers;

public:
	/// Constructors
	ShopOwner(std::string username, std::string password);

	/// Getters
	std::shared_ptr<Shop> getShopPtr();
	std::string getShopName() const;
	/**
	 * \brief: to get the number of items in the shop
	 * \return :number of items
	 */
	int getShopSize() const;

	/// Setters
	void setShopName(const std::string& shopName);
	void setShopAddress(const std::string& shopAddress);

	/// Methods
	void setInfo(std::string name, int age, double balance, Location location) override;
	/**
	 * \brief : create a shop to shop owner
	 * \param shopName : the name of shop
	 * \param shopLocation :the location of shop
	 * \param startTime :the hour start operation
	 * \param endTime :the hour end operation
	 */
	void createShop(std::string shopName, Location shopLocation, int startTime, int endTime);
	void respondToOrder(std::shared_ptr<Order> order);
	void assignVolunteer(std::shared_ptr<Order> order);
	/**
	 * \brief : storing new item to the stock of the shop
	 *			checks if the item is available already
	 * \param newItem : item name
	 * \param quantity : quantity of the item
	 * \param isNew : true if item is a new one, false if available
	 */
	void addToStock(std::shared_ptr<Item> newItem, int quantity, bool isNew);
	void sellItem(std::shared_ptr<Item> item, int quantity);
	/**
	 * \brief :to send the shop owner to menu
	 *			overrides function from User class
	 */
	void welcome() override;
	void setInfoFile(const std::string& name, int age, double balance, const std::string& location,
	                 const std::string& shopname, const std::string& shoplocation, int availableTime1,
	                 int availableTime2);

	/// Friend Classes
	friend class ShopOwnerFlow;
	friend class O_List;
	friend class Shop;
	friend class SO_List;
};
