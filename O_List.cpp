#include "O_List.h"


#include <fstream>
#include <iostream>
#include <sstream>

#include "C_List.h"
#include "SH_List.h"
#include "V_List.h"

/// Members
std::string O_List::filePath = "olist.txt";
std::fstream O_List::dataFile;

void O_List::setFilePath(const char* fP)
{
	filePath = fP;
}

/// Methods
void O_List::readOrders()
{
	dataFile.open(filePath, std::ios::in);
	if (!dataFile)
		throw filePath.c_str();
	dataFile.seekg(0, std::ios::beg);
	std::string shopOwner, customer, volunteer, empty;
	int hour{}, minute{};
	std::string status;
	bool deliveryStatus, paymentStatus, overdue, contactless;
	double reward{};
	int itemIdx{}, itemQuantity{};
	std::string iteminfo;
	int depth{};
	while (std::getline(dataFile, shopOwner))
	{
		
		dataFile >> customer;
		dataFile >> volunteer;
		int customerIdx{}, shopOwnerIdx{}, volunteerIdx{};

		for (auto i = 0; i < C_List::CUSTOMERS.size(); i++) {
			if (C_List::CUSTOMERS[i]->getUsername() == customer) {
				customerIdx = i;
				break;
			}
		}


		for (int i = 0; i < SO_List::SHOPOWNERS.size(); i++) {
			if (SO_List::SHOPOWNERS[i]->getUsername() == shopOwner) {
				shopOwnerIdx = i;
				break;
			}
		}

		if ( volunteer != "null")
			for (int i = 0; i < V_List::VOLUNTEERS.size(); i++) {
				if (V_List::VOLUNTEERS[i]->getUsername() == volunteer) {
					volunteerIdx = i;
					break;
				}
			}

		auto orderObj = std::make_shared <Order>(C_List::CUSTOMERS[customerIdx], SH_List::SHOPS[shopOwnerIdx]);
		(volunteer == "null") ? orderObj->setDelivery(nullptr) : orderObj->setDelivery(V_List::VOLUNTEERS[volunteerIdx]);

		dataFile >> hour;
		dataFile >> minute;
		orderObj->setDeliveryTime(hour,minute);
		dataFile.ignore();
		dataFile >> orderObj->orderStatus;
		dataFile >> deliveryStatus;
		orderObj->setDeliveryStatus(deliveryStatus);
		dataFile >> paymentStatus;
		orderObj->setPaymentStatus(paymentStatus);
		dataFile >> overdue;
		orderObj->setOverdueStatus(overdue);
		dataFile >> contactless;
		orderObj->setContactlessDlvr(contactless);
		dataFile >> reward;
		dataFile.ignore();
		orderObj->setReward(reward);

		
		while (getline(dataFile,iteminfo) && iteminfo != "")
		{
			std::stringstream inputStream(iteminfo);
			inputStream >> itemIdx;
			inputStream >> itemQuantity;

			orderObj->addItem(itemIdx, itemQuantity);
		}
		C_List::CUSTOMERS[customerIdx] ->orders.emplace_back(orderObj);
		SO_List::SHOPOWNERS[shopOwnerIdx]->orders.emplace_back(orderObj);
		if (volunteer != "null")
		V_List::VOLUNTEERS[volunteerIdx]->orders.emplace_back(orderObj);

	}
	dataFile.close();
}


void O_List::writeOrders() {
	dataFile.open(filePath, std::ios::out);
	if (!dataFile)
		throw filePath.c_str();

	 
	int countOrders = 0;
	for (int i=0; i<C_List :: getCustomerCount();i++)
	{
		if (!C_List::CUSTOMERS[i]->orders.empty()) continue;
		for (int j = 0;  j< C_List::CUSTOMERS[i]->orders.size(); j++)
		{
			countOrders++;
		}
	}
	
	for (int i = 0; i < C_List::getCustomerCount(); i++) {
		if (C_List::CUSTOMERS[i]->orders.empty()) continue;
		for (int j = 0;  j< C_List::CUSTOMERS[i]->orders.size(); j++) {
			countOrders--;
			dataFile << C_List::CUSTOMERS[i]->orders[j]->shop->getShopOwner().lock()->getUsername() << '\n';
			dataFile << C_List::CUSTOMERS[i]->orders[j]->customer->getUsername() << '\n';
			if (C_List::CUSTOMERS[i]->orders[j]->delivery != nullptr) {
				dataFile << C_List::CUSTOMERS[i]->orders[j]->delivery->getUsername() << '\n';
			}
			else {
				dataFile << "null" << '\n';
			}
			dataFile << C_List::CUSTOMERS[i]->orders[j]->deliveryTime.getHour() << '\n';
			dataFile << C_List::CUSTOMERS[i]->orders[j]->deliveryTime.getMinute() << '\n';
			dataFile << C_List::CUSTOMERS[i]->orders[j]->orderStatus << '\n';
			dataFile << C_List::CUSTOMERS[i]->orders[j]->deliveryStatus << '\n';
			dataFile << C_List::CUSTOMERS[i]->orders[j]->paymentStatus << '\n';
			dataFile << C_List::CUSTOMERS[i]->orders[j]->overdue << '\n';
			dataFile << C_List::CUSTOMERS[i]->orders[j]->contactless << '\n';
			dataFile << C_List::CUSTOMERS[i]->orders[j]->reward << '\n';

			auto itemsCount = C_List::CUSTOMERS[i]->orders[j]->itemsIndices.size();
			for (int k=0; k < itemsCount ; k++) {
				// writing the index 
				dataFile << C_List::CUSTOMERS[i]->orders[j]->itemsIndices[k] << " ";
				// writing the quantity
				dataFile << C_List::CUSTOMERS[i]->orders[j]->items[k].second; 
				if (k != itemsCount - 1) dataFile << '\n';
				else if (k == itemsCount - 1 && countOrders != 0) dataFile << "\n";
			}
			if (countOrders) dataFile << '\n';
		}
		
	}
	dataFile.close();
}
