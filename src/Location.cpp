#include "../include/Location.h"

/// Constructors
Location::Location()
{
}

Location::Location(std::string address)
{
	this->address=address;
}

Location::Location(std::pair<int, int> coordinates)
{
	this->geoLocation = coordinates;
}

/// Getters
std::string Location::getAddress() const
{
	return address;
}
std::pair<int,int> Location::getGeoLocation() const
{
	return geoLocation;
}

/// Setters
void Location::setAddress(std::string address)
{
	this->address=address;
}
void Location::setGeoLocation(int longitude,int latitude)
{
	geoLocation= std::make_pair(longitude,latitude);
}		

