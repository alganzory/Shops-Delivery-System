#include<iostream>
#include"Item.h"
#include"Customer.h"
#include"Shop.h"
#include"volunteer.h"
#include"order.h"
#include<vector>
#include<iterator>

Order::Order(std::shared_ptr<Customer> customer, std::shared_ptr<Shop> shop) {
	this->customer = customer;
	this->shop = shop;
}

void Order::addItem(std::shared_ptr<Item> item, int quantity) {
	std::pair<std::shared_ptr<Item>, int> newItem = std::make_pair(item, quantity);
	//check item if its in the list
	auto found = std::find_if(items.begin(), items.end(), [item](const std::pair<std::shared_ptr<Item>, int>& newItem) {
		return newItem.first->getName() == item->getName();
		});
	if (found != items.end()) {
		newItem.second += quantity;
	}
	else { //add them into items
		items.push_back(newItem);
	}

	item->subQuantity(newItem.second);		//substracts the quantity of items in stock
}

void Order::removeItem(std::pair<std::shared_ptr<Item>, int> theItem) {
	std::shared_ptr<Item> item;
	int quantity;
	auto found = std::find_if(items.begin(), items.end(), [item](const std::pair<std::shared_ptr<Item>, int>& theItem) {
		return theItem.first->getName() == item->getName();
		});
	if (found != items.end()) {
		std::vector <std::pair<std::shared_ptr<Item>, int>>::iterator itemToRemove;
		itemToRemove = found;
		items.erase(itemToRemove);
		item->addQuantity(theItem.second);
	}
}
void Order::setTotalPrice(double& totalPrice) {
	this->totalPrice = totalPrice;
}

double Order::getTotalPrice() {
	return totalPrice;
}

void Order::setDelivery(std::shared_ptr<Volunteer> volunteer) {
	delivery = volunteer;
}

void Order::setPaymentStatus(bool& paymentStatus) {
	this->paymentStatus = paymentStatus;
}

void Order::setDeliveryStatus(bool& deliveryStatus) {
	this->deliveryStatus = deliveryStatus;
}

std::shared_ptr<Volunteer> Order::getDelivery() {
	return delivery;
}

//operator overloading to add prices???
//deliverystatus::so tht volunteer can call and chg the status
//operator overloading
//friend
