#include<iostream>
//#include"Item.h"		//not sure
//#include"Item.cpp"		//not sure
#include"volunteer.h"
#include"order.h"
#include<vector>

Order::Order(std::shared_ptr<Customer> customer, std::vector <std::shared_ptr<Shop>> shop) {
	this->customer = customer;
	this->shop = shop;
}

void Order::addItem(std::pair<std::shared_ptr<Item>, int quantity> items) {
	items = std::make_pair(item, quantity);
	//check item if its in the list
	if (items.first == std::find(itemsList.begin(), itemsList.end(), item)) {
		items.second += quantity;
	}
	else { //add them into items
		itemsList.push_back(items);
		//substracts the quantity of items in stock
		Item.subQuantity(items.second);
	}

}

void Order::removeItem(std::pair<std::shared_ptr<Item>, int quantity> items) {
	if (items.first == std::find(itemsList.begin(), itemList.end(), items)) {
		itemList.erase(items);
		Item.addQuantity(items.second);
	}
}
void Order::setTotalPrice(double& totalPrice) {
	this->totalPrice = totalPrice;
}

double Order::getTotalPrice() {
	return totalPrice;
}

void Order::setDelivery(Volunteer* volunteer, int deliveryTime) {

	std::cout << "Please enter your desirable delivery time: ";
	std::cin >> deliveryTime;
	if (volunteer->isAvailable(deliveryTime) == 1) {
		std::cout << "Your items will be delivered." << std::endl;
	}
	else {
		std::cout << "No volunteers available." << std::endl;
	}

}

void Order::setPaymentStatus(std::shared_ptr<Customer> customer) {
	paymentStatus = false;
	if (customer.getBalance() == 0) {
		paymentStatus = true;
	}
}

void Order::setDeliveryStatus(bool& deliveryStatus) {
	deliveryStatus = false;
}

//operator overloading to add prices???
//deliverystatus::so tht volunteer can call and chg the status
//operator overloading
//friend
