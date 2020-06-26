#pragma once
#include "ShopOwner.h"
#include <algorithm>

class ShopOwnerFlow
{
	/// Members
public:
	/**
	 * \brief: the current shop owner that logged in
	 */
	static std::shared_ptr <ShopOwner> currentSO;

public:
	/// Methods
	/**
	 * \brief : to let shop owner to update the item of 
	 *			shop in terms of name, price, quantity
	 * \param item : the item to be edited
	 */
	static void editItem(const std::shared_ptr<Item> item);
	/**
	 * \brief : to let shop owner 
	 *			to add new item
	 *			to the list of item
	 *			or add to existing
	 *			item in the shop
	 */
	static void addNewItem();
	static void myShop();
	static void mainMenu();
	/**
	 * \brief : to view all orders the shop has
	 *			ongoing or all orders
	 *			ask to view specific order
	 * \param ongoingOnly : true to view ongoing
	 *						order, false view all
	 */
	static void allOrders(bool ongoingOnly = false);
	/**
	 * \brief : assign volunteer to specific order if there are 
				volunteers available at the time
	 * \param order : the specific order from list of orders of 
	 *				  the shop
	 */
	static void assignVolunteer(const std::shared_ptr<Order>& order);
	static void viewOrder(std::shared_ptr<Order>& order);
	/**
	 * \brief : to prepare order and change the status of items
	 * \param order : the specific order from list of orders 
	 */
	static void orderPreparation(std::shared_ptr<Order>order);
	/**
	 * \brief : to find available volunteers at the given time
	 * \param time : the time of the order
	 * \return : list of available volunteers at the given time
	 */
	static std::vector<std::shared_ptr<Volunteer>> findAvailableVolunteers(Time time);

	/// Friend Classes
	friend class Order;
};

