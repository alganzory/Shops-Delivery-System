#include "Time.h"
#include <iomanip>
#include <string>

SYSTEMTIME Time::lt;
int Time::localHour = lt.wHour;
int Time::localMinute = lt.wMinute;

/// constructors
Time::Time()
{
	hour = 0;
	minute = 0;
}

Time::Time(int hr, int m)
{
	hour = hr;
	minute = m;
}

/// Getters
int Time::getHour()
{
	return hour;
}

int Time::getMinute()
{
	return minute;
}

std::pair<int, int> Time::getTime()
{
	return {hour, minute};
}

std::pair<int, int> Time::getTimeDiff()
{
	calcLocalTime();
	int minDiff = (hour - localHour) * 60 + minute - localMinute;
	int hourDiff = abs(minDiff / 60);
	minDiff %= 60;
	//if minDiff is -ve means the time is overdue.
	return {hourDiff, minDiff};
}


/// Setters
void Time::setTime(int hr, int m)
{
	calcLocalTime();
	if (hr < 0 || hr > 24 || m < 0 || m > 60)
	{
		throw "Invalid time input, make sure it's in 24-hour format...";
	}
	/*if (hr == localHour && m-localHour < 30)
	{
		throw "The time should be at least 30 mins after now.";
	}
	if (hr<localHour)
	{
		throw "The time has passed. Please enter the time 30 mins after now.";
	}*/
	hour = hr;
	minute = m;
}

void Time::calcLocalTime()
{
	GetLocalTime(&lt);
	Time::localHour = lt.wHour;
	Time::localMinute = lt.wMinute;
}


/// Operators
bool Time::operator==(const Time& rhs)
{
	return (hour == rhs.hour && minute == rhs.minute);
}

bool operator >(const Time& lhs, const Time& rhs)
{
	if (lhs.hour == rhs.hour)
	{
		return (lhs.minute > rhs.minute);
	}
	else
	{
		return lhs.hour > rhs.hour;
	}
}

bool operator <(const Time& lhs, const Time& rhs)
{
	if (lhs.hour == rhs.hour)
	{
		return lhs.minute < rhs.minute;
	}
	else
	{
		return lhs.hour < rhs.hour;
	}
}

std::ostream& operator <<(std::ostream& out, Time time)
{
	std::string output = "";
	if (time.getHour() < 10)
	{
		output += "0";
	}
	output += std::to_string(time.getHour()) + ":";
	if (time.getMinute() < 10)
	{
		output += "0";
	}
	output += std::to_string(time.getMinute());
	out << output;
	return out;
}
