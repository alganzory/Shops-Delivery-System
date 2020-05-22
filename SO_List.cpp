#include "SO_List.h"



std::fstream SO_List::dataFile;
std::string SO_List::filePath = "file.txt";

std::vector <std::shared_ptr <ShopOwner> > SO_List:: SHOPOWNERS = {
	// insert SHOPOWNERS here
};


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
	dataFile.seekg(0, std::ios::beg);

	// enumerate the array elements and store the read into them
}

void SO_List::writeToFile()
{
	// read from the file and store in the array.
	dataFile.seekp(0, std::ios::beg);

	// enumerate the array elements and write them to the file
}
