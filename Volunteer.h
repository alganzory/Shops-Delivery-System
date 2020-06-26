#ifndef Volunteer_H
#define Volunteer_H

#include "User.h"

class Volunteer :
    public User,
    public std::enable_shared_from_this <Volunteer> // to enable getting a shared_ptr using this ptr
{
    /// Members
private:
	
    std::string transportation;
    std::pair<Time, Time> availableTimes;
    /**
     * \brief: the list of boolean representing
     *          whether the shop is registered 
     */
    std::vector<bool> registeredShops; 

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
    /**
     * \brief : set the start time and end time that the 
     *           volunteer available
     * \param availableTimes : the start hour and the end hour
     */
    void setAvailableTimes(std::pair<int, int> availableTimes);


    /// Methods
    void setInfo(std::string name, int age, double balance, Location location);
    /** 
     * \brief : set the registered shop of the index
     *          when volunteer registered to the shop
     * \param shopIdx : the index representing the shop
     */
    void registerToShop(int shopIdx);
    /**
     * \brief : to deliver the order to customer
     * \param order : ongoing order
     */
    void handoverOrder(std::shared_ptr<Order>& order); 
    void getReward(double reward);
    /**
     * \brief : function override from
     *          User class to 
     *          welcome and as menu
     */
    void welcome() override;
    void display();

    /// Friend Classes
    friend class O_List;
    friend class VolunteerFlow;
    friend class V_List;
};

#endif

