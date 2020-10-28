#include "../include/SH_List.h"

/// Members
std::vector<std::shared_ptr<Shop> > SH_List::SHOPS;
/// Getters
int SH_List::getCount()
{
	return SHOPS.size();
}
/// Setters
void SH_List::readShops()
{
	SHOPS.reserve(SO_List::getCount()); 
	for (auto &shopOwner: SO_List::SHOPOWNERS)
	{
		SHOPS.push_back(shopOwner->getShopPtr());
	}
}
/// Methods
void SH_List::addShop(std::shared_ptr<Shop> newShop) {
	SHOPS.push_back(newShop);
}


