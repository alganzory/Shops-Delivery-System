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
		std::getline(dataFile, empty);
		
	
		SHOPOWNERS.emplace_back
		(std::make_shared<ShopOwner>(username, password)
		);
		SHOPOWNERS.back()->setInfoFile(name, age, balance, location, shopname, shoplocation);
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
			SHOPOWNERS.back()->addToStock(std::make_shared<Item>(itemName, price, itemQuantity), itemQuantity, true);
		}		
		std::cout << "anything " << std::endl;
	}
	dataFile.close();
	// enumerate the array elements and store the read into them
}

void SO_List::writeToFile()
{
	// read from the file and store in the array.
	std::vector<std::shared_ptr<Item>> items;
	dataFile.open(filePath,std::ios::out);
	if (!dataFile) {
		std::cout << "Fail to open file.\n";
	}
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
			dataFile << "items" << std::endl;
			//item, price stock
			items = SHOPOWNERS[i]->shop->getItems();
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