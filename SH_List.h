#pragma once

#include "Shop.h"
#include "SO_List.h"
#include <memory>
#include <vector>

class SH_List
{

	/// Members
public:
	static std::vector<std::shared_ptr<Shop> > SHOPS;

public:
	/// Getters
	static int getCount();

	/// Setters
	static void setList();

	/// Methods
	static void addShop(std::shared_ptr<Shop> newShop);

	/// Friend Classes
	friend class V_List;
};

