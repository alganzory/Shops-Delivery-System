#ifndef order_H
#define order_H
#include <vector>

class Order {
private:
	std::vector <pair<shared_ptr<Item>, int>> items;
	std::shared_ptr<Customer> customer;
	std::vector <std::shared_ptr<Shop>> shop;
	double totalPrice;
	bool paymentStatus;
	Volunteer* delivery;
	bool deliveryStatus;
	int deliveryTime;

public:
	Order(std::shared_ptr<Customer> customer, std::vector <std::shared_ptr<Shop>> shop);
	void addItem(pair<std::shared_ptr<Item>, int quantity>);
	void removeItem(pair<std::shared_ptr<Item>, int quantity>);
	void setTotalPrice(double& totalPrice);
	double getTotalPrice();
	void setDelivery(Volunteer* volunteer, int deliveryTime);
	void setPaymentStatus(std::shared_ptr<Customer> customer);
	void setDeliveryStatus();
	//operator overloading to add prices???
	//set delivery status???how to do tht for true, get from volunteer??so volunteer need to add deliverystatus??
	//operator overloading
	//friend
};

#endif
