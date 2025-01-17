#include"../include/Order.h"
#include<vector>

#include <iomanip>
#include <algorithm>
#include "../include/Helper.h"
#include "../include/Volunteer.h"
#include "../include/Customer.h"
#include "../include/Shop.h"
#include "../include/ShopOwner.h"

/// Constructors
Order::Order()
{
	orderStatus = Pending;
	reward = 0;
	this->deliveryStatus = false;
	this->paymentStatus = true;
	this->overdue = false;
	this->contactless = false;
}

Order::Order(std::shared_ptr<Customer> customer, std::shared_ptr<Shop> shop)
{
	this->customer = customer;
	this->shop = shop;
	this->deliveryStatus = false;
	this->paymentStatus = false;
	this->delivery = nullptr;
	orderStatus = Order::Pending;
	reward = 0;
	this->overdue = false;
	this->contactless = false;
}

/// Getters
std::string Order::getDlvryAddress() const
{
	return customer->getLocation().getAddress();
}

std::string Order::getCustomerName() const
{
	return customer->getName();
}

bool Order::isEmpty()
{
	return items.empty();
}

double Order::getTotalPrice()
{
	double totalPrice = 0;
	for (int i = 0; i < items.size(); i++)
	{
		totalPrice += items[i].second * items[i].first->getPrice();
	}
	return totalPrice;
}

std::shared_ptr<Volunteer> Order::getDelivery()
{
	return delivery;
}

bool Order::getDeliveryStatus()
{
	return deliveryStatus;
}

bool Order::getPaymentStatus()
{
	return paymentStatus;
}

Time Order::getDeliveryTime()
{
	return deliveryTime;
}

int Order::getOrderSize()
{
	return items.size();
}

bool Order::isReady()
{
	return std::find(preparationStatus.begin(),
	                 preparationStatus.end(), false) == preparationStatus.end();
}

double Order::getReward()
{
	return this->reward;
}

bool Order::getContactlessDlvr()
{
	return contactless;
}

std::pair<std::shared_ptr<Item>, int>& Order::getItem(int position)
{
	return items.at(position);
}

Order::Status Order::getStatus()
{
	return orderStatus;
}

std::shared_ptr<Shop> Order::getShop()
{
	return shop;
}

/// Setters

void Order::setStatus(Status newStatus)
{
	orderStatus = newStatus;
}

void Order::setOverdueStatus(bool overdueStatus)
{
	overdue = overdueStatus;
}

void Order::setTotalPrice(double totalPrice)
{
	this->totalPrice = totalPrice;
}

void Order::setDelivery(std::shared_ptr<Volunteer> volunteer)
{
	delivery = volunteer;
}

void Order::setPaymentStatus(bool paymentStatus)
{
	this->paymentStatus = paymentStatus;
}

void Order::setDeliveryStatus(bool deliveryStatus)
{
	this->deliveryStatus = deliveryStatus;
}

void Order::setDeliveryTime(int hour, int minute)
{
	try
	{
		this->deliveryTime.setTime(hour, minute);
	}
	catch (const char*)
	{
		throw;
	}
}

void Order::setShop(std::shared_ptr<Shop> shop)
{
	this->shop = shop;
}

void Order::setCustomer(std::shared_ptr<Customer> shared)
{
	this->customer = shared;
}

void Order::setPreparationStatus(int num)
{
	preparationStatus[num] = true;
}

void Order::setReward(double reward)
{
	this->reward = reward;
}

void Order::setContactlessDlvr(bool contactless)
{
	this->contactless = contactless;
}

/// Methods
void Order::cancelOrder()
{
	customer->addBalance(getTotalPrice());
	shop->getShopOwner().lock()->subtractBalance(getTotalPrice());
	customer->addBalance(reward);

	for (int i = 0; i < items.size(); i++)
	{
		items[i].first->addQuantity(items[i].second);
	}

	setStatus(Order::Cancelled);
}

void Order::addItem(std::shared_ptr<Item> item, int quantity)
{
	//check item if its in the list
	auto found = std::find_if(items.begin(), items.end(), [item](const std::pair<std::shared_ptr<Item>, int>& rhs) {
		return rhs.first->getName() == item->getName();
		});
	if (found != items.end())
	{
		found->second += quantity;
	}
	else
	{
		//add them into items
		items.push_back({item, quantity});
		preparationStatus.push_back(false);
	}
}

