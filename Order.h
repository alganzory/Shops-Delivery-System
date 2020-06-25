#ifndef order_H
#define order_H
#include <vector>
#include <memory>
#include "Item.h"
#include "Time.h"

class Shop;
class Customer;
class Volunteer;


class Order : public std::enable_shared_from_this<Order>
{
	/// Members
public:
	enum Status // this is the class that groups the statuses together
	{
		Pending,
		// the initial state of the order, the shop owner did not deal with it yet
		Preparing,
		// once the shop owner starts preparing the order (the todo check list)
		VolunteerFound,
		// once a volunteer is Assigned
		Delivering,
		// once a volunteer chooses to deliver
		Complete,
		// once the volunteer is done delivering the order
		Cancelled // once the shop owner cancel the order
	};

private:
	std::vector<std::pair<std::shared_ptr<Item>, int>> items;
	std::vector<int> itemsIndices;
	std::shared_ptr<Customer> customer;
	std::shared_ptr<Shop> shop;
	double totalPrice;
	bool paymentStatus;
	std::shared_ptr<Volunteer> delivery;
	bool deliveryStatus;
	Time deliveryTime;
	Status orderStatus; // this is the status of each order 
	std::vector<bool> preparationStatus;
	double reward;
	bool contactless;
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
	bool isOverdue();
	bool isReady();
	bool getContactlessDlvr();
	//useless
	bool getDeliveryStatus();
	bool getPaymentStatus();
	bool isEmpty();
	int getOrderSize();

	/// Setters
	//useless
	void setTotalPrice(double totalPrice); //useless
	void setDelivery(std::shared_ptr<Volunteer> volunteer);
	void setPaymentStatus(bool paymentStatus);
	void setDeliveryStatus(bool deliveryStatus);
	void setShop(std::shared_ptr<Shop> shop);
	void setCustomer(std::shared_ptr<Customer> shared);
	void setStatus(Status newStatus);
	void setDeliveryTime(int hour, int minute);
	void setPreparationStatus(int num);
	void setReward(double);
	void setContactlessDlvr(bool contactless);

	/// Methods
	void cancelOrder();
	void setOverdueStatus(bool overdueStatus);
	void addItem(std::shared_ptr<Item> item, int quantity);
	void addItem(int itemIdx, int quantity);
	void removeItem(std::pair<std::shared_ptr<Item>, int>& itemReq);
	void display(bool showPreparationStatus = false);
	void summary(char userType = 'c');
	void buyItems();
	void reorder(const std::shared_ptr<Order>);
	void reduceItem(int quantity, std::pair<std::shared_ptr<Item>, int>& itemReq);

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
