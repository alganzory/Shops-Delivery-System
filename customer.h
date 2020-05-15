#pragma once
#include <string>
#include "user.h" 
class Customer:public User
{
	private:
		string healthStatus;
		Shop *availableShops[];
	public:
		Customer(string _username, string _password):User(_username,_password)
		void setHS(string hs)
		string getHS()
		void setInfo(string _name, int _age, double _balance, Location _location)
		void placeOrder(Order *_order)
		void rewardVolunteer (Volunteer *volunteer,string reward)
		//operators overloading
		//friend classes and functions
};

