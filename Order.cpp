#include"Order.h"
#include<vector>

#include <iomanip>

#include "Helper.h"
#include "Volunteer.h"
#include "Customer.h"
#include "Shop.h"


void Order::cancelOrder()
{
	/*while (!items.empty())
	{
		items.back().first->addQuantity(items.back().second);
		items.pop_back();
		itemsIndices.pop_back();
	}*/
	for (int i = 0; i < items.size(); i++)
	{
		items[i].first->addQuantity(items[i].second);
	}
	//customer->removeOrder(shared_from_this());
	if (getPaymentStatus())
	{
		customer->setBalance(customer->getBalance() + reward);
	}
	
	//shop->removeOrder(shared_from_this());
	setStatus( Order::Cancelled);

	
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
	reward = 0;
	overdue = FALSE;
}

Order::Order(std::shared_ptr<Customer> customer, std::shared_ptr<Shop> shop) {
	this->customer = customer;
	this->shop = shop;
	this->deliveryStatus = false;
	this->paymentStatus = false;
	this->delivery = nullptr;
	orderStatus = Order::Pending;
	reward = 0;
	overdue = FALSE;
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

void Order::addItem(int itemIdx, int quantity)
{
	//// we get the item by its index from the shop list of items
	auto found = std::find_if(items.begin(), items.end(), [itemIdx, this](const std::pair<std::shared_ptr<Item>, int>& rhs) {
		return rhs.first->getName() == shop->items[itemIdx]->getName();
		});
	if (found != items.end()) {
		found->second += quantity;
	}
	else { //add them into items
		items.push_back({ shop->items[itemIdx],quantity });
		preparationStatus.push_back(false);
		itemsIndices.push_back(itemIdx);
	}
}

void Order::removeItem(std::pair<std::shared_ptr<Item>, int>& itemReq)
{

	const auto itemPosition = find(items.begin(), items.end(), itemReq);
	int distance = itemPosition - items.begin();
	items.erase(itemPosition);
	itemsIndices.erase(itemsIndices.begin() + distance);

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

void Order::setDeliveryTime(int hour,int minute)
{
	try {
		this->deliveryTime.setTime(hour, minute);
	}
	catch (const char* ){
		throw;
	}
}

bool Order::getPaymentStatus()
{
	return paymentStatus;
}

Time Order::getDeliveryTime()
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
	if (userType != 'v') {
		std::cout << std::setw(20)
			<< (orderStatus != Status::Cancelled ? (paymentStatus == true ? "Paid" : "Pending") : (paymentStatus == true ? "Refunded" : "Not paid"));
			
		if ((getStatus() == Order::Preparing && isOverdue()) || getStatus() == Order::Cancelled && overdue)
		{
			std::cout <<std::setw(10) << getStatus() << std::setw(15) << "(overdue)";
		}
		else
			std::cout << std::setw(25) << getStatus();
	}
	if (userType != 'c') {
		std::cout << deliveryTime
			<< std::setw(5)<<std::right;
		
		if (userType != 'v') {
			std::cout << std::setw(13);
			std::cout << getTotalPrice();
			std::cout << std::left;
		}
	}
	if (userType != 'c') {
		std::cout << std::left;
		std::cout << std::setw(18) << " ";
		
		std::cout << std::setw(25);
		if (customer->getHealthStatus() == Customer::Healthy) {
			std::cout << "Healthy";
		}
		else if (customer->getHealthStatus() == Customer::ShowSymptoms) {
			std::cout << "Has symptoms";
		}
		else if (customer->getHealthStatus() == Customer::Infected) {
			std::cout << "Infected";
		}

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

void Order::setShop(std::shared_ptr<Shop> shop)
{
	this->shop = shop;
}

void Order::setCustomer(std::shared_ptr<Customer> shared)
{
	this->customer = shared;
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
	case Order::Cancelled: s = "Cancelled";
		break;
	}
	output << s;
	return output;
}

std::istream& operator>>(std::istream& input, Order::Status& status)
{
	std::string s;
	input >> s;

	if (s == "Pending")
		status = Order::Pending;
	else if (s == "Preparing")
		status = Order::Preparing;
	else if (s == "Volunteer Found")
		status = Order::VolunteerFound;
	else if (s == "Delivering")
		status = Order::Delivering;
	else if (s == "Complete")
		status = Order::Complete;
	else
		status = Order::Cancelled;
	
	return input;
}

bool operator<(const std::shared_ptr<Order>& lhs, const std::shared_ptr<Order>& rhs)
{
	if (lhs->deliveryTime == rhs->deliveryTime)
		return lhs->customer->getHealthStatus() < rhs->customer->getHealthStatus();
	else {
		return lhs->deliveryTime < rhs->deliveryTime;
	}	
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

void Order::setReward(double reward) 
{
	this->reward = reward;
}

double Order::getReward()
{
	return this->reward;
}

void Order::setContactlessDlvr(bool contactless) {
	this->contactless = contactless;
}

bool Order::getContactlessDlvr() {
	return contactless;
}

void Order::operator = ( Order& order) {
	this->customer = order.customer;
	shop->setShopOwner(order.shop->getShopOwner());
	
	
	for (int i = 0; i < order.getOrderSize(); i++)
	{
		items.push_back({ shop->items[order.itemsIndices[i]],order.items[i].second });
		preparationStatus.push_back(false);
		itemsIndices.push_back(order.itemsIndices[i]);
	}
}

std::shared_ptr<Shop> Order::getShop()
{
	return shop;
}

void Order::reorder(const std::shared_ptr <Order> order)
{
	this->customer = order->customer;
	this->shop=order->getShop();

	items.clear();
	itemsIndices.clear();
	preparationStatus.clear();
	for (int i = 0; i < order->getOrderSize(); i++)
	{
		items.push_back({ shop->items[order->itemsIndices[i]],order->items[i].second });
		preparationStatus.push_back(false);
		itemsIndices.push_back(order->itemsIndices[i]);
	}
}

bool Order::isOverdue()
{
	if (getDeliveryTime().getTimeDiff().second < 0)
	{
		overdue = TRUE;	
	}
	return overdue;
}