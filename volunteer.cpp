#include<iostream>
#include<string>
#include"volunteer.h"
#include<vector>


Volunteer::Volunteer(std::string username, std::string password) :User(username, password) {

}

void Volunteer::setTransport(std::string& transport) {
    transportation = transport;
    std::cout << "What is your transportation? ";
    getline(std::cin, transport);
}

void Volunteer::setAvailableTimes() {
    int start, end;
    std::cout << "Please enter your available times: ";
    std::cin >> start >> end;
    availableTimes = std::make_pair(start, end);
}

std::string Volunteer::getTransport() const {
    return transportation;
}

void Volunteer::setInfo(std::string name, int age, double balance, Location location) {
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

void Volunteer::registerToShop(std::vector<std::shared_ptr<Shop>> registeredShops) {
    registeredShops.push_back(shop);
}

void Volunteer::respondToOrder(std::vector<std::shared_ptr<Order>> acceptedOrders, bool accept) {
    if (accept = 1) {
        acceptedOrders.push_back(order);  //if accept will add into acceptedOrders
        orderList.erase(std::find(orderList.begin(), orderList.end(), order);        //then delete from list of orders to be accepted
    }
}

void Volunteer::deliverOrder(std::vector<std::shared_ptr<Order>> acceptedOrders) {
    acceptedOrders.push_back(order);
    order.erase(std::find(order.begin(), order.end(), order));
    order.setDeliveryStatus(true);

}

std::vector<double> Volunteer::getReward(std::vector<double> rewards) {
    return rewards;
}


//operators overloading
//friend 

