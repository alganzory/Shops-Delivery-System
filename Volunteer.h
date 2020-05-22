#ifndef Volunteer_H
#define Volunteer_H

#include "User.h"

class Volunteer : public User {
private:
    std::string transportation;
    std::pair<int, int> availableTimes;
    std::vector<std::shared_ptr<Shop>> registeredShops;
    std::vector<std::shared_ptr<Order>> acceptedOrders;
    std::vector<double> rewards;

public:
    Volunteer(std::string username, std::string password);
    void setTransport(std::string& transport);
    void setAvailableTimes(std::pair<int, int> availableTimes);
    std::string getTransport() const;
    void setInfo(std::string name, int age, double balance, Location location);
    bool isAvailable(int time);
    void registerToShop(std::shared_ptr<Shop> newShop);
    void respondToOrder(std::shared_ptr<Order> acceptedOrders, bool accept);
    void deliverOrder(std::shared_ptr<Order> acceptedOrders);
    void getReward(double reward);


    //operators overloading
    //friend 
};

#endif