void Order::addItem(int itemIdx, int quantity)
{
	//// we get the item by its index from the shop list of items
	auto found = std::find_if(items.begin(), items.end(),
	                          [itemIdx, this](const std::pair<std::shared_ptr<Item>, int>& rhs)
	                          {
		                          return rhs.first->getName() == shop->items[itemIdx]->getName();
	                          });
	if (found != items.end())
	{
		if (found->second + quantity > found->first->getInStock())
			throw (found->first->getInStock() - found->second); // the max he can ask for
		found->second += quantity;
	}
	else
	{
		//add them into items
		if (quantity > shop->items[itemIdx]->getInStock())
			throw (shop->items[itemIdx]->getInStock()); // throw the max they can enter
		items.push_back({shop->items[itemIdx], quantity});
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
	preparationStatus.erase(preparationStatus.begin() + distance);
}

void Order::display(bool showPreparationStatus)
{
	int counter = 0;
	std::cout << std::left << std::setw(4) << "No." << std::setw(18)
		<< "Item" << std::setw(20) << "Price"
		<< std::setw(20) << "Quantity"
		<< std::setw(10) << "Total";
	showPreparationStatus ? std::cout << "Preparation Status" << std::endl : std::cout << std::endl;

	showPreparationStatus ? Helper::line(110) : Helper::line(70);
	for (const auto& item : items)
	{
		std::cout << std::setw(4) << ++counter;
		std::cout << std::setw(18) << item.first->getName()
			<< std::setw(20) << item.first->getPrice()
			<< std::setw(20) << item.second << std::setw(10)
			<< item.second * item.first->getPrice();
		showPreparationStatus
			? std::cout << (preparationStatus.at(counter - 1) ? "Prepared" : "Not Prepared") << std::endl
			: std::cout << std::endl;
	}
}

void Order::summary(char userType)
{
	if (userType != 's') std::cout << std::setw(20) << shop->getName();
	if (userType == 'c')
		std::cout << std::setw(15) << getTotalPrice();
	if (userType == 'v')
	{
		if (shop->getLocation().getAddress().length() <= 18)
		{
			std::cout << std::setw(20) << shop->getLocation().getAddress();
		}
		else
		{
			for (int i = 0; i < 15; i++)
			{
				std::cout << shop->getLocation().getAddress().at(i);
			}
			std::cout << "...  ";
		}
	}
	userType == 's' ? std::cout << std::setw(20) << customer->getName() : std::cout << "";
	if (userType == 'v')
	{
		if (customer->getLocation().getAddress().length() <= 18)
		{
			std::cout << std::setw(20) << customer->getLocation().getAddress();
		}
		else
		{
			for (int i = 0; i < 15; i++)
			{
				std::cout << customer->getLocation().getAddress().at(i);
			}
			std::cout << "...  ";
		}

	}
	if (userType != 'v')
	{

		std::cout << std::setw(17)
			<< (orderStatus != Status::Cancelled
				    ? (paymentStatus == true ? "Paid" : "Pending")
				    : (paymentStatus == true ? "Refunded" : "Not paid"));

		if ((getStatus() == Order::Cancelled && overdue) || (getStatus() == Order::Preparing && isOverdue()))
		{
			std::cout << std::setw(10) << getStatus() << std::setw(13) << "(overdue)";
		}
		else
			std::cout << std::setw(23) << getStatus();
	}
	if (userType != 'c')
	{
		std::cout << std::setw(15) << deliveryTime;


		if (userType != 'v')
		{
			std::cout << std::setw(20);
			std::cout << getTotalPrice();
		}
	}
	if (userType != 'c')
	{
		std::cout << std::setw(25);
		if (customer->getHealthStatus() == Customer::Healthy)
		{
			std::cout << "Healthy";
		}
		else if (customer->getHealthStatus() == Customer::ShowSymptoms)
		{
			std::cout << "Has symptoms";
		}
		else if (customer->getHealthStatus() == Customer::Infected)
		{
			std::cout << "Infected";
		}
	}
	std::cout << '\n';
}

void Order::buyItems()
{
	for (int i = 0; i < static_cast<int>(items.size()); i++)
	{
		items[i].first->subQuantity(items[i].second);
	}
}

void Order::reorder(const std::shared_ptr<Order> order)
{
	this->customer = order->customer;
	this->shop = order->getShop();

	items.clear();
	itemsIndices.clear();
	preparationStatus.clear();
	for (int i = 0; i < order->getOrderSize(); i++)
	{
		items.push_back({shop->items[order->itemsIndices[i]], order->items[i].second});
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

void Order::reduceItem(std::pair<std::shared_ptr<Item>, int>& itemReq, int quantity)
{
	itemReq.second -= quantity;
	if (itemReq.second == 0)
	{
		std::cout << "You have 0 items. Order will be automatically removed.\n";
		removeItem(itemReq);
	}
}

/// Operators
std::ostream& operator<<(std::ostream& output, const Order::Status& status)
{
	const char* s = "0";
	switch (status)
	{
	case Order::Pending: s = "Pending";
		break;
	case Order::Preparing: s = "Preparing";
		break;
	case Order::VolunteerFound: s = "Volunteer Found";
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
	std::getline(input, s);

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

	if (lhs->getStatus() == rhs->getStatus())
	{
		if (lhs->deliveryTime == rhs->deliveryTime)
			return rhs->customer->getHealthStatus() < lhs->customer->getHealthStatus();
		return lhs->deliveryTime < rhs->deliveryTime;
	}
	else 
		return lhs->getStatus() < rhs->getStatus();
	
}
