#include<iostream>
#include"volunteer.h"


Volunteer::Volunteer(string usernamev, string passwordv) :User(usernamev, passwordv) {
        username = usernamev;
        password = passwordv;
    }
void Volunteer::setTransport(string& transport) {
        transportation = transport;
    }
void Volunteer::setrewards(double& rewards[]) {
}
string Volunteer::gettransport() {
        return transportation;
}
void Volunteer::setInfo(string namev, int agev, double balancev, Location locationv) {
        name = namev;
        
        age = agev;
        
        balance = balancev;
        
        location = locationv;
        
}
bool Volunteer::IsAvailable(int hr,int m) {
        bool status = true;
        availableTimes = make_pair(hr, m);
        //if 
        return status;
}
void Volunteer::registerToShop(Shop* shop) {
        shops = new Shop registeredShops[];
    }
void Volunteer::respondToOrder(Order* order) {
        //acceptedOrders[count-1]=order;
    }
void Volunteer::deliverOrder(Order* order) {
        //acceptedOrder[count-1]=order;
        //ReadOrders();
    }
    //getReward(g &reward){

    //}
    //operators overloading
    //friend 

