#include<iostream>
#include"Item.h"
#include"Item.cpp"
#include"volunteer.h"

Order::Order(std::shared_ptr<Customer> customer, std::vector <std::shared_ptr<Shop>> shop) {
	this->customer = customer;
	this->shop = shop;
}

void Order::addItem(pair<std::shared_ptr<Item>, int quantity> items) {
	items = make_pair(item, quantity);
	//check item if its in the list
	if (items.first == std::find(itemsList.begin(), itemsList.end(), item)) {
		items.second += quantity;
	}
	else { //add them into items
		itemsList.push_back(items);
		//substracts the quantity of items in stock
		Item->subQuantity(items.second);
	}

}

void Order::removeItem(pair<std::shared_ptr<Item>, int quantity> items) {
	if (items.first == std::find(itemsList.begin(), itemList.end(), items)) {
		itemList.erase(items);
		Item->addQuantity(items.second);
	}
}
void Order::setTotalPrice(double& totalPrice) {
	this->totalPrice = totalPrice;
}

double Order::getTotalPrice() {
	return totalPrice;
}

void Order::setDelivery(Volunteer* volunteer, int deliveryTime) {

	cout << "Please enter your desirable delivery time: ";
	cin >> deliveryTime;
	if (volunteer->isAvailable(deliveryTime) == 1) {
		cout << "Your items will be delivered." << endl;
	}
	else {
		cout << "No volunteers available." << endl;
	}

}

void Order::setPaymentStatus(std::shared_ptr<Customer> customer) {
	paymentStatus = false;
	if (customer->getBalance() == 0) {
		paymentStatus = true;
	}
}

void Order::setDeliveryStatus() {
	deliveryStatus = false;
}

//operator overloading to add prices???
//set delivery status???how to do tht for true, get from volunteer??so volunteer need to add deliverystatus??
//operator overloading
//friend
