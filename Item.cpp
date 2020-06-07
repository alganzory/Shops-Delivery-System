#include "Item.h"

#include <iomanip>
#include <iostream>

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

std::string Item::getName() const
{
	return name;
}

void Item::display(int width1, int width2, const char* append)
{
	std::cout << std::left << std::setw(width1) << name
		<< std::setw(width2) << price << inStock << append;
}

void Item::setName(const std::string& cs)
{
	name = cs;
}


bool operator==(std::shared_ptr<Item> lhs, std::string itemName)
{
	return lhs->name == itemName;
}
