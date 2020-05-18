#include<iostream>
#include<string>
#include"volunteer.h"
#include"Shop.h"
#include"User.h"
#include"Location.h"

#include<vector>

Volunteer::Volunteer(std::string username, std::string password) :User(username, password) {
}

void Volunteer::setTransport(std::string& transport) {
    transportation = transport;
}

void Volunteer::setAvailableTimes(std::pair <int, int>availableTimes) {
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

    std::cout << "What is your transportation? ";
    getline(std::cin, transportation);
    setTransport(transportation);

}

bool Volunteer::isAvailable(int time) {
    bool available = true;
    if (time > availableTimes.first && time < availableTimes.second) {
        return available;
    }
}

void Volunteer::registerToShop(std::shared_ptr<Shop> newShop) {
    registeredShops.push_back(newShop);
}

void Volunteer::respondToOrder(std::shared_ptr<Order> order, bool accept) {
    if (accept == 1) {
        acceptedOrders.push_back(order);  //if accept will add into acceptedOrders
        orders.erase(std::find(orders.begin(), orders.end(), order));        //then delete from list of orders of user
    }
}

void Volunteer::deliverOrder(std::shared_ptr<Order> order) {
    acceptedOrders.erase(std::find(acceptedOrders.begin(), acceptedOrders.end(), order));
    bool doneDeliver = true;
    order->setDeliveryStatus(doneDeliver);
}

void Volunteer::getReward(double reward) {
    balance += reward;
}


//operators overloading
//friend 
