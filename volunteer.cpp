#include<iostream>
#include"volunteer.h"


Volunteer::Volunteer(string username, string password) :User(username, password) {

}

void Volunteer::setTransport(std::string& transport) {
    transportation = transport;
    cout << "What is your transportation? ";
    getline(std::cin, transport);
}

void Volunteer::setAvailableTimes() {
    int start, end;
    cout << "Please enter your available times: ";
    cin >> start >> end;
    availableTimes = make_pair(start, end);
}

string Volunteer::getTransport() const {
    return transportation;
}

void Volunteer::setInfo(string name, int age, double balance, Location location) {
    this->name = name;
    this->age = age;
    this->balance = balance;
    this->location = location;

}

bool Volunteer::isAvailable(int time) {
    bool available = true;
    if (time > availableTimes.first && time < availableTimes.second) {
        return available;
    }
}

void Volunteer::registerToShop(std::shared_ptr<Shops> registeredShops) {
    registeredShops.push_back(shop);
}

void Volunteer::respondToOrder(std::shared_ptr<Order> acceptedOrders, bool accept) {
    if (accept = 1) {
        acceptedOrders.push_back(order);                                                                        //if accept will add into acceptedOrders
        ordersToBeAccepted.erase(std::find(ordersToBeAccepted.begin(), ordersToBeAccepted.end(), order);        //then delete from list of orders to be accepted
    }
}

void Volunteer::deliverOrder(std::shared_ptr<Order> acceptedOrders) {
    acceptedOrders.push_back(order);
    order.erase(std::find(order.begin(), order.end(), order);
}

double Volunteer::getReward(std::vector<double> rewards) {
    return rewards;
}
//refer to order class do we need to add delivery status?
//operators overloading
//friend 

