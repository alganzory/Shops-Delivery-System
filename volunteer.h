#ifndef volunteer_H
#define volunteer_H

#include"User.h"
#include<vector>

class Volunteer : public User {
private:
    string transportation;
    pair<int, int> availableTimes;

    std::vector<std::shared_ptr<Shop>> registeredShops;

    std::vector<std::shared_ptr<Order>> acceptedOrders;

    std::vector<double> rewards;

public:
    Volunteer(string usernamev, string passwordv);
    void setTransport(string& transport);
    void setAvailableTimes();
    string getTransport() const;
    void setInfo(string name, int age, double balance, Location location);
    bool isAvailable(int time);
    void registerToShop(std::shared_ptr<Shops> registeredShops);
    void respondToOrder(std::shared_ptr<Order> acceptedOrders, bool accept);
    void deliverOrder(std::shared_ptr<Order> acceptedOrders);
    double getReward(std::vector<double> rewards);
    //refer to order class do we need to add delivery status?
    //operators overloading
    //friend 
};

#endif

