#ifndef order_H
#define order_H
#include <vector>
#include <memory>
#include "Item.h"
#include "Time.h"

class Shop;
class Customer;
class Volunteer;



class Order : public std::enable_shared_from_this <Order>
{
public:
	enum Status  // this is the class that groups the statuses together
	{
		Pending,  // the initial state of the order, the shop owner did not deal with it yet
		Preparing, // once the shop owner starts preparing the order (the todo check list)
		VolunteerFound, // once a volunteer is Assigned
		Delivering, // once a volunteer chooses to deliver
		Complete // once the volunteer is done delivering the order
	};
	void cancelOrder();
	std::string getDlvryAddress() const;
	std::string getCustomerName() const;

private:
	std::vector <std::pair<std::shared_ptr<Item>, int> > items;
	std::vector <int> itemsIndices;
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
public:
	Order();
	Order(std::shared_ptr<Customer> customer, std::shared_ptr<Shop> shop);
	void addItem(std::shared_ptr<Item> item, int quantity);
	void addItem(int itemIdx, int quantity);
	void removeItem(std::pair<std::shared_ptr<Item>, int>& itemReq);
	void setTotalPrice(double totalPrice);
	double getTotalPrice();
	void setDelivery(std::shared_ptr<Volunteer>volunteer);
	void setPaymentStatus(bool paymentStatus);
	void setDeliveryStatus(bool deliveryStatus);
	std::shared_ptr<Volunteer> getDelivery();
	bool getDeliveryStatus();
	void setDeliveryTime(int hour,int minute);
	bool  getPaymentStatus();
	Time getDeliveryTime();
	void display(bool showPreparationStatus = false);
	void summary(char userType = 'c');
	int getOrderSize();
	std::pair<std::shared_ptr<Item>, int>& getItem(int);
	void setShop(const std::shared_ptr<Shop>& shop);
	void setCustomer(const std::shared_ptr<Customer>& shared);
	void buyItems();

	Status getStatus();
	void setStatus(Status newStatus);

	friend std::ostream& operator << (std::ostream& output, const Order::Status& status);
	friend std::istream& operator>>(std::istream& input, Status& status);
	bool isReady();
	void setPreparationStatus(int num);
	friend bool operator < (const std::shared_ptr <Order> lhs, const std::shared_ptr <Order> rhs);
	void setReward(double);
	double getReward();
	friend class O_List;
	friend class VolunteerFlow;
	friend class ShopOwnerFlow;
	void setContactlessDlvr(bool contactless);
	bool getContactlessDlvr();

};

#endif
