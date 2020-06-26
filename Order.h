#ifndef order_H
#define order_H
#include <vector>
#include <memory>
#include "Item.h"
#include "Time.h"

class Shop;
class Customer;
class Volunteer;


class Order
{
	/// Members
public:
	enum Status 
	{
		Pending,			// the initial state of the order
		Preparing,			// once the shop owner starts preparing the order (preparation list)
		VolunteerFound,		// once a volunteer is Assigned
		Delivering,			// once a volunteer chooses to deliver
		Complete,			// once the volunteer hands out the order
		Cancelled			// once the order is canceled, or become overdue
	};

private:
	
	/**
	 * \brief : the items are stored as a pair of pointer
	 *			to item object and the quantity in order
	 */
	std::vector<std::pair<std::shared_ptr<Item>, int>> items;
	
	/**
	 * \brief : stores the respective indices of the items
	 *			from the shop from which the order comes
	 *			this is useful for faster lookup
	 *			
	 */
	std::vector<int> itemsIndices;
	std::shared_ptr<Customer> customer;
	std::shared_ptr<Shop> shop;
	double totalPrice{};
	bool paymentStatus;
	/**
	 * \brief : the volunteer assigned the delivery
	 *			starts as a nullptr until one found
	 */
	std::shared_ptr<Volunteer> delivery;
	bool deliveryStatus;
	Time deliveryTime;
	Status orderStatus;
	/**
	 * \brief : status of preparation of each item
	 *			in the order, looking up the index
	 *			of the item will return true or
	 *			false based on the preparation status
	 */
	std::vector<bool> preparationStatus;
	
	/**
	 * \brief : the tip that the customer leaves
	 */
	double reward;
	bool contactless;
	/**
	 * \brief a flag to mark overdue order
	 */
	bool overdue;

public:
	/// Constructors	
	Order();
	Order(std::shared_ptr<Customer> customer, std::shared_ptr<Shop> shop);

	/// Getters
	std::string getDlvryAddress() const;
	std::string getCustomerName() const;
	std::shared_ptr<Shop> getShop();
	std::shared_ptr<Volunteer> getDelivery();
	std::pair<std::shared_ptr<Item>, int>& getItem(int);
	Time getDeliveryTime();
	Status getStatus();
	double getTotalPrice();
	double getReward();
	/**
	 * \brief : calculates the time difference
	 *			of delivery time and current time
	 *			also sets or clears the flag overdue
	 * \return : if the order has been overdue
	 */
	bool isOverdue();
	
	/**
	 * \brief : checks the preparation status
	 *			of items
	 * \return : if all items have been prepared
	 */
	bool isReady();
	bool getContactlessDlvr();
	bool getDeliveryStatus();
	bool getPaymentStatus();
	bool isEmpty();
	int getOrderSize();

	/// Setters
	void setTotalPrice(double totalPrice);

	/**
	 * \brief : setting the volunteer responsible
	 *			to deliver this order
	 * \param volunteer : the volunteer to be assigned
	 */
	void setDelivery(std::shared_ptr<Volunteer> volunteer);
	void setPaymentStatus(bool paymentStatus);
	void setDeliveryStatus(bool deliveryStatus);
	void setShop(std::shared_ptr<Shop> shop);
	void setCustomer(std::shared_ptr<Customer> shared);
	void setStatus(Status newStatus);
	void setDeliveryTime(int hour, int minute);
	void setPreparationStatus(int num);

	/**
	 * \brief :sets the reward that will be given
	 *			to the volunteer upon hand out
	 */
	void setReward(double);
	void setContactlessDlvr(bool contactless);

	/// Methods

	/**
	 * \brief : used to return the items to their
	 *			shop and change the order status
	 */
	void cancelOrder();
	void setOverdueStatus(bool overdueStatus);
	/**
	 * \brief : this method can be used to add a pointer
	 *			to an item object
	 * \param item : a pointer to the item to be added
	 * \param quantity : the quantity to be added
	 */
	void addItem(std::shared_ptr<Item> item, int quantity);
	/**
	 * \brief : used to add the item by knowing its index
	 *			in the shop that this orders is from
	 * \param itemIdx : the index of the item in the shop
	 * \param quantity : the quantity required 
	 */
	void addItem(int itemIdx, int quantity);

	/**
	 * \brief : removes the item from the order
	 * \param itemReq : the item to be removed
	 */
	void removeItem(std::pair<std::shared_ptr<Item>, int>& itemReq);

	void display(bool showPreparationStatus = false);
	void summary(char userType = 'c');
	/**
	 * \brief : buys the items from the shop
	 *			(i.e decrease their quantity)
	 */
	void buyItems();

	/**
	 * \brief : copying one order to the other
	 */
	void reorder(std::shared_ptr<Order>);

	/**
	 * \brief : used to reduce the quantity of the
	 *			item in the order
	 * \param quantity : the quantity to be reduced
	 * \param itemReq : the item to be reduced
	 */
	void reduceItem(std::pair<std::shared_ptr<Item>, int>& itemReq, int quantity);

	/// Operators
	friend std::ostream& operator <<(std::ostream& output, const Order::Status& status);
	friend std::istream& operator>>(std::istream& input, Status& status);
	friend bool operator <(const std::shared_ptr<Order>& lhs, const std::shared_ptr<Order>& rhs);

	/// Friend Classes
	friend class O_List;
	friend class VolunteerFlow;
	friend class ShopOwnerFlow;
};

#endif
