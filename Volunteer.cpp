
#include"Volunteer.h"

#include <iomanip>
#include<memory>

#include "VolunteerFlow.h"

Volunteer::Volunteer(std::string username, std::string password) :User(username, password) {
}

void Volunteer::setTransport(std::string& transport) {
    transportation = transport;
}

void Volunteer::setAvailableTimes(std::pair <int, int>availableTimes) {
    this->availableTimes = std::pair < Time,Time>(Time(availableTimes.first, 0), Time(availableTimes.second, 0));
}

std::string Volunteer::getTransport() const {
    return transportation;
}

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
    int startHour;
    std::cin >> startHour;
    std::cout << "End hour: ";
    int endHour;
    std::cin >> endHour;
    std::cin.ignore();

    setAvailableTimes({ startHour,endHour });

}

bool Volunteer::isAvailable(Time time) {
    bool available = true;
    if (time > availableTimes.first && time < availableTimes.second) {
        return available;
    }
}

void Volunteer::registerToShop(std::shared_ptr<Shop> newShop) {
    registeredShops.push_back(newShop);
}
void Volunteer::respondToOrder(std::shared_ptr<Order> order, bool acceptance)
{
	if (acceptance == true)
	{
		acceptedOrders.push_back(order);
		const auto orderPos = find(orders.begin(), orders.end(), order);
		orders.erase(orderPos);
	}
}

void Volunteer::deliverOrder(std::shared_ptr<Order> order)
{
	order->setDeliveryStatus(true);
	const auto orderPos = find(acceptedOrders.begin(), acceptedOrders.end(), order);
	acceptedOrders.erase(orderPos);
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
