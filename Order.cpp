
#include"Order.h"
#include<vector>

#include <iomanip>
#include "volunteer.h"


Order::Order()
{
}

Order::Order(std::shared_ptr<Customer> customer, std::shared_ptr<Shop> shop) {
	this->customer = customer;
	this->shop = shop;
	this->deliveryStatus = false;
	this->paymentStatus = false;
	this->delivery = nullptr;
}

void Order::addItem(std::shared_ptr<Item> item, int quantity) {
	//check item if its in the list
	auto found = std::find_if(items.begin(), items.end(), [item](const std::pair<std::shared_ptr<Item>, int>& rhs) {
		return rhs.first->getName() == item->getName();
		});
	if (found != items.end()) {
		found->second += quantity;
	}
	else { //add them into items
		items.push_back(*found);
	}

	item->subQuantity(quantity);		//subtracts the quantity of items in stock
}

void Order::removeItem(std::pair<std::shared_ptr<Item>, int>& itemReq)
{

	const int toBeReturned = itemReq.second;
	// return that quantity to the stock 
	itemReq.first->addQuantity(toBeReturned);
	itemReq.second = 0;
	const auto itemPosition = find(items.begin(), items.end(), itemReq);
	items.erase(itemPosition);

}
void Order::setTotalPrice(double totalPrice) {
	this->totalPrice = totalPrice;
}

double Order::getTotalPrice() {
	return totalPrice;
}


void Order::setDelivery(std::shared_ptr<Volunteer> volunteer) {
	delivery = volunteer;
}

void Order::setPaymentStatus(bool paymentStatus) {
	this->paymentStatus = paymentStatus;
}

void Order::setDeliveryStatus(bool deliveryStatus) {
	this->deliveryStatus = deliveryStatus;
}

std::shared_ptr<Volunteer> Order::getDelivery() {
	return delivery;
}

bool Order::getDeliveryStatus()
{
	return deliveryStatus;
}

void Order::setDeliveryTime(int deliveryTime)
{
	this->deliveryTime = deliveryTime;
}

bool Order::getPaymentStatus()
{
	return paymentStatus;
}

int Order::getDeliveryTime()
{
	return deliveryTime;
}

//operator overloading to add prices???
//deliverystatus::so tht volunteer can call and chg the status
//operator overloading
//friend