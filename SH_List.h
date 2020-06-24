#pragma once

#include "Shop.h"
#include "SO_List.h"
#include <memory>
#include <vector>

class SH_List
{


public:
	static std::vector<std::shared_ptr<Shop> > SHOPS;


public:
	static int getCount();
	static void setList();
	static void addShop(std::shared_ptr<Shop> newShop);
	friend class V_List;
};

