#include"Order.h"
#include<vector>

#include <iomanip>

#include "Helper.h"
#include "volunteer.h"
#include "Customer.h"
#include "Shop.h"


void Order::cancelOrder()
{
	customer->removeOrder(shared_from_this());
	shop->removeOrder(shared_from_this());
	for (auto& item : items) {
		removeItem(item);
	}
}

std::string Order::getDlvryAddress() const
{
	return customer->getLocation().getAddress();
}

std::string Order::getCustomerName() const
{
	return customer->getName();
}

Order::Order()
{
	orderStatus = Order::Pending;
}

Order::Order(std::shared_ptr<Customer> customer, std::shared_ptr<Shop> shop) {
	this->customer = customer;
	this->shop = shop;
	this->deliveryStatus = false;
	this->paymentStatus = false;
	this->delivery = nullptr;
	orderStatus = Order::Pending;
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
		items.push_back({ item,quantity });
		preparationStatus.push_back(false);
	}

}

void Order::removeItem(std::pair<std::shared_ptr<Item>, int>& itemReq)
{

	const auto itemPosition = find(items.begin(), items.end(), itemReq);
	items.erase(itemPosition);

}
void Order::setTotalPrice(double totalPrice) {
	this->totalPrice = totalPrice;
}

double Order::getTotalPrice() {
	double totalPrice = 0;
	for (int i = 0; i < items.size(); i++) {
		totalPrice += items[i].second * items[i].first->getPrice();
	}

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

void Order::display(bool showPreparationStatus)
{
	int counter = 0;
	std::cout << std::left << std::setw(20)
		<< "Item" << std::setw(20) << "Price"
		<< std::setw(20) << "Quantity"
		<<std::setw(10)<< "Total";
	showPreparationStatus ? std::cout << "Preparation Status" << std::endl : std::cout << std::endl;

	showPreparationStatus ? Helper::line(110) : Helper::line(70);
	for (const auto& item : items)
	{
		std::cout << ++counter << "- ";
		std::cout << std::setw(18) << item.first->getName()
			<< std::setw(20) << item.first->getPrice()
			<< std::setw(20) << item.second << std::setw(10)
			<< item.second * item.first->getPrice();
		showPreparationStatus ? std::cout <<( preparationStatus.at(counter-1)?"Prepared":"Not Prepared") << std::endl : std::cout << std::endl;
	}
}

void Order::summary(char userType)
{
	
	if (userType != 's') std::cout << std::setw(20) << shop->getName();
	if (userType == 'c')
		std::cout << std::setw(15) << getTotalPrice();
	if (userType == 'v')
		std::cout << std::setw(20) << shop->getLocation().getAddress();
	userType == 's' ? std::cout << std::setw(20) << customer->getName() : std::cout << "";
	if (userType == 'v')
		std::cout << std::setw(20) << customer->getLocation().getAddress();
	if (userType!= 'v') 
		std::cout << std::setw(20) << (paymentStatus == true ? "Paid" : "Pending")
		<< std::setw(20) << getStatus();
	if (userType != 'c') {
		std::cout << std::setw(15) << deliveryTime;
		if (userType != 'v')
			std::cout << getTotalPrice();
	}
	std::cout << '\n';
}


int Order::getOrderSize()
{
	return items.size();
}

std::pair<std::shared_ptr<Item>, int>& Order::getItem(int position)
{
	return items.at(position);
}

void Order::setShop(const std::shared_ptr<Shop>& shop)
{
	this->shop = shop;
}

void Order::setCustomer(const std::shared_ptr<Customer>& customer)
{
	this->customer = customer;
}

void Order::buyItems()
{
	for (int i = 0; i < static_cast<int>(items.size()); i++)
	{
		items[i].first->subQuantity(items[i].second);
	}
}

Order::Status Order::getStatus()
{
	return orderStatus;
}

void Order::setStatus(Status newStatus)
{
	orderStatus = newStatus;
}


std::ostream& operator<<(std::ostream& output, const Order::Status& status)
{
	const char* s = "0";
	switch (status)
	{
	case Order::Pending: s = "Pending";
		break;
	case Order::Preparing: s = "Preparing";
		break;
	case Order::VolunteerFound:  s = "Volunteer Found";
		break;
	case Order::Delivering: s = "Delivering";
		break;
	case Order::Complete: s = "Complete";
		break;
	}
	output << s;
	return output;
}

bool operator<(const std::shared_ptr<Order> lhs, const std::shared_ptr<Order> rhs)
{
	return lhs->deliveryTime < rhs->deliveryTime;
}

void Order::setPreparationStatus(int num)
{
	preparationStatus[num] = true;
	
}


bool Order::isReady()
{
	return std::find(preparationStatus.begin(),
		preparationStatus.end(), false) == preparationStatus.end();
}