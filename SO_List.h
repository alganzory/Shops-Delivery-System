#pragma once
#include "ShopOwner.h"
#include <fstream>
#include <memory>
#include <string>
#include <vector>

class SO_List
{


public:
	static std::vector <std::shared_ptr <ShopOwner> > SHOPOWNERS;
	static std::fstream dataFile;
	static std::string filePath;

public:
	static int getCount();
	static void addShopOwner(std::shared_ptr <ShopOwner> newShopOwner);
	static void readFromFile();
	static void writeToFile();	
	
};

