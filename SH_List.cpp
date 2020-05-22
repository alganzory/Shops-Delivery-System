#include "SH_List.h"

std::vector<std::shared_ptr<Shop> > SH_List::SHOPS;

int SH_List::getCount()
{
	return SHOPS.size();
}

void SH_List::setList()
{
	SHOPS.reserve(SO_List::getCount());
	for (auto &shopOwner: SO_List::SHOPOWNERS)
	{
		SHOPS.push_back(shopOwner->getShopPtr());
	}
}
