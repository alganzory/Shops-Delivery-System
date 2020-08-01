#pragma once
#include <string>

/**
 * \brief This class can be expanded to use coordinates
 *		  and hence use path filtering mechanisms.
 */
class Location
{
	/// Members
private:
	std::string address;
	std::pair<int, int> geoLocation;

public:
	/// Constructors
	Location(); 
	Location(std::string address);
	Location(std::pair <int, int> coordinates);
	
	/// Getters
	std::string getAddress() const;
	
	std::pair<int, int> getGeoLocation() const; 

	/// Setters
	void setAddress(std::string address);
	void setGeoLocation(int longitude, int latitude);
};
