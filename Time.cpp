#include "Time.h"
#include <iomanip>

SYSTEMTIME Time::lt;
int Time::localHour = lt.wHour;
int Time::localMinute  = lt.wMinute;

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

void Time::setTime(int hr, int m)
{
	if (hr < 0 || hr>24 || m < 0 || m>60)
	{
		throw "Invalid time.";
	}
	hour = hr;
	minute = m;
}

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
	return std::pair<int, int>(hour, minute);
}

// if order time has passed the real time or not 



std::pair<int, int> Time::getTimeDiff()
{
	GetLocalTime(&lt);
	int minDiff = (hour - localHour) * 60 + minute - localMinute;
	int hourDiff = abs(minDiff / 60);
	minDiff %= 60;
	//if minDiff is -ve means the time is overdue.
	return std::pair<int, int>(hourDiff, minDiff);
}

bool operator > (const Time& lhs,const Time& rhs){
	if (lhs.hour == rhs.hour)
	{
		return ( lhs.minute > rhs.minute);
	}
	else
	{
		return lhs.hour > rhs.hour;
	}
}

bool operator < (const Time& lhs, const Time& rhs)
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
	if (time.getHour() < 10)
	{
		out << "0";
	}
	out << time.getHour() << ":";
	if (time.getMinute() < 10)
	{
		out << "0";
	}
	out<< time.getMinute();
	return out;
}