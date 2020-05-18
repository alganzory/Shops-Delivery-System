#ifndef order_H
#define order_H
#include <vector>
#include"volunteer.h"
#include"customer.h"
#include"Shop.h"
#include"Item.h"

class Order {
private:
	std::vector <std::pair<std::shared_ptr<Item>, int>> items;
	std::shared_ptr<Customer> customer;
	std::shared_ptr<Shop> shop;
	double totalPrice;
	bool paymentStatus;
	std::shared_ptr<Volunteer> delivery;
	bool deliveryStatus;
	int deliveryTime;

public:
	Order(std::shared_ptr<Customer> customer, std::shared_ptr<Shop> shop);
	void addItem(std::shared_ptr<Item> item, int quantity);
	void removeItem(std::pair<std::shared_ptr<Item>, int>);
	void setTotalPrice(double& totalPrice);
	double getTotalPrice();
	void setDelivery(std::shared_ptr<Volunteer>volunteer);
	void setPaymentStatus(bool& paymentStatus);
	void setDeliveryStatus(bool& deliveryStatus);
	std::shared_ptr<Volunteer> getDelivery();

	//operator overloading to add prices???
	//deliverystatus::so tht volunteer can call and chg the status
	//operator overloading
	//friend
};

#endif
