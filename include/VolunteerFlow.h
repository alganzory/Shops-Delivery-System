#pragma once
#include "Volunteer.h"
#include "UserFlow.h"
#include <algorithm>


class VolunteerFlow
{
public:
	/// Members
	/**
	 * \brief : the volunteer logged in
	 */
	static std::shared_ptr<Volunteer> currentVolunteer;
	/**
	 * \brief : the current order being delivered
	 *			by volunteer
	 */
	static std::shared_ptr<Order> currentOrder;
public:
	/// Methods
	/**
	 * \brief : displaying the order
	 *			that is currently
	 *			being delivered
	 */
	static void ongoingOrder();
	/**
	 * \brief : displaying the list of orders
	 * \param pendingOnly : true to see only pending
	 *						false to see complete						
	 */
	static void myOrders(bool pendingOnly = false);
	/**
	 * \brief : lists shops in program
	 *			and the registration
	 *			status, volunteer can
	 *			change status
	 */
	static void registerShops();
	static void mainMenu();
	/**
	 * \brief :display the detail of the order
	 * \param order : the specific order from list of orders
	 */
	static void viewOrder(const std::shared_ptr<Order>& order);
	//friend class Customer;
};


