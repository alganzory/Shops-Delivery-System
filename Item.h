#pragma once
#include <memory>
#include <string>
#include <memory>

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
	std::string getName() const;
	void display (int width1 = 30, int width2 =20, const char* append = "\n");
	friend bool operator==(std::shared_ptr<Item> lhs, std::string itemName); // will be used in finding i
																			  // items which are similar
};
