#ifndef order_H
#define order_H
#include <vector>
#include"volunteer.h"
#include"volunteer.cpp"
//not sure
#include"Item.h"
#include"Item.cpp"

class Order {
private:
	std::vector <std::pair<std::shared_ptr<Item>, int>> items;
	std::shared_ptr<Customer> customer;
	std::vector <std::shared_ptr<Shop>> shop;
	double totalPrice;
	bool paymentStatus;
	Volunteer* delivery;
	bool deliveryStatus;
	int deliveryTime;

public:
	Order(std::shared_ptr<Customer> customer, std::vector<std::shared_ptr<Shop>> shop);
	void addItem(std::pair<std::shared_ptr<Item>, int quantity>);
	void removeItem(std::pair<std::shared_ptr<Item>, int quantity>);
	void setTotalPrice(double& totalPrice);
	double getTotalPrice();
	void setDelivery(Volunteer* volunteer, int deliveryTime);
	void setPaymentStatus(std::shared_ptr<Customer> customer);
	void setDeliveryStatus(bool& deliveryStatus);

	//operator overloading to add prices???
	//deliverystatus::so tht volunteer can call and chg the status
	//operator overloading
	//friend
};

#endif
