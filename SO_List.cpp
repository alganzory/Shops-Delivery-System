#include "SO_List.h"


#include <memory>
#include <sstream>

/// Members
std::fstream SO_List::dataFile;
std::string SO_List::filePath = "file.txt";
std::vector <std::shared_ptr <ShopOwner> > SO_List::SHOPOWNERS;


/// Getters
int SO_List::getCount()
{
	return SHOPOWNERS.size();
}

void SO_List::setFilePath(const char* fP)
{
	filePath = fP;
}

/// Methods
void SO_List::addShopOwner(std::shared_ptr<ShopOwner> newShopOwner)
{
	SHOPOWNERS.push_back(newShopOwner);
}

void SO_List::readShopOwners()
{
	// read from the file and store in the array.
	dataFile.open(filePath, std::ios::in);
	if (!dataFile)
		throw filePath.c_str();
	
	dataFile.seekg(0, std::ios::beg);
	std::string username, password, name, location, shopname, shoplocation, itemName, empty;
	std::string item;
	int age, itemQuantity;
	double balance, price;
	int startHour, endHour;
	
	while (std::getline(dataFile, username))
	{
		std::getline(dataFile, password);
		std::getline(dataFile, name);
		dataFile >> age;
		dataFile >> balance;
		dataFile.ignore();
		std::getline(dataFile, location);
		std::getline(dataFile, shopname);
		std::getline(dataFile, shoplocation);
		dataFile >> startHour;
		dataFile >> endHour;
		dataFile.ignore();
		std::getline(dataFile, empty);
		
	
		SHOPOWNERS.emplace_back
		(std::make_shared<ShopOwner>(username, password)
		);
		SHOPOWNERS.back()->setInfoFile(name, age, balance, location, shopname, shoplocation,startHour,endHour);
		char isBlank;
		while (getline(dataFile, item)) {
			if (item.empty())
			{
				isBlank = dataFile.peek();
				if (isBlank != '\n') break;
				else if (isBlank == '\n') continue;
			}
			std::istringstream s(item);
			std::getline(s, itemName, ',');
			s  >> price >> itemQuantity;
			SHOPOWNERS.back()->shop->items.emplace_back(std::make_shared<Item>(itemName,price,itemQuantity));
		}		
	}
	dataFile.close();
	// enumerate the array elements and store the read into them
}

void SO_List::writeShopOwners()
{
	dataFile.open(filePath,std::ios::out);
	if (!dataFile)
		throw filePath.c_str();
	else {

		for (int i = 0; i < getCount(); i++) {
			dataFile << SHOPOWNERS[i]->getUsername() << std::endl;
			dataFile << SHOPOWNERS[i]->password << std::endl;
			dataFile << SHOPOWNERS[i]->getName() << std::endl;
			dataFile << SHOPOWNERS[i]->getAge() << std::endl;
			dataFile << SHOPOWNERS[i]->getBalance() << std::endl;
			Location shopOwnerAddress = SHOPOWNERS[i]->getLocation();
			dataFile << shopOwnerAddress.getAddress() << std::endl;
			dataFile << SHOPOWNERS[i]->getShopName() << std::endl;
			dataFile << SHOPOWNERS[i]->shop->getLocation().getAddress() << std::endl;
			dataFile << SHOPOWNERS[i]->shop->getAvailableTimes().first.getHour() << " "
				<< SHOPOWNERS[i]->shop->getAvailableTimes().second.getHour() << std::endl;
			dataFile << "items" << std::endl;
			//item, price stock
			std::vector<std::shared_ptr<Item>> items = SHOPOWNERS[i]->shop->getItems();
			bool isLast = (i == getCount()-1);
			for (int j = 0; j < items.size(); j++) {
				dataFile << items[j]->getName() << ", ";
				dataFile << items[j]->getPrice() << " ";
				dataFile << items[j]->getInStock() ;
				if (j!= items.size()-1 || !isLast) 
					dataFile << std::endl;
			}
			if (!isLast)  dataFile<< std::endl;
		}
	}
	dataFile.close();
	// enumerate the array elements and write them to the file
}