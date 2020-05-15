#include<iostream>
#include"volunteer.h"

Order::Order(Customer *c,Shop *cshop){
	customer=c;
	shop=cshop;
}
void Order::addItem(Item *io, int quantity){
	item=io;
	numitem=quantity;
}
void Order::removeItem(pair<Item *_i, int quantity> item){
	//RemoveOrder();
}
void Order::setPrice(double &price){
	price+=price;
}
void Order::setDelivery(Volunteer *volunteer){
	
}

double Order::getPrice(){
	return price;
}

//bool operator>()
//operator overloading
//friend
