#include "O_List.h"


#include <fstream>
#include <iostream>
#include <sstream>

#include "C_List.h"
#include "SH_List.h"
#include "V_List.h"

std::string O_List::filePath = "olist.txt";
std::fstream O_List::dataFile;

void O_List::readFromFile()
{
	dataFile.open(filePath, std::ios::in);
	if (!dataFile)
		std::cout << "fail to open file\n";
	dataFile.seekg(0, std::ios::beg);
	std::string shopOwner, customer, volunteer, empty;
	int hour{}, minute{};
	std::string status;
	bool deliveryStatus, paymentStatus;
	double reward{};
	int itemIdx{}, itemQuantity{};
	std::string iteminfo;
	int depth{};
	///std::cerr << ++depth << std::endl;
	///
	while (std::getline(dataFile, shopOwner))
	{
		
		dataFile >> customer;
		dataFile >> volunteer;
		std::cerr << ++depth << std::endl;
		int customerIdx{}, shopOwnerIdx{}, volunteerIdx{};

		for (int i = 0; i < C_List::ALL_CUSTOMERS.size(); i++) {
			//std::cerr << ++depth << std::endl;
			if (C_List::ALL_CUSTOMERS[i]->getUsername() == customer) {
				customerIdx = i;
				break;
			}
		}


		for (int i = 0; i < SO_List::SHOPOWNERS.size(); i++) {
			//std::cerr << ++depth << std::endl;
			if (SO_List::SHOPOWNERS[i]->getUsername() == shopOwner) {
				shopOwnerIdx = i;
				break;
			}
		}

		if ( volunteer != "null")
			for (int i = 0; i < V_List::ALL_VOLUNTEERS.size(); i++) {
			//	std::cerr << ++depth << std::endl;
				if (V_List::ALL_VOLUNTEERS[i]->getUsername() == volunteer) {
					volunteerIdx = i;
					break;
				}
			}

		auto orderObj = std::make_shared <Order>(C_List::ALL_CUSTOMERS[customerIdx], SH_List::SHOPS[shopOwnerIdx]);
		(volunteer == "null") ? orderObj->setDelivery(nullptr) : orderObj->setDelivery(V_List::ALL_VOLUNTEERS[volunteerIdx]);

		dataFile >> hour;
		dataFile >> minute;
		orderObj->setDeliveryTime(hour,minute);
		dataFile.ignore();
		dataFile >> orderObj->orderStatus;
		dataFile >> deliveryStatus;
		orderObj->setDeliveryStatus(deliveryStatus);
		dataFile >> paymentStatus;
		orderObj->setPaymentStatus(paymentStatus);
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
		C_List::ALL_CUSTOMERS[customerIdx] ->orders.emplace_back(orderObj);
		SO_List::SHOPOWNERS[shopOwnerIdx]->orders.emplace_back(orderObj);
		if (volunteer != "null")
		V_List::ALL_VOLUNTEERS[volunteerIdx]->orders.emplace_back(orderObj);

	}
	dataFile.close();
}


void O_List::writeToFile() {
	dataFile.open(filePath, std::ios::out);
	bool isLast = false;
	if (!dataFile)
		std::cout << "fail to open file\n";
	 // std::vector <std::shared_ptr <Order> > ordersToPrint;
	int countOrders = 0;
	for (int i=0; i<C_List :: getCustomerCount();i++)
	{
		if (C_List::ALL_CUSTOMERS[i]->orders.size() == 0) continue;
		for (int j = 0;  j< C_List::ALL_CUSTOMERS[i]->orders.size(); j++)
		{
			countOrders++;
		}
	}
	
	for (int i = 0; i < C_List::getCustomerCount(); i++) {
		if (C_List::ALL_CUSTOMERS[i]->orders.size() == 0) continue;
		for (int j = 0;  j< C_List::ALL_CUSTOMERS[i]->orders.size(); j++) {
			countOrders--;
			dataFile << C_List::ALL_CUSTOMERS[i]->orders[j]->shop->getShopOwner().lock()->getUsername() << '\n';
			dataFile << C_List::ALL_CUSTOMERS[i]->orders[j]->customer->getUsername() << '\n';
			if (C_List::ALL_CUSTOMERS[i]->orders[j]->delivery != nullptr) {
				dataFile << C_List::ALL_CUSTOMERS[i]->orders[j]->delivery->getUsername() << '\n';
			}
			else {
				dataFile << "null" << '\n';
			}
			dataFile << C_List::ALL_CUSTOMERS[i]->orders[j]->deliveryTime.getHour() << '\n';
			dataFile << C_List::ALL_CUSTOMERS[i]->orders[j]->deliveryTime.getMinute() << '\n';
			dataFile << C_List::ALL_CUSTOMERS[i]->orders[j]->orderStatus << '\n';
			dataFile << C_List::ALL_CUSTOMERS[i]->orders[j]->deliveryStatus << '\n';
			dataFile << C_List::ALL_CUSTOMERS[i]->orders[j]->paymentStatus << '\n';
			dataFile << C_List::ALL_CUSTOMERS[i]->orders[j]->reward << '\n';

			auto itemsCount = C_List::ALL_CUSTOMERS[i]->orders[j]->itemsIndices.size();
			for (int k=0; k < itemsCount ; k++) {
				// writing the index 
				dataFile << C_List::ALL_CUSTOMERS[i]->orders[j]->itemsIndices[k] << " ";
				// writing the quantity
				dataFile << C_List::ALL_CUSTOMERS[i]->orders[j]->items[k].second; 
				if (k != itemsCount - 1) dataFile << '\n';
				else if (k == itemsCount - 1 && countOrders != 0) dataFile << "\n";
			}
			if (countOrders) dataFile << '\n';
		}
		
	}
	dataFile.close();
}
// for each customer we iterate over the list of orders they have and write each order to the file 
// in the same format they are being read in, thanks for watching, *sticker* you are very good (y)