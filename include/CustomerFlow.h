#pragma once
#include "Customer.h"
#include "UserFlow.h"

class CustomerFlow
{
	/// Members
public:
	/**
	 * \brief: the customer currently logged in
	 */
	static std::shared_ptr<Customer> currentCustomer;
	/**
	 * \brief : the shop chose by the customer
	 */
	static std::shared_ptr<Shop> currentShop;

	
	/// Methods
public:
	static void mainMenu();
	/**
	 * \brief: find the shops
	 *		   operating at the
	 *		   current time
	 */
	static void findAvailableShops();
	static void displayShops();
	static void viewShop();
	/**
	 * \brief : to go through the 
	 *			flow of displaying
	 *			shops and then
	 *			making order
	 */
	static void makeAnOrder();
	static void checkout();
	static void myCart();
	/**
	 * \brief : to view all of the orders made in
	 *			summary, ask to choose specific 
	 *			order and check the status of the orders
	 * \param ongoingOnly : true to view only ongoing
	 *						orders, false to see all
	 */
	static void myOrders(bool ongoingOnly = false);
	/**
	 * \brief : to view the specific order made by the customer
	 *			to see if customer wants to reorder or cancel
	 * \param order : the order to be viewed
	 */
	static void viewOrder(const std::shared_ptr <Order>& order);

};

