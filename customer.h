#pragma once
#include <string>
#include <vector>
#include "user.h" 
class Customer:public User
{
	private:
		string healthStatus;
		vector <shared_ptr<Shop>> availableShops[];
		shared_ptr <Order> cart;
	public:
		Customer(string _username, string _password):User(_username,_password);
		void setHealthStatus(string hs);
		string getHealthStatus();
		void setInfo(string _name, int _age, double _balance, Location _location);
		void placeOrder();
		void rewardVolunteer (Volunteer *volunteer,double reward);
		//operators overloading
		//friend classes and functions
};

