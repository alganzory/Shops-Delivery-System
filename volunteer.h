#ifndef volunteer_H
#define volunteer_H

#include"User.h"

class Volunteer : public User {
private:
    string transportation;
    pair<int hour, int min> availableTimes;
    Shop* registeredShops[];
    Order* acceptedOrders[];
    double rewards[];
public:
    Volunteer(string usernamev, string passwordv) :User(usernamev, passwordv);
    void setTransport(string& transport);
    void setrewards(double& rewards[]);
    string gettransport();
    void setInfo(string namev, int agev, double balancev, Location locationv);
    bool IsAvailable(int hr,int m);
    void registerToShop(Shop* shop);
    void respondToOrder(Order* order);
    void deliverOrder(Order* order);
    //getReward(g &reward);
    //operators overloading
    //friend 

};

#endif
