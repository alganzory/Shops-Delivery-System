#pragma once
#include <windows.h>
#include <iostream>

class Time
{
	/// Members
private:
	int hour;
	int minute;

public:
	static SYSTEMTIME lt;
	static int localHour;
	static int localMinute;

public:
	/// Constructors
	Time();
	Time(int hr, int m);

	/// Getters
	int getHour();
	int getMinute();
	//useless
	std::pair<int, int> getTime();
	std::pair<int, int> getTimeDiff();

	/// Setters
	void setTime(int, int);
	static void calcLocalTime();

	/// Operator
	friend bool operator >(const Time& lhs, const Time& rhs);
	friend bool operator <(const Time& lhs, const Time& rhs);
	bool operator ==(const Time& rhs);
	friend std::ostream& operator <<(std::ostream& output, Time time);
};
