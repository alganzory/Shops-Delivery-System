#ifndef order_H
#define order_H


class Order{
	private:
		pair <Item *i, int numitem> items[];
		Customer *customer;
		Shop *shop;
		double price;
		bool paymentStatus;
		Volunteer *delivery;
		
	public:
		Order(Customer *c,Shop *cshop);
		void addItem(Item *io, int quantity);
		void removeItem(pair<Item *_i, int quantity> item);
		void setPrice(double &price);
		void setDelivery(Volunteer *volunteer);
		double getPrice();
		//bool operator>()
		//operator overloading
		//friend
}; 

#endif
