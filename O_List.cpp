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
	while (!dataFile.eof())
	{
		dataFile >> shopOwner;
		dataFile >> customer;
		dataFile >> volunteer;
		
		int customerIdx{}, shopOwnerIdx{}, volunteerIdx{};

		for (int i = 0; i < C_List::ALL_CUSTOMERS.size(); i++) {
			if (C_List::ALL_CUSTOMERS[i]->getName() == customer) {
				customerIdx = i;
				break;
			}
		}


		for (int i = 0; i < SO_List::SHOPOWNERS.size(); i++) {
			if (SO_List::SHOPOWNERS[i]->getName() == shopOwner) {
				shopOwnerIdx = i;
				break;
			}
		}

		if ( volunteer != "null")
			for (int i = 0; i < V_List::ALL_VOLUNTEERS.size(); i++) {
				if (V_List::ALL_VOLUNTEERS[i]->getName() == volunteer) {
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
	
}
