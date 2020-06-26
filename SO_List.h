#pragma once
#include "ShopOwner.h"
#include <fstream>
#include <memory>
#include <string>
#include <vector>

class SO_List
{
	/// Members
private:

	static std::fstream dataFile;
	static std::string filePath;

public:
	/**
	 * \brief :list of all shop owners registered
	 */
	static std::vector<std::shared_ptr<ShopOwner>> SHOPOWNERS;

public:
	
	/// Getters
	static int getCount();

	/// Setters
	static void setFilePath(const char* fP);
	
	/// Methods
	static void addShopOwner(std::shared_ptr<ShopOwner> newShopOwner);
	static void readShopOwners();
	static void writeShopOwners();
};
