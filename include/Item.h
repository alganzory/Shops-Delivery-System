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
	/**
	 * \brief : in stock quantity
	 */
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
	/**
	 * \brief : used to display item in style
	 * \param width1 width between name and price
	 * \param width2 width between price and quantity
	 * \param append what to add at the end of the line
	 */
	void display (int width1 = 30, int width2 =20, const char* append = "\n");
	void setName(const std::string& cs);


	/// Operators
	/**
	 * \brief : used to find an item using the name
	 * \param lhs : item to compare with
	 * \param itemName : name of item
	 * \return 
	 */
	friend bool operator==(std::shared_ptr<Item> lhs, std::string itemName); 

	
};
