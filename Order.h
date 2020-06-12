#ifndef order_H
#define order_H
#include <vector>
#include <memory>
#include "Item.h"

class Shop;
class Customer;
class Volunteer;



class Order {
public:
	enum Status  // this is the class that groups the statuses together
	{
		Pending,  // the initial state of the order, the shop owner did not deal with it yet
		Preparing, // once the shop owner starts preparing the order (the todo check list)
		Delivering, // once a volunteer chooses to deliver
		Complete // once the volunteer is done delivering the order
	};
private:
	std::vector <std::pair<std::shared_ptr<Item>, int> > items;
	std::shared_ptr<Customer> customer;
	std::shared_ptr<Shop> shop;
	double totalPrice;
	bool paymentStatus;
	std::shared_ptr<Volunteer> delivery;
	bool deliveryStatus;
	int deliveryTime;

	Status orderStatus; // this is the status of each order 
	std::vector<bool> preparationStatus;
public:
	Order();
	Order(std::shared_ptr<Customer> customer, std::shared_ptr<Shop> shop);
	void addItem(std::shared_ptr<Item> item, int quantity);
	void removeItem(std::pair<std::shared_ptr<Item>, int>& itemReq);
	void setTotalPrice(double totalPrice);
	double getTotalPrice();
	void setDelivery(std::shared_ptr<Volunteer>volunteer);
	void setPaymentStatus(bool paymentStatus);
	void setDeliveryStatus(bool deliveryStatus);
	std::shared_ptr<Volunteer> getDelivery();
	bool getDeliveryStatus();
	void setDeliveryTime(int deliveryTime);
	bool  getPaymentStatus();
	int getDeliveryTime();
	void display(char userType ='c');
	int getOrderSize();
	std::pair<std::shared_ptr<Item>, int>& getItem(int);
	void setShop(const std::shared_ptr<Shop>& shop);
	void setCustomer(const std::shared_ptr<Customer>& shared);
	void buyItems();

	Status getStatus();
	void setStatus(Status newStatus);
	std::shared_ptr<Customer> getCustomer();
	void setPreparationStatus(int num);
	bool isReady();
};

#endif
