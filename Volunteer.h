#ifndef Volunteer_H
#define Volunteer_H

#include "User.h"

class Volunteer :
    public User,
    public std::enable_shared_from_this <Volunteer>
{
    /// Members
private:
    std::string transportation;
    std::pair<Time, Time> availableTimes;
    std::vector<bool> registeredShops; // this array is like a map between shop index and registration status
    std::vector<std::shared_ptr<Order>> acceptedOrders;
    std::vector<double> rewards; //useless

public:
    /// Constructors
    Volunteer();
    Volunteer(std::string username, std::string password);

    /// Getters
    std::pair <Time, Time> getAvailableTimes() const;
    std::string getTransport() const;
    bool isAvailable(Time time);

    /// Setters
    void setTransport(std::string& transport);
    void setAvailableTimes(std::pair<int, int> availableTimes);


    /// Methods
    void setInfo(std::string name, int age, double balance, Location location);
    void registerToShop(int shopIdx);
    void respondToOrder(std::shared_ptr<Order> acceptedOrders, bool accept); //useless
    void deliverOrder(std::shared_ptr<Order> acceptedOrders); //useless
    void getReward(double reward);
    void welcome() override;
    void display();

    /// Friend Classes
    friend class O_List;
    friend class VolunteerFlow;
    friend class V_List;
};

#endif

