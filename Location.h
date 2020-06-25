#pragma once
#include <string>

class Location
{
	/// Members
private:
	std::string address;
	std::pair<int, int> geoLocation;

public:
	/// Constructors
	Location(); // Default constructor will be needed
	Location(std::string address);

	/// Getters
	std::string getAddress() const;
	//useless
	std::pair<int, int> getGeoLocation() const;

	/// Setters
	//useless
	void setAddress(std::string address);
	//useless
	void setGeoLocation(int longitude, int latitude);
};
