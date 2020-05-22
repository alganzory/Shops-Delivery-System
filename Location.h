#pragma once
#include <string>

class Location
{
	private:
		std::string address;
		std::pair<int,int> geoLocation;
	public:
		Location (); // Default constructor will be needed
		Location(std::string address);
		std::string getAddress() const;
		std::pair<int,int> getGeoLocation () const;
		void setAddress(std::string address);
		void setGeoLocation(int longitude,int latitude)	;	
};
