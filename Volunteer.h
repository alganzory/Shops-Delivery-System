#ifndef Volunteer_H
#define Volunteer_H

#include "User.h"

class Volunteer :
    public User,
    public std::enable_shared_from_this <Volunteer>
{
private:
    std::string transportation;
    std::pair<Time, Time> availableTimes;
    std::vector<std::shared_ptr<Shop>> registeredShops;
    std::vector<std::shared_ptr<Order>> acceptedOrders;
    std::vector<double> rewards;

public:
    Volunteer(std::string username, std::string password);
    void setTransport(std::string& transport);
    void setAvailableTimes(std::pair<int, int> availableTimes);
    std::string getTransport() const;
    void setInfo(std::string name, int age, double balance, Location location);
    bool isAvailable(Time time);
    void registerToShop(std::shared_ptr<Shop> newShop);
    void respondToOrder(std::shared_ptr<Order> acceptedOrders, bool accept);
    void deliverOrder(std::shared_ptr<Order> acceptedOrders);
    void getReward(double reward);
    void welcome() override;
    void display();

    friend class O_List;
    //operators overloading
    //friend
    friend class VolunteerFlow;
};

#endif

