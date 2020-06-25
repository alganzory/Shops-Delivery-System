#pragma once
#include <memory>
#include <string>
#include <memory>

class Item
{

	/// Members
private:
	std::string name;
	double price{};
	int inStock{};

public:
	/// Constructors
	Item();
	Item(std::string name, double price, int inStock);

	/// Getters
	double getPrice() const;
	int getInStock() const;
	std::string getName() const;

	/// Setters
	void setPrice(double price);
	void setInStock(int inStock);

	/// Methods
	void addQuantity(int quantity);
	void subQuantity(int quantity);
	void display (int width1 = 30, int width2 =20, const char* append = "\n");
	void setName(const std::string& cs);
	// items which are similar

	/// Operators
	friend bool operator==(std::shared_ptr<Item> lhs, std::string itemName); // will be used in finding i

	
};
