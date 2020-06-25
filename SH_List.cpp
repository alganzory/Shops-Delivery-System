#include "SH_List.h"

/// Members
std::vector<std::shared_ptr<Shop> > SH_List::SHOPS;
/// Getters
int SH_List::getCount()
{
	return SHOPS.size();
}
/// Setters
void SH_List::setList()
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

/*add a function to this class that takes a shared ptr of shop
as a parameterand adds it to the list of shops, it gets that parameter from the shopowner
that was just created, so that means you can do it after the setInfo function in the userflow
class, you call the addShop function from this classand you pass in the pointer that you get from
	the newly created shop owner, or you can immediately call it in the setINFO function in the shoopowner class, got it ? !*/
