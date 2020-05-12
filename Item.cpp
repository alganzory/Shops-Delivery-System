#include "Item.h"

Item::Item()
{
}

double Item::getPrice() const
{
	return price;
}

void Item::setPrice(double price)
{
	this->price = price;
}

void Item::setInStock(int inStock)
{
	this->inStock = inStock;
}

Item::Item(std::string name, double price, int inStock) :
	name(name),
	price(price),
	inStock(inStock)
{
}

void Item::addQuantity(const int quantity)
{
	inStock += quantity;
}

int Item::getInStock() const
{
	return inStock;
}

void Item::subQuantity(const int quantity)
{
	inStock -= quantity;
}
