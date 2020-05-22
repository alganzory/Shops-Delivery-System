#include "Location.h"

Location::Location()
{
}

Location::Location(std::string address)
{
	this->address=address;
}
std::string Location::getAddress() const
{
	return address;
}
std::pair<int,int> Location::getGeoLocation() const
{
	return geoLocation;
}
void Location::setAddress(std::string address)
{
	this->address=address;
}
void Location::setGeoLocation(int longitude,int latitude)
{
	geoLocation= std::make_pair(longitude,latitude);
}		

