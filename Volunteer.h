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
    std::vector<bool> registeredShops; // this array is like a map between shop index and registration status
    std::vector<std::shared_ptr<Order>> acceptedOrders;
    std::vector<double> rewards;

public:
    Volunteer();
    Volunteer(std::string username, std::string password);
    void setTransport(std::string& transport);
    void setAvailableTimes(std::pair<int, int> availableTimes);
    std::pair <Time, Time> getAvailableTimes() const;
    std::string getTransport() const;
    void setInfo(std::string name, int age, double balance, Location location);
    bool isAvailable(Time time);
    void registerToShop(int shopIdx);
    void respondToOrder(std::shared_ptr<Order> acceptedOrders, bool accept);
    void deliverOrder(std::shared_ptr<Order> acceptedOrders);
    void getReward(double reward);
    void welcome() override;
    void display();

    friend class O_List;
    //operators overloading
    //friend
    friend class VolunteerFlow;
    friend class V_List;
};

#endif

