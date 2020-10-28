#pragma once
#include <memory>
#include <vector>

#include "Item.h"
#include "User.h"


class ShopOwner;

class Shop
{
	/// Members
private:
	
	std::weak_ptr<ShopOwner> shopOwner;
	std::string name;
	std::vector<std::shared_ptr<Item>> items;
	Location location;
	/**
	 * \brief : store the shop's operation time
	 */
	std::pair<Time, Time> operationTimes;

public:

	/// Constructors
	Shop();
	Shop(std::weak_ptr<ShopOwner> shopOwner, std::string name, Location location);

	/// Getters
	std::weak_ptr<ShopOwner> getShopOwner() const;
	std::string getName() const;
	std::pair<Time, Time> getAvailableTimes() const;
	/**
	 * \brief : to get a list of items
	 * \return : vector of items
	 */
	const std::vector<std::shared_ptr<Item>>& getItems();
	int getItemsCount() const;
	/**
	 * \brief : checks if the system time matches the operation time
	 *          of the shop
	 * \param time : system's time
	 * \return : if it is available
	 */
	bool isOperating(Time time);
	Location getLocation() const;

	/// Setters

	/**
	 * \brief : to set the shop owner to the shop
	 */
	void setShopOwner(std::weak_ptr<ShopOwner> shopOwner);
	void setName(std::string name);
	void setItems(std::vector<std::shared_ptr<Item>> items);
	void setLocation(Location location);
	void setAvailableTimes(std::pair<int, int> availableTimes);

	/// Methods
	/**
	 * \brief: to add items
	 * \param newItem: the item to add
	 * \param quantity: quantity of item
	 * \param isNew: whether there is same item in the shop
	 */
	void storeItem(std::shared_ptr<Item> newItem, int quantity, bool isNew = false);
	/**
	 * \brief: operate when selling items
	 * \param item: the item to sell
	 * \param quantity: quantity of item
	 */
	void sellItem(std::shared_ptr<Item> item, int quantity);
	/**
	 * \brief: display the information of shop based on the userType
	 * \param userType: the type of user
	 */
	void display(char useType = 'c');
	/**
	 * \brief : receive order from customer
	 * \param cart: the order from customer
	 */
	void recieveOrder(std::shared_ptr<Order> cart);
	void removeOrder(const std::shared_ptr<Order>& order);
	/**
	 * \brief : add new volunteer into the list of registered volunteers of shop
	 * \param volunteer : new registered volunteer
	 */
	void addVolunteer(const std::shared_ptr<Volunteer>& volunteer);
	void removeVolunteer(const std::shared_ptr<Volunteer>& volunteer);

	/// Friend Classes
	friend class Order;
	friend class SO_List;
	friend class SH_List;
};
