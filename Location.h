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
		//useless
		std::pair<int,int> getGeoLocation () const;
		//useless
		void setAddress(std::string address);
		//useless
		void setGeoLocation(int longitude,int latitude)	;	
};
