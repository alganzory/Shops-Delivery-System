#include<iostream>
//#include<>

using namespace std;

class Volunteer : public User {
private:
    string transportation;
    pair<int hour, int min> availableTimes;
    Shop* registeredShops[];
    Order* acceptedOrders[];
    double rewards[];
public:
    Volunteer(string usernamev, string passwordv) :User(usernamev, passwordv) {
        username = usernamev;
        password = passwordv;
    }
    void setTransport(string& transport) {
        transportation = transport;
    }
    /*void setrewards(double& rewards[]) {

    }*/
    string gettransport() {
        return transportation;
    }
    void setInfo(string namev, int agev, double balancev, Location locationv) {
        name = namev;
        
        age = agev;
        
        balance = balancev;
        
        location = locationv;
        
    }
    bool IsAvailable(int hr,int m) {
        bool status = true;
        availableTimes = make_pair(hr, m);
        //if 
        return status;
    }
    void registerToShop(Shop* shop) {
        shops = new Shop registeredShops[];
    }
    void respondToOrder(Order* order) {
        //acceptedOrders[count-1]=order;
    }
    void deliverOrder(Order* order) {
        //acceptedOrder[count-1]=order;
        //ReadOrders();
    }
    //getReward(g &reward){

    //}
    //operators overloading
    //friend 

};
