#include "SO_List.h"


#include <memory>
#include <sstream>


std::fstream SO_List::dataFile;
std::string SO_List::filePath = "file.txt";
std::vector <std::shared_ptr <ShopOwner> > SO_List::SHOPOWNERS;



int SO_List::getCount()
{
	return SHOPOWNERS.size();
}

void SO_List::addShopOwner(std::shared_ptr<ShopOwner> newShopOwner)
{
	SHOPOWNERS.push_back(newShopOwner);
}

void SO_List::readFromFile()
{
	// read from the file and store in the array.
	dataFile.open(filePath, std::ios::in);
	if (!dataFile)
		std::cout << "fail to open file\n";
	
	dataFile.seekg(0, std::ios::beg);
	std::string username, password, name, location, shopname, shoplocation, itemName, empty;
	std::string item;
	int age, itemQuantity;
	double balance, price;
	
	while (dataFile)
	{
		std::getline(dataFile, username);
		std::getline(dataFile, password);
		std::getline(dataFile, name);
		dataFile >> age;
		dataFile >> balance;
		dataFile.ignore();
		std::getline(dataFile, location);
		std::getline(dataFile, shopname);
		std::getline(dataFile, shoplocation);
		std::getline(dataFile, empty);
		
	
		SHOPOWNERS.emplace_back
		(std::make_shared<ShopOwner>(username, password)
		);
		SHOPOWNERS.back()->setInfoFile(name, age, balance, location, shopname, shoplocation);

		while (getline(dataFile, item) && !item.empty()) {
			std::istringstream s(item);
			s >> itemName >> price >> itemQuantity;
			SHOPOWNERS.back()->addToStock(std::make_shared<Item>(itemName, price, itemQuantity), itemQuantity, true);
		}		
		
	}

	// enumerate the array elements and store the read into them
}

void SO_List::writeToFile()
{
	// read from the file and store in the array.
	dataFile.seekp(0, std::ios::beg);

	// enumerate the array elements and write them to the file
}
