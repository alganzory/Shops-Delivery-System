#ifndef volunteer_H
#define volunteer_H

//#include"order.h"
//#include"order.cpp"
#include<vector>

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
    void setAvailableTimes();
    std::string getTransport() const;
    void setInfo(std::string name, int age, double balance, Location location);
    bool isAvailable(int time);
    void registerToShop(std::vector<std::shared_ptr<Shop>> registeredShops);
    void respondToOrder(std::vector<std::shared_ptr<Order>> acceptedOrders, bool accept);
    void deliverOrder(std::vector<std::shared_ptr<Order>> acceptedOrders);
    std::vector<double> getReward(std::vector<double> rewards);


    //operators overloading
    //friend 
};

#endif

