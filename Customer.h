#pragma once
#include "User.h"

/**
 * \brief : Attributes and methods special to the
 *			use of type Customer
 */
class Customer :
	public User,
	public std::enable_shared_from_this<Customer> // to be able to get a shared_ptr using this pointer
{
	/// Members
public:
	enum HealthStatus
	{
		Healthy,
		ShowSymptoms,
		Infected
	};

private:
	HealthStatus healthStatus;
	/**
	 * \brief: The list of shops available to the customer
	 *		   at the time of attempting to make an order
	 */
	std::vector<std::shared_ptr<Shop>> availableShops;
	std::shared_ptr<Order> cart;


public:
	/// Constructors
	Customer(std::string username, std::string password);

	/// Getters
	HealthStatus getHealthStatus() const;

	/// Setters
	void setHealthStatus(HealthStatus health);

	/// Methods

	void setInfo(std::string name, int age, double balance, Location location) override;

	void placeOrder();

	/**
	 * \brief adds and item to the cart of the customer
	 * \param item the pointer to the item to be added
	 * \param quantity the quantity of the item
	 */
	void addToCart(std::shared_ptr<Item> item, int quantity);

	/**
	 * \brief : this function is an alternative (not very safe)
	 *			way to add items to the cart, looks up the item
	 *			index in the shop of the current order
	 * \param itemIdx : the index for the item in the shop
	 * \param quantity : the quantity of the required item
	 */
	void addToCart(int itemIdx, int quantity);

	void removeFromCart(std::pair<std::shared_ptr<Item>, int>& itemReq);


	/**
	 * \brief : sends the customer to the welcome page
	 */
	void welcome() override;

	/// Operators
	friend std::ostream& operator <<(std::ostream& output, const Customer::HealthStatus& healthStatus);

	/// Friend Classes
	friend class CustomerFlow; 
	friend class O_List;
	friend class C_List;
};
