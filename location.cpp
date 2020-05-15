#include "location.h"

Location::Location(string _address)
{
	address=_address;
}
Location::string getAddress() const
{
	return address;
}
Location::pair<int,int> getGeoLocation const
{
	return geoLocation;
}
Location::void setAddress(string _address)
{
	address=_address;
}
Location::void setGeoLocation(int longitude,int latitude)
{
	geoLocation=make_pair(longitude,latitude);
}		

