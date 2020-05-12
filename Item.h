#pragma once
#include <string>

class Item
{
private:
	std::string name;
	double price{};
	int inStock{};

public:


	Item();
	Item(std::string name, double price, int inStock);
	double getPrice() const;
	void setPrice(double price);
	
	int getInStock() const;
	void setInStock(int inStock);
	void addQuantity(int quantity);
	void subQuantity(int quantity);
};
