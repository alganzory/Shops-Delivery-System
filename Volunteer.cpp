
#include"Volunteer.h"

#include <iomanip>
#include<memory>
#include "Helper.h"


#include "SH_List.h"
#include "VolunteerFlow.h"
/// Constructors
Volunteer::Volunteer()
{
}

Volunteer::Volunteer(std::string username, std::string password) :User(username, password) {
    registeredShops.resize(SH_List::getCount());
}

/// Getters
std::pair<Time, Time> Volunteer::getAvailableTimes() const
{
    return availableTimes;
}
std::string Volunteer::getTransport() const {
    return transportation;
}
bool Volunteer::isAvailable(Time time) {
	const bool available = true;
    if (time > availableTimes.first && time < availableTimes.second) {
        return available;
    }
    else return !available;
}


/// Setters
void Volunteer::setTransport(std::string& transport) {
    transportation = transport;
}

void Volunteer::setAvailableTimes(std::pair <int, int>availableTimes) {
    this->availableTimes = {  Time(availableTimes.first, 0), Time(availableTimes.second, 0) };
}

/// Methods
void Volunteer::setInfo(std::string name, int age, double balance, Location location) {
    this->name = name;
    this->age = age;
    this->balance = balance;
    this->location = location;

    std::cout << "What is your transportation? ";
    getline(std::cin, transportation);
    setTransport(transportation);

    std::cout << "When are you available?\n"
        << "Start hour: ";
    int startHour = Helper::readChoice(0, 23);
    std::cout << "End hour: ";
    int endHour = Helper::readChoice(startHour, 24);

    setAvailableTimes({ startHour,endHour });

}

void Volunteer::registerToShop(int shopIdx) {
    registeredShops[shopIdx] = true;
}

void Volunteer::handoverOrder(std::shared_ptr<Order>& order)
{
	order->setDeliveryStatus(true);
	order->setStatus(Order::Complete);
	
}

void Volunteer::getReward(double reward) {
    balance += reward;
}

void Volunteer::welcome()
{
    VolunteerFlow::currentVolunteer = shared_from_this();
    VolunteerFlow::mainMenu();
}

void Volunteer::display()
{
    std::cout << std::setw(20) << name
        << std::setw(26) << location.getAddress()
        << availableTimes.first << " - " 
        << availableTimes.second
        << "\n";
}


//operators overloading
//friend 
