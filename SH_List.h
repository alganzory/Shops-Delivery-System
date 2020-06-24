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
	friend class V_List;
};

